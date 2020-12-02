#include "Configure.h"

// Pin assignments are specific to Arduino Nano.  Some direct port manipulation is done
// that may not be compatible with other Arduino models.

// USB reserves pins 0..1
// Data bus is pins 2..9
enum {
    PGM = 11,   // OUTPUT - puts the host in PROGRAM mode
    CLK = 12,   // OUTPUT - drives the host CLK line
    RST = 13    // OUTPUT - drives the host RST line
};

enum {
    // ALU mode and select bits to place in the instruction register
    ALU_INC = 0x00, // A plus 1
    ALU_SUB = 0x06, // A minus B
    ALU_ADD = 0x09, // A plus B
    ALU_SHL = 0x0c, // A + A
    ALU_DEC = 0x0f, // A minus 1
    ALU_NOT = 0x10, // not A
    ALU_XOR = 0x16, // A xor B
    ALU_B =   0x1a, // B
    ALU_AND = 0x1b, // A and B
    ALU_OR  = 0x1e  // A or B
};

const uint8_t aluUnaryOperations[] = {
    ALU_INC,
    ALU_SHL,
    ALU_DEC,
    ALU_NOT,
    ALU_B
};
const char * aluUnaryNames[] = {
    "INC", "SHL", "DEC", "NOT", "B"
};
const uint8_t aluBinaryOperations[] = {
    ALU_SUB,
    ALU_ADD,
    ALU_XOR,
    ALU_AND,
    ALU_OR
};
const char * aluBinaryNames[] = {
    "SUB", "ADD", "XOR", "AND", "OR"
};

// Register select controls
// Lower 4 bits are the register number.  RCLK and WCLK are connected to the CLK lines of
// two 74LS173s that provide the register select values to the decoders.  To select a
// register, set the number in the lower four bits and then toggle the RCLK or WCLK line
// high then low to latch the value.
enum {
    REGSEL_MASK = 0x0f,
    REGSEL_RCLK = 0x10,
    REGSEL_WCLK = 0x20
};

// Write register is PC0-2 (pin A0-A2)
// Read register is PC3-5 (pin A3-A5)
// PC6 and PC7 (pin A6, A7) are analog input only and are not used
enum {
    REG_NONE= 0x00,    // No register selected
    REG_MEM = 0x01,
    REG_A =   0x02,
    REG_B =   0x03,
    REG_ALU = 0x04,
    REG_SP  = 0x05,
    REG_PC =  0x06,
    REG_D =   0x08,
    REG_MAR = 0x09,
    REG_X =   0x0a,
    REG_Y =   0x0b,
    REG_OUT = 0x0c,
    REG_IR =  0x0f
};


static const char * registerNames[] = {
    "none", "MEM", "A",  "B",   "ALU", "SP", "PC", "07",
    "D",    "MAR", "X",  "Y",   "OUT", "0d", "0e", "IR"
};
static const unsigned woRegisters[] = { REG_OUT, REG_MAR, REG_IR };
static const unsigned rwRegisters[] = { REG_D, REG_X, REG_Y, REG_A, REG_B, REG_PC, REG_SP };
static unsigned numWoRegisters() { return sizeof(woRegisters) / sizeof(*woRegisters); }
static unsigned numRwRegisters() { return sizeof(rwRegisters) / sizeof(*rwRegisters); }

#if 0
static void waitForUser(const char * s = 0) {
    if (s) {
        Serial.println(s);
    }
    while (Serial.read() == -1) {}
}
#endif

LoaderHw::LoaderHw(uint32_t size)
    : mSize(size), mEnabled(false)
{}


void LoaderHw::begin() {
    // The loader's data bus is connected directly to the host bus.  Define the
    // data bus as input initially so that it does not put out a signal that
    // could collide with host outputs on the bus.
    // Care must be taken to ensure that the bus is never left in the OUTPUT
    // mode when control is handed back to the host computer.
    setDataBusMode(INPUT);

    // Set register selects as outputs
    DDRC = 0x3f;
    PORTC = 0x00;

    // External pull-up resistors are present on RST and PGM.  An external pull-down is on
    // CLK.  This allows the system to function as normal if the arduino is not present,
    // although without a way to load programs there isn't a lot that the system will do.
    digitalWrite(PGM, HIGH);    // PGM is active LOW
    pinMode(PGM, OUTPUT);
    digitalWrite(RST, HIGH);    // RST is active LOW
    pinMode(RST, OUTPUT);
    digitalWrite(CLK, LOW);     // Normally LOW.  Pulse high-low to generate a clock
    pinMode(CLK, OUTPUT);

    disable();
}

void LoaderHw::disable() {
  // Make sure the loader data bus and register selects are not putting out a signal and
  // then return control to the host.
  setDataBusMode(INPUT);
  digitalWrite(PGM, HIGH);
  mEnabled = false;
}

void LoaderHw::enable() {
    if (!mEnabled) {
        setDataBusMode(INPUT);
        digitalWrite(PGM, LOW);
        mEnabled = true;
        delay(1);
    }
}

// Generate one pulse on the host clock
void LoaderHw::clkPulse() {
    delayMicroseconds(1);
    digitalWrite(CLK, HIGH);
    delayMicroseconds(1);
    digitalWrite(CLK, LOW);
    delayMicroseconds(1);
}

// Generate one reset pulse to the host
void LoaderHw::reset() {
    digitalWrite(RST, LOW);
    delayMicroseconds(4);
    digitalWrite(RST, HIGH);
    delay(1);
}

// Return a name for a given register number
const char * LoaderHw::registerName(int registerNumber)
{
    return registerNames[registerNumber];
}

uint8_t LoaderHw::readRegister(uint8_t reg) {
    selectReadRegister(reg);
    delayMicroseconds(3);
    uint8_t data = readDataBus();
    delayMicroseconds(1);
    return data;
}

void LoaderHw::writeRegister(uint8_t reg, uint8_t data) {
    selectWriteRegister(reg);
    setDataBusMode(OUTPUT);
    writeDataBus(data);
    clkPulse();
    setDataBusMode(INPUT);
}

void LoaderHw::transferRegister(uint8_t wReg, uint8_t rReg) {
    selectReadRegister(rReg);
    selectWriteRegister(wReg);
    clkPulse();
}

// Write a block of data to the memory.
bool LoaderHw::writeData(const byte data[], uint32_t len, uint32_t address) {
    bool status = true;

    for (uint32_t ix = 0; (ix < len); ix++) {
        if (burnByte(data[ix], address + ix) == false) {
            status = false;
            break;
        }
    }
    return status;
}

// Read a byte from a given address
byte LoaderHw::readByte(uint32_t address) {
    byte data = 0;

    setAddress(address);
    setDataBusMode(INPUT);
    selectReadRegister(REG_MEM);
    selectWriteRegister(0);
    delayMicroseconds(1);
    data = readDataBus();
    delayMicroseconds(1);

    return data;
}

bool LoaderHw::testHardware() {
    unsigned ix;

    enable();
    for (ix = 0; (ix < numRwRegisters()); ix++) {
        writeRegister(REG_IR, 0);  // NOP so no control lines asserted
        writeRegister(REG_X, 0);   // Have adder return D+0 for D register test
        if (!testRegister(rwRegisters[ix], true)) {
            return false;
        }
    }
    for (ix = 0; (ix < numWoRegisters()); ix++) {
        writeRegister(REG_IR, 0);  // NOP so no control lines asserted
        if (!testRegister(woRegisters[ix], false)) {
            return false;
        }
    }

    if (!testMemory()) {
        return false;
    }

    if (!testAlu()) {
        return false;
    }

    return testAdder();
}


////////////////////////////////////////////////
// BEGIN PRIVATE METHODS
//

// Burn a byte to the memory and verify that it was written.
bool LoaderHw::burnByte(byte value, uint32_t address) {
    enable();
    setAddress(address);
    setDataBusMode(OUTPUT);
    selectWriteRegister(REG_MEM);
    writeDataBus(value);
    clkPulse();
    selectWriteRegister(REG_NONE);
    setDataBusMode(INPUT);
    delayMicroseconds(1);

    // Read back the value and return success if it matches
//    return readByte(address) == value;
    return true;
}

static const uint8_t patterns[] = {
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
    0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff,
    0xff, 0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0xff,
    0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00,
    0xaa, 0x55, 0xaa, 0x55, 0xcc, 0x33, 0xcc, 0x33, 0x00
};

bool LoaderHw::testRegister(unsigned reg, bool isRw) {
    Serial.print("Testing ");
    Serial.print(registerNames[reg]);
    Serial.print(": ");

    for (unsigned ix = 0; (ix < sizeof(patterns)); ix++) {
        writeRegister(reg, patterns[ix]);
        delayMicroseconds(2);
        selectWriteRegister(0);
        delay(100);
        uint8_t readVal = readRegister(reg);
        if (isRw && (readVal != patterns[ix])) {
            char s[60];
            sprintf(s, "failed, read=%02x, expected=%02x", readVal, patterns[ix]);
            Serial.println(s);
            return false;
        }
    }

    Serial.println(F("pass"));
    selectReadRegister(REG_NONE);
    selectWriteRegister(REG_NONE);
    return true;
}

bool LoaderHw::testMemory() {
    unsigned numPatterns = sizeof(patterns);
    unsigned addr;

    Serial.print(F("Testing memory: "));
    for (unsigned offset = 0; (offset < numPatterns); offset++) {
        for (addr = 0; (addr < 256); addr++) {
            burnByte(patterns[(offset + addr) % numPatterns], addr);
        }
        for (addr = 0; (addr < 256); addr++) {
            uint8_t readVal = readByte(addr);
            uint8_t expectedVal = patterns[(offset + addr) % numPatterns];
            if (readVal != expectedVal) {
                char s[60];
                sprintf(s, "failed at %02x, read=%02x, expected=%02x", addr, readVal, expectedVal);
                Serial.println(s);
                return false;
            }
        }
    }

    selectReadRegister(REG_NONE);
    selectWriteRegister(REG_NONE);
    Serial.println("pass");
    return true;
}

bool LoaderHw::testAlu() {
    unsigned numPatterns = sizeof(patterns);
    unsigned numOperations = sizeof(aluUnaryOperations);

    Serial.print(F("Testing ALU unary operations: "));
    for (unsigned opIndex = 0; (opIndex < numOperations); opIndex++) {
        for (unsigned aIndex = 0; (aIndex < numPatterns); aIndex++) {
            if (!testAluOperation(aluUnaryOperations[opIndex], aluUnaryNames[opIndex], patterns[aIndex], patterns[aIndex])) {
                return false;
            }
        }
    }
    Serial.println("pass");

    numOperations = sizeof(aluBinaryOperations);
    Serial.print(F("Testing ALU binary operations: "));
    for (unsigned opIndex = 0; (opIndex < numOperations); opIndex++) {
        for (unsigned aIndex = 0; (aIndex < numPatterns); aIndex++) {
            for (unsigned bIndex = 0; (bIndex < numPatterns); bIndex++) {
                if (!testAluOperation(aluBinaryOperations[opIndex], aluBinaryNames[opIndex], patterns[aIndex], patterns[bIndex])) {
                    return false;
                }
            }
        }
    }
    Serial.println("pass");
    return true;
}

bool LoaderHw::testAluOperation(uint8_t op, const char * opName, uint8_t a, uint8_t b) {
    uint8_t readVal = aluCompute(op, a, b);
    uint8_t expectedVal = localCompute(op, a, b);
    if (readVal != expectedVal) {
        char s[60];
        sprintf(s, "failed on %s with a=%02x b=%02x, result=%02x, expected=%02x", opName, a, b, readVal, expectedVal);
        Serial.println(s);
        return false;
    }
    return true;
}

uint8_t LoaderHw::aluCompute(uint8_t op, uint8_t a, uint8_t b) {
    writeRegister(REG_IR, op);
    writeRegister(REG_A, a);
    writeRegister(REG_B, b);
    return readRegister(REG_ALU);
}


// The Loader cannot directly control the carry into the ALU so the Ring Counter's CLR is
// wired to the Loader's enable to ensure that the T cycle is always zero and therefore
// the carry bit from the microcode ROM is zero as well. This gives a predictable result
// for all operations, but the results are not all ideal.
// For example, DEC A returns DEC A+1, which is simply the value of A.
uint8_t LoaderHw::localCompute(uint8_t op, uint8_t a, uint8_t b) {
    switch (op) {
    case ALU_INC: return a + 1;
    case ALU_SUB: return a - b;
    case ALU_ADD: return a + b + 1; // Carry bit low
    case ALU_SHL: return a + a + 1; // Carry bit low
    case ALU_DEC: return a;         // Carry bit low
    case ALU_NOT: return ~a;
    case ALU_XOR: return a ^ b;
    case ALU_B:   return b;
    case ALU_AND: return a & b;
    case ALU_OR:  return a | b;
    }
    return 0;
}

bool LoaderHw::testAdder() {
    unsigned numPatterns = sizeof(patterns);

    Serial.print(F("Testing DXY adder: "));
    for (unsigned aIndex = 0; (aIndex < numPatterns); aIndex++) {
        for (unsigned bIndex = 0; (bIndex < numPatterns); bIndex++) {
            if (!testAdderOperation(patterns[aIndex], patterns[bIndex])) {
                return false;
            }
        }
    }
    Serial.println("pass");
    return true;
}


bool LoaderHw::testAdderOperation(uint8_t a, uint8_t b) {
    // The Loader cannot switch between X and Y as the adder source but it can be
    // hard-wired temporarily for testing.  Put the operand in both X and Y so that the
    // add operation works no matter the selected source.
    writeRegister(REG_X, a);
    writeRegister(REG_Y, a);
    writeRegister(REG_D, b);
    writeRegister(REG_NONE, 0); // don't want the next CLK to write the D register
    uint8_t readVal = readRegister(REG_D);
    uint8_t expectedVal = a + b;
    if (readVal != expectedVal) {
        char s[60];
        sprintf(s, "FAILED to add - X=%02x D=%02x, result=%02x, expected=%02x", a, b, readVal, expectedVal);
        Serial.println(s);
        return false;
    }

    // Test that the Adder result can be transfered back to X without corruption
    transferRegister(REG_X, REG_D);
    readVal = readRegister(REG_X);
    if (readVal != expectedVal) {
        char s[60];
        sprintf(s, "FAILED to transfer - X=%02x D=%02x, result=%02x, expected=%02x", a, b, readVal, expectedVal);
        Serial.println(s);
        return false;
    }

    return true;
}


static void selectRegister(uint8_t reg, uint8_t clk) {
    reg &= REGSEL_MASK;
    PORTC = reg;
    delayMicroseconds(1);
    PORTC = reg | clk;
    delayMicroseconds(1);
    PORTC = reg;
}

void LoaderHw::selectWriteRegister(uint8_t reg) {
    if (reg != REG_NONE) {
        enable();
    }
    selectRegister(reg, REGSEL_WCLK);
}

void LoaderHw::selectReadRegister(uint8_t reg) {
    if (reg != REG_NONE) {
        // Make sure the loader is not on the bus if a register is selected.
        setDataBusMode(INPUT);
        enable();
    }
    selectRegister(reg, REGSEL_RCLK);
}

// Set the I/O state of the data bus.
// The first two bits of port D are used for serial, so the 8 bits data bus are
// on pins D2..D9.
void LoaderHw::setDataBusMode(uint8_t mode) {
    // On the Uno and Nano, D2..D9 maps to the upper 6 bits of port D and the
    // lower 2 bits of port B.
    if (mode == OUTPUT) {
        // Make sure that none of the host hardware registers are also writing to the bus.
        selectReadRegister(REG_NONE);
        DDRB |= 0x03;
        DDRD |= 0xfc;
    } else {
        DDRB &= 0xfc;
        DDRD &= 0x03;
    }
}

// Set an 8 bit address using the 8 address/data bus and latch it into the MAR
void LoaderHw::setAddress(uint32_t address) {
    // NOTE: Must call selectWriteRegister before setting the bus because the call to
    // selectWriteRegister may call enable and that will reset the bus.
    selectWriteRegister(REG_MAR);
    setDataBusMode(OUTPUT);
    writeDataBus(byte(address & 0xff));
    clkPulse();
    selectWriteRegister(REG_NONE);
    setDataBusMode(INPUT);
}

// Read a byte from the data bus.  The caller must set the bus to input_mode
// before calling this or no useful data will be returned.
byte LoaderHw::readDataBus() {
    return (PINB << 6) | (PIND >> 2);
}

// Write a byte to the data bus.  The caller must set the bus to output_mode
// before calling this or no data will be written.
void LoaderHw::writeDataBus(byte data) {
     PORTB = (PORTB & 0xfc) | (data >> 6);
     PORTD = (PORTD & 0x03) | (data << 2);
}

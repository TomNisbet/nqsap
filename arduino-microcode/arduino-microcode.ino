#include "Arduino.h"

static const char * MY_VERSION = "1.0";

// IO lines for the EEPROM device control
// Pins D2..D9 are used for the data bus.
#define WE              A0
#define CE              A1
#define OE              A2
#define ADDR_CLK_HI     A3
#define ADDR_CLK_LO     A4
#define ADDR_DATA       A5

#define GREEN_LED       A7
#define RED_LED         13

void burnMicrocodeRoms();
void disableSoftwareWriteProtect();
byte readByte(uint32_t address);
bool burnByte(byte value, uint32_t address);
bool burnBlock(byte data[], uint32_t len, uint32_t address);
bool waitForWriteCycleEnd(byte lastValue);
void setByte(byte value, uint32_t address);
void setAddress(uint32_t address);
void setAddressRegister(uint8_t clkPin, byte addr);
bool writeData(byte data[], uint32_t len, uint32_t address);
void setDataBusMode(uint8_t mode);
byte readDataBus();
void writeDataBus(byte data);

// Set the status of the device control pins
static void enableChip()       { digitalWrite(CE, LOW); }
static void disableChip()      { digitalWrite(CE, HIGH);}
static void enableOutput()     { digitalWrite(OE, LOW); }
static void disableOutput()    { digitalWrite(OE, HIGH);}
static void enableWrite()      { digitalWrite(WE, LOW); }
static void disableWrite()     { digitalWrite(WE, HIGH);}


void setup() {
    // The address control pins are always outputs.
    pinMode(ADDR_DATA, OUTPUT);
    pinMode(ADDR_CLK_LO, OUTPUT);
    pinMode(ADDR_CLK_HI, OUTPUT);
    digitalWrite(ADDR_DATA, LOW);
    digitalWrite(ADDR_CLK_LO, LOW);
    digitalWrite(ADDR_CLK_HI, LOW);
    DDRB |= 0x1c; // Set D10..D12 as outputs

    // To save time, the setAddress only writes the hi byte if it has changed.
    // The value used to detect the change is initialized to a non-zero value,
    // so set an initial address to avoid the the case where the first address
    // written is the 'magic' initial address.
    setAddress(0x0000);

    // Define the data bus as input initially so that it does not put out a
    // signal that could collide with output on the data pins of the EEPROM.
    setDataBusMode(INPUT);

    // Define the EEPROM control pins as output, making sure they are all
    // in the disabled state.
    digitalWrite(OE, HIGH);
    pinMode(OE, OUTPUT);
    digitalWrite(CE, HIGH);
    pinMode(CE, OUTPUT);
    digitalWrite(WE, HIGH);
    pinMode(WE, OUTPUT);

    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    digitalWrite(GREEN_LED, LOW);

    Serial.begin(115200);

    burnMicrocodeRoms();
}

void loop() {
  digitalWrite(RED_LED, HIGH);
  delay(200);
  digitalWrite(RED_LED, LOW);
  delay(200);
}


//               ROM3    ROM2    ROM1    ROM0
//             +------++------++------++------+
// ROM3        WWWWxRRR765432107654321076543210
#define WM   0b00010000000000000000000000000000L  // 1 Write Memory
#define WA   0b00100000000000000000000000000000L  // 2 Write A
#define WB   0b00110000000000000000000000000000L  // 3 Write B (ALU operand)
#define WX4  0b01000000000000000000000000000000L  // 4
#define WX5  0b01010000000000000000000000000000L  // 5
#define WP   0b01100000000000000000000000000000L  // 6 Write PC (Jump)
#define WX7  0b01110000000000000000000000000000L  // 7
#define WX8  0b10000000000000000000000000000000L  // 8
#define WMA  0b10010000000000000000000000000000L  // 9 Write Memory Address
#define WXA  0b10100000000000000000000000000000L  // A
#define WXB  0b10110000000000000000000000000000L  // B
#define WO   0b11000000000000000000000000000000L  // C Write Output
#define WMD  0b11010000000000000000000000000000L  // D
#define WXE  0b11100000000000000000000000000000L  // E
#define WI   0b11110000000000000000000000000000L  // F Write IR
                                                  //
#define RM   0b00000001000000000000000000000000L  // 1 Read Memory
#define RA   0b00000010000000000000000000000000L  // 2 Read A
#define RB   0b00000011000000000000000000000000L  // 3 Read B (ALU result)
#define RX4  0b00000100000000000000000000000000L  // 4
#define RX5  0b00000101000000000000000000000000L  // 5
#define RP   0b00000110000000000000000000000000L  // 6 Read PC
#define RX7  0b00000111000000000000000000000000L  // 7

// ROM2
#define XX27 0b00000000100000000000000000000000L
#define XX26 0b00000000010000000000000000000000L
#define XX25 0b00000000001000000000000000000000L
#define XX24 0b00000000000100000000000000000000L
#define XX23 0b00000000000010000000000000000000L
#define XX22 0b00000000000001000000000000000000L
#define XX21 0b00000000000000100000000000000000L
#define XX20 0b00000000000000010000000000000000L

// ROM1
#define XX17 0b00000000000000001000000000000000L
#define XX16 0b00000000000000000100000000000000L
#define XX15 0b00000000000000000010000000000000L
#define XX14 0b00000000000000000001000000000000L
#define XX13 0b00000000000000000000100000000000L
#define XX12 0b00000000000000000000010000000000L
#define XX11 0b00000000000000000000001000000000L
#define XX10 0b00000000000000000000000100000000L

// ROM0
#define HLT  0b00000000000000000000000010000000L  // 80 Halt
#define IP   0b00000000000000000000000001000000L  // 40 Increment PC
#define CR   0b00000000000000000000000000100000L  // 20 Clear Ring Counter
#define AC   0b00000000000000000000000000010000L  // 10 ALU Carry Flag
#define XX03 0b00000000000000000000000000001000L
#define XX02 0b00000000000000000000000000000100L
#define XX01 0b00000000000000000000000000000010L
#define XX00 0b00000000000000000000000000000001L

#define N  CR           // Shorthand for start next instruction
#define RPI  RP | IP    // Shorthand for Read PC and post increment
#define F1  RPI | WMA   // Instruction fetch step 1
#define F2  RM | WI     // Instruction fetch step 2
#define FA  RPI | WMA   // Fetch argument (operand) step 1

enum {
    // Status flag bits.  These are based at the least significant bit position, not at
    // their position in the address word.  These values can be used when iterating
    // between zero and NUM_FLAG_COMBOS.
    SF_Z = 0x01,        // Zero
    SF_C = 0x02,        // Carry
};

// GGGGIIII - Instruction register opcode format, group and instruction bits
// GGGMSSSS - Mapping of ALU control bits to opcode bits
enum {
    // The Mode bit and the four Select bits of the ALU are connected directly to the
    // Instruction Register so that 5 additional microcode ROM bits are not consumed.
    //  This means that, other than the CARRY-IN bit, all ALU instructions have identical
    // microcode.
    //
    // The CARRY IN flag is not wired to the Instruction Register, so it is not encoded as
    // part of the instruction.  The ALU_CI is used to represent it in the ALU instruction
    // table so that it can be detected and used to set the AC bit in the full 32 bit
    // microinstruction.  Note that this bit must be outside of the 8 bits used for the
    // opcode.
    ALU_CI = 0b000100000000,
    ALU_B  = 0b001000000000,

    // The M bit is wired from the lowest group bit in the IR to the ALU.
    ALU_GROUP_MASK =    0b01110000,
    ALU_LOGIC =         0b00110000,
    ALU_ARITH =         0b00100000,

    ALU_M =             0b00010000,
    ALU_S3 =            0b00001000,
    ALU_S2 =            0b00000100,
    ALU_S1 =            0b00000010,
    ALU_S0 =            0b00000001
};

enum {
    // 00 - 0f   General
    IN_NOP = 0x00,
    IN_LDA = 0x01,
    IN_STA = 0x02,
    IN_LDB = 0x03,
    IN_JMP = 0x04,
    IN_JZ  = 0x05,
    IN_JC  = 0x06,
    IN_OUT = 0X07,
    IN_HLT = 0x0f,

    // 10 -1f  General

    // 30 - 3f   ALU Arithmetic
    IN_INC = ALU_ARITH,                                     // 20 - A plus 1
    IN_SUB = ALU_ARITH          | ALU_S2 | ALU_S1,          // 26 - A minus B
    IN_ADD = ALU_ARITH | ALU_S3                   | ALU_S0, // 29 - A plus B
    IN_SHL = ALU_ARITH | ALU_S3 | ALU_S2,                   // 2c - A + A
    IN_DEC = ALU_ARITH | ALU_S3 | ALU_S2 | ALU_S1 | ALU_S0, // 2f - A minus 1

    // 20 - 2f  ALU Logic
    IN_NOT = ALU_LOGIC,                                     // 30 - not A
    IN_XOR = ALU_LOGIC          | ALU_S2 | ALU_S1,          // 36 - A xor B
    IN_AND = ALU_LOGIC | ALU_S3          | ALU_S1 | ALU_S0, // 3b - A and B
    IN_OR  = ALU_LOGIC | ALU_S3 | ALU_S2 | ALU_S1           // 3e - A or B

    // 40 - ff unused
};

// This table contains the opcodes that are used for ALU instructions plus additional bits
// to indicate if a second operand is specified for the B register and if the AC flag
// should be set in the microcode steps for the instruction.  Many of the combinations of
// control bits in the ALU do not map to useful operations, so this is a small subset of
// the complete ALU operation set.
uint16_t aluInstructions[] = {
    // 20-2f   ALU Arithmetic
    IN_INC,                     // A + 1
    IN_SUB | ALU_B,             // A - B
    IN_ADD | ALU_B | ALU_CI,    // A + B
    IN_SHL         | ALU_CI,    // A + A (shift left)
    IN_DEC         | ALU_CI,    // A - 1

    // 30 - 3f  ALU Logic
    IN_NOT,                     // NOT A
    IN_XOR | ALU_B,             // A xor B
    IN_AND | ALU_B,             // A and B
    IN_OR  | ALU_B              // A or B
};


// ROM addressing 32K = 15 address bits
// rrffggg iiiiisss
// rr                4 ROM chips possible (32 bit microinstruction word)
//   ff              2 flag bits (could steal from G to add another)
//     gggg          16 groups of instructions
//         iiii      16 instructions per group = 256 possible instructions
//             sss   8 steps (max) per instruction
//
// NOTE that the instruction groups are an artificial construct used by this code.  The
// target machine has 256 possible instructions with 8 microinstructions steps each and a
// 32-bit wide control word broken up over 4 8-bit wide microcode ROMs.  The groups are a
// convention to break the instruction set into smaller pieces that can be processed in
// the limited RAM on the Arduino.  Also, the ALU instructions are generated in this code
// programmatically and the others are generated through tables.  The instruction
// groupings segment these to process them differently.
//
// To simplify microcode ROM burning and management, the microcode for all four chips is
// burned into every chip and the ROMs have the uppermost two address bits hardwired to
// determine which part of the microcode a chip is providing.  This means that all chips
// can be burned identically and that any chip can be installed in any slot.
//
// If the number of flag bits increases, the two ROM select bits could be reclaimed and
// each ROM could be burned uniquely instead.

enum {
    NUM_ROMS = 4,
    NUM_FLAG_COMBOS = 4,
    NUM_GROUPS = 16,
    NUM_INSTRUCTIONS = 16,  // instructions per group
    NUM_STEPS = 8,

    GROUP_MASK = 0xf0,
    INSTRUCTION_MASK = 0x0f,
    OPCODE_MASK = GROUP_MASK | INSTRUCTION_MASK
};

typedef uint32_t microcode_t;

const microcode_t template0[NUM_INSTRUCTIONS][NUM_STEPS] PROGMEM = {
//  0   1   2         3         4        5 6 7
  { F1, F2, 0,        0,        0,       0,0,0 }, // 00 NOP
  { F1, F2, FA,       RM|WA|N,  0,       0,0,0 }, // 01 LDA
  { F1, F2, FA,       RA|WM|N,  0,       0,0,0 }, // 02 STA
  { F1, F2, FA,       RM|WB|N,  0,       0,0,0 }, // 03 LDB - redundant
  { F1, F2, FA,       RM|WP|N,  0,       0,0,0 }, // 04 JMP
  { F1, F2, 0,        0,        0,       0,0,0 }, // 05 JZ
  { F1, F2, 0,        0,        0,       0,0,0 }, // 06 JC
  { F1, F2, RA|WO|N,  0,        0,       0,0,0 }, // 07 OUT
  { F1, F2, HLT,      0,        0,       0,0,0 }, // 08 HLT
  { F1, F2, HLT,      0,        0,       0,0,0 }, // 0a HLT
  { F1, F2, FA,       RM|WB,    RB|WA|N, 0,0,0 }, // 09 ADD
  { F1, F2, HLT,      0,        0,       0,0,0 }, // 0b HLT
  { F1, F2, HLT,      0,        0,       0,0,0 }, // 0c HLT
  { F1, F2, HLT,      0,        0,       0,0,0 }, // 0d HLT
  { F1, F2, HLT,      0,        0,       0,0,0 }, // 0e HLT
  { F1, F2, HLT,      0,        0,       0,0,0 }  // 0f HLT
};

// A buffer to hold a group of instruction microcode words that have been
// built from a template or from the ALU building code.
microcode_t code[NUM_INSTRUCTIONS][NUM_STEPS];

// A buffer to hold an 8-bit slice of a group of microinstruction words to burn into a
// section of ROM.  This buffer allows the use of the block write capability of the
// 28C256 chips, which results in a significant speed up of the ROM burn times.  The
// alternative without the buffers would be to step through the 32-bit words and burn
// them as 4 individual single-byte writes.
uint8_t burnBuffer[NUM_INSTRUCTIONS * NUM_STEPS];


// TODO: test code only!
microcode_t testCode[NUM_INSTRUCTIONS][NUM_STEPS];

// Convert the individual address components into a 15-bit address for the ROM.
uint16_t makeAddress(uint16_t rom, uint16_t flags=0, uint16_t groupBits=0, uint16_t instr=0, uint16_t step=0) {
    char b[50];
    uint16_t addr =  (rom << 13) | (flags << 11) | (groupBits << 3) | (instr << 3) | step;
    sprintf(b, "a=x%04x  r=%d f=%d g=x%02x i=%u s=%u", addr, rom, flags, groupBits, instr, step);
    Serial.println(b);
    return addr;
}

// Convert a group number (0..NUM_GROUPS) into the group bits portion of an opcode.
// Note that this is not the same position that the group bits occupy in a ROM address.
uint8_t makeGroupBits(uint8_t group) {
    return group << 4;
}

// Make an opcode from a group number and an instruction number.
// Group numbers are (0..NUM_GROUPS) and an instruction numbers are (0..NUM_INSTRUCTIONS)
uint8_t makeOpcode(uint8_t group, uint8_t instr) {
    return makeGroupBits(group) | instr;
}

void burnAluInstructions(uint8_t groupBits) {
    // Initialize the buffer with a HLT instruction.
    for (int i = 0; (i < NUM_INSTRUCTIONS); i++) {
        code[i][0] = F1;
        code[i][1] = F2;
        code[i][2] = HLT;
        code[i][3] = code[i][4] = code[i][5] = code[i][6] = code[i][7] = 0;
    }

    // Walk the ALU instruction table and process those that match the current group. For
    // each ALU instruction in the group being processed, generate a set of steps to fetch
    // the operand into B (if needed) and then store the ALU result back into A.  The mode
    // and select lines on the ALU chips are wired to the instruction register, so the
    // only code differences in the instructions are the setting of the ALU CARRY-IN bit.
    for (unsigned i = 0; (i < (sizeof(aluInstructions) / sizeof(*aluInstructions))); i++) {
        uint8_t opcode = aluInstructions[i] & OPCODE_MASK;
        if ((opcode & GROUP_MASK) == groupBits) {
            unsigned index = opcode & INSTRUCTION_MASK;
            microcode_t carry = aluInstructions[i] & ALU_CI ? AC : 0;
            code[index][0] = F1;            // Fetch instruction from memory
            code[index][1] = F2;            // Opcode into IR (sets ALU mode and S bits)
            if (aluInstructions[i] & ALU_B) {
                code[index][2] = RPI | WMA;     // Get address of operand from PC
                code[index][3] = RM | WB;       // Read operand into B
                code[index][4] = RB | carry | WA | N;   // Write ALU result into A
            } else {
                code[index][2] = RB | carry | WA | N;   // Write ALU result into A
                code[index][3] = code[index][4] = 0;
            }
            code[index][5] = code[index][6] = code[index][7] = 0;
        }
    }

    // None of the ALU instructions depend on the state of the flags, so burn identical
    // copies of the microcode for all flag values.
    for (int flags = 0; (flags < NUM_FLAG_COMBOS); flags++) {
        burnCodeBuffer(flags, groupBits);
    }
}

// Modify the microcode for a NOP to convert it to a JMP.
// Used for all of the conditional jump instrutions.
void buildJmpInstruction(uint16_t instr) {
    code[instr][2] = RPI | WMA;
    code[instr][3] = RM | WP | N;
}

void customizeCodeGroup(uint16_t flags, uint16_t group) {
    for (uint16_t instr = 0; (instr < NUM_INSTRUCTIONS); instr++) {
        uint16_t opcode = makeOpcode(group, instr);
        switch (opcode) {
        case IN_JZ:
            if (flags & SF_Z) {
                // default JZ is a NOP.  Make it a JMP if the Z flag is set.
                buildJmpInstruction(instr);
            }
            break;
        case IN_JC:
            if (flags & SF_C) {
                // default JZ is a NOP.  Make it a JMP if the Z flag is set.
                buildJmpInstruction(instr);
            }
            break;
        default:
            break;
        }
    }
}
// Slice a group of 32-bit instruction control words into individual 8-bit chunks and
// burn them into the appropriate position in the ROM.
void burnInstructionGroup(uint16_t group) {
    // TODO - template is hard-coded to burn only group 0.  Need to extend template to
    // an array to accomodate more groups if needed.
    for (uint16_t flags = 0; (flags < NUM_FLAG_COMBOS); flags++) {
        memcpy_P(code, template0, sizeof(code));
        customizeCodeGroup(flags, group);
        burnCodeBuffer(flags, makeGroupBits(group));
    }
}

void burnCodeBuffer(uint16_t flags, uint16_t groupBits) {
    for (uint16_t rom = 0; (rom < NUM_ROMS); rom++) {
        uint16_t shift = rom << 3;  // Shift 8 bits for each ROM position
        for (int instr = 0; instr < NUM_INSTRUCTIONS; instr++) {
            for (int step = 0; step < NUM_STEPS; step++) {
                if ((rom == 1) || (rom == 2)) {
                    burnBuffer[instr * NUM_STEPS + step] = uint8_t(testCode[instr][step] >> shift);
                } else {
                    burnBuffer[instr * NUM_STEPS + step] = uint8_t(code[instr][step] >> shift);
                }
            }
        }
        //writeData(burn_buffer, sizeof(burnBuffer), makeAddress(rom, flags, group));
        // TODO: this is a hack!
        // Only two ROMs are currently wired, but they are addressed as ROM0 and ROM3
        // instead of ROM0 and ROM1.  Burn the code for 0 into 0 and burn the code for 1
        // into 3.
        if (!writeData(burnBuffer, sizeof(burnBuffer), makeAddress(rom, flags, groupBits))) {
            Serial.println("FAILED!");
        }
//        writeData(burnBuffer, sizeof(burnBuffer), makeAddress(rom * 2 + 1, flags, groupBits));
    }
}


void burnMicrocodeRoms() {
#if 1
    uint32_t bit = 0x100;
    for (unsigned ix = 0; (ix < NUM_INSTRUCTIONS); ix++) {
        for (unsigned step = 0; (step < NUM_STEPS); step++) {
            testCode[ix][step] = bit;
            bit <<= 1;
            if (bit >= 0x1000000) {
                bit = 0x100;
            }
        }
    }

    Serial.println("Group 0");
    burnInstructionGroup(0);
    /*
    word addr;
    for (int instr = 0; instr < NUM_INSTRUCTIONS; instr++) {
        for (int step = 0; step < NUM_STEPS; step++) {
            addr = instr << 3 | step;
            burnByte(template0[instr][step] >> 8, addr);
            burnByte(template0[instr][step] & 0xff, addr | 0x2000);
        }
    }
*/
    Serial.println("\nALU L");
    burnAluInstructions(ALU_LOGIC);
    Serial.println("\nALU A");
    burnAluInstructions(ALU_ARITH);
#else
    // walking bit test for ROM0 to test control bits
    uint8_t bit = 1;
    for (int a = 0; a < 8*1024; a++) {
        burnByte(bit, a);
        bit = bit << 1;
        if (bit == 0) {
            bit = 1;
        }
    }
    // incrementing test for ROM3 to test 3-to-8 decoders
    for (unsigned a = 0; (a < 128); a++) {
        burnBuffer[a] = a & 0x0f | ((a & 0x0f) << 4);
    }
    for (unsigned flags = 0; flags < NUM_FLAG_COMBOS; flags++) {
        for (unsigned group = 0; group < NUM_GROUPS; group++) {
            unsigned groupBits = makeGroupBits(group);
            writeData(burnBuffer, sizeof(burnBuffer), makeAddress(3, flags, groupBits));
        }
    }
#endif
}



const uint32_t mSize = 32 * 1024L;       // Size of the device, in bytes
const unsigned int mBlockSize = 0;    // Block size for page writes, zero if N/A
const unsigned int mMaxWriteTime = 10;  // Max time (in ms) to wait for write cycle to complete

// Write the special six-byte code to turn off Software Data Protection.
void disableSoftwareWriteProtect() {
    disableOutput();
    disableWrite();
    enableChip();
    setDataBusMode(OUTPUT);

    setByte(0xaa, 0x5555);
    setByte(0x55, 0x2aaa);
    setByte(0x80, 0x5555);
    setByte(0xaa, 0x5555);
    setByte(0x55, 0x2aaa);
    setByte(0x20, 0x5555);

    setDataBusMode(INPUT);
    disableChip();
}

// Read a byte from a given address
byte readByte(uint32_t address) {
    byte data = 0;
    setAddress(address);
    setDataBusMode(INPUT);
    disableOutput();
    disableWrite();
    enableChip();
    enableOutput();
    data = readDataBus();
    disableOutput();
    disableChip();
    return data;
}


// Burn a byte to the chip and verify that it was written.
bool burnByte(byte value, uint32_t address) {
    bool status = false;

    disableOutput();
    disableWrite();

    setAddress(address);
    setDataBusMode(OUTPUT);
    writeDataBus(value);

    enableChip();
    delayMicroseconds(1);
    enableWrite();
    delayMicroseconds(1);
    disableWrite();

    status = waitForWriteCycleEnd(value);

    disableChip();

    return status;
}


bool burnBlock(byte data[], uint32_t len, uint32_t address) {
    bool status = false;
    char cb[50];
    sprintf(cb, "burn %02x at %04x", uint16_t(len), uint16_t(address));
    Serial.println(cb);
    Serial.println(address, HEX);
    if (len == 0)  return true;

    disableOutput();
    disableWrite();
    enableChip();

    // Write all of the bytes in the block out to the chip.  The chip will
    // program them all at once as long as they are written fast enough.
    setDataBusMode(OUTPUT);
    for (uint32_t ix = 0; (ix < len); ix++) {
        setAddress(address + ix);
        writeDataBus(data[ix]);

        delayMicroseconds(1);
        enableWrite();
        delayMicroseconds(1);
        disableWrite();
    }

    status = waitForWriteCycleEnd(data[len - 1]);
    disableChip();

    return status;
}


bool waitForWriteCycleEnd(byte lastValue) {
    // Verify programming complete by reading the last value back until it matches the
    // value written twice in a row.  The D7 bit will read the inverse of last written
    // data and the D6 bit will toggle on each read while in programming mode.
    //
    // Note that the max readcount is set to the device's maxReadTime (in uSecs)
    // divided by two because there are two 1 uSec delays in the loop.  In reality,
    // the loop could run for longer because this does not account for the time needed
    // to run all of the loop code.  In actual practice, the loop will terminate much
    // earlier because it will detect the end of the write well before the max time.
    setDataBusMode(INPUT);
    delayMicroseconds(1);
    for (int readCount = mMaxWriteTime * 1000 / 2; (readCount > 0); readCount--) {
        enableOutput();
        delayMicroseconds(1);
        byte b1 = readDataBus();
        disableOutput();
        enableOutput();
        delayMicroseconds(1);
        byte b2 = readDataBus();
        disableOutput();
        if ((b1 == b2) && (b1 == lastValue)) {
            return true;
        }
    }

    return false;
}


// Set an address and data value and toggle the write control.  This is used
// to write control sequences, like the software write protect.  This is not a
// complete byte write function because it does not set the chip enable or the
// mode of the data bus.
void setByte(byte value, uint32_t address)
{
    setAddress(address);
    writeDataBus(value);

    delayMicroseconds(1);
    enableWrite();
    delayMicroseconds(1);
    disableWrite();
}

// Set a 16 bit address in the two address shift registers.
void setAddress(uint32_t address) {
    static byte lastHi = 0xca;
    byte hi = (address >> 8) & 0xff;
    byte lo = address & 0xff;

    if (hi != lastHi) {
        setAddressRegister(ADDR_CLK_HI, hi);
        lastHi = hi;
    }
    setAddressRegister(ADDR_CLK_LO, lo);
}

// Shift an 8-bit value into one of the address shift registers.  Note that
// the data pins are tied together, selecting the high or low address register
// is a matter of using the correct clock pin to shift the data in.
void setAddressRegister(uint8_t clkPin, byte addr) {
    byte mask = 0;

    if (clkPin == ADDR_CLK_HI) {
        mask = 0x08;
    } else if (clkPin == ADDR_CLK_LO) {
        mask = 0x10;
    }

    // Make sure the clock is low to start.
    PORTC &= ~mask;

    // Shift 8 bits in, starting with the MSB.
    for (int ix = 0; (ix < 8); ix++) {
        // Set the data bit
        if (addr & 0x80) {
            PORTC |= 0x20;
        } else {
            PORTC &= 0xdf;
        }

        // Toggle the clock high then low
        PORTC |= mask;
        delayMicroseconds(3);
        PORTC &= ~mask;
        addr <<= 1;
    }
}

void dump(uint16_t address, byte data[]) {
    char buffer[80];
    sprintf(buffer, "%04x %02x %02x %02x %02x  %02x %02x %02x %02x  %02x %02x %02x %02x  %02x %02x %02x %02x",
    address,
    data[0],data[1],data[2],data[3],
    data[4],data[5],data[6],data[7],
    data[8],data[9],data[10],data[11],
    data[12],data[13],data[14],data[15]);
    Serial.println(buffer);

}
// Write a block of data to the device.  The device supports block writes,
// so the data will be broken into chunks and written using the block mode.
bool writeData(byte data[], uint32_t len, uint32_t address)
{
    dump(address, data);
    dump(address+0x10, data+0x10);
    dump(address+0x20, data+0x20);
    dump(address+0x30, data+0x30);
    dump(address+0x40, data+0x40);
    dump(address+0x50, data+0x50);
    dump(address+0x60, data+0x60);
    dump(address+0x70, data+0x70);
    bool status = true;

    if (mBlockSize == 0) {
        // Device does not support block writes.
        for (uint32_t ix = 0; (ix < len); ix++) {
            if (burnByte(data[ix], address + ix) == false) {
                status = false;
                break;
            }
        }
    } else {
        uint32_t offset = 0;
        uint32_t chunkSize;
        if (address & (mBlockSize - 1)) {
            // Address does not start on a block boundary.  Adjust the size of
            // the first block to fit within a single block.
            chunkSize = mBlockSize - (address & (mBlockSize - 1));
            chunkSize = (chunkSize > len) ? len : chunkSize;
            Serial.print("burnBlock1 a=");
            Serial.println(address, HEX);
            if (burnBlock(data, chunkSize, address) == false) {
                return false;
            }
            offset += chunkSize;
            len -= chunkSize;
        }

        // All writes are now aligned to block boundaries, so write full blocks
        // or remaining length, whichever is smaller.
        while (len > 0) {
            chunkSize = (len > mBlockSize) ? mBlockSize : len;
            Serial.print("burnBlock2 a=");
            Serial.println(address, HEX);
            if (burnBlock(data + offset, chunkSize, address + offset) == false) {
                status = false;
                break;
            }
            offset += chunkSize;
            len -= chunkSize;
        }
    }

    return status;
}

void setDataBusMode(uint8_t mode) {
    // On the Uno and Nano, D2..D9 maps to the upper 6 bits of port D and the
    // lower 2 bits of port B.
    if (mode == OUTPUT) {
        DDRB |= 0x03;
        DDRD |= 0xfc;
    } else {
        DDRB &= 0xfc;
        DDRD &= 0x03;
    }
}

// Read a byte from the data bus.  The caller must set the bus to input_mode
// before calling this or no useful data will be returned.
byte readDataBus() {
    return (PINB << 6) | (PIND >> 2);
}

// Write a byte to the data bus.  The caller must set the bus to output_mode
// before calling this or no data will be written.
void writeDataBus(byte data) {
     PORTB = (PORTB & 0xfc) | (data >> 6);
     PORTD = (PORTD & 0x03) | (data << 2);
}

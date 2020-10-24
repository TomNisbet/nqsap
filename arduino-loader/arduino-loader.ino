/**
**/

#include "Configure.h"
#include "CmdStatus.h"
#include "XModem.h"


static const char * MY_VERSION = "2.3";


// Global status
CmdStatus cmdStatus;

// Global loader hardware interface
LoaderHw hw(32 * 1024L);

// Global XModem driver
XModem xmodem(hw, cmdStatus);

// Instruction opcodes.  Those marked with an asterisk use the ALU and thus must have
// specific opcodes that match the bits that are hardwired from the IR to the ALU control.
enum {
    // 00 - 1f   Immediate - ALU Arithmetic
    IP_NOP = 0x00,  // no operation
    IM_LDA = 0x03,  // load immediate to A
    IM_JMP = 0x05,  // jump
    IM_SBC = 0x06,  // * subtract with carry A
    IP_OUT = 0x07,  // output A
    IM_ADC = 0x09,  // * add with carry A
    IM_JZ  = 0x0a,  // jump if zero
    IM_JC  = 0x0b,  // jump if carry
    IP_HLT = 0x0f,  // halt
    IP_PHA = 0x11,  // push A
    IP_PLA = 0x12,  // pull A
    IM_EOR = 0x16,  // * XOR A
    IM_AND = 0x1b,  // * AND A
    IM_JSR = 0x1c,  // jump to subroutine
    IP_RTS = 0x1d,  // return from subroutine
    IM_OR  = 0x1e,  // * OR A

    // 20 - 2f   Absolute ALU Arithmetic and ALU unary
    IP_INC = 0x20,  // * increment A
    AB_LDA = 0x23,  // load A from memory
    AB_STA = 0x24,  // store A to memory
    AB_SBC = 0x26,  // * subtract with carry A
    AB_ADC = 0x29,  // * add with carry A
    IP_ASL = 0x2c,  // * arithmetic shift left A
    IP_DEC = 0x2f,  // * decrement A
    IP_NOT = 0x30,  // * NOT A
    AB_EOR = 0x36,  // * exlcusive OR A
    AB_AND = 0x3b,  // * AND A
    AB_OR  = 0x3e,   // * OR A

    // 40 - 4f   General
    IP_JPA = 0x49,    // * jump immediate+A       * this opcode is ADD *
    IM_LDS = 0x50,  // load immediate to SP
    IP_TAS = 0x51,  // transfer A to SP
    IP_TSA = 0x52   // transfer SP to A

    // 60 - ff unused
};

static const uint8_t program0[] = {
    // Count by 3
    IM_LDA, 10,   // start at 10
// LOOP
    IM_ADC, 3,    // ADD 3 to A
    IP_OUT,       // OUT (A to display)
    IM_JMP, 2     // JMP back to LOOP
};

static const uint8_t program1[] = {
    // Memory test pattern - not an executable program
    'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
    0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe,
    0x00, 0xff, 0x55, 0xaa, '0',  '1',  '2',  '3'
};

static const uint8_t program2[] = {
    IM_LDA, 1,    // start at 1
    IP_DEC,
    IM_JC, 11,
    IM_JZ, 15,
// 7
    IM_LDA, 22,
    IP_OUT,
    IP_HLT,
// 11
    IM_LDA, 33,
    IP_OUT,
    IP_HLT,
// 15
    IM_LDA, 44,
    IP_OUT,
    IP_HLT
};

static const uint8_t program3[] = {
    IM_LDA, 10,    // Test stack - load value to A and push, change A, pop
    IP_PHA,
    IP_INC,
    IP_INC,
    IP_PLA,
    IP_HLT
};

static const uint8_t program4[] = {
    IM_LDS, 0x80,
    IM_LDA, 0,
// LOOP
    IM_ADC, 5,    // ADD 5 to A
    IM_JSR, 16,   // OUT (A to display)
    IM_JMP, 4,    // JMP back to LOOP
    IP_NOP,IP_NOP,IP_NOP,IP_NOP,IP_NOP,IP_NOP,
    IP_PHA,
    IP_OUT,
    IP_DEC,
    IP_OUT,
    IP_DEC,
    IP_OUT,
    IP_PLA,
    IP_RTS
};

static const uint8_t program5[] = {
    IM_LDA, 0x22,
    AB_STA, 0x50,
    IP_INC,
    AB_STA, 0x51,
    AB_LDA, 0x50,
    IP_OUT,
    IM_JMP, 10
};
struct program_t {
    const uint8_t * data;
    size_t          len;
};
static const program_t programs[] = {
    program0, sizeof(program0),
    program1, sizeof(program1),
    program2, sizeof(program2),
    program3, sizeof(program3),
    program4, sizeof(program4),
    program5, sizeof(program5)
};


/*****************************************************************************/
/*****************************************************************************/

/**
 * CLI parse functions
 */
const char hex[] = "0123456789abcdef";

enum {
    // CLI Commands
    CMD_INVALID,
    CMD_DUMP,
    CMD_FILL,
    CMD_INSERT,
    CMD_GET,
    CMD_PUT,
    CMD_READ,
    CMD_QUIT,
    CMD_TEST,
    CMD_WRITE,
    CMD_EXAMINE,
    CMD_CYCLE,
    CMD_ZAP,
    CMD_DOLLAR,
    CMD_ASSIGN,
    CMD_LAST_STATUS
};


void setup() {
    Serial.begin(115200);
    hw.begin();

    // burn the first sample program and return control to the host.  This lets the loader
    // (and then the host) run with no user interaction at power up.
    burnProgram(0, 0x00);
    hw.disable();
}

void loop() {
    if (hw.isCliMode()) {
        commandLoop();
    }
}

char waitChar() {
    while (!Serial.available()) {}
    return Serial.read();
}

// Read a line of data from the serial connection.
char * readLine(char * buffer, int len) {
    for (int ix = 0; (ix < len); ix++) {
         buffer[ix] = 0;
    }

    // read serial data until linebreak or buffer is full
    char c = ' ';
    int ix = 0;
    do {
        c = waitChar();
        if (c == '\\') {
            // Do a cYcle command without waiting for newline character.
            buffer[0] = 'Y';
            ix = 2;
            break;
        } else if (c == '\b') {
            // Backspace, forget last character.
            if (ix > 0) {
                --ix;
            }
        } else {
            buffer[ix++] = c;
        }
        Serial.write(c);
    } while ((c != '\n') && (ix < len));

    buffer[ix - 1] = '\0';
    return buffer;
}


/************************************************************
* convert a single hex character [0-9a-fA-F] to its value
* @param char c single character (digit)
* @return byte value of the digit (0-15)
************************************************************/
byte hexDigit(char c) {
    if ((c >= '0') && (c <= '9')) {
        return c - '0';
    } else if ((c >= 'a') && (c <= 'f')) {
        return c - 'a' + 10;
    } else if ((c >= 'A') && (c <= 'F')) {
        return c - 'A' + 10;
    } else {
        return 0xff;
    }
}

/************************************************************
* Convert a hex string to a uint32_t value.
* Skips leading spaces and terminates on the first non-hex
* character.  Leading zeroes are not required.
*
* No error checking is performed - if no hex is found then
* defaultValue is returned.  Similarly, a hex string of more than
* 8 digits will return the value of the last 8 digits.
* @param pointer to string with the hex value of the word (modified)
* @return unsigned int represented by the digits
************************************************************/
uint32_t getHex32(char *& pData, uint32_t defaultValue=0) {
    uint32_t u32 = 0;

    while (isspace(*pData)) {
        ++pData;
    }

    if (isxdigit(*pData)) {
        while (isxdigit(*pData)) {
            u32 = (u32 << 4) | hexDigit(*pData++);
        }
    } else {
        u32 = defaultValue;
    }

    return u32;
}


void printByte(byte b) {
    char line[3];

    line[0] = hex[b >> 4];
    line[1] = hex[b & 0x0f];
    line[2] = '\0';

    Serial.print(line);
}


void printWord(word w) {
    char line[5];

    line[0] = hex[(w >> 12) & 0x0f];
    line[1] = hex[(w >>  8) & 0x0f];
    line[2] = hex[(w >>  4) & 0x0f];
    line[3] = hex[(w)       & 0x0f];
    line[4] = '\0';

    Serial.print(line);
}


/*
* Prints a 32 bit value as a hex.
*
* Note that no values over 4 digits are used in
* this appication, so only 4 digits are printed.*/
void printHex32(uint32_t u32) {
    char line[6];

    line[0] = hex[(u32 >> 12) & 0x0f];
    line[1] = hex[(u32 >>  8) & 0x0f];
    line[2] = hex[(u32 >>  4) & 0x0f];
    line[3] = hex[(u32)       & 0x0f];
    line[4] = '\0';

    Serial.print(line);
}


// If the user presses a key then pause until they press another.  Return true if
// Ctrl-C is pressed.
bool checkForBreak() {
    if (Serial.available()) {
        if (Serial.read() == 0x03) {
            return true;
        }
        while (!Serial.available())
        {}
        if (Serial.read() == 0x03) {
            return true;
        }
    }

    return false;
}


/*****************************************************************************/
/*****************************************************************************/
/**
 * Command implementations
 */


/**
* Read data from the device and dump it in hex and ascii.
**/
void dumpBlock(uint32_t start, uint32_t end) {
    char line[81];
//  01234567891 234567892 234567893 234567894 234567895 234567896 234567897 23456789
//  01234: 01 23 45 67  89 ab cf ef  01 23 45 67  89 ab cd ef  1.2.3.4. 5.6.7.8.
    int count = 0;

    memset(line, ' ', sizeof(line));

    char * pHex = line;
    char * pChar = line + 59;
    for (uint32_t addr = start; (addr <= end); addr++) {
        if (count == 0) {
            //print out the address at the beginning of the line
            pHex = line;
            pChar = line + 59;
            *pHex++ = hex[(addr >> 16) & 0x0f];
            *pHex++ = hex[(addr >> 12) & 0x0f];
            *pHex++ = hex[(addr >>  8) & 0x0f];
            *pHex++ = hex[(addr >>  4) & 0x0f];
            *pHex++ = hex[(addr)       & 0x0f];
            *pHex++ = ':';
            *pHex++ = ' ';
        }

        byte data = hw.readByte(addr);
        *pHex++ = hex[data >> 4];
        *pHex++ = hex[data & 0x0f];
        *pHex++ = ' ';
        *pChar++ = ((data < 32) | (data >= 127)) ? '.' : data;

        if ((count & 3) == 3) {
            *pHex++ = ' ';
        }
        if ((count & 7) == 7) {
            *pChar++ = ' ';
        }
        if ((++count >= 16) || (addr == end)) {
            *pChar = '\0';
            Serial.println(line);
            if (checkForBreak()) {
                return;
            }
            memset(line, ' ', sizeof(line));
            count = 0;
        }
    }

    if (count) {
        Serial.println();
    }
}

/**
* Print an address and value and then prompt the user for input.  If two hex characters
* are entered then the value is stored in memory at the current address the the process
* is repeated for the next address.  The loop stops when a non-hex character is entered.
**/
void examine(uint32_t addr) {
    uint8_t val;
    uint8_t x;
    char c;
    while (1) {
        val = 0;
        printWord(addr);
        Serial.print(':');
        printByte(hw.readByte(addr));
        Serial.print(' ');
        Serial.flush();
        c = waitChar();
        if ((c == '\n') || (c == '\r')) {
            // The Arduino IDE serial monitor requires a newline so read and ignore
            // newlineif it is seen.
            Serial.println();
            continue;
        }
        x = hexDigit(c);
        if (x == 0xff) {
            break;
        }
        val = x << 4;
        x = hexDigit(waitChar());
        if (x == 0xff) {
            break;
        }
        hw.writeData(&val, 1, addr++);
        Serial.println();
    }
    Serial.println();
}

/**
 * Fill a block of RAM data with a single value.
 *
 * @param start - start address
 * @param end - end address
 * @param val - data byte to write to all addresses
 */
void fillBlock(uint32_t start, uint32_t end, byte val) {
    enum { BLOCK_SIZE = 32 };
    byte block[BLOCK_SIZE];

    for (int ix = 0; ix < BLOCK_SIZE; ix++) {
        block[ix] = val;
    }

    for (uint32_t addr = start; (addr <= end); addr += BLOCK_SIZE) {
        uint32_t writeLen = ((end - addr + 1) < BLOCK_SIZE) ? (end - addr + 1) : uint32_t(BLOCK_SIZE);
        if (!hw.writeData(block, writeLen, addr)) {
            cmdStatus.error("Write failed");
            return;
        }
    }
}


void burnProgram(unsigned pgmIx, uint32_t start) {
    char s[50];
    if (pgmIx < (sizeof(programs) / sizeof(*programs))) {
        const uint8_t * pgmData = programs[pgmIx].data;
        size_t pgmLen = programs[pgmIx].len;
        sprintf(s, "Burning program %u at %04x len=%u", pgmIx, unsigned(start), pgmLen);
        Serial.println(s);
        hw.enable();
        bool status = hw.writeData(pgmData, pgmLen, start);
        if (!status) {
            cmdStatus.error("Write failed");
            return;
        }

        for (unsigned ix = 0; (ix < pgmLen); ix++) {
            byte val = hw.readByte(start + ix);
            if (val != pgmData[ix]) {
                cmdStatus.error("Verify failed");
                cmdStatus.setValueHex(0, "addr", start + ix);
                cmdStatus.setValueHex(1, "read", val);
                cmdStatus.setValueHex(2, "expected", pgmData[ix]);
                return;
            }
        }
        cmdStatus.info("Write verification test successful");
    }
}

void insertBytes(char * pCursor)
{
    uint32_t val;
    uint32_t start;
    unsigned byteCtr = 0;

    enum { BLOCK_SIZE = 32 };
    byte data[BLOCK_SIZE];

    //first value returned is the starting address
    start = getHex32(pCursor, 0);
    while (((val = getHex32(pCursor, 0xffff)) != 0xffff) && (byteCtr < BLOCK_SIZE)) {
        data[byteCtr++] = byte(val);
    }

    if (byteCtr > 0) {
        if (!hw.writeData(data, byteCtr, start)) {
            cmdStatus.error("Write failed");
            return;
        }
    } else {
        cmdStatus.error("Missing address or data");
        return;
    }
    delay(100);

    for (unsigned ix = 0; ix < byteCtr ; ix++) {
        byte val = hw.readByte(start + ix);
        if (val != data[ix]) {
            cmdStatus.error("Verify failed");
            cmdStatus.setValueHex(0, "addr", start + ix);
            cmdStatus.setValueHex(1, "read", val);
            cmdStatus.setValueHex(2, "expected", data[ix]);
            return;
        }
    }
    cmdStatus.info(" successful");
}


/*
G5 - get r5 into $ and print
P6 2f- put value 2f into r6 - can use $ for value
=2 4 - transfer r2 from r4 (dest first, like P command)
$ - print last value
$ 3c - set value of $ to 3c
Y - cYcle clock - for example, if IR has an ALU op will change values
The G,P,T commands will leave the RW selects set for additional Y cmds
Dssss eeee dump memory
Fssss eeee vv fill memory
Xssss eXamine memory will step through and can change values see gwmon
T - test memory, alu, and all registers.  R/W registers will verify a set of values. R/O registers will do the light show. Some R/O are implicitly tested.
*/
byte parseCommand(char c)
{
    byte cmd = CMD_INVALID;

    // Convert the command to lowercase.
    if ((c >= 'A') && (c <= 'Z')) {
        c |= 0x20;
    }

    switch (c) {
        case 'd':  cmd = CMD_DUMP;      break;
        case 'f':  cmd = CMD_FILL;      break;
        case 'g':  cmd = CMD_GET;       break;
        case 'i':  cmd = CMD_INSERT;    break;
        case 'p':  cmd = CMD_PUT;       break;
        case 'r':  cmd = CMD_READ;      break;
        case 'q':  cmd = CMD_QUIT;      break;
        case 't':  cmd = CMD_TEST;      break;
        case 'w':  cmd = CMD_WRITE;     break;
        case 'x':  cmd = CMD_EXAMINE;   break;
        case 'y':  cmd = CMD_CYCLE;     break;
        case 'z':  cmd = CMD_ZAP;       break;
        case '$':  cmd = CMD_DOLLAR;    break;
        case '=':  cmd = CMD_ASSIGN;    break;
        case '/':  cmd = CMD_LAST_STATUS;break;
        default:   cmd = CMD_INVALID;   break;
    }

    return cmd;
}


void commandLoop() {
    char line[60];
    char buff[50];
    uint32_t a1, a2, a3;
    byte lastVal = 0;
    uint32_t numBytes;
    uint32_t noArg = uint32_t(-1);
    int argc = 0;

    Serial.print("\n>");
    Serial.flush();
    readLine(line, sizeof(line));
    Serial.println();
    byte cmd = parseCommand(line[0]);
    char * pCursor = line+1;
    if ((a1 = getHex32(pCursor, noArg)) != noArg) { ++argc; }
    if ((a2 = getHex32(pCursor, noArg)) != noArg) { ++argc; }
    if ((a3 = getHex32(pCursor, noArg)) != noArg) { ++argc; }

    if ((cmd != CMD_LAST_STATUS) && (cmd != CMD_INVALID)) {
        cmdStatus.clear();
    }

    switch (cmd) {
    case CMD_DUMP:
        if (argc < 2) { a2 = a1 + 255; }
        dumpBlock(a1, a2);
        break;

    case CMD_GET:
        lastVal = hw.readRegister(a1);
        Serial.println(lastVal, HEX);
        break;

    case CMD_PUT:
        // Note that this command will not work with the Output Register because it uses
        // a latch instead of a clock pulse to store its data.  This command will
        // briefly put a value on the bus (and into the output register), but immediately
        // after the clock pulse, the loader will release the bus and the default zero
        // value will show on the Output Register.  The Assign command will work correctly
        // with Output because it leaves the read register on the bus upon completion.
        hw.writeRegister(a1, a2);
        break;

    case CMD_INSERT:
        insertBytes(line + 1);
        break;

    case CMD_EXAMINE:
        if (argc < 1) { a1 = 0; }
        examine(a1);
        break;

    case CMD_ASSIGN:
        hw.transferRegister(a1, a2);
        break;

    case CMD_FILL:
        if (argc < 2) { a2 = a1 + 255; }
        fillBlock(a1, a2, byte(a3));
        break;

    case CMD_QUIT:
        hw.disable();
        Serial.println(F("Loader disabled, control returned to host.  Press ENTER to re-enable loader."));
        readLine(line, sizeof(line));
        break;

    case CMD_READ:
        if (argc < 2) { a2 = a1 + 255; }
        Serial.println(F("Set the terminal to receive XMODEM CRC"));
        if (xmodem.SendFile(a1, uint32_t(a2) - a1 + 1)) {
            cmdStatus.info("Send complete.");
            cmdStatus.setValueDec(0, "NumBytes", uint32_t(a2) - a1 + 1);
        }
        break;

    case CMD_WRITE:
        Serial.println(F("Send the image file using XMODEM CRC"));
        numBytes = xmodem.ReceiveFile(a1);
        if (numBytes) {
            cmdStatus.info("Success writing to RAM.");
            cmdStatus.setValueDec(0, "NumBytes", numBytes);
        } else {
            xmodem.Cancel();
        }
        break;

    case CMD_TEST:
        if (hw.testHardware()) {
            Serial.println(F("Hardware test passed"));
        } else {
            Serial.println(F("Hardware test failed"));
        }
        break;

    case CMD_CYCLE:
        if (argc < 1) { a1 = 1; }
        for (unsigned ix = 0; (ix < a1); ix++) {
            hw.clkPulse();
            delay(100);
        }
        break;

    case CMD_DOLLAR:
        sprintf(buff, "%u (0x%02x)", lastVal, lastVal);
        Serial.println(buff);
        break;

    case CMD_ZAP:
        if (argc < 2) { a2 = 0; }
        burnProgram(a1, a2);
        break;

    case CMD_LAST_STATUS:
        Serial.println(F("Status of last command:"));
        break;

    default:
        Serial.print(F("NQSAP Loader "));
        Serial.println(MY_VERSION);
        Serial.println(F("RAM commands:"));
        Serial.println(F("  Dss ee    - Dump bytes from RAM to terminal"));
        Serial.println(F("  Fss ee dd - Fill block of RAM with fixed value"));
        Serial.println(F("  Rss ee    - Read from RAM and save to XMODEM CRC file"));
        Serial.println(F("  Wss       - Write to RAM from XMODEM CRC file"));
        Serial.println(F("  Xss       - eXamine (and optionally modify) RAM"));

        Serial.println(F("\nRegister and hardware commands:"));
        Serial.println(F("  Gr        - Get (read) and print register value"));
        Serial.println(F("  Pr dd     - Put (write) value to register"));
        Serial.println(F("  =r1 r2    - Assign (r1=r2) copy value from register r2 to r1"));
        Serial.println(F("  Y[cc]     - cYcle host hardware clock (with optional repeat count)"));

        Serial.println(F("\nMisc commands:"));
        Serial.println(F("  T         - Test host hardware"));
        Serial.println(F("  Zpp ss    - Zap (burn) and verify a 32 byte test pattern"));
        Serial.println(F("  Q         - Quit loader mode and return control to host"));
        break;
    }

    if (!cmdStatus.isClear() || (cmd == CMD_LAST_STATUS)) {
        Serial.println();
        cmdStatus.printStatus();
    }
}

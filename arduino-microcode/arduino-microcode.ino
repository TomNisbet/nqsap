#include "Arduino.h"

static const char * MY_VERSION = "2.0";

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


// TODO: may need better high-level explanation of the buffers used in this code, i.e.
// group of 32-bit instruction generated, customized multiple times for the flag
// combinations, then split into the 4 b-bit chuck to be written to the chip.

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
    Serial.print("\nBurning NQSAP microcode version ");
    Serial.println(MY_VERSION);
    burnMicrocodeRoms();
    Serial.println(F("burn complete"));
}

void loop() {
    digitalWrite(RED_LED, HIGH);
    delay(500);
    digitalWrite(RED_LED, LOW);
    delay(500);
}

void fail() {
    Serial.println(F("Write FAILED"));
    while (1) {
      digitalWrite(RED_LED, HIGH);
      delay(200);
      digitalWrite(RED_LED, LOW);
      delay(200);
      digitalWrite(RED_LED, HIGH);
      delay(200);
      digitalWrite(RED_LED, LOW);
      delay(200);
      digitalWrite(RED_LED, HIGH);
      delay(200);
      digitalWrite(RED_LED, LOW);
      delay(500);
    }
}

//               ROM3    ROM2    ROM1    ROM0
//             +------++------++------++------+
// ROM3        WWWWxRRR765432107654321076543210
#define WM   0b00010000000000000000000000000000L  // 1 Write Memory
#define WA   0b00100000000000000000000000000000L  // 2 Write A
#define WB   0b00110000000000000000000000000000L  // 3 Write B
#define WX4  0b01000000000000000000000000000000L  // 4
#define WS   0b01010000000000000000000000000000L  // 5 Write SP
#define WP   0b01100000000000000000000000000000L  // 6 Write PC (Jump)
#define WX7  0b01110000000000000000000000000000L  // 7
#define WX8  0b10000000000000000000000000000000L  // 8
#define WMA  0b10010000000000000000000000000000L  // 9 Write Memory Address
#define WXA  0b10100000000000000000000000000000L  // A
#define WXB  0b10110000000000000000000000000000L  // B
#define WO   0b11000000000000000000000000000000L  // C Write Output
#define WXD  0b11010000000000000000000000000000L  // D
#define WXE  0b11100000000000000000000000000000L  // E
#define WI   0b11110000000000000000000000000000L  // F Write IR

#define RM   0b00000001000000000000000000000000L  // 1 Read Memory
#define RA   0b00000010000000000000000000000000L  // 2 Read A
#define RB   0b00000011000000000000000000000000L  // 3 Read B
#define RL  0b00000100000000000000000000000000L   // 4 Read L (ALU result)
#define RS   0b00000101000000000000000000000000L  // Read SP
#define RP   0b00000110000000000000000000000000L  // 6 Read PC
#define RX7  0b00000111000000000000000000000000L  // 7

// ROM2
// TODO not used now - burnInstructionGroup hard-coded to write test
// patterns into the ROM2 space
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
#define SPI  0b00000000000000000000001000000000L  // 02 Stack Pointer inc (dec)
#define SCE  0b00000000000000000000000100000000L  // 01 SP count enable

// ROM0
#define HLT  0b00000000000000000000000010000000L  // 80 Halt
#define IP   0b00000000000000000000000001000000L  // 40 Increment PC
#define CR   0b00000000000000000000000000100000L  // 20 Clear Ring Counter
#define AC   0b00000000000000000000000000010000L  // 10 ALU Carry Flag
#define LF   0b00000000000000000000000000001000L  // 08 Load Flags
#define XX02 0b00000000000000000000000000000100L
#define XX01 0b00000000000000000000000000000010L
#define XX00 0b00000000000000000000000000000001L

#define N  CR           // Shorthand for start next instruction
#define RPI  RP | IP    // Shorthand for Read PC and post increment
#define F1  RPI | WMA   // Instruction fetch step 1
#define F2  RM  | WI    // Instruction fetch step 2
#define FA  RPI | WMA   // Fetch argument (operand) step 1
#define SI  SCE | SPI   // Stack Pointer increment
#define SD  SCE         // Stack Pointer decrement
enum {
    // Status flag bits.  These are based at the least significant bit position, not at
    // their position in the address word.  These values can be used when iterating
    // between zero and NUM_FLAG_COMBOS.
    SF_Z = 0x01,        // Zero
    SF_C = 0x02,        // Carry
};


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

    // 10 - 1f  Immediate - ALU Logic
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

    // 30 - 3f  Absolute ALU Logic Absolute and ALU unary
    IP_NOT = 0x30,  // * NOT A
    AB_EOR = 0x36,  // * exlcusive OR A
    AB_AND = 0x3b,  // * AND A
    AB_OR  = 0x3e,  // * OR A

    // These instructions are temporary.  When the X/Y/T registers are added, most of
    // these will be replaced.
    // The JPA will be replaced by ABS,X and ABS,Y addressing modes.  TXS and TSX will
    // replace TAS and TSA.

    // 40 - 4f   General
    IP_JPA = 0x49,    // * jump immediate+A       * this opcode is ADD *

    // 50 -5f  General
    IM_LDS = 0x50,  // load immediate to SP
    IP_TAS = 0x51,  // transfer A to SP
    IP_TSA = 0x52   // transfer SP to A

    // 60 - ff unused
};


// GGGGIIII - Instruction register opcode format, group and instruction bits
// GGGMSSSS - Mapping of ALU control bits to opcode bits
enum {
    // The ALU operation is determined by the Mode bit (Arithmetic/Logic), the Select
    // bits, and the CARRY-IN bit. The Mode bit and the four Select bits of the ALU are
    // connected directly to the Instruction Register so that 5 additional microcode ROM
    // bits are not consumed. This means that, other than the CARRY-IN bit, all ALU
    // instructions can have identical microcode.  The bits below match the wiring of the
    // IR to the ALU and therefore also match the lower 5 bits of the 8-bit instruction
    // opcode. The CARRY-IN flag is not wired to the Instruction Register, so it is not
    // encoded as part of the instruction.
    ALU_M =               0b00010000,
    ALU_S3 =              0b00001000,
    ALU_S2 =              0b00000100,
    ALU_S1 =              0b00000010,
    ALU_S0 =              0b00000001,

    // The flags below are per-instruction options.  They are used only in the definition
    // table to assist in building the microcode.  They do not map to any physical bits
    // and are defined outside of the 8-bit opcode area to avoid confusion.
    // The ALU_DEF_CI flag indicates that an ALU instruction needs its microcode to set
    // the AC bit for the ALU CARRY-IN flag input.

    // The ALU_DEF_BINARY flag indicates an instruction that uses both the A and B operand
    // inputs to the ALU.  The A operand always comes from the current contents of the A
    // register.  Multiple version of each instruction can be created (with  different
    // opcodes) so that the B operand could come from memory, immediate value, or other
    // options.  There is no point in generating multiple instruction variants for the
    // unary operations, because they always work only on the contents of the A register.
    ALU_DEF_CI      = 0b000100000000,
    ALU_DEF_BINARY  = 0b001000000000,
};

// This table contains the opcodes that are used for ALU instructions plus additional bits
// to indicate if a second operand is specified for the B register and if the AC flag
// should be set in the microcode steps for the instruction.  Many of the combinations of
// control bits in the ALU do not map to useful operations, so this is a small subset of
// the complete ALU operation set.  Note that some ALU operations in the table are
// commented out.  They are to show ALU operations that might be used by the underlying
// microcode, but are not useful as standalone instructions.  For example, the B operation
// us a worthless instruction, but the ALU operation is used by the CALL instruction so
// that B can be used for temporary storage.  The all-zeroes or all-ones operations
// may also be useful utilities.

uint16_t aluInstructionDefinitions[] = {
    // M=0 ALU Arithmetic operations
    0,                                                               // 00 INC - A plus 1
    //                                              ALU_S1 | ALU_S0, // 03 zero - all zero
    //               ALU_DEF_CI                   | ALU_S1 | ALU_S0, // 03 ones - all one
    ALU_DEF_BINARY                       | ALU_S2 | ALU_S1,          // 06 SUB - A minus B
    ALU_DEF_BINARY | ALU_DEF_CI | ALU_S3                   | ALU_S0, // 09 ADD - A plus B
                     ALU_DEF_CI | ALU_S3 | ALU_S2,                   // 0c ASL - A + A
                     ALU_DEF_CI | ALU_S3 | ALU_S2 | ALU_S1 | ALU_S0, // 0f DEC - A minus 1

    // M=1 ALU Logic operations
                     ALU_M,                                          // 10 NOT - not A
    ALU_DEF_BINARY | ALU_M               | ALU_S2 | ALU_S1,          // 16 XOR - A xor B
    //               ALU_M      | ALU_S3          | ALU_S1,          // 1a B - returns B
    ALU_DEF_BINARY | ALU_M      | ALU_S3          | ALU_S1 | ALU_S0, // 1b AND - A and B
    ALU_DEF_BINARY | ALU_M      | ALU_S3 | ALU_S2 | ALU_S1           // 1e OR - A or B
};

// The ALU instruction group options allow programmatic generation of a group of ALU
// instructions.  By specifying different group options, the aluInstructionDefinitions
// table can be used to create multiple instruction groups with different processing.
//
// For example, one group could have instructions like "ADD A to immediate value" and
// another could have "ADD A to value from memory".
// The OPT_UNARY flag allows selective generation of the instructions that only have a
// single operand (not ALU_IN_BINARY), so that multiple versions of these instructions
// are not generated for each addressing mode.
enum {
    ALU_OPT_UNARY     = 0b00000001,     // Generate unary instructions
    ALU_OPT_IMMEDIATE = 0b00000010,     // Operands are A and immediate value
    ALU_OPT_ABSOLUTE  = 0b00000100,     // Operands are A and value from memory location
    ALU_OPT_NONE      = 0b00001000      // Do not generate ALU instructions
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
typedef microcode_t template_t[NUM_INSTRUCTIONS][NUM_STEPS];

// Note that the default conditional jump code is to increment the PC to skip the
// address argument and clear the ring counter to execute the next instruction.  This is
// effectively a NOP.  The customizeCodeGroup code will replace this with the microcode
// for an unconditional jump for flag combinations that match the type of jump.

//const microcode_t template0[NUM_INSTRUCTIONS][NUM_STEPS] PROGMEM = {
const template_t template0 PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 00 IP_NOP
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 01
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 02
  { F1, F2, FA,       RM|WA|N,    0,       0,        0,       0 }, // 03 IM_LDA
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 04
  { F1, F2, FA,       RM|WP|N,    0,       0,        0,       0 }, // 05 IP_JMP
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 06 IM_SBC *
  { F1, F2, RA|WO|N,  0,          0,       0,        0,       0 }, // 07 IP_OUT
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 08
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 09 IM_ADC *
  { F1, F2, 0,        IP|N,       0,       0,        0,       0 }, // 0a IM_JZ // TODO use T2?
  { F1, F2, 0,        IP|N,       0,       0,        0,       0 }, // 0b IM_JC
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 0c
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 0d
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 0e
  { F1, F2, HLT,      0,          0,       0,        0,       0 }  // 0f IP_HLT
};

const template_t template1 PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 10
  { F1, F2, RS|WMA,   RA|WM|SI|N, 0,       0,        0,       0 }, // 11 PHA
  { F1, F2, SD,       RS|WMA,     RM|WA|N, 0,        0,       0 }, // 12 PLA
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 13
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 14
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 15
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 16 IM_EOR *
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 17
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 18
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 19
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 1a
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 1b IM_AND *
  { F1, F2, FA,       RM|WB,      RS|WMA,  WM|RP|SI, RB|WP|N, 0 }, // 1c IM_JSR
  { F1, F2, SD,       RS|WMA,     RM|WP|N, 0,        0,       0 }, // 1d IP_RTS
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 1e IM_OR *
  { F1, F2, HLT,      0,          0,       0,        0,       0 }  // 1f
};

const template_t template2 PROGMEM = {
//  0   1   2         3           4        5         6        7
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 20 IP_INC *
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 21
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 22
  { F1, F2, FA,       RM|WMA,     RM|WA|N, 0,        0,       0 }, // 23 AB_LDA
  { F1, F2, FA,       RM|WMA,     RA|WM|N, 0,        0,       0 }, // 24 AB_STA
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 25
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 26 AB_SBC *
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 27
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 28
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 29 AB_ADC *
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 2a
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 2b
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 2c IP_ASL *
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 2d
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 2e
  { 0,  0,  0,        0,          0,       0,        0,       0 }  // 2f IP_DEC *
};

const template_t template3 PROGMEM = {
//  0   1   2         3           4        5         6        7
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 30 IP_NOT *
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 31
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 32
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 33
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 34
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 35
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 36 AB_EOR *
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 37
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 38
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 39
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 3a
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 3b AB_AND *
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 3c
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 3d
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 3e AB_OR *
  { F1, F2, HLT,      0,          0,       0,        0,       0 }  // 3f
};

const template_t template4 PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 40
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 41
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 42
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 43
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 44
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 45
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 46
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 47
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 48
  { F1, F2, FA,       RM|WB,      RL|WP|N, 0,        0,       0 }, // 49 IP_JPA * ALU op=ADD
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 4a
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 4b
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 4c
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 4d
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 4e
  { F1, F2, HLT,      0,          0,       0,        0,       0 }  // 4f
};

const template_t template5 PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, FA,       RM|WS|N,    0,       0,        0,       0 }, // 50 IM_LDS
  { F1, F2, RS|WA|N,  0,          0,       0,        0,       0 }, // 51 IP_TAS
  { F1, F2, RA|WS|N,  0,          0,       0,        0,       0 }, // 52 IP_TSA
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 53
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 54
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 55
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 56
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 57
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 58
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 59
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 5a
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 5b
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 5c
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 5d
  { F1, F2, HLT,      0,          0,       0,        0,       0 }, // 5e
  { F1, F2, HLT,      0,          0,       0,        0,       0 }  // 5f
};

const template_t * templates[] = { &template0, &template1, &template2, &template3,
                                   &template4, &template5 };

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
    uint16_t addr =  (rom << 13) | (flags << 11) | (groupBits << 3) | (instr << 3) | step;
//    char b[50];
//    sprintf(b, "a=x%04x  r=%d f=%d g=x%02x i=%u s=%u", addr, rom, flags, groupBits, instr, step);
//    Serial.println(b);
    return addr;
}

// Convert a group number (0..NUM_GROUPS) into the group bits portion of an opcode.
// Note that this is not the same position that the group bits occupy in a ROM address.
uint8_t makeOpcodeGroupBits(uint8_t group) {
    return group << 4;
}

// Make an opcode from a group number and an instruction number.
// Group numbers are (0..NUM_GROUPS) and an instruction numbers are (0..NUM_INSTRUCTIONS)
uint8_t makeOpcode(uint8_t group, uint8_t instr) {
    return makeOpcodeGroupBits(group) | instr;
}

// Each call to this burns one block of code at group and the other at group+1.
void burnInstructionGroups(uint8_t group, const char * name, uint8_t groupOptions) {
    // Note that groupOptions are specific to a whole block of instructions, like
    // should unaries be generated and where does the B argument come from.  There
    // are also instructionOptions that are encoded into the high bits of the
    // aluInstructions entries.  These indicate whether a specific instruction
    // is binary or unary, sets the status flags, and needs the ALU carry in flag.

    burnInstructionGroup(group,   name, groupOptions);  // Arithmetic
    burnInstructionGroup(group+1, name, groupOptions);  // Logical
}

void burnInstructionGroup(uint8_t group, const char * name, uint8_t groupOptions) {
    Serial.print(F("burning "));
    Serial.print(group);
    Serial.print(F(" - "));
    Serial.println(name);
    for (int flags = 0; (flags < NUM_FLAG_COMBOS); flags++) {
        buildInstructions(group, groupOptions);
        customizeCodeGroup(flags, group);
        burnCodeBuffer(flags, group);
    }
}

void buildInstructions(uint8_t group, uint8_t groupOptions) {
    // Initialize the code buffer with values for the entries that will not get
    // overwritten by ALU instructions.
    if (group < (sizeof(templates) / sizeof(*templates))) {
        // Initialize the code buffer from a template.
        memcpy_P(code, templates[group], sizeof(code));
    } else {
        // Initialize the code buffer with a HLT instruction.
        for (int i = 0; (i < NUM_INSTRUCTIONS); i++) {
            code[i][0] = F1;
            code[i][1] = F2;
            code[i][2] = HLT;
            code[i][3] = code[i][4] = code[i][5] = code[i][6] = code[i][7] = 0;
        }
    }

    // There are currently some non-ALU instructions (like IP_JMPIA) that use ALU
    // functionality that would conflict with existing ALU instructions.  Skip ALU
    // instruction generation in this case and just use the microcode from the templates.
    // These instrutions will likely all be removed when the X/Y/T registers are added.
    if (groupOptions & ALU_OPT_NONE) return;

    // Walk the ALU instruction definitions table and generate the microcode.  There are
    // two conditions that must be met for a table entry to output microcode:

    //   1. The low order bit of the groupBits is the position of the ALU_M bit that
    //   indicates an arithmetic or logical instruction.  The table has both types, so
    //   only generate the set of instructions that match the ALU_M bit for the group.

    //   2. The instruction must use two operands (ALU_IN_BINARY) or the options to
    //   generate unary instructions for the group (ALU_OPT_UNARY) must be set. This
    //   prevents multiple instances of the unary ALU instructions for being created when
    //   generating multiple sets of binary ALU instructions with differing operand
    //   sources.

    // For each ALU instruction in the group being processed, generate a set of steps to
    // fetch the operand into B (if needed) and then store the ALU result back into A. The
    // mode and select lines on the ALU chips are wired to the instruction register, so
    // the only code differences in the instructions are the setting of the ALU CARRY-IN
    // bit.
    uint8_t groupBits = makeOpcodeGroupBits(group);
    for (unsigned i = 0; (i < (sizeof(aluInstructionDefinitions) / sizeof(*aluInstructionDefinitions))); i++) {
        uint16_t def = aluInstructionDefinitions[i];
        uint8_t opcode = def & OPCODE_MASK;
        if (((opcode & ALU_M) == (groupBits & ALU_M)) &&
            ((groupOptions & ALU_OPT_UNARY) || (def & ALU_DEF_BINARY))) {
            unsigned index = opcode & INSTRUCTION_MASK;
            microcode_t carry = (def & ALU_DEF_CI) ? AC : 0;
            code[index][5] = code[index][6] = code[index][7] = 0;
            code[index][0] = F1;            // Fetch instruction from memory
            code[index][1] = F2;            // Opcode into IR (sets ALU mode and S bits)
            if ((def & ALU_DEF_BINARY) == 0) {
                // Unary operation, no additional operand needed
                code[index][2] = RL | carry | WA | LF | N;   // Write ALU result into A and flags
            } else if (groupOptions & ALU_OPT_IMMEDIATE) {
                // Get B operand from immediate value
                code[index][2] = RPI | WMA;     // Get next address from PC
                code[index][3] = RM | WB;       // Read operand into B (immediate data)
                code[index][4] = RL | carry | WA | LF | N;   // Write ALU result into A and flags
            } else if (groupOptions & ALU_OPT_ABSOLUTE) {
                    // Get B operand from specified memory location
                    code[index][2] = RPI | WMA;     // Get next address from PC
                    code[index][3] = RM | WMA;      // Read address of operand into MAR
                    code[index][4] = RM | WB;       // Read operand into B
                    code[index][5] = RL | carry | WA | LF | N;   // Write ALU result into A and flags
            } else {
                Serial.print(F("ALU microcode error, opcode="));
                Serial.println(opcode);
            }
        }
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
        case IM_JZ:
            if (flags & SF_Z) {
                // default JZ is a NOP.  Make it a JMP if the Z flag is set.
                buildJmpInstruction(instr);
            }
            break;
        case IM_JC:
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

#if 0
// Slice a group of 32-bit instruction control words into individual 8-bit chunks and
// burn them into the appropriate position in the ROM.
void burnInstructionGroup(uint16_t group) {
    Serial.print("Group ");
    Serial.println(group);

    for (uint16_t flags = 0; (flags < NUM_FLAG_COMBOS); flags++) {
        memcpy_P(code, templates[group], sizeof(code));
        customizeCodeGroup(flags, group);
        burnCodeBuffer(flags, group);
    }
}
#endif

void burnCodeBuffer(uint16_t flags, uint8_t group) {
    uint16_t groupBits = makeOpcodeGroupBits(group);
    for (uint16_t rom = 0; (rom < NUM_ROMS); rom++) {
        uint16_t shift = rom << 3;  // Shift 8 bits for each ROM position
        for (int instr = 0; instr < NUM_INSTRUCTIONS; instr++) {
            for (int step = 0; step < NUM_STEPS; step++) {
                if (rom == 2) {
                    // TODO - not using ROM2 yet, so burn test patterns into it
                    burnBuffer[instr * NUM_STEPS + step] = uint8_t(testCode[instr][step] >> shift);
                } else {
                    burnBuffer[instr * NUM_STEPS + step] = uint8_t(code[instr][step] >> shift);
                }
            }
        }
        if (!writeData(burnBuffer, sizeof(burnBuffer), makeAddress(rom, flags, groupBits))) {
            fail();
        }
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

    // Note that each call to burnAluInstructionGroups burns two groups of instructions.
    burnInstructionGroups(0, "Immediate", ALU_OPT_IMMEDIATE);
    burnInstructionGroups(2, "Absolute and unary", ALU_OPT_ABSOLUTE | ALU_OPT_UNARY);
    burnInstructionGroups(4, "Special", ALU_OPT_NONE);
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
            unsigned groupBits = makeOpcodeGroupBits(group);
            writeData(burnBuffer, sizeof(burnBuffer), makeAddress(3, flags, groupBits));
        }
    }
#endif
}



const uint32_t mSize = 32 * 1024L;      // Size of the device, in bytes
const unsigned int mBlockSize = 64;     // Block size for page writes, zero if N/A
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
    delayMicroseconds(3);
    enableWrite();
    delayMicroseconds(3);
    disableWrite();

    status = waitForWriteCycleEnd(value);

    disableChip();

    if (!status) {
        Serial.print(F("burn address="));
        Serial.println(address, HEX);
    }
    return status;
}


bool burnBlock(byte data[], uint32_t len, uint32_t address) {
    bool status = false;
//    char cb[50];
//    sprintf(cb, "burn %02x at %04x", uint16_t(len), uint16_t(address));
//    Serial.println(cb);
//    Serial.println(address, HEX);
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
        enableChip();
        enableOutput();
        delayMicroseconds(1);
        byte b1 = readDataBus();
        disableOutput();
        disableChip();
        enableChip();
        enableOutput();
        delayMicroseconds(1);
        byte b2 = readDataBus();
        disableOutput();
        disableChip();
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
    /*
    dump(address, data);
    dump(address+0x10, data+0x10);
    dump(address+0x20, data+0x20);
    dump(address+0x30, data+0x30);
    dump(address+0x40, data+0x40);
    dump(address+0x50, data+0x50);
    dump(address+0x60, data+0x60);
    dump(address+0x70, data+0x70);
    */
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

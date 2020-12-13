#include "Arduino.h"

static const char * MY_VERSION = "4.0";

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
    disableSoftwareWriteProtect();
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
      delay(600);
    }
}

// Get rid of Arduino macro definitions that conflict with control signal names
#undef PI

//               ROM3    ROM2    ROM1    ROM0
//             +------++------++------++------+
// ROM3        WWWWRRRR765432107654321076543210
#define WR   0b00010000000000000000000000000000L  // 1 Write RAM
#define WA   0b00100000000000000000000000000000L  // 2 Write A
#define WB   0b00110000000000000000000000000000L  // 3 Write B
#define WX4  0b01000000000000000000000000000000L  // 4
#define WS   0b01010000000000000000000000000000L  // 5 Write SP
#define WP   0b01100000000000000000000000000000L  // 6 Write PC (Jump)
#define WX7  0b01110000000000000000000000000000L  // 7
#define WD   0b10000000000000000000000000000000L  // 8 Write D (Adder)
#define WM   0b10010000000000000000000000000000L  // 9 Write Memory Address
#define WX   0b10100000000000000000000000000000L  // A Write X
#define WY   0b10110000000000000000000000000000L  // B Write Y
#define WO   0b11000000000000000000000000000000L  // C Write Output
#define WXD  0b11010000000000000000000000000000L  // D
#define WXE  0b11100000000000000000000000000000L  // E
#define WI   0b11110000000000000000000000000000L  // F Write IR

#define RR   0b00000001000000000000000000000000L  // 1 Read RAM
#define RA   0b00000010000000000000000000000000L  // 2 Read A
#define RB   0b00000011000000000000000000000000L  // 3 Read B
#define RL   0b00000100000000000000000000000000L  // 4 Read L (ALU result)
#define RS   0b00000101000000000000000000000000L  // 5 Read SP
#define RP   0b00000110000000000000000000000000L  // 6 Read PC
#define RX7  0b00000111000000000000000000000000L  // 7
#define RD   0b00001000000000000000000000000000L  // 8 Read D (Adder)
#define RX9  0b00001001000000000000000000000000L  // 9
#define RX   0b00001010000000000000000000000000L  // A Read X
#define RY   0b00001011000000000000000000000000L  // B Read Y
#define RXC  0b00001100000000000000000000000000L  // C
#define RH   0b00001101000000000000000000000000L  // D Read H (sHift register (ALU A)
#define RXE  0b00001110000000000000000000000000L  // E
#define RXF  0b00001111000000000000000000000000L  // F

// ROM2
#define C2   0b00000000100000000000000000000000L  // 80 Carry source select 2
#define C1   0b00000000010000000000000000000000L  // 40 Carry source select 1
#define C0   0b00000000001000000000000000000000L  // 20 Carry source select 0
#define HC   0b00000000000100000000000000000000L  // 10 H register use carry-in
#define DZ   0b00000000000010000000000000000000L  // 08 DXY Select zero
#define DY   0b00000000000001000000000000000000L  // 04 DXY Select X/Y
#define HL   0b00000000000000100000000000000000L  // 02 H register shift left
#define HR   0b00000000000000010000000000000000L  // 01 H register shift right

// ROM1
#define JC   0b00000000000000001000000000000000L  // 80 Jump if flag clear / V Clear (shared)
#define JZ   0b00000000000000000100000000000000L  // 40 Jump if Zero flag
#define JV   0b00000000000000000010000000000000L  // 20 Jump if oVerflow flag
#define JN   0b00000000000000000001000000000000L  // 10 Jump if Negative flag
#define FC   0b00000000000000000000100000000000L  // 08 set Carry flag
#define FZ   0b00000000000000000000010000000000L  // 04 set Zero flag
#define FV   0b00000000000000000000001000000000L  // 02 set oVerflow flag
#define FN   0b00000000000000000000000100000000L  // 01 set Negative flag

// ROM0
#define XX07 0b00000000000000000000000010000000L
#define PI   0b00000000000000000000000001000000L  // 40 PC Increment
#define N    0b00000000000000000000000000100000L  // 20 Next Instruction (clear RC)
#define AC   0b00000000000000000000000000010000L  // 10 ALU Carry flag
#define AS   0b00000000000000000000000000001000L  // 80 ALU force Subtraction
#define XX02 0b00000000000000000000010000000000L
#define SPI  0b00000000000000000000000000000010L  // 02 Stack Pointer Inc (dec)
#define SCE  0b00000000000000000000000000000001L  // 01 SP Count Enable

// Microinstruction bit aliases
#define RPI   RP | PI       // Read PC and post increment
#define F1    RP | WM       // Instruction fetch step 1
#define F2    RR | WI |PI   // Instruction fetch step 2
#define FA    RPI | WM      // Fetch argument (operand) step 1
#define SI    SCE | SPI     // Stack Pointer increment
#define SD    SCE           // Stack Pointer decrement
#define RDZ   RD|DZ         // Read D+zero (read D)
#define RDX   RD            // Read D+X
#define RDY   RD|DY         // Read D+Y
#define WH    HR|HL         // Write H
#define WAH   WA|WH         // Write A and also H
#define CC    0             // Carry source clear
#define CS    C0            // Carry source set
#define CA    C1            // Carry source ALU
#define CI    C1|C0         // Carry source ALU inverted
#define CL    C2            // Carry source shift left (H msb)
#define CR    C2|C0         // Carry source shift right (H lsb)
#define VC    JI            // V flag clear (shared control line)

// Note the F1 and F2 instructions: the PC is incremented during F2.  It would make more
// sense to increment the PC in F1 using RPI.  It was moved to F2 so that the PC does not
// increment during the self-test and other Loader operations.  While active, the Loader
// holds the Ring Counter in reset, forcing the F1 microinstruction to load from the ROMs.
//
// Note that the H register (sHift) has two control lines for left or right shift.  If
// both are HIGH then the register does a parallel load from the bus.  Because H is
// controlled by dedicated ROM lines instead of the 3-8 selectors, it can be loaded in the
// same cycle as another register.  By convention, H is a shadow of A and the microcode
// will always write to H whenever A is written.  Microcode can use H independently, but
// it must be restored from A at the completion of an instruction.  The user-accessible
// Accumulator register is A and the hardwired ALU A operand register is H.

#define FF  FC|FZ|FV|FN     // Set all flags
#define FCZN FC|FV|FN       // Set C,V,N flags
#define FZN FZ|FN           // Set Z,N flags

enum {
    // Status flag bits.  These are based at the least significant bit position, not at
    // their position in the address word.  These values can be used when iterating
    // between zero and NUM_FLAG_COMBOS.
    SF_Z = 0x01,        // Zero
    SF_C = 0x02,        // Carry
    SF_M = 0x04,        // Minus
    SF_V = 0x08         // oVerflow
};


// Instruction opcodes.  Those marked with an asterisk use the ALU and thus must have
// specific opcodes that match the bits that are hardwired from the IR to the ALU control.
enum {
    // 00 - 0f   A, Implied, Relative, and Indirect - ALU Arithmetic
    IP_NOP = 0x00,  // no operation
    IP_OUT = 0x01,  // output A
    IP_RTS = 0x0a,  // return from subroutine
    IN_JMP = 0x0b,  // jump
    AA_ASL = 0x0c,  // * arithmetic shift left A

    // 10 - 1f   A, Implied, Relative, and Indirect - ALU Logic
    AA_NOT = 0x10,  // * NOT A
    IP_PHA = 0x16,  // push A
    IP_CLC = 0x17,  // clear carry flag
    AA_LSR = 0x18,  // * logical shift left
    AA_ROL = 0x19,  // rotate left thru carry
    AA_ROR = 0x1a,  // rotate right thru carry
    AB_BIT = 0x1b,  // * bit test A with memory
    IP_PLA = 0x1e,  // pull A

    // 20 - 2f   Immediate - ALU Arithmetic
    AA_INA = 0x20,  // * increment A
    IM_LDA = 0x21,  // load immediate to A
    IM_LDX = 0x24,  // load immediate to X
    IM_SBC = 0x26,  // * subtract with carry
    IM_LDY = 0x27,  // load immediate to Y
    IM_ADC = 0x29,  // * add with carry A
    RE_BCC = 0x2a,  // branch on carry clear
    RE_BCS = 0x2b,  // branch on carry set
    AA_DEA = 0x2f,  // * decrement A

    // 30 - 3f  Immediate - ALU Logic
    IM_CMP = 0x31,  // compare A immediate
    IM_CPX = 0x32,  // compare X immediate
    IM_CPY = 0x33,  // compare Y immediate
    IM_EOR = 0x36,  // * XOR A
    IP_SEC = 0x37,  // set carry flag
    IM_AND = 0x3b,  // * AND A
    IM_ORA = 0x3e,  // * OR A

    // 40 - 4f   Absolute - ALU Arithmetic
    AB_INC = 0x40,  // * increment memory
    AB_LDA = 0x41,  // load A from memory
    AB_STA = 0x42,  // store A to memory
    AB_LDX = 0x44,  // load X
    AB_STX = 0x45,  // store X
    AB_SBC = 0x46,  // * subtract with carry memory
    AB_LDY = 0x47,  // load Y
    AB_STY = 0x48,  // store Y
    AB_ADC = 0x49,  // * add with carry memory
    AB_JSR = 0x4a,  // jump to subroutine
    AB_JMP = 0x4b,  // jump
    AB_ASL = 0x4c,  // * arithmetic shift left memory
    AB_DEC = 0x4f,  // * decrement memory

    // 50 - 5f  Absolute - ALU Logic
    AB_CMP = 0x51,  // compare A
    AB_CPX = 0x52,  // compare X
    AB_CPY = 0x53,  // compare Y
    AB_EOR = 0x56,  // * exlcusive OR A
    IP_CLV = 0x57,  // clear overflow flag
    AB_LSR = 0x58,  // logical shift right memory
    AB_ROL = 0x59,  // rotate left thru carry memory
    AB_ROR = 0x5a,  // rotate right thru carry memory
    AB_AND = 0x5b,  // * AND A
    AB_ORA = 0x5e,  // * OR A

    // 60 - 6f   Absolute+X - ALU Arithmetic
    AX_INC = 0x60,  // * increment memory
    AX_LDA = 0x61,  // load A from memory
    AX_STA = 0x62,  // store A to memory
    IP_TAX = 0x64,  // transfer A to X
    IP_TXA = 0x65,  // transfer X to A
    AX_SBC = 0x66,  // * subtract with carry memory
    AX_LDY = 0x67,  // load Y
    AX_STY = 0x68,  // store Y
    AX_ADC = 0x69,  // * add with carry memory
    RE_BNE = 0x6a,  // branch if not equal (zero clear)
    RE_BEQ = 0x6b,  // branch if equal (zero set)
    AX_ASL = 0x6c,  // * arithmetic shift left memory
    AX_DEC = 0x6f,  // * decrement memory

    // 70 - 7f  Absolute+X - ALU Logic
    AX_CMP = 0x71,  // compare A
    AX_EOR = 0x76,  // * exlcusive OR A
    AX_LSR = 0x78,  // logical shift right memory
    AX_ROL = 0x79,  // rotate left thru carry memory
    AX_ROR = 0x7a,  // rotate right thru carry memory
    AX_AND = 0x7b,  // * AND A
    AX_ORA = 0x7e,  // * OR A

    // 80 - 8f  Absolute+Y - ALU Arithmetic
    AY_LDA = 0x81,  // load A from memory
    AY_STA = 0x82,  // store A to memory
    AY_LDX = 0x84,  // load X
    AY_STX = 0x85,  // store X
    AY_SBC = 0x86,  // * subtract with carry memory
    IP_TAY = 0x87,  // transfer A to Y
    IP_TYA = 0x88,  // transfer Y to A
    AY_ADC = 0x89,  // * add with carry memory
    RE_BPL = 0x8a,  // branch if plus (minus clear)
    RE_BMI = 0x8b,  // branch if minus (minus set)

    // 90 - 9f  Absolute+Y - ALU Logic
    AY_CMP = 0x91,  // compare A
    AY_EOR = 0x96,  // * exlcusive OR A
    AY_AND = 0x9b,  // * AND A
    AY_ORA = 0x9e,  // * OR A

    // a0 - af  Indexed Indirect (X) - ALU Arithmetic
    IP_INX = 0xa0,  // * increment X
    IX_LDA = 0xa1,  // load A from memory
    IX_STA = 0xa2,  // store A to memory
    IP_TSX = 0xa4,  // transfer SP to X
    IP_TXS = 0xa5,  // transfer X to SP
    IX_SBC = 0xa6,  // * subtract with carry memory
    IX_ADC = 0xa9,  // * add with carry memory
    RE_BVC = 0xaa,  // branch if overflow clear
    RE_BVS = 0xab,  // branch if overflow set
    IP_DEX = 0xaf,  // * decrement X

    // b0 - bf  Indexed Indirect (X) - ALU Logic
    IX_CMP = 0xb1,  // compare A
    IX_EOR = 0xb6,  // * exlcusive OR A
    AB_JCC = 0xb7,  // jump if carry clear
    AB_JNE = 0xb8,  // jump if not equal (zero clear)
    AB_JPL = 0xb9,  // jump if plus (minus clear)
    AB_JVC = 0xba,  // jump if overflow clear
    IX_AND = 0xbb,  // * AND A
    IX_ORA = 0xbe,  // * OR A

    // c0 - cf  Indirect Indexed (Y) - ALU Arithmetic
    IP_INY = 0xc0,  // * increment Y
    IY_LDA = 0xc1,  // load A from memory
    IY_STA = 0xc2,  // store A to memory
    IY_SBC = 0xc6,  // * subtract with carry memory
    IY_ADC = 0xc9,  // * add with carry memory
    IP_DEY = 0xcf,  // * decrement Y

    // d0 - df  Indirect+Y - ALU Logic
    IY_CMP = 0xd1,  // compare A
    IY_EOR = 0xd6,  // * exlcusive OR A
    AB_JCS = 0xd7,  // jump if carry set
    AB_JEQ = 0xd8,  // jump if equal (zero set)
    AB_JMI = 0xd9,  // jump if minus (minus set)
    AB_JVS = 0xda,  // jump if overflow set
    IY_AND = 0xdb,  // * AND A
    IY_ORA = 0xde,  // * OR A

    // e0 - ef unused
    // f0 - ff unused
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

    // The ALU_DEF_CI flag indicates that an ALU instruction needs its microcode to set
    // the AC bit for the ALU CARRY-IN flag input. The ALU_DEF_CI flag is used only in the
    // definition table to assist in building the microcode.  It does not map to any
    // physical bits and is defined outside of the 8-bit opcode area to avoid confusion.
    //
    // The A operand always comes from the current contents of the A register.  Multiple
    // version of each instruction can be created (with  different opcodes) so that the B
    // operand could come from memory, immediate value, or other options.
    //
    // The ALU unary operations only work on the contents of the A register, so the
    // multiple addressing modes don't apply.  These instructions are defined in the
    // instruction template tables rather than being generated from the ALU tables.
    ALU_DEF_CI      = 0b000100000000
};

// This table contains the opcodes that are used for ALU instructions plus an additional
// bit to indicate if the AC flag should be set in the microcode steps for the
// instruction.  Many of the combinations of control bits in the ALU do not map to useful
// operations, so this is a small subset of the complete 74181 ALU operation set.  Note
// that some ALU operations in the table are commented out.  They are to show unary
// operations or ALU operations that might be used by the underlying microcode, but are
// not useful as standalone instructions.  For example, the all-zeroes or all-ones
// operations may be used by the microcode to put fixed values in registers.

// The aluInstructionDefinitions table is used to create multiple versions of each
// instruction with different argument processing. For example, "ADD A to immediate value"
// and  "ADD A to value from memory indexed by X".  All of the two argument ALU operations
// with the same addressing mode, like ADD immediate and XOR immediate, share the same
// microcode.  This code is generated programmatically based on a selected argument
// addressing mode.

uint16_t aluInstructionDefinitions[] = {
    // M=0 ALU Arithmetic operations
// 0,                                               // 00 INC - A plus 1
//                                 ALU_S1 | ALU_S0, // 03 zero - all zero
//  ALU_DEF_CI                   | ALU_S1 | ALU_S0, // 03 ones - all one
                          ALU_S2 | ALU_S1,          // 06 SUB - A minus B
    ALU_DEF_CI | ALU_S3                   | ALU_S0, // 09 ADD - A plus B
//  ALU_DEF_CI | ALU_S3 | ALU_S2,                   // 0c ASL - A + A
//  ALU_DEF_CI | ALU_S3 | ALU_S2 | ALU_S1 | ALU_S0, // 0f DEC - A minus 1

    // M=1 ALU Logic operations
//  ALU_M,                                          // 10 NOT - not A
    ALU_M               | ALU_S2 | ALU_S1,          // 16 XOR - A xor B
//  ALU_M      | ALU_S3          | ALU_S1,          // 1a B - returns B
    ALU_M      | ALU_S3          | ALU_S1 | ALU_S0, // 1b AND - A and B
    ALU_M      | ALU_S3 | ALU_S2 | ALU_S1           // 1e OR - A or B
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

// TODO - increase FLAG_COMBOS to 16 to accomodate the M and V flags.  This will consume
// the two ROM ID bits, so the code will no longer be able to build identical ROMs.
// instead, the programmer will use DIP switches to identify the ROM to be burned and will
// burn only the 8 control bits for that ROM.
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

// Instruction addressing modes
enum {
    ADDR_MODE_MASK = 0xe0,  // top 3 bits are address mode
    ADDR_MODE_00 = 0x00,    // No ALU instructions
    ADDR_MODE_IM = 0x20,    // #20 immediate value
    ADDR_MODE_AB = 0x40,    // $20 absolute memory location
    ADDR_MODE_AX = 0x60,    // $20,X absolute memory location + X
    ADDR_MODE_AY = 0x80,    // $20,Y absolute memory location + Y
    ADDR_MODE_IX = 0xa0,    // ($20,X) indexed indirect memory location + X
    ADDR_MODE_IY = 0xc0,    // ($20),Y indirect indexed memory location + Y
    ADDR_MODE_E0 = 0xe0     // No ALU instructions
};

typedef uint32_t microcode_t;
typedef microcode_t template_t[NUM_INSTRUCTIONS][NUM_STEPS];

// Note that the default conditional jump code is to increment the PC to skip the
// address argument and clear the ring counter to execute the next instruction.  This is
// effectively a NOP.  The customizeCodeGroup code will replace this with the microcode
// for an unconditional jump for flag combinations that match the type of jump.


// unary A instruction
// code[index][2] = RL | carry | WAH | FF | N;   // Write ALU result into A and flags

const template_t template0 PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, N,        0,          0,       0,        0,       0 }, // 00 IP_NOP
  { F1, F2, RA|WO|N,  0,          0,       0,        0,       0 }, // 01 IP_OUT
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 02
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 03
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 04
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 05
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 06
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 07
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 08
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 09
  { F1, F2, SD,       RS|WM,      RR|WP|N, 0,        0,       0 }, // 0a IP_RTS
  { F1, F2, FA,       RR|WM,      RR|WP|N, 0,        0,       0 }, // 0b IN_JMP
  { F1, F2, RL|WAH|AC|N, 0,       0,       0,        0,       0 }, // 0c AA_ASL *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 0d
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 0e
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 0f
};

const template_t template1 PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, RL|WAH|N, 0,          0,       0,        0,       0 }, // 10 AA_NOT *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 11
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 12
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 13
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 14
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 15
  { F1, F2, RS|WM,    RA|WR|SI|N, 0,       0,        0,       0 }, // 16 IP_PHA
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 17 IP_CLC $
  { F1, F2, HR,       RH|WA|FCZN|CR|N, 0,  0,        0,       0 }, // 18 AA_LSR
  { F1, F2, HL|HC,    RH|WA|FCZN|CL|N, 0,  0,        0,       0 }, // 19 AA_ROL
  { F1, F2, HR|HC,    RH|WA|FCZN|CR|N, 0,  0,        0,       0 }, // 1a AA_ROR
  { F1, F2, FA,       RR|WB,      FZN|N,   0,        0,       0 }, // 1b AB_BIT *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 1c
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 1d
  { F1, F2, SD,       RS|WM,      RR|WAH|N,0,        0,       0 }, // 1e IP_PLA
  { F1, F2, 0,        0,          0,       0,        0,       0 }  // 1f
};

// Immediate
const template_t template2 PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, RL|WAH|N, 0,          0,       0,        0,       0 }, // 20 AA_INA *
  { F1, F2, FA,       RR|WAH|N,   0,       0,        0,       0 }, // 21 IM_LDA
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 22
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 23
  { F1, F2, FA,       RR|WX|N,    0,       0,        0,       0 }, // 24 IM_LDX
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 25
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 26 IM_SBC *
  { F1, F2, FA,       RR|WY|N,    0,       0,        0,       0 }, // 21 IM_LDY
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 28
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 29 IM_ADC *
  { F1, F2, N,        0,          0,       0,        0,       0 }, // 2a RE_BCC
  { F1, F2, N,        0,          0,       0,        0,       0 }, // 2b RE_BCS
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 2c
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 2d
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 2e
  { F1, F2, RL|WAH|AC|N, 0,       0,       0,        0,       0 }  // 2f AA_DEA *
};

const template_t template3 PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 30
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 31 IM_CMP $
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 32 IM_CPX $
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 33 IM_CPY $
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 34
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 35
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 36 IM_EOR *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 37 IP_SEC $
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 38
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 39
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 3a
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 3b IM_AND *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 3c
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 3d
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 3e IM_ORA *
  { F1, F2, 0,        0,          0,       0,        0,       0 }  // 3f
};

// Absolute
const template_t template4 PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, FA,       RR|WM,      RR|WH,   RL|WR,    RA|WH|N, 0 }, // 40 AB_INC *
  { F1, F2, FA,       RR|WM,      RR|WAH|N,0,        0,       0 }, // 41 AB_LDA
  { F1, F2, FA,       RR|WM,      RA|WR|N, 0,        0,       0 }, // 42 AB_STA
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 43
  { F1, F2, FA,       RR|WM,      RR|WX|N, 0,        0,       0 }, // 44 AB_LDX
  { F1, F2, FA,       RR|WM,      RX|WR|N, 0,        0,       0 }, // 45 AB_STX
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 46 AB_SBC *
  { F1, F2, FA,       RR|WM,      RR|WY|N, 0,        0,       0 }, // 47 AB_LDY
  { F1, F2, FA,       RR|WM,      RY|WR|N, 0,        0,       0 }, // 48 AB_STY
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 49 AB_ADC *
  { F1, F2, FA,       RR|WB,      RS|WM,   WR|RP|SI, RB|WP|N, 0 }, // 4a AB_JSR
  { F1, F2, FA,       RR|WP|N,    0,       0,        0,       0 }, // 4b AB_JMP
  { F1, F2, FA,       RR|WM,      RR|WH,   RL|WR|AC, RA|WH|N, 0 }, // 4c AB_ASL *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 4d
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 4e
  { F1, F2, FA,       RR|WM,      RR|WH,   RL|WR|AC, RA|WH|N, 0 }  // 4f AB_DEC *
};

const template_t template5 PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 50
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 51 AB_CMP $
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 52 AB_CPX $
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 53 AB_CPY $
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 54
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 55
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 56 AB_EOR *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 57 IP_CLV $
  { F1, F2, FA,       RR|WM,      RR|WH,   HR,       RH|WR|FCZN|CR,  RA|WH|N }, // 58 AB_LSR
  { F1, F2, FA,       RR|WM,      RR|WH,   HL|HC,    RH|WR|FCZN|CL,  RA|WH|N }, // 59 AB_ROL
  { F1, F2, FA,       RR|WM,      RR|WH,   HR|HC,    RH|WR|FCZN|CR,  RA|WH|N }, // 5a AB_ROR
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 5b AB_AND *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 5c
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 5d
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 5e AB_ORA *
  { F1, F2, 0,        0,          0,       0,        0,       0 }  // 5f
};

// Absolute + X
// Single byte operations, like INC, DEX, and ASL, don't fit in the number of steps
// available for Absolute+ modes because they need to save and restore the A register
// around using it.  Here it is with 9 steps.
//  { F1, F2, FA,       RR|WD,      RDX|WM,  RA|WB,    RR|WA,   RL|WR,   RB|WAH,N }, // 60 AX_INC *
// One possible solution is to build a new A register as an independent register and have
// the existing A that is hardwired to the ALU become the sHadow A register (H).  This
// register can be written independently, but it also writes any time A writes.  So H will
// have the same value as A unless it is explicitly written.  Any code that writes H needs
// to manually write it back from A at the end of its microcode.  This takes one fewer
// step because A already has the value that needs to be restored so there is no need for
// a save before using H.  Here's the same code with H as a hardware shadow of A.
//  { F1, F2, FA,       RR|WD,      RDX|WM,  RR|WH,    RL|WR,   RA|WH,N }, // 60 AX_INC *
// Explore this after the ROL/ROR/LSR are coded to make sure they don't have issues.
const template_t template6 PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, FA,       RR|WD,      RDX|WM,  RR|WH,    RL|WR,   RA|WH|N }, // 60 AX_INC *
  { F1, F2, FA,       RR|WD,      RDX|WM,  RR|WAH|N, 0,       0 }, // 61 AX_LDA
  { F1, F2, FA,       RR|WD,      RDX|WM,  RA|WR|N,  0,       0 }, // 62 AX_STA
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 63
  { F1, F2, RA|WX|N,  0,          0,       0,        0,       0 }, // 64 IP_TAX
  { F1, F2, RX|WAH|N, 0,          0,       0,        0,       0 }, // 65 IP_TXA
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 66 AX_SBC *
  { F1, F2, FA,       RR|WD,      RDX|WM,  RR|WY|N,  0,       0 }, // 67 AX_LDY
  { F1, F2, FA,       RR|WD,      RDX|WM,  RY|WR|N,  0,       0 }, // 68 AX_STY
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 69 AX_ADC *
  { F1, F2, N,        0,          0,       0,        0,       0 }, // 6a RE_BNE
  { F1, F2, N,        0,          0,       0,        0,       0 }, // 6b RE_BEQ
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 6c AX_ASL *$ (too many steps)
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 6d
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 6e
  { F1, F2, FA,       RR|WD,      RDX|WM,  RR|WH,    RL|WR,   RA|WH|N } // 6f AX_DEC *
};

const template_t template7 PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 70
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 71 AX_CMP $
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 72
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 73
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 74
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 75
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 76 AX_EOR *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 77
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 78 AX_LSR $
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 79 AX_ROL $
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 7a AX_ROR $
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 7b AX_AND *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 7c
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 7d
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 7e AX_ORA *
  { F1, F2, 0,        0,          0,       0,        0,       0 }  // 7f
};

// Absolute + Y
const template_t template8 PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 80
  { F1, F2, FA,       RR|WD,      RDY|WM,  RR|WAH|N, 0,       0 }, // 81 AY_LDA
  { F1, F2, FA,       RR|WD,      RDY|WM,  RA|WR|N,  0,       0 }, // 82 AY_STA
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 83
  { F1, F2, FA,       RR|WD,      RDY|WM,  RR|WX|N,  0,       0 }, // 84 AY_LDX
  { F1, F2, FA,       RR|WD,      RDY|WM,  RR|WX|N,  0,       0 }, // 85 AY_STX
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 86 AY_SBC *
  { F1, F2, RA|WY|N,  0,          0,       0,        0,       0 }, // 87 IP_TAY
  { F1, F2, RY|WAH|N,  0,          0,       0,       0,       0 }, // 88 IP_TYA
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 89 AY_ADC *
  { F1, F2, N,        0,          0,       0,        0,       0 }, // 8a RE_BPL $
  { F1, F2, N,        0,          0,       0,        0,       0 }, // 8b RE_BMI $
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 8c
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 8d
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 8e
  { F1, F2, 0,        0,          0,       0,        0,       0 }  // 8f
};

const template_t template9 PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 90
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 91 AY_CMP $
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 92
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 93
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 94
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 95
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 96 AY_EOR *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 97
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 98
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 99
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 9a
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 9b AY_AND *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 9c
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // 9d
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // 9e AY_ORA *
  { F1, F2, 0,        0,          0,       0,        0,       0 }  // 9f
};

// Indexed Indirect (X)
const template_t templateA PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, RX|WH,    RL|WX,      RA|WH|N, 0,        0,       0 }, // a0 IP_INX *
  { F1, F2, FA,       RR|WD,      RDX|WM,  RR|WM,    RR|WAH|N,0 }, // a1 IX_LDA
  { F1, F2, FA,       RR|WD,      RDX|WM,  RR|WM,    RA|WR|N, 0 }, // a2 IX_STA
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // a3
  { F1, F2, RS|WX|N,  0,          0,       0,        0,       0 }, // a4 IP_TSX
  { F1, F2, RX|WS|N,  0,          0,       0,        0,       0 }, // a5 IP_TXS
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // a6 IX_SBC *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // a7
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // a8
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // a9 IX_ADC *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // aa RE_BVC $
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // ab RE_BVS $
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // ac
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // ad
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // ae
  { F1, F2, RX|WH,    RL|WX|AC,   RA|WH|N, 0,        0,       0 }  // af IP_DEX *
};

const template_t templateB PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // b0
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // b1 IX_CMP $
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // b2
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // b3
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // b4
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // b5
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // b6 IX_EOR *
  { F1, F2, N,        0,          0,       0,        0,       0 }, // b7 AB_JCC
  { F1, F2, N,        0,          0,       0,        0,       0 }, // b8 AB_JNE
  { F1, F2, N,        0,          0,       0,        0,       0 }, // b9 AB_JPL $
  { F1, F2, N,        0,          0,       0,        0,       0 }, // ba AB_JVC $
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // bb IX_AND *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // bc
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // bd
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // be IX_ORA *
  { F1, F2, 0,        0,          0,       0,        0,       0 }  // bf
};

// Indirect Indexed (Y)
const template_t templateC PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, RY|WH,    RL|WY,      RA|WH|N, 0,        0,       0 }, // c0 IP_INY *
  { F1, F2, FA,       RR|WM,      RR|WD,   RDY|WM,   RR|WAH|N,0 }, // c1 IY_LDA
  { F1, F2, FA,       RR|WM,      RR|WD,   RDY|WM,   RA|WR|N, 0 }, // c2 IY_STA
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // c3
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // c4
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // c5
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // c6 IY_SBC *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // c7
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // c8
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // c9 IY_ADC *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // ca
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // cb
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // cc
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // cd
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // ce
  { F1, F2, RY|WH,    RL|WY|AC,   RA|WH|N, 0,        0,       0 }  // cf IP_DEY *
};

const template_t templateD PROGMEM = {
//  0   1   2         3           4        5         6        7
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // d0
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // d1 IY_CMP $
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // d2
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // d3
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // d4
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // d5
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // d6 IY_EOR *
  { F1, F2, N,        0,          0,       0,        0,       0 }, // b7 AB_JCS
  { F1, F2, N,        0,          0,       0,        0,       0 }, // b8 AB_JEQ
  { F1, F2, N,        0,          0,       0,        0,       0 }, // b9 AB_JMI $
  { F1, F2, N,        0,          0,       0,        0,       0 }, // ba AB_JVS $
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // db IY_AND *
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // dc
  { F1, F2, 0,        0,          0,       0,        0,       0 }, // dd
  { 0,  0,  0,        0,          0,       0,        0,       0 }, // de IY_ORA *
  { F1, F2, 0,        0,          0,       0,        0,       0 }  // df
};

const template_t * templates[] = { &template0, &template1, &template2, &template3,
                                   &template4, &template5, &template6, &template7,
                                   &template8, &template9, &templateA, &templateB,
                                   &templateC, &templateD };

// A buffer to hold a group of instruction microcode words that have been
// built from a template or from the ALU building code.
microcode_t code[NUM_INSTRUCTIONS][NUM_STEPS];

// A buffer to hold an 8-bit slice of a group of microinstruction words to burn into a
// section of ROM.  This buffer allows the use of the block write capability of the
// 28C256 chips, which results in a significant speed up of the ROM burn times.  The
// alternative without the buffers would be to step through the 32-bit words and burn
// them as 4 individual single-byte writes.
uint8_t burnBuffer[NUM_INSTRUCTIONS * NUM_STEPS];


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
void burnInstructionGroups(uint8_t group, const char * name) {
    burnInstructionGroup(group,   name);  // Arithmetic
    burnInstructionGroup(group+1, name);  // Logical
}

void burnInstructionGroup(uint8_t group, const char * name) {
    Serial.print(F("burning "));
    Serial.print(group);
    Serial.print(F(" - "));
    Serial.println(name);
    for (int flags = 0; (flags < NUM_FLAG_COMBOS); flags++) {
        buildInstructions(group);
        customizeCodeGroup(flags, group);
        burnCodeBuffer(flags, group);
    }
}

void buildInstructions(uint8_t group) {
    // Initialize the code buffer with values for the entries that will not get
    // overwritten by ALU instructions.
    if (group < (sizeof(templates) / sizeof(*templates))) {
        // Initialize the code buffer from a template.
        memcpy_P(code, templates[group], sizeof(code));
    } else {
        // Initialize the code buffer with a NOP instruction.
        for (int i = 0; (i < NUM_INSTRUCTIONS); i++) {
            code[i][0] = F1;
            code[i][1] = F2;
            code[i][2] = N,
            code[i][3] = code[i][4] = code[i][5] = code[i][6] = code[i][7] = 0;
        }
    }

    uint8_t groupBits = makeOpcodeGroupBits(group);
    uint8_t addrMode = groupBits & ADDR_MODE_MASK;
    // Skip ALU instruction generation for modes with no two-argument ALU instructions and
    // just use the microcode from the templates.
    if ((addrMode == ADDR_MODE_00) || (addrMode == ADDR_MODE_E0)) return;

    // Walk the ALU instruction definitions table and generate microcode. The low
    // order bit of the groupBits is the position of the ALU_M bit that indicates an
    // arithmetic or logical instruction.  The table has both types, so only generate the
    // set of instructions that match the ALU_M bit for the group.

    // For each ALU instruction in the group being processed, generate a set of steps to
    // fetch the operand into B and then store the ALU result back into A. The mode and
    // select lines on the ALU chips are wired to the instruction register, so the only
    // code differences in the instructions are the setting of the ALU CARRY-IN bit.
    for (unsigned i = 0; (i < (sizeof(aluInstructionDefinitions) / sizeof(*aluInstructionDefinitions))); i++) {
        uint16_t def = aluInstructionDefinitions[i];
        uint8_t opcode = def & OPCODE_MASK;
        if ((opcode & ALU_M) == (groupBits & ALU_M)) {
            unsigned index = opcode & INSTRUCTION_MASK;
            microcode_t carry = (def & ALU_DEF_CI) ? AC : 0;
// TODO - need customize code for ADC and SBC to set the carry based on the physical flag.
//        not yet - need CLC first also inverter on flag output line to match 6502 polarity.
            code[index][5] = code[index][6] = code[index][7] = 0;
            code[index][0] = F1;            // Fetch instruction from memory
            code[index][1] = F2;            // Opcode into IR (sets ALU mode and S bits)
            switch (addrMode) {
            case ADDR_MODE_IM: // Get B operand from immediate value
                code[index][2] = RPI | WM;          // Get next address from PC
                code[index][3] = RR | WB;           // Read operand into B (immediate data)
                code[index][4] = RL|carry|WAH|FF|N; // Write ALU result into A and flags
                break;
            case ADDR_MODE_AB: // Get B operand from specified memory location
                code[index][2] = RPI | WM;          // Get next address from PC
                code[index][3] = RR | WM;           // Read address of operand into MAR
                code[index][4] = RR | WB;           // Read operand into B
                code[index][5] = RL|carry|WAH|FF|N; // Write ALU result into A and flags
                break;
            case ADDR_MODE_AX: // Absolute+X
                code[index][2] = RPI | WM;          // Get next address from PC
                code[index][3] = RR | WD;           // Read address of operand into D
                code[index][4] = RDX | WM;          // Read addr+X from adder into MAR
                code[index][5] = RR | WB;           // Read operand into B
                code[index][6] = RL|carry|WAH|FF|N; // Write ALU result into A and flags
                break;
            case ADDR_MODE_AY: // Absolute+Y
                code[index][2] = RPI | WM;          // Get next address from PC
                code[index][3] = RR | WD;           // Read address of operand into D
                code[index][4] = RDY | WM;          // Read addr+Y from adder into MAR
                code[index][5] = RR | WB;           // Read operand into B
                code[index][6] = RL|carry|WAH|FF|N; // Write ALU result into A and flags
                break;
            case ADDR_MODE_IX: // Indexed Indirect X
//              { FA,       RR|WD,      RDX|WM, RR|WM,   RR|WAH|N, 0 }, // a1 IX_LDA
                code[index][2] = RPI | WM;          // Get next address from PC
                code[index][3] = RR | WD;           // Read address of operand into D
                code[index][4] = RDX | WM;          // Read addr+X from adder into MAR
                code[index][5] = RR | WM;           // Read pointer into MAR
                code[index][6] = RR | WB;           // Read operand into B
                code[index][7] = RL|carry|WAH|FF|N; // Write ALU result into A and flags
                break;
            case ADDR_MODE_IY: // Indirect Indexed Y
//              { F1, F2, FA,       RR|WM,     RR|WD,   RDY|WM,  RR|WAH|N, 0 }, // c1 IY_LDA
                code[index][2] = RPI | WM;          // Get next address from PC
                code[index][3] = RR | WM;           // Read pointer into MAR
                code[index][4] = RR | WD;           // Read address of operand into D
                code[index][5] = RDY | WM;          // Read addr+Y from adder into MAR
                code[index][6] = RR | WB;           // Read operand into B
                code[index][7] = RL|carry|WAH|FF|N; // Write ALU result into A and flags
                break;
            }
        }
    }
}

// Modify the microcode for a NOP to convert it to an absolute JMP.
// Used for all of the conditional jump instructions.
void buildAbJmpInstruction(uint16_t instr) {
    code[instr][2] = RPI | WM;
    code[instr][3] = RR | WP | N;
}
// Modify the microcode for a NOP to convert it to a relative JMP.
// Used for all of the conditional branch instructions.
void buildReJmpInstruction(uint16_t instr) {
    code[instr][2] = RPI | WM;
    code[instr][3] = RR | WD;       // offset to adder D
    code[instr][4] = RX | WB;       // save X
    code[instr][5] = RP | WX;
    code[instr][6] = RDX | WP;      // PC + offset (X + D) to PC
    code[instr][7] = RB | WX | N;   // restore previous X
}


void customizeCodeGroup(uint16_t flags, uint16_t group) {
    for (uint16_t instr = 0; (instr < NUM_INSTRUCTIONS); instr++) {
        uint16_t opcode = makeOpcode(group, instr);
        switch (opcode) {
        // Default template code for a conditional jmp or branch is a NOP.  Build the
        // appropriate absolute or relative jmp microcode if the flag condition is met.
        case AB_JCC: if (!(flags & SF_C)) buildAbJmpInstruction(instr); break;
        case AB_JNE: if (!(flags & SF_Z)) buildAbJmpInstruction(instr); break;
        case AB_JPL: if (!(flags & SF_M)) buildAbJmpInstruction(instr); break;
        case AB_JVC: if (!(flags & SF_V)) buildAbJmpInstruction(instr); break;
        case AB_JCS: if (flags & SF_C)    buildAbJmpInstruction(instr); break;
        case AB_JEQ: if (flags & SF_Z)    buildAbJmpInstruction(instr); break;
        case AB_JMI: if (flags & SF_M)    buildAbJmpInstruction(instr); break;
        case AB_JVS: if (flags & SF_V)    buildAbJmpInstruction(instr); break;
        case RE_BCC: if (!(flags & SF_C)) buildReJmpInstruction(instr); break;
        case RE_BNE: if (!(flags & SF_Z)) buildReJmpInstruction(instr); break;
        case RE_BPL: if (!(flags & SF_M)) buildReJmpInstruction(instr); break;
        case RE_BVC: if (!(flags & SF_V)) buildReJmpInstruction(instr); break;
        case RE_BCS: if (flags & SF_C)    buildReJmpInstruction(instr); break;
        case RE_BEQ: if (flags & SF_Z)    buildReJmpInstruction(instr); break;
        case RE_BMI: if (flags & SF_M)    buildReJmpInstruction(instr); break;
        case RE_BVS: if (flags & SF_V)    buildReJmpInstruction(instr); break;
        default:
            break;
        }
    }
}

void burnCodeBuffer(uint16_t flags, uint8_t group) {
    // Slice a group of 32-bit instruction control words into individual 8-bit chunks and
    // burn them into the appropriate position in the ROM.
    uint16_t groupBits = makeOpcodeGroupBits(group);
    for (uint16_t rom = 0; (rom < NUM_ROMS); rom++) {
        uint16_t shift = rom << 3;  // Shift 8 bits for each ROM position
        for (int instr = 0; instr < NUM_INSTRUCTIONS; instr++) {
            for (int step = 0; step < NUM_STEPS; step++) {
                burnBuffer[instr * NUM_STEPS + step] = uint8_t(code[instr][step] >> shift);
            }
        }
        if (!writeData(burnBuffer, sizeof(burnBuffer), makeAddress(rom, flags, groupBits))) {
            fail();
        }
    }
}


void burnMicrocodeRoms() {
    // Note that each call to burnAluInstructionGroups burns two groups of instructions.
    burnInstructionGroups(0x0, "Address Mode 0");
    burnInstructionGroups(0x2, "Immediate");
    burnInstructionGroups(0x4, "Absolute");
    burnInstructionGroups(0x6, "Absolute+X");
    burnInstructionGroups(0x8, "Absolute+Y");
    burnInstructionGroups(0xa, "Indexed Indirect (a,x)");
    burnInstructionGroups(0xc, "Indirect Indexed (a),y");
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
    char cb[50];
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

    if (!status) {
        Serial.print(F("burnBlock fail at 0x"));
        Serial.println(address, HEX);
        for (uint32_t ix = 0; (ix < len); ix++) {
            uint8_t b = readByte(address+ix);
            if (b != data[ix]) {
                sprintf(cb, "addr=%04x, data=%0x2, readback=%02x", unsigned(address+ix), unsigned(data[ix]), unsigned(b));
                Serial.println(cb);
                break;
            }
        }
    }

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

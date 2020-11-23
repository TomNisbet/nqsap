// Instruction opcodes.  Those marked with an asterisk use the ALU and thus must have
// specific opcodes that match the bits that are hardwired from the IR to the ALU control.
enum {
    // 00 - 0f   A, Implicit, Relative, and Indirect - ALU Arithmetic
    IP_NOP = 0x00,  // no operation
    IP_OUT = 0x01,  // output A
    IP_RTS = 0x0a,  // return from subroutine
    IN_JMP = 0x0b,  // jump
    AA_ASL = 0x0c,  // * arithmetic shift left A

    // 10 - 1f   A, Implicit, Relative, and Indirect - ALU Logic
    AA_NOT = 0x10,  // * NOT A
    IP_PHA = 0x16,  // push A
    IP_CLC = 0x17,  // clear carry flag
    AA_LSR = 0x18,  // * logical shift left
    AA_ROL = 0x19,  // rotate left thru carry
    AA_ROR = 0x1a,  // rotate right thru carry
    AB_BIT = 0x1b,  // * bit test A with memory
    IP_PLA = 0x1e,  // pull A
    IP_HLT = 0x1f,  // halt

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

    // 30 - 3f   Immediate - ALU Logic
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

    // 50 - 5f   Absolute - ALU Logic
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

    // 70 - 7f   Absolute+X - ALU Logic
    AX_CMP = 0x71,  // compare A
    AX_EOR = 0x76,  // * exlcusive OR A
    AX_LSR = 0x78,  // logical shift right memory
    AX_ROL = 0x79,  // rotate left thru carry memory
    AX_ROR = 0x7a,  // rotate right thru carry memory
    AX_AND = 0x7b,  // * AND A
    AX_ORA = 0x7e,  // * OR A

    // 80 - 8f   Absolute+Y - ALU Arithmetic
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

    // 90 - 9f   Absolute+Y - ALU Logic
    AY_CMP = 0x91,  // compare A
    AY_EOR = 0x96,  // * exlcusive OR A
    AY_AND = 0x9b,  // * AND A
    AY_ORA = 0x9e,  // * OR A

    // a0 - af   Indexed Indirect (X) - ALU Arithmetic
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

    // b0 - bf   Indexed Indirect (X) - ALU Logic
    IX_CMP = 0xb1,  // compare A
    IX_EOR = 0xb6,  // * exlcusive OR A
    AB_JCC = 0xb7,  // jump if carry clear
    AB_JNE = 0xb8,  // jump if not equal (zero clear)
    AB_JPL = 0xb9,  // jump if plus (minus clear)
    AB_JVC = 0xba,  // jump if overflow clear
    IX_AND = 0xbb,  // * AND A
    IX_ORA = 0xbe,  // * OR A

    // c0 - cf   Indirect Indexed (Y) - ALU Arithmetic
    IP_INY = 0xc0,  // * increment Y
    IY_LDA = 0xc1,  // load A from memory
    IY_STA = 0xc2,  // store A to memory
    IY_SBC = 0xc6,  // * subtract with carry memory
    IY_ADC = 0xc9,  // * add with carry memory
    IP_DEY = 0xcf,  // * decrement Y

    // d0 - df   Indirect+Y - ALU Logic
    IY_CMP = 0xd1,  // compare A
    IY_EOR = 0xd6,  // * exlcusive OR A
    AB_JCS = 0xd7,  // jump if carry set
    AB_JEQ = 0xd8,  // jump if equal (zero set)
    AB_JMI = 0xd9,  // jump if minus (minus set)
    AB_JVS = 0xda,  // jump if overflow set
    IY_AND = 0xdb,  // * AND A
    IY_ORA = 0xde,  // * OR A
};

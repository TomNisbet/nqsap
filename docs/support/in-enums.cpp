// Instruction opcodes.  Those marked with an asterisk use the ALU and thus must have
// specific opcodes that match the bits that are hardwired from the IR to the ALU control.
enum {
    // 00 - 0f   A, Implicit, Relative, and Indirect - ALU Arithmetic
    IP_NOP = 0x00,  // no operation
    IP_OUT = 0x01,  // output A
    IP_CLC = 0x03,  // * clear carry flag
    IM_CPX = 0x06,  // * compare X immediate
    IM_CPY = 0x07,  // * compare Y immediate
    IP_PHP = 0x09,  // push PS
    IP_RTS = 0x0a,  // return from subroutine
    IN_JMP = 0x0b,  // jump
    AA_ASL = 0x0c,  // * arithmetic shift left A
    IP_PLP = 0x0f,  // pull PS

    // 10 - 1f   A, Implicit, Relative, and Indirect - ALU Logic
    AA_NOT = 0x10,  // * NOT A
    IP_PHA = 0x16,  // push A
    AA_LSR = 0x18,  // * logical shift left
    AA_ROL = 0x19,  // rotate left thru carry
    AA_ROR = 0x1a,  // rotate right thru carry
    AB_BIT = 0x1b,  // * bit test A with memory
    RE_BCS = 0x1c,  // branch if carry set
    AB_JCS = 0x1d,  // jump if carry set
    IP_PLA = 0x1e,  // pull A

    // 20 - 2f   Immediate - ALU Arithmetic
    AA_INA = 0x20,  // * increment A
    IM_LDA = 0x21,  // load immediate to A
    IP_SEC = 0x23,  // * set carry flag
    IM_SBC = 0x26,  // * subtract with carry
    IM_CMP = 0x27,  // * compare A immediate
    IM_ADC = 0x29,  // * add with carry A
    AA_DEA = 0x2f,  // * decrement A

    // 30 - 3f   Immediate - ALU Logic
    IM_LDX = 0x31,  // load immediate to X
    IM_LDY = 0x33,  // load immediate to Y
    IM_EOR = 0x36,  // * XOR A
    IM_AND = 0x3b,  // * AND A
    RE_BCC = 0x3c,  // branch if carry clear
    AB_JCC = 0x3d,  // jump if carry clear
    IM_ORA = 0x3e,  // * OR A

    // 40 - 4f   Absolute - ALU Arithmetic
    AB_INC = 0x40,  // * increment memory
    AB_LDA = 0x41,  // load A from memory
    AB_STA = 0x42,  // store A to memory
    IP_CLV = 0x43,  // * clear overflow flag
    AB_SBC = 0x46,  // * subtract with carry memory
    AB_CMP = 0x47,  // * compare A
    AB_ADC = 0x49,  // * add with carry memory
    AB_JSR = 0x4a,  // jump to subroutine
    AB_JMP = 0x4b,  // jump
    AB_ASL = 0x4c,  // * arithmetic shift left memory
    AB_DEC = 0x4f,  // * decrement memory

    // 50 - 5f   Absolute - ALU Logic
    AB_LDX = 0x51,  // load X
    AB_STX = 0x52,  // store X
    AB_LDY = 0x53,  // load Y
    AB_STY = 0x54,  // store Y
    AB_EOR = 0x56,  // * exlcusive OR A
    AB_LSR = 0x58,  // logical shift right memory
    AB_ROL = 0x59,  // rotate left thru carry memory
    AB_ROR = 0x5a,  // rotate right thru carry memory
    AB_AND = 0x5b,  // * AND A
    RE_BEQ = 0x5c,  // branch if equal (zero set)
    AB_JEQ = 0x5d,  // jump if equal (zero set)
    AB_ORA = 0x5e,  // * OR A

    // 60 - 6f   Absolute+X - ALU Arithmetic
    AX_INC = 0x60,  // * increment memory
    AX_LDA = 0x61,  // load A from memory
    AX_STA = 0x62,  // store A to memory
    AX_SBC = 0x66,  // * subtract with carry memory
    AX_CMP = 0x67,  // * compare A
    AX_ADC = 0x69,  // * add with carry memory
    AX_ASL = 0x6c,  // * arithmetic shift left memory
    AX_DEC = 0x6f,  // * decrement memory

    // 70 - 7f   Absolute+X - ALU Logic
    IP_TAX = 0x71,  // transfer A to X
    IP_TXA = 0x72,  // transfer X to A
    AX_LDY = 0x73,  // load Y
    AX_STY = 0x74,  // store Y
    AX_EOR = 0x76,  // * exlcusive OR A
    AX_LSR = 0x78,  // logical shift right memory
    AX_ROL = 0x79,  // rotate left thru carry memory
    AX_ROR = 0x7a,  // rotate right thru carry memory
    AX_AND = 0x7b,  // * AND A
    RE_BNE = 0x7c,  // branch if not equal (zero clear)
    AB_JNE = 0x7d,  // jump if not equal (zero clear)
    AX_ORA = 0x7e,  // * OR A

    // 80 - 8f   Absolute+Y - ALU Arithmetic
    AY_LDA = 0x81,  // load A from memory
    AY_STA = 0x82,  // store A to memory
    AY_SBC = 0x86,  // * subtract with carry memory
    AY_CMP = 0x87,  // * compare A
    AY_ADC = 0x89,  // * add with carry memory

    // 90 - 9f   Absolute+Y - ALU Logic
    AY_LDX = 0x91,  // load X
    AY_STX = 0x92,  // store X
    IP_TAY = 0x93,  // transfer A to Y
    IP_TYA = 0x94,  // transfer Y to A
    AY_EOR = 0x96,  // * exlcusive OR A
    AY_AND = 0x9b,  // * AND A
    RE_BVS = 0x9c,  // branch if overflow set
    AB_JVS = 0x9d,  // jump if overflow set
    AY_ORA = 0x9e,  // * OR A

    // a0 - af   Indexed Indirect (X) - ALU Arithmetic
    IP_INX = 0xa0,  // * increment X
    IX_LDA = 0xa1,  // load A from memory
    IX_STA = 0xa2,  // store A to memory
    IX_SBC = 0xa6,  // * subtract with carry memory
    IX_CMP = 0xa7,  // * compare A
    IX_ADC = 0xa9,  // * add with carry memory
    IP_DEX = 0xaf,  // * decrement X

    // b0 - bf   Indexed Indirect (X) - ALU Logic
    IP_TSX = 0xb1,  // transfer SP to X
    IP_TXS = 0xb2,  // transfer X to SP
    IX_EOR = 0xb6,  // * exlcusive OR A
    IX_AND = 0xbb,  // * AND A
    RE_BVC = 0xbc,  // branch if overflow clear
    AB_JVC = 0xbd,  // jump if overflow clear
    IX_ORA = 0xbe,  // * OR A

    // c0 - cf   Indirect Indexed (Y) - ALU Arithmetic
    IP_INY = 0xc0,  // * increment Y
    IY_LDA = 0xc1,  // load A from memory
    IY_STA = 0xc2,  // store A to memory
    IY_SBC = 0xc6,  // * subtract with carry memory
    IY_CMP = 0xc7,  // * compare A
    IY_ADC = 0xc9,  // * add with carry memory
    IP_DEY = 0xcf,  // * decrement Y

    // d0 - df   Indirect+Y - ALU Logic
    IY_EOR = 0xd6,  // * exlcusive OR A
    IY_AND = 0xdb,  // * AND A
    RE_BMI = 0xdc,  // branch if plus (negative set)
    AB_JMI = 0xdd,  // jump if plus (negative set)
    IY_ORA = 0xde,  // * OR A

    // e0 - ef   Misc
    AB_CPX = 0xe6,  // * compare X
    AB_CPY = 0xe7,  // * compare Y

    // f0 - ff   Misc
    RE_BPL = 0xfc,  // branch if plus (negative clear)
    AB_JPL = 0xfd,  // jump if plus (negative clear)
};

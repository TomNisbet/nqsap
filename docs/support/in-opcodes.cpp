// Opcode comments - aid in verification of microcode tables
    // 00 IP_NOP  3
    // 01 IP_OUT  3
    // 02
    // 03 IP_CLC * 3
    // 04
    // 05
    // 06 IM_CPX * 7
    // 07 IM_CPY * 7
    // 08
    // 09 IP_PHP  4
    // 0a IP_RTS  5
    // 0b IN_JMP  5
    // 0c AA_ASL * 3
    // 0d
    // 0e
    // 0f IP_PLP  5
    // 10 AA_NOT * 3
    // 11
    // 12
    // 13
    // 14
    // 15
    // 16 IP_PHA  4
    // 17
    // 18 AA_LSR * 4
    // 19 AA_ROL  4
    // 1a AA_ROR  4
    // 1b AB_BIT * 5
    // 1c RE_BCC  8
    // 1d AB_JCC  4
    // 1e IP_PLA  5
    // 1f
    // 20 AA_INA * 3
    // 21 IM_LDA  4
    // 22
    // 23 IP_SEC * 3
    // 24
    // 25
    // 26 IM_SBC * 5
    // 27 IM_CMP * 5
    // 28
    // 29 IM_ADC * 5
    // 2a
    // 2b
    // 2c
    // 2d
    // 2e
    // 2f AA_DEA * 3
    // 30
    // 31 IM_LDX  4
    // 32
    // 33 IM_LDY  4
    // 34
    // 35
    // 36 IM_EOR * 5
    // 37
    // 38
    // 39
    // 3a
    // 3b IM_AND * 5
    // 3c RE_BCS  8
    // 3d AB_JCS  4
    // 3e IM_ORA * 5
    // 3f
    // 40 AB_INC * 7
    // 41 AB_LDA  5
    // 42 AB_STA  5
    // 43 IP_CLV * 3
    // 44
    // 45
    // 46 AB_SBC * 6
    // 47 AB_CMP * 6
    // 48
    // 49 AB_ADC * 6
    // 4a AB_JSR  7
    // 4b AB_JMP  4
    // 4c AB_ASL * 7
    // 4d
    // 4e
    // 4f AB_DEC * 7
    // 50
    // 51 AB_LDX  5
    // 52 AB_STX  5
    // 53 AB_LDY  5
    // 54 AB_STY  5
    // 55
    // 56 AB_EOR * 6
    // 57
    // 58 AB_LSR  8
    // 59 AB_ROL  8
    // 5a AB_ROR  8
    // 5b AB_AND * 6
    // 5c RE_BNE  8
    // 5d AB_JNE  4
    // 5e AB_ORA * 6
    // 5f
    // 60 AX_INC * 8
    // 61 AX_LDA  6
    // 62 AX_STA  6
    // 63
    // 64
    // 65
    // 66 AX_SBC * 7
    // 67 AX_CMP * 7
    // 68
    // 69 AX_ADC * 7
    // 6a
    // 6b
    // 6c AX_ASL * 8
    // 6d
    // 6e
    // 6f AX_DEC * 8
    // 70
    // 71 IP_TAX  3
    // 72 IP_TXA  3
    // 73 AX_LDY  6
    // 74 AX_STY  6
    // 75
    // 76 AX_EOR * 7
    // 77
    // 78 AX_LSR $ x
    // 79 AX_ROL $ x
    // 7a AX_ROR $ x
    // 7b AX_AND * 7
    // 7c RE_BEQ  8
    // 7d AB_JEQ  4
    // 7e AX_ORA * 7
    // 7f
    // 80
    // 81 AY_LDA  6
    // 82 AY_STA  6
    // 83
    // 84
    // 85
    // 86 AY_SBC * 7
    // 87 AY_CMP * 7
    // 88
    // 89 AY_ADC * 7
    // 8a
    // 8b
    // 8c
    // 8d
    // 8e
    // 8f
    // 90
    // 91 AY_LDX  6
    // 92 AY_STX  6
    // 93 IP_TAY  3
    // 94 IP_TYA  3
    // 95
    // 96 AY_EOR * 7
    // 97
    // 98
    // 99
    // 9a
    // 9b AY_AND * 7
    // 9c RE_BVC  8
    // 9d AB_JVC  4
    // 9e AY_ORA * 7
    // 9f
    // a0 IP_INX * 6
    // a1 IX_LDA  7
    // a2 IX_STA  7
    // a3
    // a4
    // a5
    // a6 IX_SBC * 8
    // a7 IX_CMP * 8
    // a8
    // a9 IX_ADC * 8
    // aa
    // ab
    // ac
    // ad
    // ae
    // af IP_DEX * 6
    // b0
    // b1 IP_TSX  3
    // b2 IP_TXS  3
    // b3
    // b4
    // b5
    // b6 IX_EOR * 8
    // b7
    // b8
    // b9
    // ba
    // bb IX_AND * 8
    // bc RE_BVS  8
    // bd AB_JVS  4
    // be IX_ORA * 8
    // bf
    // c0 IP_INY * 6
    // c1 IY_LDA  7
    // c2 IY_STA  7
    // c3
    // c4
    // c5
    // c6 IY_SBC * 8
    // c7 IY_CMP * 8
    // c8
    // c9 IY_ADC * 8
    // ca
    // cb
    // cc
    // cd
    // ce
    // cf IP_DEY * 6
    // d0
    // d1
    // d2
    // d3
    // d4
    // d5
    // d6 IY_EOR * 8
    // d7
    // d8
    // d9
    // da
    // db IY_AND * 8
    // dc RE_BPL  8
    // dd AB_JPL  4
    // de IY_ORA * 8
    // df
    // e0
    // e1
    // e2
    // e3
    // e4
    // e5
    // e6 AB_CPX * 8
    // e7 AB_CPY * 8
    // e8
    // e9
    // ea
    // eb
    // ec
    // ed
    // ee
    // ef
    // f0
    // f1
    // f2
    // f3
    // f4
    // f5
    // f6
    // f7
    // f8
    // f9
    // fa
    // fb
    // fc RE_BMI  8
    // fd AB_JMI  4
    // fe
    // ff
};

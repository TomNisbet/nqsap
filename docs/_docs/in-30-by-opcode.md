---
title: "NQSAP Instructions by Opcode"
permalink: /docs/in-by-opcode/
excerpt: "NQSAP Computer Instruction set by opcode"
---

## NQSAP Instructions by Opcode

|      |  x0  |  x1  |  x2  |  x3  |  x4  |  x5  |  x6  |  x7  |  x8  |  x9  |  xa  |  xb  |  xc  |  xd  |  xe  |  xf  |
|:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |
|**0x**|[IP_NOP](../in-details#nop)|[IP_OUT](../in-details#out)|      |      |      |      |      |      |      |      |[IP_RTS](../in-details#rts)|[IN_JMP](../in-details#jmp)|[AA_ASL](../in-details#asl)|      |      |      |
|**1x**|[AA_NOT](../in-details#not)|      |      |      |      |      |[IP_PHA](../in-details#pha)|[IP_CLC](../in-details#clc)|[AA_LSR](../in-details#lsr)|[AA_ROL](../in-details#rol)|[AA_ROR](../in-details#ror)|[AB_BIT](../in-details#bit)|      |      |[IP_PLA](../in-details#pla)|      |
|**2x**|[AA_INA](../in-details#ina)|[IM_LDA](../in-details#lda)|      |      |[IM_LDX](../in-details#ldx)|      |[IM_SBC](../in-details#sbc)|[IM_LDY](../in-details#ldy)|      |[IM_ADC](../in-details#adc)|[RE_BCC](../in-details#bcc)|[RE_BCS](../in-details#bcs)|      |      |      |[AA_DEA](../in-details#dea)|
|**3x**|      |[IM_CMP](../in-details#cmp)|[IM_CPX](../in-details#cpx)|[IM_CPY](../in-details#cpy)|      |      |[IM_EOR](../in-details#eor)|[IP_SEC](../in-details#sec)|      |      |      |[IM_AND](../in-details#and)|      |      |[IM_ORA](../in-details#ora)|      |
|**4x**|[AB_INC](../in-details#inc)|[AB_LDA](../in-details#lda)|[AB_STA](../in-details#sta)|      |[AB_LDX](../in-details#ldx)|[AB_STX](../in-details#stx)|[AB_SBC](../in-details#sbc)|[AB_LDY](../in-details#ldy)|[AB_STY](../in-details#sty)|[AB_ADC](../in-details#adc)|[AB_JSR](../in-details#jsr)|[AB_JMP](../in-details#jmp)|[AB_ASL](../in-details#asl)|      |      |[AB_DEC](../in-details#dec)|
|**5x**|      |[AB_CMP](../in-details#cmp)|[AB_CPX](../in-details#cpx)|[AB_CPY](../in-details#cpy)|      |      |[AB_EOR](../in-details#eor)|[IP_CLV](../in-details#clv)|[AB_LSR](../in-details#lsr)|[AB_ROL](../in-details#rol)|[AB_ROR](../in-details#ror)|[AB_AND](../in-details#and)|      |      |[AB_ORA](../in-details#ora)|      |
|**6x**|[AX_INC](../in-details#inc)|[AX_LDA](../in-details#lda)|[AX_STA](../in-details#sta)|      |[IP_TAX](../in-details#tax)|[IP_TXA](../in-details#txa)|[AX_SBC](../in-details#sbc)|[AX_LDY](../in-details#ldy)|[AX_STY](../in-details#sty)|[AX_ADC](../in-details#adc)|[RE_BNE](../in-details#bne)|[RE_BEQ](../in-details#beq)|[AX_ASL](../in-details#asl)|      |      |[AX_DEC](../in-details#dec)|
|**7x**|      |[AX_CMP](../in-details#cmp)|      |      |      |      |[AX_EOR](../in-details#eor)|      |[AX_LSR](../in-details#lsr)|[AX_ROL](../in-details#rol)|[AX_ROR](../in-details#ror)|[AX_AND](../in-details#and)|      |      |[AX_ORA](../in-details#ora)|      |
|**8x**|      |[AY_LDA](../in-details#lda)|[AY_STA](../in-details#sta)|      |[AY_LDX](../in-details#ldx)|[AY_STX](../in-details#stx)|[AY_SBC](../in-details#sbc)|[IP_TAY](../in-details#tay)|[IP_TYA](../in-details#tya)|[AY_ADC](../in-details#adc)|[RE_BPL](../in-details#bpl)|[RE_BMI](../in-details#bmi)|      |      |      |      |
|**9x**|      |[AY_CMP](../in-details#cmp)|      |      |      |      |[AY_EOR](../in-details#eor)|      |      |      |      |[AY_AND](../in-details#and)|      |      |[AY_ORA](../in-details#ora)|      |
|**ax**|[IP_INX](../in-details#inx)|[IX_LDA](../in-details#lda)|[IX_STA](../in-details#sta)|      |[IP_TSX](../in-details#tsx)|[IP_TXS](../in-details#txs)|[IX_SBC](../in-details#sbc)|      |      |[IX_ADC](../in-details#adc)|[RE_BVC](../in-details#bvc)|[RE_BVS](../in-details#bvs)|      |      |      |[IP_DEX](../in-details#dex)|
|**bx**|      |[IX_CMP](../in-details#cmp)|      |      |      |      |[IX_EOR](../in-details#eor)|[AB_JCC](../in-details#jcc)|[AB_JNE](../in-details#jne)|[AB_JPL](../in-details#jpl)|[AB_JVC](../in-details#jvc)|[IX_AND](../in-details#and)|      |      |[IX_ORA](../in-details#ora)|      |
|**cx**|[IP_INY](../in-details#iny)|[IY_LDA](../in-details#lda)|[IY_STA](../in-details#sta)|      |      |      |[IY_SBC](../in-details#sbc)|      |      |[IY_ADC](../in-details#adc)|      |      |      |      |      |[IP_DEY](../in-details#dey)|
|**dx**|      |[IY_CMP](../in-details#cmp)|      |      |      |      |[IY_EOR](../in-details#eor)|[AB_JCS](../in-details#jcs)|[AB_JEQ](../in-details#jeq)|[AB_JMI](../in-details#jmi)|[AB_JVS](../in-details#jvs)|[IY_AND](../in-details#and)|      |      |[IY_ORA](../in-details#ora)|      |
|**ex**|      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
|**fx**|      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |


---
title: "NQSAP Instructions by Opcode"
permalink: /docs/in-by-opcode/
excerpt: "NQSAP Computer Instruction set by opcode"
---

## NQSAP Instructions by Opcode

|      |  x0  |  x1  |  x2  |  x3  |  x4  |  x5  |  x6  |  x7  |  x8  |  x9  |  xa  |  xb  |  xc  |  xd  |  xe  |  xf  |
|:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |
|**0x**|[IP_NOP](../in-details#nop)|[IP_OUT](../in-details#out)|      |[**IP_CLC**](../in-details#clc)|      |      |[**IM_CPX**](../in-details#cpx)|[**IM_CPY**](../in-details#cpy)|      |[**IP_PHP**](../in-details#php)|[IP_RTS](../in-details#rts)|[IN_JMP](../in-details#jmp)|[AA_ASL](../in-details#asl)|      |      |[**IP_PLP**](../in-details#plp)|
|**1x**|[AA_NOT](../in-details#not)|      |      |      |      |      |[IP_PHA](../in-details#pha)|      |[AA_LSR](../in-details#lsr)|[AA_ROL](../in-details#rol)|[AA_ROR](../in-details#ror)|[AB_BIT](../in-details#bit)|[**RE_BCS**](../in-details#bcs)|[**AB_JCS**](../in-details#jcs)|[IP_PLA](../in-details#pla)|      |
|**2x**|[AA_INA](../in-details#ina)|[IM_LDA](../in-details#lda)|      |[**IP_SEC**](../in-details#sec)|      |      |[IM_SBC](../in-details#sbc)|[**IM_CMP**](../in-details#cmp)|      |[IM_ADC](../in-details#adc)|      |      |      |      |      |[AA_DEA](../in-details#dea)|
|**3x**|      |[**IM_LDX**](../in-details#ldx)|      |[**IM_LDY**](../in-details#ldy)|      |      |[IM_EOR](../in-details#eor)|      |      |      |      |[IM_AND](../in-details#and)|[**RE_BCC**](../in-details#bcc)|[**AB_JCC**](../in-details#jcc)|[IM_ORA](../in-details#ora)|      |
|**4x**|[AB_INC](../in-details#inc)|[AB_LDA](../in-details#lda)|[AB_STA](../in-details#sta)|[**IP_CLV**](../in-details#clv)|      |      |[AB_SBC](../in-details#sbc)|[**AB_CMP**](../in-details#cmp)|      |[AB_ADC](../in-details#adc)|[AB_JSR](../in-details#jsr)|[AB_JMP](../in-details#jmp)|[AB_ASL](../in-details#asl)|      |      |[AB_DEC](../in-details#dec)|
|**5x**|      |[**AB_LDX**](../in-details#ldx)|[**AB_STX**](../in-details#stx)|[**AB_LDY**](../in-details#ldy)|[**AB_STY**](../in-details#sty)|      |[AB_EOR](../in-details#eor)|      |[AB_LSR](../in-details#lsr)|[AB_ROL](../in-details#rol)|[AB_ROR](../in-details#ror)|[AB_AND](../in-details#and)|[**RE_BEQ**](../in-details#beq)|[**AB_JEQ**](../in-details#jeq)|[AB_ORA](../in-details#ora)|      |
|**6x**|[AX_INC](../in-details#inc)|[AX_LDA](../in-details#lda)|[AX_STA](../in-details#sta)|      |      |      |[AX_SBC](../in-details#sbc)|[**AX_CMP**](../in-details#cmp)|      |[AX_ADC](../in-details#adc)|      |      |[AX_ASL](../in-details#asl)|      |      |[AX_DEC](../in-details#dec)|
|**7x**|      |[**IP_TAX**](../in-details#tax)|[**IP_TXA**](../in-details#txa)|[**AX_LDY**](../in-details#ldy)|[**AX_STY**](../in-details#sty)|      |[AX_EOR](../in-details#eor)|      |[AX_LSR](../in-details#lsr)|[AX_ROL](../in-details#rol)|[AX_ROR](../in-details#ror)|[AX_AND](../in-details#and)|[**RE_BNE**](../in-details#bne)|[**AB_JNE**](../in-details#jne)|[AX_ORA](../in-details#ora)|      |
|**8x**|      |[AY_LDA](../in-details#lda)|[AY_STA](../in-details#sta)|      |      |      |[AY_SBC](../in-details#sbc)|[**AY_CMP**](../in-details#cmp)|      |[AY_ADC](../in-details#adc)|      |      |      |      |      |      |
|**9x**|      |[**AY_LDX**](../in-details#ldx)|[**AY_STX**](../in-details#stx)|[**IP_TAY**](../in-details#tay)|[**IP_TYA**](../in-details#tya)|      |[AY_EOR](../in-details#eor)|      |      |      |      |[AY_AND](../in-details#and)|[**RE_BVS**](../in-details#bvs)|[**AB_JVS**](../in-details#jvs)|[AY_ORA](../in-details#ora)|      |
|**ax**|[IP_INX](../in-details#inx)|[IX_LDA](../in-details#lda)|[IX_STA](../in-details#sta)|      |      |      |[IX_SBC](../in-details#sbc)|[**IX_CMP**](../in-details#cmp)|      |[IX_ADC](../in-details#adc)|      |      |      |      |      |[IP_DEX](../in-details#dex)|
|**bx**|      |[**IP_TSX**](../in-details#tsx)|[**IP_TXS**](../in-details#txs)|      |      |      |[IX_EOR](../in-details#eor)|      |      |      |      |[IX_AND](../in-details#and)|[**RE_BVC**](../in-details#bvc)|[**AB_JVC**](../in-details#jvc)|[IX_ORA](../in-details#ora)|      |
|**cx**|[IP_INY](../in-details#iny)|[IY_LDA](../in-details#lda)|[IY_STA](../in-details#sta)|      |      |      |[IY_SBC](../in-details#sbc)|[**IY_CMP**](../in-details#cmp)|      |[IY_ADC](../in-details#adc)|      |      |      |      |      |[IP_DEY](../in-details#dey)|
|**dx**|      |      |      |      |      |      |[IY_EOR](../in-details#eor)|      |      |      |      |[IY_AND](../in-details#and)|[**RE_BMI**](../in-details#bmi)|[**AB_JMI**](../in-details#jmi)|[IY_ORA](../in-details#ora)|      |
|**ex**|      |      |      |      |      |      |[**AB_CPX**](../in-details#cpx)|[**AB_CPY**](../in-details#cpy)|      |      |      |      |      |      |      |      |
|**fx**|      |      |      |      |      |      |      |      |      |      |      |      |[**RE_BPL**](../in-details#bpl)|[**AB_JPL**](../in-details#jpl)|      |      |


*this file was generated by nqsap-instructions.py at 25-Mar-2021 11:57:28*

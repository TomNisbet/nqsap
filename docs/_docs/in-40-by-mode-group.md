---
title: "NQSAP Instructions by Adddress Mode Group"
permalink: /docs/in-by-mode-group/
excerpt: "NQSAP Computer Instructions by Address Mode Group"
---

|      |P/A/R/N<br />00,10  |Immediate<br />20,30  |Absolute<br />40,50  |Absolute+X<br />60,70  |Absolute+Y<br />80,90  |Indexed Indirect (X)<br />a0,b0  |Indirect Indexed (Y)<br />c0,d0  |NONE<br />e0,f0  |ALU Operation|
|:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---         |
|**00**|[IP_NOP](../in-details#nop)|[AA_INA](../in-details#ina)|[AB_INC](../in-details#inc)|[AX_INC](../in-details#inc)|      |[IP_INX](../in-details#inx)|[IP_INY](../in-details#iny)|      |A plus 1     |
|**01**|[IP_OUT](../in-details#out)|[IM_LDA](../in-details#lda)|[AB_LDA](../in-details#lda)|[AX_LDA](../in-details#lda)|[AY_LDA](../in-details#lda)|[IX_LDA](../in-details#lda)|[IY_LDA](../in-details#lda)|      |             |
|**02**|      |      |[AB_STA](../in-details#sta)|[AX_STA](../in-details#sta)|[AY_STA](../in-details#sta)|[IX_STA](../in-details#sta)|[IY_STA](../in-details#sta)|      |             |
|**03**|      |      |      |      |      |      |      |      |             |
|**04**|      |[IM_LDX](../in-details#ldx)|[AB_LDX](../in-details#ldx)|[IP_TAX](../in-details#tax)|[AY_LDX](../in-details#ldx)|[IP_TSX](../in-details#tsx)|      |      |             |
|**05**|      |      |[AB_STX](../in-details#stx)|[IP_TXA](../in-details#txa)|[AY_STX](../in-details#stx)|[IP_TXS](../in-details#txs)|      |      |             |
|**06**|      |[IM_SBC](../in-details#sbc)|[AB_SBC](../in-details#sbc)|[AX_SBC](../in-details#sbc)|[AY_SBC](../in-details#sbc)|[IX_SBC](../in-details#sbc)|[IY_SBC](../in-details#sbc)|      |A minus B    |
|**07**|      |[IM_LDY](../in-details#ldy)|[AB_LDY](../in-details#ldy)|[AX_LDY](../in-details#ldy)|[IP_TAY](../in-details#tay)|      |      |      |             |
|**08**|      |      |[AB_STY](../in-details#sty)|[AX_STY](../in-details#sty)|[IP_TYA](../in-details#tya)|      |      |      |             |
|**09**|      |[IM_ADC](../in-details#adc)|[AB_ADC](../in-details#adc)|[AX_ADC](../in-details#adc)|[AY_ADC](../in-details#adc)|[IX_ADC](../in-details#adc)|[IY_ADC](../in-details#adc)|      |A plus B     |
|**0a**|[IP_RTS](../in-details#rts)|[RE_BCC](../in-details#bcc)|[AB_JSR](../in-details#jsr)|[RE_BNE](../in-details#bne)|[RE_BPL](../in-details#bpl)|[RE_BVC](../in-details#bvc)|      |      |             |
|**0b**|[IN_JMP](../in-details#jmp)|[RE_BCS](../in-details#bcs)|[AB_JMP](../in-details#jmp)|[RE_BEQ](../in-details#beq)|[RE_BMI](../in-details#bmi)|[RE_BVS](../in-details#bvs)|      |      |             |
|**0c**|[AA_ASL](../in-details#asl)|      |[AB_ASL](../in-details#asl)|[AX_ASL](../in-details#asl)|      |      |      |      |A plus A     |
|**0d**|      |      |      |      |      |      |      |      |             |
|**0e**|      |      |      |      |      |      |      |      |             |
|**0f**|      |[AA_DEA](../in-details#dea)|[AB_DEC](../in-details#dec)|[AX_DEC](../in-details#dec)|      |[IP_DEX](../in-details#dex)|[IP_DEY](../in-details#dey)|      |A minus 1    |
|**10**|[AA_NOT](../in-details#not)|      |      |      |      |      |      |      |not A        |
|**11**|      |[IM_CMP](../in-details#cmp)|[AB_CMP](../in-details#cmp)|[AX_CMP](../in-details#cmp)|[AY_CMP](../in-details#cmp)|[IX_CMP](../in-details#cmp)|[IY_CMP](../in-details#cmp)|      |             |
|**12**|      |[IM_CPX](../in-details#cpx)|[AB_CPX](../in-details#cpx)|      |      |      |      |      |             |
|**13**|      |[IM_CPY](../in-details#cpy)|[AB_CPY](../in-details#cpy)|      |      |      |      |      |             |
|**14**|      |      |      |      |      |      |      |      |             |
|**15**|      |      |      |      |      |      |      |      |             |
|**16**|[IP_PHA](../in-details#pha)|[IM_EOR](../in-details#eor)|[AB_EOR](../in-details#eor)|[AX_EOR](../in-details#eor)|[AY_EOR](../in-details#eor)|[IX_EOR](../in-details#eor)|[IY_EOR](../in-details#eor)|      |A xor B      |
|**17**|[IP_CLC](../in-details#clc)|[IP_SEC](../in-details#sec)|[IP_CLV](../in-details#clv)|      |      |[AB_JCC](../in-details#jcc)|[AB_JCS](../in-details#jcs)|      |             |
|**18**|[AA_LSR](../in-details#lsr)|      |[AB_LSR](../in-details#lsr)|[AX_LSR](../in-details#lsr)|      |[AB_JNE](../in-details#jne)|[AB_JEQ](../in-details#jeq)|      |             |
|**19**|[AA_ROL](../in-details#rol)|      |[AB_ROL](../in-details#rol)|[AX_ROL](../in-details#rol)|      |[AB_JPL](../in-details#jpl)|[AB_JMI](../in-details#jmi)|      |             |
|**1a**|[AA_ROR](../in-details#ror)|      |[AB_ROR](../in-details#ror)|[AX_ROR](../in-details#ror)|      |[AB_JVC](../in-details#jvc)|[AB_JVS](../in-details#jvs)|      |             |
|**1b**|[AB_BIT](../in-details#bit)|[IM_AND](../in-details#and)|[AB_AND](../in-details#and)|[AX_AND](../in-details#and)|[AY_AND](../in-details#and)|[IX_AND](../in-details#and)|[IY_AND](../in-details#and)|      |A and B      |
|**1c**|      |      |      |      |      |      |      |      |             |
|**1d**|      |      |      |      |      |      |      |      |             |
|**1e**|[IP_PLA](../in-details#pla)|[IM_ORA](../in-details#ora)|[AB_ORA](../in-details#ora)|[AX_ORA](../in-details#ora)|[AY_ORA](../in-details#ora)|[IX_ORA](../in-details#ora)|[IY_ORA](../in-details#ora)|      |A or B       |
|**1f**|      |      |      |      |      |      |      |      |             |


*this file was generated by nqsap-instructions.py at 02-Dec-2020 16:57:46*

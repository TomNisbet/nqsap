---
title: "NQSAP Instructions by Address Mode Group"
permalink: /docs/in-by-mode-group/
excerpt: "NQSAP Computer Instructions by Address Mode Group"
---

|      |P/A/R/N<br />00,10  |Immediate<br />20,30  |Absolute<br />40,50  |Absolute+X<br />60,70  |Absolute+Y<br />80,90  |Indexed Indirect (X)<br />a0,b0  |Indirect Indexed (Y)<br />c0,d0  |Misc<br />e0,f0  |ALU Operation|
|:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---         |
|**00**|[IP_NOP](../in-details#nop)|[AA_INA](../in-details#ina)|[AB_INC](../in-details#inc)|[AX_INC](../in-details#inc)|      |[IP_INX](../in-details#inx)|[IP_INY](../in-details#iny)|      |A plus 1     |
|**01**|[IP_OUT](../in-details#out)|[IM_LDA](../in-details#lda)|[AB_LDA](../in-details#lda)|[AX_LDA](../in-details#lda)|[AY_LDA](../in-details#lda)|[IX_LDA](../in-details#lda)|[IY_LDA](../in-details#lda)|      |             |
|**02**|      |      |[AB_STA](../in-details#sta)|[AX_STA](../in-details#sta)|[AY_STA](../in-details#sta)|[IX_STA](../in-details#sta)|[IY_STA](../in-details#sta)|      |             |
|**03**|[**IP_CLC**](../in-details#clc)|[**IP_SEC**](../in-details#sec)|[**IP_CLV**](../in-details#clv)|      |      |      |      |      |zero/ones    |
|**04**|      |      |      |      |      |      |      |      |             |
|**05**|      |      |      |      |      |      |      |      |A minus B *  |
|**06**|[**IM_CPX**](../in-details#cpx)|[IM_SBC](../in-details#sbc)|[AB_SBC](../in-details#sbc)|[AX_SBC](../in-details#sbc)|[AY_SBC](../in-details#sbc)|[IX_SBC](../in-details#sbc)|[IY_SBC](../in-details#sbc)|[**AB_CPX**](../in-details#cpx)|A minus B    |
|**07**|[**IM_CPY**](../in-details#cpy)|[**IM_CMP**](../in-details#cmp)|[**AB_CMP**](../in-details#cmp)|[**AX_CMP**](../in-details#cmp)|[**AY_CMP**](../in-details#cmp)|[**IX_CMP**](../in-details#cmp)|[**IY_CMP**](../in-details#cmp)|[**AB_CPY**](../in-details#cpy)|             |
|**08**|      |      |      |      |      |      |      |      |             |
|**09**|[**IP_PHP**](../in-details#php)|[IM_ADC](../in-details#adc)|[AB_ADC](../in-details#adc)|[AX_ADC](../in-details#adc)|[AY_ADC](../in-details#adc)|[IX_ADC](../in-details#adc)|[IY_ADC](../in-details#adc)|      |A plus B     |
|**0a**|[IP_RTS](../in-details#rts)|      |[AB_JSR](../in-details#jsr)|      |      |      |      |      |             |
|**0b**|[IN_JMP](../in-details#jmp)|      |[AB_JMP](../in-details#jmp)|      |      |      |      |      |             |
|**0c**|[AA_ASL](../in-details#asl)|      |[AB_ASL](../in-details#asl)|[AX_ASL](../in-details#asl)|      |      |      |      |A plus A     |
|**0d**|      |      |      |      |      |      |      |      |             |
|**0e**|      |      |      |      |      |      |      |      |             |
|**0f**|[**IP_PLP**](../in-details#plp)|[AA_DEA](../in-details#dea)|[AB_DEC](../in-details#dec)|[AX_DEC](../in-details#dec)|      |[IP_DEX](../in-details#dex)|[IP_DEY](../in-details#dey)|      |A minus 1    |
|**10**|[AA_NOT](../in-details#not)|      |      |      |      |      |      |      |not A        |
|**11**|      |[**IM_LDX**](../in-details#ldx)|[**AB_LDX**](../in-details#ldx)|[**IP_TAX**](../in-details#tax)|[**AY_LDX**](../in-details#ldx)|[**IP_TSX**](../in-details#tsx)|      |      |             |
|**12**|      |      |[**AB_STX**](../in-details#stx)|[**IP_TXA**](../in-details#txa)|[**AY_STX**](../in-details#stx)|[**IP_TXS**](../in-details#txs)|      |      |             |
|**13**|      |[**IM_LDY**](../in-details#ldy)|[**AB_LDY**](../in-details#ldy)|[**AX_LDY**](../in-details#ldy)|[**IP_TAY**](../in-details#tay)|      |      |      |             |
|**14**|      |      |[**AB_STY**](../in-details#sty)|[**AX_STY**](../in-details#sty)|[**IP_TYA**](../in-details#tya)|      |      |      |             |
|**15**|      |      |      |      |      |      |      |      |             |
|**16**|[IP_PHA](../in-details#pha)|[IM_EOR](../in-details#eor)|[AB_EOR](../in-details#eor)|[AX_EOR](../in-details#eor)|[AY_EOR](../in-details#eor)|[IX_EOR](../in-details#eor)|[IY_EOR](../in-details#eor)|      |A xor B      |
|**17**|      |      |      |      |      |      |      |      |             |
|**18**|[AA_LSR](../in-details#lsr)|      |[AB_LSR](../in-details#lsr)|[AX_LSR](../in-details#lsr)|      |      |      |      |             |
|**19**|[AA_ROL](../in-details#rol)|      |[AB_ROL](../in-details#rol)|[AX_ROL](../in-details#rol)|      |      |      |      |             |
|**1a**|[AA_ROR](../in-details#ror)|      |[AB_ROR](../in-details#ror)|[AX_ROR](../in-details#ror)|      |      |      |      |             |
|**1b**|[AB_BIT](../in-details#bit)|[IM_AND](../in-details#and)|[AB_AND](../in-details#and)|[AX_AND](../in-details#and)|[AY_AND](../in-details#and)|[IX_AND](../in-details#and)|[IY_AND](../in-details#and)|      |A and B      |
|**1c**|[**RE_BCC**](../in-details#bcc)|[**RE_BCS**](../in-details#bcs)|[**RE_BNE**](../in-details#bne)|[**RE_BEQ**](../in-details#beq)|[**RE_BVC**](../in-details#bvc)|[**RE_BVS**](../in-details#bvs)|[**RE_BPL**](../in-details#bpl)|[**RE_BMI**](../in-details#bmi)|             |
|**1d**|[**AB_JCC**](../in-details#jcc)|[**AB_JCS**](../in-details#jcs)|[**AB_JNE**](../in-details#jne)|[**AB_JEQ**](../in-details#jeq)|[**AB_JVC**](../in-details#jvc)|[**AB_JVS**](../in-details#jvs)|[**AB_JPL**](../in-details#jpl)|[**AB_JMI**](../in-details#jmi)|             |
|**1e**|[IP_PLA](../in-details#pla)|[IM_ORA](../in-details#ora)|[AB_ORA](../in-details#ora)|[AX_ORA](../in-details#ora)|[AY_ORA](../in-details#ora)|[IX_ORA](../in-details#ora)|[IY_ORA](../in-details#ora)|      |A or B       |
|**1f**|      |      |      |      |      |      |      |      |             |


*this file was generated by nqsap-instructions.py at 30-Dec-2020 12:27:09*

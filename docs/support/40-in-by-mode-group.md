---
title: "NQSAP Instructions by Adddress Mode Group"
permalink: /docs/in-by-mode-group/
excerpt: "NQSAP Computer Instructions by Address Mode Group"
---

|      |P/A/R/N<br />00,10  |Immediate<br />20,30  |Absolute<br />40,50  |Absolute+X<br />60,70  |Absolute+Y<br />80,90  |Indexed Indirect (X)<br />a0,b0  |Indirect Indexed (Y)<br />c0,d0  |NONE<br />e0,f0  |ALU Operation|
|:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---         |
|**00**|[IP_NOP](../in-details#NOP)|[AA_INA](../in-details#INA)|[AB_INC](../in-details#INC)|[AX_INC](../in-details#INC)|      |[IP_INX](../in-details#INX)|[IP_INY](../in-details#INY)|      |A plus 1     |
|**01**|[IP_OUT](../in-details#OUT)|[IM_LDA](../in-details#LDA)|[AB_LDA](../in-details#LDA)|[AX_LDA](../in-details#LDA)|[AY_LDA](../in-details#LDA)|[IX_LDA](../in-details#LDA)|[IY_LDA](../in-details#LDA)|      |             |
|**02**|      |      |[AB_STA](../in-details#STA)|[AX_STA](../in-details#STA)|[AY_STA](../in-details#STA)|[IX_STA](../in-details#STA)|[IY_STA](../in-details#STA)|      |             |
|**03**|      |      |      |      |      |      |      |      |             |
|**04**|      |[IM_LDX](../in-details#LDX)|[AB_LDX](../in-details#LDX)|[IP_TAX](../in-details#TAX)|[AY_LDX](../in-details#LDX)|[IP_TSX](../in-details#TSX)|      |      |             |
|**05**|      |      |[AB_STX](../in-details#STX)|[IP_TXA](../in-details#TXA)|[AY_STX](../in-details#STX)|[IP_TXS](../in-details#TXS)|      |      |             |
|**06**|      |[IM_SBC](../in-details#SBC)|[AB_SBC](../in-details#SBC)|[AX_SBC](../in-details#SBC)|[AY_SBC](../in-details#SBC)|[IX_SBC](../in-details#SBC)|[IY_SBC](../in-details#SBC)|      |A minus B    |
|**07**|      |[IM_LDY](../in-details#LDY)|[AB_LDY](../in-details#LDY)|[AX_LDY](../in-details#LDY)|[IP_TAY](../in-details#TAY)|      |      |      |             |
|**08**|      |      |[AB_STY](../in-details#STY)|[AX_STY](../in-details#STY)|[IP_TYA](../in-details#TYA)|      |      |      |             |
|**09**|      |[IM_ADC](../in-details#ADC)|[AB_ADC](../in-details#ADC)|[AX_ADC](../in-details#ADC)|[AY_ADC](../in-details#ADC)|[IX_ADC](../in-details#ADC)|[IY_ADC](../in-details#ADC)|      |A plus B     |
|**0a**|[IP_RTS](../in-details#RTS)|[RE_BCC](../in-details#BCC)|[AB_JSR](../in-details#JSR)|[RE_BNE](../in-details#BNE)|[RE_BPL](../in-details#BPL)|[RE_BVC](../in-details#BVC)|      |      |             |
|**0b**|[IN_JMP](../in-details#JMP)|[RE_BCS](../in-details#BCS)|[AB_JMP](../in-details#JMP)|[RE_BEQ](../in-details#BEQ)|[RE_BMI](../in-details#BMI)|[RE_BVS](../in-details#BVS)|      |      |             |
|**0c**|[AA_ASL](../in-details#ASL)|      |[AB_ASL](../in-details#ASL)|[AX_ASL](../in-details#ASL)|      |      |      |      |A plus A     |
|**0d**|      |      |      |      |      |      |      |      |             |
|**0e**|      |      |      |      |      |      |      |      |             |
|**0f**|      |[AA_DEA](../in-details#DEA)|[AB_DEC](../in-details#DEC)|[AX_DEC](../in-details#DEC)|      |[IP_DEX](../in-details#DEX)|[IP_DEY](../in-details#DEY)|      |A minus 1    |
|**10**|[AA_NOT](../in-details#NOT)|      |      |      |      |      |      |      |not A        |
|**11**|      |[IM_CMP](../in-details#CMP)|[AB_CMP](../in-details#CMP)|[AX_CMP](../in-details#CMP)|[AY_CMP](../in-details#CMP)|[IX_CMP](../in-details#CMP)|[IY_CMP](../in-details#CMP)|      |             |
|**12**|      |[IM_CPX](../in-details#CPX)|[AB_CPX](../in-details#CPX)|      |      |      |      |      |             |
|**13**|      |[IM_CPY](../in-details#CPY)|[AB_CPY](../in-details#CPY)|      |      |      |      |      |             |
|**14**|      |      |      |      |      |      |      |      |             |
|**15**|      |      |      |      |      |      |      |      |             |
|**16**|[IP_PHA](../in-details#PHA)|[IM_EOR](../in-details#EOR)|[AB_EOR](../in-details#EOR)|[AX_EOR](../in-details#EOR)|[AY_EOR](../in-details#EOR)|[IX_EOR](../in-details#EOR)|[IY_EOR](../in-details#EOR)|      |A xor B      |
|**17**|[IP_CLC](../in-details#CLC)|[IP_SEC](../in-details#SEC)|[IP_CLV](../in-details#CLV)|      |      |[AB_JCC](../in-details#JCC)|[AB_JCS](../in-details#JCS)|      |             |
|**18**|[AA_LSR](../in-details#LSR)|      |[AB_LSR](../in-details#LSR)|[AX_LSR](../in-details#LSR)|      |[AB_JNE](../in-details#JNE)|[AB_JEQ](../in-details#JEQ)|      |             |
|**19**|[AA_ROL](../in-details#ROL)|      |[AB_ROL](../in-details#ROL)|[AX_ROL](../in-details#ROL)|      |[AB_JPL](../in-details#JPL)|[AB_JMI](../in-details#JMI)|      |             |
|**1a**|[AA_ROR](../in-details#ROR)|      |[AB_ROR](../in-details#ROR)|[AX_ROR](../in-details#ROR)|      |[AB_JVC](../in-details#JVC)|[AB_JVS](../in-details#JVS)|      |             |
|**1b**|[AB_BIT](../in-details#BIT)|[IM_AND](../in-details#AND)|[AB_AND](../in-details#AND)|[AX_AND](../in-details#AND)|[AY_AND](../in-details#AND)|[IX_AND](../in-details#AND)|[IY_AND](../in-details#AND)|      |A and B      |
|**1c**|      |      |      |      |      |      |      |      |             |
|**1d**|      |      |      |      |      |      |      |      |             |
|**1e**|[IP_PLA](../in-details#PLA)|[IM_ORA](../in-details#ORA)|[AB_ORA](../in-details#ORA)|[AX_ORA](../in-details#ORA)|[AY_ORA](../in-details#ORA)|[IX_ORA](../in-details#ORA)|[IY_ORA](../in-details#ORA)|      |A or B       |
|**1f**|[IP_HLT](../in-details#HLT)|      |      |      |      |      |      |      |             |


*this file was generated by nqsap-instructions.py at 22-Nov-2020 11:53:49*

---
title: "NQSAP Instructions by Opcode"
permalink: /docs/in-by-opcode/
excerpt: "NQSAP Computer Instruction set by opcode"
---

## NQSAP Instructions by Opcode

|      |  x0  |  x1  |  x2  |  x3  |  x4  |  x5  |  x6  |  x7  |  x8  |  x9  |  xa  |  xb  |  xc  |  xd  |  xe  |  xf  |
|:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |:---: |
|**0x**|[IP_NOP](../in-details#NOP)|[IP_OUT](../in-details#OUT)|      |      |      |      |      |      |      |      |[IP_RTS](../in-details#RTS)|[IN_JMP](../in-details#JMP)|[AA_ASL](../in-details#ASL)|      |      |      |
|**1x**|[AA_NOT](../in-details#NOT)|      |      |      |      |      |[IP_PHA](../in-details#PHA)|[IP_CLC](../in-details#CLC)|[AA_LSR](../in-details#LSR)|[AA_ROL](../in-details#ROL)|[AA_ROR](../in-details#ROR)|[AB_BIT](../in-details#BIT)|      |      |[IP_PLA](../in-details#PLA)|[IP_HLT](../in-details#HLT)|
|**2x**|[AA_INA](../in-details#INA)|[IM_LDA](../in-details#LDA)|      |      |[IM_LDX](../in-details#LDX)|      |[IM_SBC](../in-details#SBC)|[IM_LDY](../in-details#LDY)|      |[IM_ADC](../in-details#ADC)|[RE_BCC](../in-details#BCC)|[RE_BCS](../in-details#BCS)|      |      |      |[AA_DEA](../in-details#DEA)|
|**3x**|      |[IM_CMP](../in-details#CMP)|[IM_CPX](../in-details#CPX)|[IM_CPY](../in-details#CPY)|      |      |[IM_EOR](../in-details#EOR)|[IP_SEC](../in-details#SEC)|      |      |      |[IM_AND](../in-details#AND)|      |      |[IM_ORA](../in-details#ORA)|      |
|**4x**|[AB_INC](../in-details#INC)|[AB_LDA](../in-details#LDA)|[AB_STA](../in-details#STA)|      |[AB_LDX](../in-details#LDX)|[AB_STX](../in-details#STX)|[AB_SBC](../in-details#SBC)|[AB_LDY](../in-details#LDY)|[AB_STY](../in-details#STY)|[AB_ADC](../in-details#ADC)|[AB_JSR](../in-details#JSR)|[AB_JMP](../in-details#JMP)|[AB_ASL](../in-details#ASL)|      |      |[AB_DEC](../in-details#DEC)|
|**5x**|      |[AB_CMP](../in-details#CMP)|[AB_CPX](../in-details#CPX)|[AB_CPY](../in-details#CPY)|      |      |[AB_EOR](../in-details#EOR)|[IP_CLV](../in-details#CLV)|[AB_LSR](../in-details#LSR)|[AB_ROL](../in-details#ROL)|[AB_ROR](../in-details#ROR)|[AB_AND](../in-details#AND)|      |      |[AB_ORA](../in-details#ORA)|      |
|**6x**|[AX_INC](../in-details#INC)|[AX_LDA](../in-details#LDA)|[AX_STA](../in-details#STA)|      |[IP_TAX](../in-details#TAX)|[IP_TXA](../in-details#TXA)|[AX_SBC](../in-details#SBC)|[AX_LDY](../in-details#LDY)|[AX_STY](../in-details#STY)|[AX_ADC](../in-details#ADC)|[RE_BNE](../in-details#BNE)|[RE_BEQ](../in-details#BEQ)|[AX_ASL](../in-details#ASL)|      |      |[AX_DEC](../in-details#DEC)|
|**7x**|      |[AX_CMP](../in-details#CMP)|      |      |      |      |[AX_EOR](../in-details#EOR)|      |[AX_LSR](../in-details#LSR)|[AX_ROL](../in-details#ROL)|[AX_ROR](../in-details#ROR)|[AX_AND](../in-details#AND)|      |      |[AX_ORA](../in-details#ORA)|      |
|**8x**|      |[AY_LDA](../in-details#LDA)|[AY_STA](../in-details#STA)|      |[AY_LDX](../in-details#LDX)|[AY_STX](../in-details#STX)|[AY_SBC](../in-details#SBC)|[IP_TAY](../in-details#TAY)|[IP_TYA](../in-details#TYA)|[AY_ADC](../in-details#ADC)|[RE_BPL](../in-details#BPL)|[RE_BMI](../in-details#BMI)|      |      |      |      |
|**9x**|      |[AY_CMP](../in-details#CMP)|      |      |      |      |[AY_EOR](../in-details#EOR)|      |      |      |      |[AY_AND](../in-details#AND)|      |      |[AY_ORA](../in-details#ORA)|      |
|**ax**|[IP_INX](../in-details#INX)|[IX_LDA](../in-details#LDA)|[IX_STA](../in-details#STA)|      |[IP_TSX](../in-details#TSX)|[IP_TXS](../in-details#TXS)|[IX_SBC](../in-details#SBC)|      |      |[IX_ADC](../in-details#ADC)|[RE_BVC](../in-details#BVC)|[RE_BVS](../in-details#BVS)|      |      |      |[IP_DEX](../in-details#DEX)|
|**bx**|      |[IX_CMP](../in-details#CMP)|      |      |      |      |[IX_EOR](../in-details#EOR)|[AB_JCC](../in-details#JCC)|[AB_JNE](../in-details#JNE)|[AB_JPL](../in-details#JPL)|[AB_JVC](../in-details#JVC)|[IX_AND](../in-details#AND)|      |      |[IX_ORA](../in-details#ORA)|      |
|**cx**|[IP_INY](../in-details#INY)|[IY_LDA](../in-details#LDA)|[IY_STA](../in-details#STA)|      |      |      |[IY_SBC](../in-details#SBC)|      |      |[IY_ADC](../in-details#ADC)|      |      |      |      |      |[IP_DEY](../in-details#DEY)|
|**dx**|      |[IY_CMP](../in-details#CMP)|      |      |      |      |[IY_EOR](../in-details#EOR)|[AB_JCS](../in-details#JCS)|[AB_JEQ](../in-details#JEQ)|[AB_JMI](../in-details#JMI)|[AB_JVS](../in-details#JVS)|[IY_AND](../in-details#AND)|      |      |[IY_ORA](../in-details#ORA)|      |
|**ex**|      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
|**fx**|      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |


---
title: "NQSAP Instructions"
permalink: /docs/in-details/
excerpt: "Instruction set for the NQSAP Computer"
---

|           |           |           |           |           |           |           |           |
|:---:      |:---:      |:---:      |:---:      |:---:      |:---:      |:---:      |:---:      |
|[ADC](#adc)|[AND](#and)|[ASL](#asl)|[BCC](#bcc)|[BCS](#bcs)|[BEQ](#beq)|[BIT](#bit)|[BMI](#bmi)|
|[BNE](#bne)|[BPL](#bpl)|[BVC](#bvc)|[BVS](#bvs)|[CLC](#clc)|[CLV](#clv)|[CMP](#cmp)|[CPX](#cpx)|
|[CPY](#cpy)|[DEA](#dea)|[DEC](#dec)|[DEX](#dex)|[DEY](#dey)|[EOR](#eor)|[INA](#ina)|[INC](#inc)|
|[INX](#inx)|[INY](#iny)|[JCC](#jcc)|[JCS](#jcs)|[JEQ](#jeq)|[JMI](#jmi)|[JMP](#jmp)|[JNE](#jne)|
|[JPL](#jpl)|[JSR](#jsr)|[JVC](#jvc)|[JVS](#jvs)|[LDA](#lda)|[LDX](#ldx)|[LDY](#ldy)|[LSR](#lsr)|
|[NOP](#nop)|[NOT](#not)|[ORA](#ora)|[OUT](#out)|[PHA](#pha)|[PHP](#php)|[PLA](#pla)|[PLP](#plp)|
|[ROL](#rol)|[ROR](#ror)|[RTS](#rts)|[SBC](#sbc)|[SEC](#sec)|[STA](#sta)|[STX](#stx)|[STY](#sty)|
|[TAX](#tax)|[TAY](#tay)|[TSX](#tsx)|[TXA](#txa)|[TXS](#txs)|[TYA](#tya)|

## ADC

Add with Carry

**Flags:** CZVN

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x29|2|5|
|AB - Absolute|0x49|2|6|
|AX - Absolute+X|0x69|2|7|
|AY - Absolute+Y|0x89|2|7|
|IX - Indexed Indirect (X)|0xa9|2|8|
|IY - Indirect Indexed (Y)|0xc9|2|8|

## AND

Logical AND

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x3b|2|5|
|AB - Absolute|0x5b|2|6|
|AX - Absolute+X|0x7b|2|7|
|AY - Absolute+Y|0x9b|2|7|
|IX - Indexed Indirect (X)|0xbb|2|8|
|IY - Indirect Indexed (Y)|0xdb|2|8|

## ASL

Arithmetic Shift Left

**Flags:** CZ-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AA - Accumulator|0x0c|1|3|
|AB - Absolute|0x4c|1|7|
|AX - Absolute+X|0x6c|1|8|

## BCC

Branch if Carry Clear

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|RE - Relative|0x3c|2|8|

## BCS

Branch if Carry Set

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|RE - Relative|0x1c|2|8|

## BEQ

Branch if Equal

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|RE - Relative|0x5c|2|8|

## BIT

Bit Test

**Flags:** -Z--

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x1b|2|5|

## BMI

Branch if Minus

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|RE - Relative|0xdc|2|8|

## BNE

Branch if Not Equal

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|RE - Relative|0x7c|2|8|

## BPL

Branch if Positive

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|RE - Relative|0xfc|2|8|

## BVC

Branch if Overflow Clear

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|RE - Relative|0xbc|2|8|

## BVS

Branch if Overflow Set

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|RE - Relative|0x9c|2|8|

## CLC

Clear Carry

**Flags:** C---

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x03|1|3|

## CLV

Clear Overflow

**Flags:** --V-

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x43|1|3|

## CMP

Compare A

**Flags:** CZ-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x27|2|5|
|AB - Absolute|0x47|2|6|
|AX - Absolute+X|0x67|2|7|
|AY - Absolute+Y|0x87|2|7|
|IX - Indexed Indirect (X)|0xa7|2|8|
|IY - Indirect Indexed (Y)|0xc7|2|8|

## CPX

Compare X

**Flags:** CZ-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x06|2|7|
|AB - Absolute|0xe6|2|8|

## CPY

Compare Y

**Flags:** CZ-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x07|2|7|
|AB - Absolute|0xe7|2|8|

## DEA

Decrement A

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AA - Accumulator|0x2f|1|3|

## DEC

Decrement Memory

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x4f|2|7|
|AX - Absolute+X|0x6f|1|8|

## DEX

Decrement X

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0xaf|1|6|

## DEY

Decrement Y

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0xcf|1|6|

## EOR

Exclusive OR

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x36|2|5|
|AB - Absolute|0x56|2|6|
|AX - Absolute+X|0x76|2|7|
|AY - Absolute+Y|0x96|2|7|
|IX - Indexed Indirect (X)|0xb6|2|8|
|IY - Indirect Indexed (Y)|0xd6|2|8|

## INA

Increment A

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AA - Accumulator|0x20|1|3|

## INC

Increment Memory

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x40|2|7|
|AX - Absolute+X|0x60|2|8|

## INX

Increment X

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0xa0|1|6|

## INY

Increment Y

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0xc0|1|6|

## JCC

Jump if Carry Clear

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x3d|2|4|

## JCS

Jump if Carry Set

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x1d|2|4|

## JEQ

Jump if Equal

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x5d|2|4|

## JMI

Jump if Minus

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0xdd|2|4|

## JMP

Jump

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x4b|2|4|
|IN - Indirect|0x0b|2|5|

## JNE

Jump if Not Equal

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x7d|2|4|

## JPL

Jump if Positive

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0xfd|2|4|

## JSR

Jump to Subroutine

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x4a|2|7|

## JVC

Jump if Overflow Clear

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0xbd|2|4|

## JVS

Jump if Overflow Set

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x9d|2|4|

## LDA

Load A

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x21|2|4|
|AB - Absolute|0x41|2|5|
|AX - Absolute+X|0x61|2|6|
|AY - Absolute+Y|0x81|2|6|
|IX - Indexed Indirect (X)|0xa1|2|7|
|IY - Indirect Indexed (Y)|0xc1|2|7|

## LDX

Load X

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x31|2|4|
|AB - Absolute|0x51|2|5|
|AY - Absolute+Y|0x91|2|6|

## LDY

Load Y

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x33|2|4|
|AB - Absolute|0x53|2|5|
|AX - Absolute+X|0x73|2|6|

## LSR

Logical Shift Right

**Flags:** CZ-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AA - Accumulator|0x18|1|4|
|AB - Absolute|0x58|2|8|
|AX - Absolute+X|0x78|2|x|

## NOP

No Operation

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x00|1|3|

## NOT

Bitwise NOT A

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AA - Accumulator|0x10|1|3|

## ORA

Logical Inclusive OR

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x3e|2|5|
|AB - Absolute|0x5e|2|6|
|AX - Absolute+X|0x7e|2|7|
|AY - Absolute+Y|0x9e|2|7|
|IX - Indexed Indirect (X)|0xbe|2|8|
|IY - Indirect Indexed (Y)|0xde|2|8|

## OUT

Output A

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x01|1|3|

## PHA

Push A

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x16|1|4|

## PHP

Push Processor Status

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x09|1|4|

## PLA

Pull A

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x1e|1|5|

## PLP

Pull Processor Status

**Flags:** CZVN

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x0f|1|5|

## ROL

Rotate Left

**Flags:** CZ-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AA - Accumulator|0x19|1|4|
|AB - Absolute|0x59|2|8|
|AX - Absolute+X|0x79|2|x|

## ROR

Rotate Right

**Flags:** CZ-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AA - Accumulator|0x1a|1|4|
|AB - Absolute|0x5a|2|8|
|AX - Absolute+X|0x7a|2|x|

## RTS

Return from Subroutine

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x0a|1|5|

## SBC

Subtract with Carry

**Flags:** CZVN

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x26|2|5|
|AB - Absolute|0x46|2|6|
|AX - Absolute+X|0x66|2|7|
|AY - Absolute+Y|0x86|2|7|
|IX - Indexed Indirect (X)|0xa6|2|8|
|IY - Indirect Indexed (Y)|0xc6|2|8|

## SEC

Set Carry

**Flags:** C---

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x23|1|3|

## STA

Store A

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x42|2|5|
|AX - Absolute+X|0x62|2|6|
|AY - Absolute+Y|0x82|2|6|
|IX - Indexed Indirect (X)|0xa2|2|7|
|IY - Indirect Indexed (Y)|0xc2|2|7|

## STX

Store X

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x52|2|5|
|AY - Absolute+Y|0x92|2|6|

## STY

Store Y

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x54|2|5|
|AX - Absolute+X|0x74|2|6|

## TAX

Transfer A to X

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x71|1|3|

## TAY

Transfer A to Y

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x93|1|3|

## TSX

Transfer SP to X

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0xb1|1|3|

## TXA

Transfer X to A

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x72|1|3|

## TXS

Transfer X to SP

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0xb2|1|3|

## TYA

Transfer Y to A

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x94|1|3|


*this file was generated by nqsap-instructions.py at 25-Mar-2021 11:57:28*

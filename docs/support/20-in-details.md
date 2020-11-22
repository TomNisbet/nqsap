---
title: "NQSAP Instructions"
permalink: /docs/instructions/
excerpt: "Instruction set for the NQSAP Computer"
---

|           |           |           |           |           |           |           |           |
|:---:      |:---:      |:---:      |:---:      |:---:      |:---:      |:---:      |:---:      |
|[ADC](#ADC)|[AND](#AND)|[ASL](#ASL)|[BCC](#BCC)|[BCS](#BCS)|[BEQ](#BEQ)|[BIT](#BIT)|[BMI](#BMI)|
|[BNE](#BNE)|[BPL](#BPL)|[BVC](#BVC)|[BVS](#BVS)|[CLC](#CLC)|[CLV](#CLV)|[CMP](#CMP)|[CPX](#CPX)|
|[CPY](#CPY)|[DEA](#DEA)|[DEC](#DEC)|[DEX](#DEX)|[DEY](#DEY)|[EOR](#EOR)|[HLT](#HLT)|[INA](#INA)|
|[INC](#INC)|[INX](#INX)|[INY](#INY)|[JCC](#JCC)|[JCS](#JCS)|[JEQ](#JEQ)|[JMI](#JMI)|[JMP](#JMP)|
|[JNE](#JNE)|[JPL](#JPL)|[JSR](#JSR)|[JVC](#JVC)|[JVS](#JVS)|[LDA](#LDA)|[LDX](#LDX)|[LDY](#LDY)|
|[LSR](#LSR)|[NOP](#NOP)|[NOT](#NOT)|[ORA](#ORA)|[OUT](#OUT)|[PHA](#PHA)|[PLA](#PLA)|[ROL](#ROL)|
|[ROR](#ROR)|[RTS](#RTS)|[SBC](#SBC)|[SEC](#SEC)|[STA](#STA)|[STX](#STX)|[STY](#STY)|[TAX](#TAX)|
|[TAY](#TAY)|[TSX](#TSX)|[TXA](#TXA)|[TXS](#TXS)|[TYA](#TYA)|

## ADC

Add with Carry

**Flags:** CZVN

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x29|2||
|AB - Absolute|0x49|2||
|AX - Absolute+X|0x69|2||
|AY - Absolute+Y|0x89|2||
|IX - Indexed Indirect (X)|0xa9|2||
|IY - Indirect Indexed (Y)|0xc9|2||

## AND

Logical AND

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x3b|2||
|AB - Absolute|0x5b|2||
|AX - Absolute+X|0x7b|2||
|AY - Absolute+Y|0x9b|2||
|IX - Indexed Indirect (X)|0xbb|2||
|IY - Indirect Indexed (Y)|0xdb|2||

## ASL

Arithmetic Shift Left

**Flags:** CZ-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AA - Accumulator|0x0c|1||
|AB - Absolute|0x4c|1||
|AX - Absolute+X|0x6c|1||

## BCC

Branch if Carry Clear

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|RE - Relative|0x2a|2||

## BCS

Branch if Carry Set

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|RE - Relative|0x2b|2||

## BEQ

Branch if Equal

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|RE - Relative|0x6b|2||

## BIT

Bit Test

**Flags:** -Z--

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x1b|2||

## BMI

Branch if Minus

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|RE - Relative|0x8b|2||

## BNE

Branch if Not Equal

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|RE - Relative|0x6a|2||

## BPL

Branch if Positive

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|RE - Relative|0x8a|2||

## BVC

Branch if Overflow Clear

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|RE - Relative|0xaa|2||

## BVS

Branch if Overflow Set

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|RE - Relative|0xab|2||

## CLC

Clear Carry

**Flags:** C---

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x17|1||

## CLV

Clear Overflow

**Flags:** --V-

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x57|1||

## CMP

Compare A

**Flags:** CZVN

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x31|2||
|AB - Absolute|0x51|2||
|AX - Absolute+X|0x71|2||
|AY - Absolute+Y|0x91|2||
|IX - Indexed Indirect (X)|0xb1|2||
|IY - Indirect Indexed (Y)|0xd1|2||

## CPX

Compare X

**Flags:** CZVN

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x32|2||
|AB - Absolute|0x52|2||

## CPY

Compare Y

**Flags:** CZVN

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x33|2||
|AB - Absolute|0x53|2||

## DEA

Decrement A

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AA - Accumulator|0x2f|1||

## DEC

Decrement Memory

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x4f|2||
|AX - Absolute+X|0x6f|1||

## DEX

Decrement X

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0xaf|1||

## DEY

Decrement Y

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0xcf|1||

## EOR

Exclusive OR

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x36|2||
|AB - Absolute|0x56|2||
|AX - Absolute+X|0x76|2||
|AY - Absolute+Y|0x96|2||
|IX - Indexed Indirect (X)|0xb6|2||
|IY - Indirect Indexed (Y)|0xd6|2||

## HLT

Halt

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x1f|1|3|

## INA

Increment A

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AA - Accumulator|0x20|1||

## INC

Increment Memory

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x40|2||
|AX - Absolute+X|0x60|2||

## INX

Increment X

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0xa0|1||

## INY

Increment Y

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0xc0|1||

## JCC

Jump if Carry Clear

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0xb7|2||

## JCS

Jump if Carry Set

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0xd7|2||

## JEQ

Jump if Equal

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0xd8|2||

## JMI

Jump if Minus

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0xd9|2||

## JMP

Jump

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x4b|2||
|IN - Indirect|0x0b|2||

## JNE

Jump if Not Equal

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0xb8|2||

## JPL

Jump if Positive

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0xb9|2||

## JSR

Jump to Subroutine

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x4a|2||

## JVC

Jump if Overflow Clear

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0xba|2||

## JVS

Jump if Overflow Set

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0xda|2||

## LDA

Load A

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x21|2||
|AB - Absolute|0x41|2||
|AX - Absolute+X|0x61|2||
|AY - Absolute+Y|0x81|2||
|IX - Indexed Indirect (X)|0xa1|2||
|IY - Indirect Indexed (Y)|0xc1|2||

## LDX

Load X

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x24|2||
|AB - Absolute|0x44|2||
|AY - Absolute+Y|0x84|2||

## LDY

Load Y

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x27|2||
|AB - Absolute|0x47|2||
|AX - Absolute+X|0x67|2||

## LSR

Logical Shift Right

**Flags:** CZ-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AA - Accumulator|0x18|1||
|AB - Absolute|0x58|2||
|AX - Absolute+X|0x78|2||

## NOP

No Operation

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x00|1|2|

## NOT

Bitwise NOT A

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AA - Accumulator|0x10|1||

## ORA

Logical Inclusive OR

**Flags:** -Z-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x3e|2||
|AB - Absolute|0x5e|2||
|AX - Absolute+X|0x7e|2||
|AY - Absolute+Y|0x9e|2||
|IX - Indexed Indirect (X)|0xbe|2||
|IY - Indirect Indexed (Y)|0xde|2||

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
|IP - Implicit|0x16|1||

## PLA

Pull A

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x1e|1||

## ROL

Rotate Left

**Flags:** CZ-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AA - Accumulator|0x19|1||
|AB - Absolute|0x59|2||
|AX - Absolute+X|0x79|2||

## ROR

Rotate Right

**Flags:** CZ-N

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AA - Accumulator|0x1a|1||
|AB - Absolute|0x5a|2||
|AX - Absolute+X|0x7a|2||

## RTS

Return from Subroutine

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x0a|1||

## SBC

Subtract with Carry

**Flags:** CZVN

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IM - Immediate|0x26|2||
|AB - Absolute|0x46|2||
|AX - Absolute+X|0x66|2||
|AY - Absolute+Y|0x86|2||
|IX - Indexed Indirect (X)|0xa6|2||
|IY - Indirect Indexed (Y)|0xc6|2||

## SEC

Set Carry

**Flags:** C---

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x37|1||

## STA

Store A

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x42|2||
|AX - Absolute+X|0x62|2||
|AY - Absolute+Y|0x82|2||
|IX - Indexed Indirect (X)|0xa2|2||
|IY - Indirect Indexed (Y)|0xc2|2||

## STX

Store X

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x45|2||
|AY - Absolute+Y|0x85|2||

## STY

Store Y

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|AB - Absolute|0x48|2||
|AX - Absolute+X|0x68|2||

## TAX

Transfer A to X

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x64|1|3|

## TAY

Transfer A to Y

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x87|1|3|

## TSX

Transfer SP to X

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0xa4|1|3|

## TXA

Transfer X to A

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x65|1|3|

## TXS

Transfer X to SP

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0xa5|1|3|

## TYA

Transfer Y to A

**Flags:** ----

|Mode|Opcode|Bytes|Cycles|
:--- |:---: |:---:|:---: |
|IP - Implicit|0x88|1|3|


*this file was generated by nqsap-instructions.py at 22-Nov-2020 11:53:49*

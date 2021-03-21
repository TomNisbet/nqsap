---
title: "NQSAP and 6502 Instructions"
permalink: /docs/in-summary/
excerpt: "Instruction set summary for the NQSAP Computer"
---

## 6502 Compatibility

The NQSAP has a 6502-inspired architecture and instruction set.  The instructions and
registers are similar, but the opcodes of the NQSAP do not map to the same values as
a 6502.  This means that the NQSAP and 6502 are somewhat compatible at the assembly
language source level, but the object code they use is completely different.

The major difference in the two implementations is that the NQSAP is an 8-bit only machine
with no 16-bit addressing modes.  This means that the absolute addressing modes and the
zero-page addressing modes are the same because all memory is in page zero.  For
simplicity of the documentation, the instructions are listed as using absolute,
absolute+X, and absolute+Y modes instead of the zero-page modes.

Two other features of the 6502 are also not implemented: decimal mode and interrupts.
This removes a few instructions from the complete set.

One interesting difference between the two implementations is the branch instructions.
On the 6502, these use fewer cycles than an unconditional jump instruction because they
only need to specify a single byte offset instead of a two byte absolute or relative
address.  On the NQSAP, the branch instructions are expensive because they need to save
and restore one of the index registers in order to calculate relative addresses.  A set
of conditional jump instructions was added that mimics all of the conditional branches
but uses absolute addressing instead of relative addressing.  These jumps use only four
cycles instead of the eight needed for a conditional branch.

## Implementation Progress

Most of the instructions and all of the addressing modes listed here are already
implemented.  The area that needs the most work is the flags.  The current design only has
the Carry and Zero flags.  A major redesign is in progress that will add the Negative and
Overflow flags and will expand the current flags capabilities to allow setting, clearing,
and updating of individual flags rather than updating the entire flags register at once.
The new design will also add new sources to the flag inputs so that, for example, the C
flags can be updated by the shift/rotate instructions.

A second redesign is planned for the A register to enable all of the shift and rotate
functions of the 6502.  Currently, only ASL is supported because it can be done using the
74LS181 ALU chip.

The compare instructions are not implemented yet because they need the ALU to be in
subtract mode.  The ALU operation select bits are hard-wired to the Instruction Register,
so there are a limited number of opcodes that are available for each ALU operation.  The
SBC instructions are using the subtract opcodes, so there is no room to implement the
compate instructions.  A change will be made to allow the ALU select bits to be
overridded to allow the compare instructions.  This is a fairly simple change, but may
require shifting a few components to free up breadboard space.

Some of the single operand memory instructions, like INC, DEC, and ASL are not available
for the indexed addressing modes because they require too many instruction cycles.  These
instructions need to save and restore the A register and that can't be done in the eight
cycles available.  A register/flags redesign could fix this.  Another possibility is to
extend the maximum microinstruction cycles from eight to sixteen.
## Instructions Common to 6502 and NQSAP

|Name|Description|Flags|Address Modes|
|:---|:---|:---:|:---|
|[ADC](../in-details#adc)|Add with Carry|CZVN|IM,AB,AX,AY,IX,IY|
|[AND](../in-details#and)|Logical AND|-Z-N|IM,AB,AX,AY,IX,IY|
|[ASL](../in-details#asl)<sub>1</sub>|Arithmetic Shift Left|CZ-N|AA,AB,AX|
|[BCC](../in-details#bcc)|Branch if Carry Clear|----|RE|
|[BCS](../in-details#bcs)|Branch if Carry Set|----|RE|
|[BEQ](../in-details#beq)|Branch if Equal|----|RE|
|[BIT](../in-details#bit)<sub>2</sub>|Bit Test|-Z--|AB|
|[BMI](../in-details#bmi)<sub>3</sub>|Branch if Minus|----|RE|
|[BNE](../in-details#bne)|Branch if Not Equal|----|RE|
|[BPL](../in-details#bpl)<sub>3</sub>|Branch if Positive|----|RE|
|[BVC](../in-details#bvc)<sub>3</sub>|Branch if Overflow Clear|----|RE|
|[BVS](../in-details#bvs)<sub>3</sub>|Branch if Overflow Set|----|RE|
|[CLC](../in-details#clc)<sub>3</sub>|Clear Carry|C---|IP|
|[CLV](../in-details#clv)<sub>3</sub>|Clear Overflow|--V-|IP|
|[CMP](../in-details#cmp)<sub>4</sub>|Compare A|CZ-N|IM,AB,AX,AY,IX,IY|
|[CPX](../in-details#cpx)<sub>4</sub>|Compare X|CZ-N|IM,AB|
|[CPY](../in-details#cpy)<sub>4</sub>|Compare Y|CZ-N|IM,AB|
|[DEC](../in-details#dec)|Decrement Memory|-Z-N|AB,AX|
|[DEX](../in-details#dex)|Decrement X|-Z-N|IP|
|[DEY](../in-details#dey)|Decrement Y|-Z-N|IP|
|[EOR](../in-details#eor)|Exclusive OR|-Z-N|IM,AB,AX,AY,IX,IY|
|[INC](../in-details#inc)|Increment Memory|-Z-N|AB,AX|
|[INX](../in-details#inx)|Increment X|-Z-N|IP|
|[INY](../in-details#iny)|Increment Y|-Z-N|IP|
|[JMP](../in-details#jmp)|Jump|----|AB,IN|
|[JSR](../in-details#jsr)|Jump to Subroutine|----|AB|
|[LDA](../in-details#lda)<sub>5</sub>|Load A|-Z-N|IM,AB,AX,AY,IX,IY|
|[LDX](../in-details#ldx)<sub>5</sub>|Load X|-Z-N|IM,AB,AY|
|[LDY](../in-details#ldy)<sub>5</sub>|Load Y|-Z-N|IM,AB,AX|
|[LSR](../in-details#lsr)<sub>6</sub>|Logical Shift Right|CZ-N|AA,AB,AX|
|[NOP](../in-details#nop)|No Operation|----|IP|
|[ORA](../in-details#ora)|Logical Inclusive OR|-Z-N|IM,AB,AX,AY,IX,IY|
|[PHA](../in-details#pha)|Push A|----|IP|
|[PHP](../in-details#php)|Push Processor Status|----|IP|
|[PLA](../in-details#pla)<sub>5</sub>|Pull A|-Z-N|IP|
|[PLP](../in-details#plp)|Pull Processor Status|----|IP|
|[ROL](../in-details#rol)<sub>6</sub>|Rotate Left|CZ-N|AA,AB,AX|
|[ROR](../in-details#ror)<sub>6</sub>|Rotate Right|CZ-N|AA,AB,AX|
|[RTS](../in-details#rts)|Return from Subroutine|----|IP|
|[SBC](../in-details#sbc)|Subtract with Carry|CZVN|IM,AB,AX,AY,IX,IY|
|[SEC](../in-details#sec)|Set Carry|C---|IP|
|[STA](../in-details#sta)|Store A|----|AB,AX,AY,IX,IY|
|[STX](../in-details#stx)|Store X|----|AB,AY|
|[STY](../in-details#sty)|Store Y|----|AB,AX|
|[TAX](../in-details#tax)<sub>5</sub>|Transfer A to X|-Z-N|IP|
|[TAY](../in-details#tay)<sub>5</sub>|Transfer A to Y|-Z-N|IP|
|[TSX](../in-details#tsx)<sub>5</sub>|Transfer SP to X|-Z-N|IP|
|[TXA](../in-details#txa)<sub>5</sub>|Transfer X to A|-Z-N|IP|
|[TXS](../in-details#txs)|Transfer X to SP|----|IP|
|[TYA](../in-details#tya)<sub>5</sub>|Transfer Y to A|-Z-N|IP|

**Notes:**
1. Does not set C flag.  Will be fixed in flags redesign
1. Does not set V and N flags
1. Requires V and N flags and ability to update, set, and clear individual flags. Redesign in progress to replace flags register with D flip-flops
1. Need to share ALU opcode with the SBC operation.  Redesign in progress to override IR and force ALU into subtract mode
1. Zero and Negative flags not yet set for non-ALU instructions
1. Requires new A register hardware
## 6502 Instructions Not Implemented in NQSAP

|Name|Description|Flags|Address Modes|
|:---|:---|:---:|:---|
|[BRK](../in-details#brk)<sub>1</sub>|Force Interrupt|----||
|[CLD](../in-details#cld)<sub>2</sub>|Clear Decimal Mode|----||
|[CLI](../in-details#cli)<sub>1</sub>|Clear Interrupt Disable|----||
|[RTI](../in-details#rti)<sub>1</sub>|Return from Interrupt|----||
|[SED](../in-details#sed)<sub>2</sub>|Set Decimal Mode|----||
|[SEI](../in-details#sei)<sub>1</sub>|Set interrupt Disable|----||

**Notes:**
1. No support for interrupts
1. No support for decimal mode
## NQSAP Extensions

|Name|Description|Flags|Address Modes|
|:---|:---|:---:|:---|
|[DEA](../in-details#dea)|Decrement A|-Z-N|AA|
|[INA](../in-details#ina)|Increment A|-Z-N|AA|
|[JCC](../in-details#jcc)|Jump if Carry Clear|----|AB|
|[JCS](../in-details#jcs)|Jump if Carry Set|----|AB|
|[JEQ](../in-details#jeq)|Jump if Equal|----|AB|
|[JMI](../in-details#jmi)|Jump if Minus|----|AB|
|[JNE](../in-details#jne)|Jump if Not Equal|----|AB|
|[JPL](../in-details#jpl)|Jump if Positive|----|AB|
|[JVC](../in-details#jvc)|Jump if Overflow Clear|----|AB|
|[JVS](../in-details#jvs)|Jump if Overflow Set|----|AB|
|[NOT](../in-details#not)|Bitwise NOT A|-Z-N|AA|
|[OUT](../in-details#out)|Output A|----|IP|


*this file was generated by nqsap-instructions.py at 30-Dec-2020 12:27:09*

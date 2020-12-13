---
title: "ALU"
permalink: /docs/alu/
excerpt: "Building the Arithmetic Logic Unit (ALU) of the NQSAP computer"
---

[![Arithmetic Logic Unit (ALU)](../../assets/images/alu-1.jpg "ALU"){:width="400px"}](../../assets/images/alu-1.jpg)

The NQSAP computer uses a pair of 74LS181 4-bit ALU chips instead of the simple
adder/subtractor circuit in the SAP-1.  The advantage to this is a greatly increased set
of operations available, including increment/decrement as well as bitwise AND OR, and XOR.

The disadvantage to the use of an ALU chip is that the 74181 requires 6 control lines to
select an operation, rather than the single ADD/SUBTRACT needed for the simple adder.

In the NQSAP design, the Mode bit and the 4 Operation Select bits are hard-wired to the
Instruction Register, so that the opcode of the instruction directly determines the
operation selected on the ALU.  This saves the need for 5 additional control lines from
the microcode ROMs.  It also makes the microcode for all ALU operations identical, so they
can be generated programmatically in the Arduino code.  Because the Mode and Select lines
are wired to the Instruction Register, only the Carry-in signal is connected to the
microcode ROMs.

In addition to the 74181 ALUs, the NQSAP ALU module needs a few more chips.  As with other
read registers in the NQSAP, a 74LS245 bus transceiver is used to selectively place the
ALU result on the bus.  

Note that the ALU result is a read-only register.

## 74181 ALU operations used by NQSAP

|M | Cn| S3| S2| S1| S0|Operation|
|:---:|:---:|:---:|:---:|:---:|:---:|---|
|0 | 0 | 0 | 0 | 0 | 0 | A plus 1
|0 | 0 | 0 | 1 | 1 | 0 | A minus B
|0 | 1 | 1 | 0 | 0 | 1 | A plus B
|0 | 1 | 1 | 1 | 0 | 0 | A plus A _[left shift]_
|0 | 1 | 1 | 1 | 1 | 1 | A minus 1
|1 | x | 0 | 0 | 0 | 0 | not A
|1 | x | 0 | 1 | 1 | 0 | A xor B
|1 | x | 1 | 0 | 1 | 0 | B
|1 | x | 1 | 0 | 1 | 1 | A and B
|1 | x | 1 | 1 | 1 | 0 | A or B
|====

The B operation is not used by a standalone instruction, but the ALU functionality of it
was used by the CALL instruction so that B can be used for temporary storage.  The B
register was later redesigned to add its own bus transceiver to allow direct read access.

The ALU also has an all-zero bits operation and an all-one bits operation that may be
useful.  While there isn't a good application for these as user-accessible instructions,
they might be helpful in the microcode to get all zeros or all ones onto the bus.  For
example, a single-byte CLR instruction could leverage all-zero to implement a register
clear that would be faster and more compact that using a load immediate 0 instruction.

## Flags

A status register, containing a zero flag and a carry flag, is used to store results from
ALU operations.  The status register is loaded by a control line from the microcode ROM.
The two outputs of the status register drive the _A<sub>13</sub>_ and _A<sub>14</sub>_
address lines of the microcode ROMs.

### Zero flag

The 74181 ALU does not have an output to indicate a zero result from an operation so a
few NOR and AND gates are used (as in the Ben Eater design) to detect all zeroes at the
ALU output.  The ALU does have an _A=B_ bit that can be used for comparison operations,
but it is not used in the NQSAP design.

**Update:** the NOR/AND solution was replaced with a single 74HCT688 8-bit comparator.
*One set of inputs is tied low, so the comparator matches when the other set of inputs are
*all zero. In addition, the inputs of the comparator are now tied to the bus instead of
*the ALU output, so the zero detect can be used with non-ALU operations like register
*loads or transfers.

### Carry flag

Using the carry flag output (C<sub>n+4</sub>) as a processor flag is not straightforward
to understand because the logic state used to indicate an overflow changes depending on
the operation.  For the addition operations, a logic LOW indicates carry occurred, but
logic HIGH is used to indicate borrow needed for subtraction.  See the
[74181 ALU notes](../74181-alu-notes/) section for an explanation of why the chip does
this.

|Selects|Operation|C<sub>n+4</sub> on overflow|
|:---:  |:---:    |:---:|
| LLLL  | A + 1   |  L  |
| LHHL  | A - B   |  H  |
| HLLH  | A + B   |  L  |
| HHLL  | A + A   |  L  |
| HHHH  | A - 1   |  H  |
|====

The NQSAP addition and subtraction operations are modeled after the 6502 processor.  An
addition with carry instruction will produce A+B when carry is clear and A+B+1 when carry
is set.  The carry flag will be set at the completion of the operation if the addition
carried into the non-existent ninth bit.

A subtraction with carry operation will produce A-B-1 when the carry bit is clear and A-B
when the carry is set.  The carry flag will be cleared at the completion of the operation
if the subtraction required a borrow from the non-existent ninth bit.

This usage is consistent with the 74181 ALU, but the use of the flag is inverted because
the 74181 uses an active low carry signal.  The C<sub>n+4</sub> carry out signal from the
high ALU is inverted to provide the 6502-like flag.

The flags are currently implemented with a single 74173 4-bit flags register, meaning that
any operation that needs to set flags will set them all.  This will be replaced with
individual D flip flops. This will require more microcode control lines, but will offer
granular control over when the flags change. It will also allow instructions to set or
reset individual flags.  This is particularly important because the addition and
subtraction instructions always use the carry flag, so a clear carry is needed to do an
initial add or subtract operation.

## Bill of Materials

* 74LS181 4-bit Arithmetic Logic Unit (2)
* 74HCT245 8-bit bus transceiver (1)

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
are wired to the Instruction Register, only the Carry-in signal needs to be provided to
control the selected ALU function.

[![NQSAP ALU schematic)](../../assets/images/alu-schematic.png "ALU schematic"){:width="400px"}](../../assets/images/alu-schematic.png)

The inputs to the ALU are the sHift Register (H) and the B register.  Neither of these
registers is visible to the user instructions, but that can be written and read by the
microcode.  By convention, the H register always contains the same value as the A register
at the end of an instruction, but it can be used independently by the microcode within
an instruction.  All ALU instructions write their result to the A register.

Note that the subtract and compare instructions both need the ALU to be in subtract mode.
Because the ALU select lines are hard-wired to the IR, there are only eight opcodes
available that put the ALU in the correct mode.  To create the sixteen different opcodes
that are needed for all of the addressing mode combinations of the subtract and compare
instructions, a NOR gate is placed between the inverted IR output and the ALU S0 input.
The other NOR input is the microcode ROM LF (aLu Force) line.  When this is asserted,
the ALU S0 is forced to zero.  This is used to create a new set of eight subtract mode
instructions by setting the ALU select bits to 0110 when the low IR bits are 0111.  The
ALU operation for 0111 would normally be A and not B, which isn't useful.

Note that the schematic image is out of date.  The L-S0 line is shown as directly
connected to IR-Q0.  It should instead be driven by the ALU-S0 signal that is shown on the
[Flags](../flags/) schematic.

In addition to the 74181 ALUs, the NQSAP ALU module needs a few more chips.  As with other
read registers in the NQSAP, a 74LS245 bus transceiver is used to selectively place the
ALU result on the bus.  

Note that the ALU result is a read-only register.

## 74181 ALU operations used by NQSAP

|M | Cn| S3| S2| S1| S0|Operation|
|:---:|:---:|:---:|:---:|:---:|:---:|---|
|0 | 0 | 0 | 0 | 0 | 0 | A plus 1
|0 | 0 | 0 | 0 | 1 | 1 | zero
|0 | 0 | 0 | 1 | 1 | 0 | A minus B
|0 | 1 | 0 | 0 | 1 | 1 | all ones
|0 | 1 | 1 | 0 | 0 | 1 | A plus B
|0 | 1 | 1 | 1 | 0 | 0 | A plus A _[left shift]_
|0 | 1 | 1 | 1 | 1 | 1 | A minus 1
|1 | x | 0 | 0 | 0 | 0 | not A
|1 | x | 0 | 1 | 1 | 0 | A xor B
|1 | x | 1 | 0 | 1 | 0 | B
|1 | x | 1 | 0 | 1 | 1 | A and B
|1 | x | 1 | 1 | 1 | 0 | A or B
|====

The ALU all-zero bits and all-one bits operations are used in the microcode to get zeros
or ones onto the bus for the flag set and clear operations.

The B operation is no longer used.  It was used by the CALL instruction to read B for
temporary storage.  The B register was later redesigned to add its own bus transceiver to
allow direct read access.

## Carry flag

Using the 74LS181's carry flag output (C<sub>n+4</sub>) as a processor flag is not
straightforward to understand because the logic state used to indicate an overflow is
dependent on the operation.  For the addition operations, a logic LOW indicates carry
occurred, but logic HIGH is used to indicate borrow needed for subtraction.  See the
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

## Bill of Materials

* 74LS181 4-bit Arithmetic Logic Unit (2)
* 74HCT245 8-bit bus transceiver (1)

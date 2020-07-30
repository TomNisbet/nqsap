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

Note that the ALU result is a read-only register and the B register is write-only.  It is
possible to read the B register (for scratch storage as part of microcode, for example)
by setting the 74LS181 ALU operation to "B" and then reading the ALU result.  Normally,
there would be no reason to read B because it is only used as an ALU source register and
not as a general-purpose register.

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
|1 | x | 1 | 0 | 1 | 1 | A and B
|1 | x | 1 | 1 | 1 | 0 | A or B
|====

The ALU also has an all-zero bits operation and an all-one bits operation that may be
useful.  While there isn't a good application for these as user-accessible instructions,
they might be helpful in the microcode to get all zeros or all ones onto the bus.  For
example, a single-byte CLR instruction could leverage all-zero to implement a register
clear that would be faster and move compact that using a load immediate 0 instruction.

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

### Carry flag

Using the carry flag output (C<sub>n+4</sub>) as a processor flag is not straightforward because the
logic state used to indicate an overflow changes depending on the operation.  For the
addition operations, a logic LOW indicates overflow, but logic HIGH is used for
subtraction.  See the [74181 ALU notes](../74181-alu-notes/) section for an explanation of
why the chip does this.

|Selects|Operation|C<sub>n+4</sub> on overflow|
|:---:  |:---:    |:---:|
| LLLL  | A + 1   |  L  |
| LHHL  | A - B   |  H  |
| HLLH  | A + B   |  L  |
| HHLL  | A + A   |  L  |
| HHHH  | A - 1   |  H  |
|====

There are several approaches that might be used to provide conditional jumps based on the
carry flag.  One would be to use an additional control line from the microcode ROM and an
XOR gate to selectively invert the C<sub>n+4</sub> signal.  This requires minimal hardware
and a small change to the microcode, but it produces a consistent flag that would be set
on either an addition overflow or a subtraction underflow.

Another possibility would be to just leave the flag as is (or always invert it) and just
change the interpretation of the flag.  This would require the programmer to know that
a jump on carry instruction would be used after addition instructions, but a jump on no
carry would be used after subtraction.  This is somewhat confusing, but requires no real
design on the computer.

A follow-on to the previous method would be to add JB (jump on borrow) and JNB (jump on no
borrow) instructions that behave oppositely of the JC and JNC instructions.  This would
essentially create a virtual borrow flag.

A final possibility would be to replace the 74173 4-bit flags register with individual D
flip flops.  This would also require a new microcode control line, but would offer more
control over when the flags change.  With this approach, an XOR gate on the C<sub>n</sub>
and C<sub>n+4</sub> signals (see the [74181 ALU notes](../74181-alu-notes/)) would provide a
normalized carry flag for the addition and subtraction operations.  The flags control
lines would not load the carry flag for the increment and decrement operations, because
those can easily detect overflow using the zero flag instead.  An additional advantage to
this idea is that it allows the carry flag to be unaffected by the non-arithmetic operations, and AND and OR, where it doesn't really apply.

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

The 74181 ALU does not have an output to indicate a zero result from an operation so a few
NOR and AND gates are used (as in the Ben Eater design) to detect all zeroes at the ALU
output.  The ALU does have an [A=B bit](#ab_bit) that is not used in the NQSAP design.

Note that the ALU result is a read-only register and the B register is write-only.  It is
possible to read the B register (for scratch storage as part of microcode, for example)
by setting the 74LS181 ALU operation to "B" and then reading the ALU result.  Normally,
there would be no reason to read B because it is only used as an ALU source register and
not as a general-purpose register.

## 74LS181 / 74181 ALU notes

### Pitfalls
#### A=B Bit

The A=B bit does not detect that the A and B inputs are the same.  Instead, it is active
when all result bits are one. This can be used with the A minus 1 operation to detect
A==0, or with A-B-1 to detect A=B, but it is not clear how all ones is useful as the
result of operations on A and B.  A bit that detects an all zero result would be more
useful.

**NOTE:** The A=B pin is wired as low or tri-state rather than low or high, so it will
never display anything if an LED is wired from A=B to ground.  Instead, the state can be
observed by wiring an LED and resistor from Vcc to A=B pin. See <https://electronics.stackexchange.com/a/454342> for details.

### Conflicting datasheets

Several datasheets for the 74181 have errors or inconsistencies:
* The Texas Instruments 1988 datasheet appears to be correct
* The Fairchild 2000 datasheet has differences compared to the TI sheet
  * the _A and not B_ operation is incorrectly listed as _A and B_
  * the _not (A xor B)_ operation is listed as _not A xor not B_ (which would be the same
      as just _A xor B_)
* The Texas Instruments 1983 Databook shows the _A plus A_ operation as _A_

## Useful Operations

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

## All Operations

The following is a list of all possible operations of the ALU using a simplified syntax.
All operations are spelled out explicitly, like 'or' and 'plus' instead of '+' and 'plus'
as in the datasheets.

### Arithmetic
```
M Cn S3 S2 S1 S0
0  0  0  0  0  0  A plus 1
0  0  0  0  0  1  (A or B) plus 1
0  0  0  0  1  0  (A or not B) plus 1
0  0  0  0  1  1  zero   [all zeroes]
0  0  0  1  0  0  A plus (A and not B) plus 1
0  0  0  1  0  1  (A or B) plus (A and not B) plus 1
0  0  0  1  1  0  A minus B
0  0  0  1  1  1  A and not B
0  0  1  0  0  0  A plus (A and B) plus 1
0  0  1  0  0  1  A plus B plus 1
0  0  1  0  1  0  (A or not B) plus (A and B) plus 1
0  0  1  0  1  1  A and B
0  0  1  1  0  0  A plus A plus 1
0  0  1  1  0  1  (A or B) plus A plus 1
0  0  1  1  1  0  (A or not B) plus A plus 1
0  0  1  1  1  1  A
0  1  0  0  0  0  A
0  1  0  0  0  1  A or B
0  1  0  0  1  0  A or not B
0  1  0  0  1  1  negative 1   [all ones]
0  1  0  1  0  0  A plus (A and not B)
0  1  0  1  0  1  (A or B) plus (A and not B)
0  1  0  1  1  0  A minus B minus 1
0  1  0  1  1  1  (A and not B) minus 1
0  1  1  0  0  0  A plus (A and B)
0  1  1  0  0  1  A plus B
0  1  1  0  1  0  (A or not B) plus (A and B)
0  1  1  0  1  1  (A and B) minus 1
0  1  1  1  0  0  A plus A
0  1  1  1  0  1  (A or B) plus A
0  1  1  1  1  0  (A or not B) plus A
0  1  1  1  1  1  A minus 1
```

### Logic
```
M Cn S3 S2 S1 S0
1  x  0  0  0  0  not A
1  x  0  0  0  1  not A or not B
1  x  0  0  1  0  not A and B
1  x  0  0  1  1  0
1  x  0  1  0  0  not (A and B)
1  x  0  1  0  1  not B
1  x  0  1  1  0  A xor B
1  x  0  1  1  1  A and not B
1  x  1  0  0  0  not A or B
1  x  1  0  0  1  not (A xor B)
1  x  1  0  1  0  B
1  x  1  0  1  1  A and B
1  x  1  1  0  0  1
1  x  1  1  0  1  A or not B
1  x  1  1  1  0  A or B
1  x  1  1  1  1  A
```

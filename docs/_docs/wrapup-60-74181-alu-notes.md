---
title: "74181 ALU Notes"
permalink: /docs/74181-alu-notes/
excerpt: "74181 / 74LS181 Arithmetic Logic Unit (ALU) notes"
---

## Pitfalls
### A=B Bit

The _A=B_ bit does not detect that the A and B inputs are the same.  Instead, it is active
when all result bits are one. This can be used with the A minus 1 operation to detect
A==0, or with A-B-1 to detect A=B, but it is not useful for other operations. A bit that detects an all-zero result would seem to be more useful.

**NOTE:** The _A=B_ pin is wired as low or tri-state rather than low or high, so it will
never display anything if an LED is wired from _A=B_ to ground.  Instead, the state can
be observed by wiring an LED and resistor from Vcc to _A=B_ pin. See
<https://electronics.stackexchange.com/a/454342> for details.

### Conflicting datasheets

Several datasheets for the 74181 have errors or inconsistencies:
* The Texas Instruments 1988 datasheet appears to be correct
* The Fairchild 2000 datasheet has differences compared to the TI sheet
  * the _A and not B_ operation is incorrectly listed as _A and B_
  * the _not (A xor B)_ operation is listed as _not A xor not B_ (which would be the same
      as just _A xor B_)
* The Texas Instruments 1983 Databook shows the _A plus A_ operation as _A_

## Carry flag

The carry flag output (C<sub>n+4</sub>) is not a simple output that indicates overflow
for all arithmetic operations.  Instead, it outputs LOW for addition overflow and HIGH
for subtraction overflow.  While this seems confusing at first glance, it makes sense
when seen in the context of chaining multiple ALUs together to do operations on larger
word lengths.

For the purpose of this discussion, some terminology is defined here that is not in the 74181 datasheet:
* CIN, or carry in, refers to the C<sub>n</sub> pin of the ALU
* COUT, or carry out, refers to the C<sub>n+4</sub> pin of the ALU
* The "normal case" refers to an operation that does not cause a carry or borrow condition
* The "upper" and "lower" ALU refer to a case where two ALUs are wired together to do operations on 8 bits, where the lower ALU holds the least significant 4 bits and the upper ALU holds the most significant 4 bits


The CIN pin is active low.  When it is low, any arithmetic operation adds an additional 1
to the final result.

The table below shows five useful arithmetic operations that can be performed by the 74181
ALU.  By showing the CIN=1 and CIN=0 operations side by side, it is  easier to see how
operations are related so that two (or more) ALUs can be used together to work with more
than 4 bits.

| Selects|CIN=H Operation|CIN=L Operation|
|:---: |:---:            |:---:          |
| LLLL | A               | **A + 1**     |
| LHHL | A - B - 1       | **A - B**     |
| HLLH | **A + B**       | A + B + 1     |
| HHLL | **A + A**       | A + A + 1     |
| HHHH | **A - 1**       | A             |
|====

When using more than one ALU, the Mode and Select bits are connected to the same pins on all ALUs.  the COUT (C<sub>n+4</sub>) of the lower ALU is connected to
the CIN (C<sub>n</sub>) of the upper ALU.  The CIN of the lower ALU is used, along with
the Mode and Select bits, to select an operation to be performed.  The COUT of the upper
ALU can be used, with some interpretation, to indicate an overflow of the entire
operation.  

The examples below use two ALUs, but the principles are the same using any arbitrary
number of 74181s to achieve the desired bit width.  There may be delay issues when using
multiple ALUs, but those are beyond the scope of this discussion.  See the 74S182 Carry
Lookahead chip datasheets for details.

For the _A+B_ addition operation, the CIN of the lower ALU is not asserted.  Note that
this means it is in a HIGH state, because the CIN pin is active low. The COUT from the
lower ALU is also not asserted in the normal case where the result of the addition does
not cause an overflow out of the lower 4 bits.  The COUT of the lower ALU is connected to
the CIN of the upper ALU, so both ALUs will do an _A+B_ operation on their respective 4
bits of data.

In the case where the lower ALU addition overflows, the COUT connected to the upper ALU's
CIN is asserted, so the lower ALU will do an _A+B_ operation on its 4 bits, and the upper
ALU will do an _A+B+1_ operation on its 4 bits. This gives the desired result of the carry
from the overflow of the lower ALU cascading into the upper ALU.

The addition cases described above for _A+B_ are identical for the _A+A_ operation as
well.

For subtraction, the no-carry operation is _A-B-1_, but asserting the CIN bit gives an
_A-B_ operation.  This is why CIN must be asserted on the lower ALU for subtraction but
not for addition.  Similar to addition, the lower ALU asserts the same value on COUT as it
receives on CIN for the normal case, so the lower ALU and upper ALU will both perform an
_A-B_ operation on their respective 4 bits.

In the case where the subtraction in the lower ALU needs a borrow from the upper ALU, the
lower ALU will not assert the COUT signal, causing the upper ALU to perform an _A-B-1_
operation.  This effectively borrows a one from the upper ALU value.

From the above operations, it would seem like a carry/borrow bit to indicate 8-bit
overflow/underflow could be implemented by checking to see if the CIN to the lower ALU has
a different value than the COUT of the upper ALU.  This could be accomplished by just an
XOR of the two signals and would work for both the addition and subtraction case.
Unfortunately, the increment and decrement (_A+1_ and _A-1_) operations break this model.

For both addition and subtraction, the upper and lower ALUs perform the same operation in the normal case and perform different operations in the lower ALU overflow case.  The
increment and decrement functions behave differently.

Consider the case to increment the number 5, or 0000 0101 in binary.  The lower ALU will
perform an _A+1_ operation, but the upper ALU must perform an _A_ operation to leave the
upper 4 bits unchanged.  The result would be 6, or 0000 0110.  In this normal case, the
lower ALU will have CIN asserted and the upper ALU will not.  For the overflow case, such
as an increment of 0000 1111, both ALUs will have CIN asserted and will both do an _A+1_
operation, giving 0001 0000 as the result. The decrement operation is similar, with the
ALUs doing different operations in the normal case and the same operation in the lower ALU
overflow case.

The following tables summarize the usage of the carry bits for the 5 arithmetic operations.

The columns in the table represent these pins and conditions:
* Selects - function select bits S<sub>3</sub> to S<sub>0</sub>
* Upper ALU - function performed by lower ALU
* Lower ALU - function performed by upper ALU
* CIN<sub>U</sub> - CIN (C<sub>n</sub>) to upper ALU produced by COUT (C<sub>n+4</sub>) of lower ALU
* CIN<sub>L</sub> - CIN (C<sub>n</sub>) to lower ALU
* COUT<sub>UN</sub> - COUT (C<sub>n+4</sub>) from upper ALU in "normal" (non-overflow) case
* COUT<sub>UC</sub> - COUT (C<sub>n+4</sub>) from upper ALU in overflow case

This table shows the five operations in the normal case, when the lower ALU does not have
an overflow condition.

|Selects|Lower ALU|Upper ALU|CIN<sub>L</sub>|CIN<sub>U</sub>|COUT<sub>UN</sub>|COUT<sub>UC</sub>|
|:---: |:---:      |:---:    |:---:|:---:|:---:|:---:|
| LLLL | A + 1     | A       |  L  |  H  |  H  |  L  |
| LHHL | A - B     | A - B   |  L  |  L  |  L  |  H  |
| HLLH | A + B     | A + B   |  H  |  H  |  H  |  L  |
| HHLL | A + A     | A + A   |  H  |  H  |  H  |  L  |
| HHHH | A - 1     | A       |  H  |  L  |  L  |  H  |
|====

The next table shows the five operations in the case when the lower ALU has an overflow
condition.  The only differences with the previous table are the upper ALU operations that
are produced by the different values produced by the COUT of the lower ALU pin that is
connected to the CIN of the upper ALU.

|Selects|Lower ALU|Upper ALU|CIN<sub>L</sub>|CIN<sub>U</sub>|COUT<sub>UN</sub>|COUT<sub>UC</sub>|
|:---: |:---:      |:---:      |:---:|:---:|:---:|:---:|
| LLLL | A + 1     | A + 1     |  L  |  L  |  H  |  L  |
| LHHL | A - B     | A - B - 1 |  L  |  H  |  L  |  H  |
| HLLH | A + B     | A + B + 1 |  H  |  L  |  H  |  L  |
| HHLL | A + A     | A + A + 1 |  H  |  L  |  H  |  L  |
| HHHH | A - 1     | A - 1     |  H  |  H  |  L  |  H  |
|====

## ALU Operations List

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

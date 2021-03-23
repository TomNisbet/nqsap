---
title: "Flags"
permalink: /docs/flags/
excerpt: "Building the flags and conditional jump logic of the NQSAP computer"
---

[![Flags Design](../../assets/images/flags-circuit.png "flags and jump logic"){:width="400px"}](../../assets/images/flags-circuit.png)

## Initial Design

The initial build supported only a Zero and a Carry flag using a single 74LS173 register
to store the values.  This meant that any instruction that set flags would need to set a
value for both flags.  The conditional jump logic, as in the Ben Eater design, was
implemented in microcode by wiring the status flag register outputs to address lines of
the microcode EEPROMs.  

This design suffers from a few problems:
* Limited number of address lines available to expand to more flags
* Changing flag values causes the control ROM outputs to briefly glitch to unknown values
* Flags cannot be set independently

## New Design (in-progress)

The updated processor status flags and conditional jump logic circuit is the most complex
part of the NQSAP design.  It consumes a large number of the available microcode ROM
outputs.

This design is still a work-in-progress.  Most of it has been prototyped, but a clocking
and ROM output problem is causing the flag registers to load unpredictably.

The new design has the following features:
* Four flags that match the behavior of the 6502's Carry, Zero, Negative, and oVerflow flags
* An instruction's microcode can set any or all of the flags independently
* Flags can be read or written to the bus, allowing push and pull of the processor status
* External hardware to control the conditional jump instructions, requires no ROM address lines

The left side of the schematic contains the logic to determine the flag values to be set.
The 74LS157 in the center allows the flags to be loaded from a hardware source like the ALU
or loaded from the value on the bus.  Each of the four flags is stored in a D flip flop,
implemented as a pair of 74LS74 dual D flip-flops.  On the right of the schematic, the
outputs of the flags go to a 74LS245 that allows them to be placed on the bus.  

The outputs also go to a 74LS151 8-to-1 selector that controls the conditional jump.
Because the flip flops provide both Q and not-Q outputs, the selector can choose to jump
on a flag set or flag clear value with no additional inverters or gates needed.  The
output of the 8-to-1 selector drives the LOAD control of the Program Counter.

Note that in the current iteration, the Carry flag is still driving the EEPROM address
lines rather than going through the selector used by the other three flags.  The carry
flag will be moved to the selector and additional logic will be added for the
unconditional jump instructions.  When the Carry flag is moved from the control ROM,
additional logic will also needed to drive the Carry flag input into the ALU rather than
controlling it though microcode.

The [Opcodes and Flag decoding circuit](https://www.reddit.com/r/beneater/comments/m76ijz/opcodes_and_flag_decoding_circuit/)
post on reddit has a different approach to conditional jumps using hardware.  Instead of
driving the LOAD line of the PC, the circuit sits between the IR and the ROM and
conditionally jams a NOP or JMP instruction to the microcode depending on the state of the
flags.  One interesting part of the design is that the opcodes of the jump instructions
are arranged so that the flag of interest can be determined by bits from the IR.  NQSAP
already does this to drive the ALU select lines for arithmetic and logic operations and it
would likely save some ROM control lines to do it for flags also.  The J0, J1, and J2
lines from the ROM would be replaced with bits from the IR.

## Flag Calculations

The Negative flag is simply the MSB of the data bus.

The Zero flag uses an 8-bit comparator to test for zero.  This saves a chip over the
AND/OR circuit used in the Ben Eater SAP-1 computer but is functionally equivalent.  One
other difference from the SAP-1 is that the zero test is performed on the value on the bus
value instead of the output value of the ALU. This allows the Zero flag to be set for
non-ALU operations such as register to register transfers.

The oVerflow flag is calculated using a 74LS151 8-to-1 selector as described in
[74181 with V_Flag](http://6502.org/users/dieter/v_flag/v_4.htm) on 6502.org.

The Carry flag has several inputs that can set it.  For arithmetic operations, it uses the
carry output of the 74LS181 ALU chip.  For shift operations, it is set by the LSB or the
MSB value of the H register.  Another of the ever-present 74LS151s chooses from the
different inputs as selected by the C0 and C1 bits from the control ROMs.

Any or all of the flags can also be loaded from the bus.  This allows for a "pull flags"
instruction to restore the set of flags.  This capability is also leveraged for the
individual flag set and clear instructions, like CLC, CLV, and SEC.  The ALU chip has an
operation that puts all ones on the bus and another that puts out all zeroes.  By putting
the ALU in one of these modes and enabling individual flag load lines, a flag can be set
or cleared by the microcode.

## Carry Flag Usage by the ALU and H Register

In addition to its use in the conditional jump instructions, the Carry flag is also used
as an input to the ALU (L) and the sHift (H) Register.  Depending on the operation, the
carry supplied to the ALU and H registers can be either a hard-coded one or zero, the
value of the Carry flag, or the inverted value of the Carry flag.  The inversion is needed
because the Carry flag uses positive logic, with a one indicating a carry is present, but
the ALU uses negative logic, where a zero indicates that a carry should be used in the
operation being performed.  

The new value of the Carry flag after an instruction also varies by instruction.  Its
value may came from either the ALU or the H register.  In addition, the CLC and SEC
instructions can explicitly clear the flag using a value from the bus.

The table below shows the usage of the carry flag for each instruction.

| Operation|Register|Input to Register|Input to Carry Flag|
|:---:     |:---:   |:---:            |:---:              |
| ADC      | ALU    | ~C              | ~ALU-carry-out    |
| ASL      | H      | 0               | H<sub>7</sub>     |
| DEC      | ALU    | 1               | flag not changed  |
| INC      | ALU    | 0               | flag not changed  |
| LSR      | H      | 0               | H<sub>0</sub>     |
| ROL      | H      | C               | H<sub>7</sub>     |
| ROR      | H      | C               | H<sub>0</sub>     |
| SBC      | ALU    | ~C              | ~ALU-carry-out    |
|====

The input to the Carry flag is described above in the Flag Calculations section.  The
output of the Carry flag to the ALU and H register is controlled by the LC and LS lines
from the Control ROM.  These two lines can force a clear or set value or just pass through
the current value of the Carry flag.  Note that the ALU uses negative logic for the carry
flag, so the inverted value of the Carry flag is used.  The inverter is placed after the
LC and LS logic, so asserting LS will present a zero to the ALU and LC will present a one.

## Other References

[Question for all 74ls181 alu people](https://www.reddit.com/r/beneater/comments/kmuuex/question_for_all_74ls181_alu_people)
on reddit led to the design of the oVerflow flag.

[How to add a decremental and incremental circuit to the ALU ?](https://www.reddit.com/r/beneater/comments/jwxke0/how_to_add_a_decremental_and_incremental_circuit/)
on reddit inspired the idea to drive the PC load line from the flags instead of running
the flags through the microcode.

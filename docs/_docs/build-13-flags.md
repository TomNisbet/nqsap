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

A [recent reddit post by WirralChris](https://www.reddit.com/r/beneater/comments/m76ijz/opcodes_and_flag_decoding_circuit/)
has a different approach to conditional jumps using hardware.  Instead of driving the
LOAD line of the PC, the circuit sits between the IR and the ROM and conditionally jams a
NOP or JMP instruction to the microcode depending on the state of the flags.  One
interesting part of the design is that the opcodes of the jump instructions are arranged
so that the flag of interest can be determined by bits from the IR.  NQSAP already does
this to drive the ALU select lines for arithmetic and logic operations and it would likely
save some ROM control lines to do it for flags also.  The J0, J1, and J2 lines from the
ROM would be replaced with bits from the IR.

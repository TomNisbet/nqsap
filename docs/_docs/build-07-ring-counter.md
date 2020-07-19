---
title: "Ring Counter"
permalink: /docs/ring-counter/
excerpt: "Building the ring counter of the NQSAP computer"
---

[![Ring Counter](../../assets/images/ring-counter.jpg "ring counter"){:width="400"}](../../assets/images/ring-counter.jpg)

The NQSAP Ring Counter is similar to the SAP-1, but has a few enhancements:
* maximum number of T cycles per instruction is 8 instead of 6
* synchronous clear input allows instructions with a variable number of steps

The reset line on the 74ls161 is asynchronous, meaning that the counter is reset to zero
as soon as the reset signal is asserted.  This is good for the Program Counter because it
means that the computer will reset immediately, even when the clock is stopped.

The asynchronous reset is not ideal for clearing the Ring Counter from the uCode ROM
because it would reset at the beginning of the microinstruction cycle instead of at the
clock pulse.  This could still be useful, but it would require a microinstruction
dedicated to the reset.  So if an instruction only needed 5 cycles, a 6th cycle could set
the reset line to end the instruction.

A better implementation would use a counter with a synchronous reset input that does the
clear operation on the clock cycle.  This would allow the RC reset control to be added to
the last microinstruction of an instruction cycle.

The 74ls163 counter is identical to the 74ls161 that is used in the PC, but it has a
synchronous clear instead of asynchronous. This would seem like be a good choice to
implement the variable instruction cycle Ring Counter, but it would then lose the ability
to do an instant clear when the RST line is asserted to reset the entire computer.  

The 74ls161 is used for the Ring Counter by leveraging the preset load feature to add a
synchronous reset.  74ls161 has a LOAD input that allows a 4-bit value to be loaded on the
next clock pulse. This is used by the Program Counter to implement the JMP instruction.
Because the Ring Counter has no need to load specific values, the input lines are all tied
to ground so that the enable line will load a zero value at the next clock pulse.  This
effectively turns the load line into a synchronous reset control.

Using the LOAD signal of the 74ls161 as a reset means that the Ring Counter now has two
reset inputs - the RST line is tied to the system RST to do an immediate clear when the
entire computer is reset and the LOAD line is tied to a control line from the uCode ROM to
do a synchronous clear at the end of an instruction cycle.

The NQSAP Ring Counter uses only two chips.  The 74LS161 is the 4-bit counter that keeps
track of the current microinstruction step (T cycle).  The lower three bits of this
counter drive the A0..A2 address lines of each microcode EEPROM.  

The second chip is a 74LS138 3-to-8 decoder that is used to drive the T cycle LEDs.  These
signals are only used for the visual indicators - they do not drive any actual control
lines.

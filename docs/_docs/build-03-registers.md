---
title: "Registers"
permalink: /docs/registers/
excerpt: "Building the general purpose registers of the NQSAP computer"
---

[![Initial Register Implementation](../../assets/images/registers-1.jpg "early register build"){:width="400px"}](../../assets/images/registers-1.jpg) [![Register Implementation](../../assets/images/registers-2.jpg "A and B registers"){:width="400px"}](../../assets/images/registers-2.jpg)

The A register was built using the standard pair of 74LS173 4-bit registers plus a 74LS245
bus transceiver.  This worked well, although it may be replaced in the future to add some
additional ALU capabilities.

Rather that the 74173 pair, the B register was implemented using a single 74574 8-bit
register. The thought was that this could save board space and simplify the wiring.  The
wiring was easier because the chip has all of the inputs on one side and the output on the
other, much like the 74245 bus transceivers that are used everywhere.  In addition, this
chip had the outputs on the top of the chip, which meant that they were easier to connect
to the ALU.

Note that, because the B register is write-only, it does not need a 74245 to control its
access to the bus.

One thing that was not accounted for in the B register design was the spacing required for
the 8 status LEDs that go with each register.  With the two-chip 74173 layout, the LEDs
are easy to place. The compact layout of the single 8-bit register plus all of the wiring
to the ALU and bus mode it impractical to place the LEDs directly at the chip outputs, and
as a result, they were moved to the side of the chip.  The single chip plus the LEDs ended
up using as much space or more than the 4-bit two-chip solution.  

The 74574 also lacks a gated input to control the loading of data.  An external NAND gate
was required to only provide a clock pulse to the chip when its write line is asserted
from the control logic.

All in all, the 8-bit register experiment didn't pan out and probably would have worked
better using a pair of 74173s, like the A register.

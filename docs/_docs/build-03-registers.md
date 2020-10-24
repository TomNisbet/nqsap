---
title: "Registers"
permalink: /docs/registers/
excerpt: "Building the general purpose registers of the NQSAP computer"
---

[![Initial Register Implementation](../../assets/images/registers-1.jpg "early register build"){:width="400px"}](../../assets/images/registers-1.jpg) [![Register Implementation](../../assets/images/registers-2.jpg "A and B registers"){:width="400px"}](../../assets/images/registers-2.jpg)

The initial build had only an A register and a B register.  These two provide the inputs
to the ALU. The A register is the accumulator, storing the result of ALU operations.  It
can be read and written with a variety of load and store instructions and its value can be
sent to the output display.

The A register was built using the standard pair of 74LS173 4-bit registers plus a 74LS245
bus transceiver.  This worked well, although it may be replaced in the future to add some
additional ALU capabilities.

## B Register

Rather that the 74173 pair, the B register was implemented using a single 74HCT574 8-bit
register. The thought was that this could save board space and simplify the wiring.  The
wiring was easier because the chip has all of the inputs on one side and the outputs on
the other, much like the 74245 bus transceivers that are used everywhere.  In addition,
this chip had the outputs on the top of the chip, which meant that they were easier to
connect to the ALU.

The 74574 lacks a gated input to control the loading of data.  An external NAND gate was
required to only provide a clock pulse to the chip when its write line is asserted from
the control logic.  Only one gate from the chip was needed, so the other three NAND gates
are available for use elsewhere.

In the original build, the B register was write-only and the ALU result was read-only, so
they shared a register address.  The B register is not a general-purpose register and is
not directly accessible to the user, so this seemed sufficient and it saved the need for
an additional 74LS245 bus transceiver.  There was a hack to read the B register using an
ALU operation that returns B.  This turned out to be useful as a temporary register for
the microcode so, during rewiring to add new features, an additional 245 was added to
allow direct access to the B register.

## Register Layout

One thing that needed to be considered for the B register design was the spacing required
for the 8 status LEDs that go with each register.  With the two-chip 74173 layout, the
LEDs are easy to place. The compact layout of the single 8-bit register, plus all of the
wiring to the ALU and bus, requires a bit more planning.

The initial build used 5mm LEDs, placed to the side of the chip.  The single chip plus the
LEDs ended up using as much space or more than the 4-bit, two-chip solution.  These large
LEDs were later replaced with a block of 3mm LEDs that were soldered together to minimize
the number of connections to the ground bus.  This was able to be placed directly on the
register outputs.  Note that these LEDs have
[built-in resistors](../getting-started/#5v-leds), so they can be connected directly from
the chip output to ground with no worries.

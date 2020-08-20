---
title: "Getting Started"
permalink: /docs/getting-started/
excerpt: "Starting the build of the NQSAP computer"
---

The build of the NQSAP followed mostly the same sequence as the [Ben Eater
SAP-1](https://eater.net/8bit), starting with the clock and registers and then the ALU.
The bus was integrated much earlier and this seemed to make testing easier.

## Breadboards

To minimize problems seen with some bargain breadboards, a higher quality version was
used.  The NQSAP is built with [BusBoard Prototype System BB830](https://smile.amazon.com/BB830-Solderless-Plug-BreadBoard-tie-Points/dp/B0040Z4QN8/) boards.  A breadboard project
of this size is difficult enough to troubleshoot without also worrying about problems with
the underlying boards.  The BB830s performed very well.

[![Breadboards](../../assets/images/bb830-breadboard.jpg "BB830 breadboard"){:width="400px"}](../../assets/images/bb830-breadboard.jpg)

## Data test board

A data test board was built that aided in the check out of the registers, memory, and ALU.
This board is simply a set of 8 DIP switches to ground with pull-up resisters.  The
switches feed a 74LS245 bus driver that can output the signals from the switches or be
tri-stated. By connecting this board to part of the circuit under test, it was easy to
check out inputs to registers without moving a lot of wires between +5 and ground.

The Test Board is seen here in the lower left side of the picture.  Because it only
needs power and a ribbon cable connection to the data lines, it was easy to move around
and connect to either the bus or to a new module that had not yet been integrated.  It is
not a permanent part of the final system.

[![Data test board](../../assets/images/data-test-board.jpg "data test board"){:width="400px"}](../../assets/images/data-test-board.jpg)

This board was first used to test the A and B registers and the ALU.  By connecting it
to the bus and then toggling the write signals to the registers, it was possible to test
multiple register and ALU values relatively quickly.  Using this board and the output LEDs
on the registers, several ALU wiring errors were found and corrected.

The data test board was also particularly helpful for early verification of the RAM
module.  The test board was used to place values into the MAR and then the RAM.  The
values could then be read back out of the RAM using the bus LEDs.

## LEDs

The Ben Eater design relies on the properties of some of the chips to drive LEDs without
current limiting resisters.  Other designs have used various methods to add resistors to
the LEDs, including buses with resistors dedicated to LEDs, spanning LEDs across the
gutter of the breadboards, and soldering resistors directly to the LED legs.

### 5V LEDs

The NQSAP uses [Kingbright 5V
resistors](https://www.mouser.com/new/kingbright/kingbright-resistor-LEDs/), which have
built-in current limiting resistors.  These are designed to run in 5V systems without the
need for an external resistor and can be even placed directly across the power bus, as
seen in some of the photos.  Definitely **do not** try this with regular LEDs!

Although they were more expensive than alternatives, the 5V LEDs made it very simple to
sprinkle LEDs throughout the boards.  The LEDs could be placed directly from the chip
outputs directly to power or ground, saving space next to the chips for more chips instead
of LEDs and resistors. Since the main purpose of a breadboard computer is to blink lights,
the 5V LEDs turned out to be a good investment.  

The only other downside to them (besides cost) is the limited colors available - only red,
green, and yellow.  Any blue LEDs seen in the NQSAP are not 5V and have external current
limiting resistors.

### LED size

Most of the design uses the large 5mm LEDs.  These can be difficult to fit into the space
available, particularly when placed in rows of eight on the registers.  Parts of the
computer that were built later, like the Instruction Resister, use smaller 3mm LEDs.
These were much easier to place and still provided a good brightness.  As some of the
temporary LEDs are replaced with shorter-lead permanent LEDs, the smaller 3mm versions
will be used.

[![LED block](../../assets/images/led-block.jpg "soldered row of LEDs"){:width="400px"}](../../assets/images/led-block.jpg)

To save even more space and make the wiring neater and easier, the 3mm LEDs have the
cathode side legs bent and soldered together so that a whole row of LEDs uses only one
ground connection. This helped in crowded areas like the ALU and its registers.  See the
before and after photos in the [Registers section](../registers/) for the difference.
Depending on where they were connected, rows of 4 or 8 LEDs were built.

---
title: "DXY Adder and Registers"
permalink: /docs/dxy-registers/
excerpt: "Building the DXY registers of the NQSAP computer"
---

[![DXY Registers](../../assets/images/dxy-registers.jpg "DXY registers build")](../../assets/images/dxy-registers.jpg)

The DXY registers are a set of three registers plus additional logic that implement two
user-accessible registers and a set of new addressing modes.  The X and Y registers are
general-purpose registers that are also used as index registers. The D register is a
temporary register and adder that is only accessible at the microcode level.

With this new hardware, NQSAP is able to use a set of addressing modes similar to those
found on a 6502.  The only difference is that the NQSAP does not have a sixteen-bit bus,
so all of the absolute address modes are the same as the zero-page modes of the 6502.  The
address modes available are:

* implicit
* accumulator
* immediate
* relative
* absolute
* absolute + X
* absolute + Y
* indirect
* indexed indirect (with X)
* indirect indexed (with Y)

The D register can be added to either the X or Y register to produce a sum that can be
read onto the bus.  The diagram below shows how the registers are connected.

[![DXY Registers Flow](../../assets/images/dxy-register-flow.png "DXY Registers data flow")](../../assets/images/dxy-register-flow.png)

The 2-to-one selectors allow either X or Y to be selected as a source for the adder.  The
selectors also have an enable line that presents zero at all of the outputs.  By wiring
the select and enable lines to the microcode ROMs, the functions D+X, D+Y, or D+0 can be
selected.  The D+0 feature allows the current value of D to be read through the adder,
eliminating the need for D to have its own output buffer.

## Hardware

The X and Y registers are each implemented using a 74HCT574 8-bit register and a 74HCT245
8-bit bus transceiver.  The D register also uses the 574 register but it does not have the
ability to write to the bus and does not have a transceiver. The X and Y register outputs
are connected to the A and B inputs of a pair of 74LS157 quad 2-to-1 selectors.  The
selector outputs, along with the D register outputs are connected to the inputs of a pair
of 74LS283 4-bit adders. The outputs of the adders are connected to a 245 transceiver so
they can be placed on the bus.

The select and output enable controls of the 2-to-1 selectors are connected to the
microcode ROMs, allowing the source of one of the adder operands to be X, Y, or zero.

The three 74574 register chips do not have a load enable line, so a NOR gate is used with
the write select and an inverted clock line to produce a rising edge to load the register
only when it is selected.  One gate of a quad NOR is used to invert the clock and the
other three are used to provide the write clocks for X, Y, and D.  See the
[B Register documentation](../registers/#74574-write-signal) for a more details of the
74574 clocking.


### Bill of Materials

* 74LS02 quad 2-input NOR gate (1)
* 74LS157 quad 2-to-1 selector (2)
* 74LS283 4-bit adder (2)
* 74HCT245 8-bit bus transceiver (3)
* 74HCT574 8-bit register (3)

Note that some 75HCT chips were used here instead of the 74LS chips used in most of the
build because the 74574 could not be found in a 74LS version.  The HCT chips were
cheaper and use less power, so when additional bus transceivers were needed those were
purchased as HCT versions as well.

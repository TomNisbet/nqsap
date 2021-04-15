---
title: "Control"
permalink: /docs/control/
excerpt: "Building the control circuits and multiplexing of the NQSAP computer"
---

[![Microcode ROMs and Control Logic](../../assets/images/control-logic.jpg "control logic"){:width="720px"}](../../assets/images/control-logic.jpg)

## Microcode ROMs

The microcode is stored in a set of 28C256 EEPROMs.  Each chip provides 8 control lines.
ROM3 is dedicated to [bus selection](#bus-control-multiplexing) (see below) and the
remaining ROMs provide general purpose control lines.  ROM3 and ROM2 have their outputs
disabled when the Loader is active so that the Loader can control the register selects and
register H control.  ROM1 and ROM0 are not output disabled, but with the ring counter held
in reset, they  are asserting logic low on all of their outputs.

The initial build was pre-wired for four ROMs but used only two.  When the flags are fully
implemented, the final build is expected to use 30 of the 32 available control lines.

## ROM addressing

The fifteen ROM address bits are allocated as follows:

```
A14 A13   A12 A11   A10 A9  A8  A7  A6  A5  A4  A3    A2  A1  A0
 R   R     X   X     I   I   I   I   I   I   I   I     T   T   T
```

 |Bits  |Count| Use                | Source             |
 |:---: |:---:|:---                |:--                 |
 |14..13|2    |ROM select          |Hardwired           |
 |12..11|2    |Not used            |Not in use          |
 |10..3 |8    |Instruction (opcode)|Instruction Register|
 |2..0  |3    |T Cycle             |Ring Counter        |

A future build may expand the T Cycle bits to four, expanding the number of
microinstruction steps from eight to sixteen.

## Bus control multiplexing

The NQSAP computer uses 74LS138 3-to-8 decoders to select the read and write source for
the bus.  Four decoders are used: two for write selection and two for read selection. The
decoders are driven by the control lines from microcode ROM 3. This has several advantages
over using individual control lines from the microcode ROMs:

* Reduces the number of microcode control ROM bit needed.  Can have 15 read locations and
15 write locations with just 8 control bits
* Reduces possibility of microcode bus errors - cannot have more than one read location
selected at a time
* The 74138s produce a low signal on the active line and most of the RAMs and registers
also use active low controls, reducing the number of inverters needed on microcode ROM
control signals

## Schematic

[![Microcode ROMs and Control Logic schematic](../../assets/images/microcode-roms-schematic.png "microcode ROMs schematic"){:width="720px"}](../../assets/images/microcode-roms-schematic.png)

The schematic for the microcode ROMs shows the 28C256 ROMs and the register decode logic.
The Ring Counter (step counter) and Instruction Register are also included.

## Bill of Materials

* 28C256 32Kx8 EEPROM (4)
* 74LS138 3-to-8 decoder (4)

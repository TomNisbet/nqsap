---
title: "Control"
permalink: /docs/control/
excerpt: "Building the control circuits and multiplexing of the NQSAP computer"
---

[![Microcode ROMs and Control Logic](../../assets/images/control-logic.jpg "control logic"){:width="720px"}](../../assets/images/control-logic.jpg)

## Microcode ROMs

The microcode is stored in a set of 28C256 EEPROMs.  Each chip provides 8 control lines.
One of the ROMs is dedicated to [bus selection](#bus-control-multiplexing) (see below) and
the remaining ROMs provide general purpose control lines.  The board is pre-wired for four
ROMs, but the current build is using only two.  Currently planned enhancements will expand
into the third ROM, but the fourth is likely to remain unused and the board probably could
have been done with just three.

## ROM addressing

The fifteen ROM address bits are allocated as follows:

```
A14 A13   A12 A11   A10 A9  A8  A7  A6  A5  A4  A3    A2  A1  A0
 R   R     F   F     I   I   I   I   I   I   I   I     T   T   T
```

 |Bits  |Count| Use                | Source             |
 |:---: |:---:|:---                |:--                 |
 |14..13|2    |ROM select          |Hardwired           |
 |12..11|2    |Flags               |Flags register      |
 |10..3 |8    |Instruction (opcode)|Instruction Register|
 |2..0  |3    |T Cycle             |Ring Counter        |


## Bus control multiplexing

The NQSAP computer uses 74LS138 3-to-8 decoders to select the read and write source for
the bus.  Three decoders are used: two for write selection and one for read selection. The
three decoders are driven by seven control lines from one of the microcode ROMs. This has
several advantages over using individual control lines from the microcode ROMs:

* Reduces the number of microcode control ROM bit needed.  Can have 7 read locations and
15 write locations with just 7 control bits
* Reduces possibility of microcode bus errors - cannot have more than one read location
selected at a time
* The 74138s produce a low signal on the active line and most of the RAMs and registers
also use active low controls, reducing the number of inverters needed on microcode ROM
control signals

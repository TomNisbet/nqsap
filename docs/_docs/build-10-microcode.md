---
title: "Microcode"
permalink: /docs/microcode/
excerpt: "Microcode design for the NQSAP computer"
---

[![Microcode programmer](../../assets/images/microcode-programmer.jpg "Arduino Nano microcode programmer"){:width="720px"}](../../assets/images/microcode-programmer.jpg)

## Microcode programming

The NQSAP microcode ROMs are programmed using an Arduino sketch running on an Arduino Nano
microcontroller.  The programmer hardware is based on the [TommyProm general-purpose
EEPROM programmer](https://github.com/TomNisbet/TommyPROM) project.

The microcode for a single ROM is 8Kx8 bits.  The 28C256 EEPROMs are 32Kx8, so each chips
holds the code for all four microcode ROMs.  The two highest order address lines on each
ROM are hardwired on the NQSAP board to select the 8K section of microcode that will be
used by the chip.  This means that all of the chips are interchangeable - they are
programmed the same and can be placed in any of the ROM slots on the NQSAP board.

The source code for the microcode programmer is in the
[Arduino microcode](https://github.com/TomNisbet/nqsap/tree/master/arduino-microcode)
folder. This code contains all of the details of the microcode implementation.

# NQSAP Microcode

This folder contains the Arduino sketch for the NQSAP Microcode Burner.  Some
documentation on the microcode is in the
[microcode documentation](https://tomnisbet.github.io/nqsap/docs/microcode/) section, but
the definitive resource is the burner code itself.

The hardware for the microcode burner is identical to the
[TommyPROM EEPROM Programmer](https://github.com/TomNisbet/TommyPROM) design.  The best
way to get started is to build and debug the hardware using that code and then compile
and load the microcode burner once the hardware is known to be working.  The TommyPROM
project has a better set of tools and more feedback to verify the design and even
includes a separate sketch for hardware troubleshooting if problems are encountered.

## Building

The Microcode Burner software is compiled using the Arduino IDE.  Load the
ardino-microcode.ino file and burn it to the target hardware.  Be sure to select the correct
Arduino board type under the tools->board menu.

## Burning microcode

The Microcode Burner sketch will burn a microcode ROM when the Arduino boots.  No user
interaction is needed.  When the burn is complete, the D13 LED will flash until the
Arduino is reset again.

If a USB cable is connected, progress messages will be printed to the serial output.

Every ROM burned receives a complete copy of the code for all of the Microcode ROMs, so
there is no need to make any selection when burning - just install each chip and then
power up the Arduino.

# NQSAP Loader and Debugger

This folder contains the Arduino sketch for the NQSAP Loader and Interactive Debugger.
The hardware design and features of the Loader/Debugger are listed in the
[Loader documentation](https://tomnisbet.github.io/nqsap/docs/loader/) in this repo.

This part of the project borrows heavily from the
[TommyPROM EEPROM Programmer](https://github.com/TomNisbet/TommyPROM) software.
Some details of the usage of the debugger, like the XMODEM transfers, may have additional
documentation available in that project.

## Building

The Loader software is compiled using the Arduino IDE.  Load the ardino-loader.ino file
and all of the supporting files should be included automatically.  Be certain to select
"Arduino Nano" as the Tools->Board menu of the IDE.

---
title: "Output Register"
permalink: /docs/output-register/
excerpt: "Building the output register and display of the NQSAP computer"
---

[![Output register and display](../../assets/images/output-register.jpg "output register"){:width="400px"}](../../assets/images/output-register.jpg)

The NQSAP uses a different approach to the output display than the Ben Eater SAP-1.
Instead of driving an LED display with a sequencer and an EEPROM, an ATmega328 is used.
While it is a bit of a cheat on a TTL computer, it was easily to assemble and uses minimal
board space.  The Atmega replaces not only the EEPROM and counter hardware, but it also
takes care of the buffering, eliminating the 74ls173 registers.

The output register can be jumpered to display its result in one of three modes:

* hex (00 to ff)
* signed decimal (-128 to 127)
* unsigned decimal (0 to 255)

One reason for the minimal output register hardware is its use of segment multiplexing
instead of digit multiplexing.  The removes the need for transistors or other drivers so
that the complete hardware consists of just the Atmege328, the display, and four
resistors.

Because the design is useful outside of the NQSAP, the Output Register is documented in
its own repository.  The [minimal-hardware 7 segment display](https://github.com/TomNisbet/minimal-hardware-7-segment-display)
repository has complete details, including source code.

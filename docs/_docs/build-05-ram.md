---
title: "RAM"
permalink: /docs/ram/
excerpt: "Building the system RAM of the NQSAP computer"
---

[![RAM and Memory Address Register](../../assets/images/ram.jpg "RAM and MAR"){:width="400px"}](../../assets/images/ram.jpg)

The NQSAP uses a single 32Kx8 static RAM instead of the 16x4 register chips used in the
SAP-1.  The 8 bit (as opposed to 4-bit in the SAP-1) addressing of the NQSAP allows 256
bytes of RAM.  This is only a small fraction of the memory available in the chip, but is
already a significant increase over the 16 bytes in the SAP-1.  It would be possible to
use additional address lines to separate the program code, data, and stack, allowing for
256 bytes of each for a total memory space of 768 bytes.  This would increase memory, but
would remove the ability to have self-modifying code or direct stack manipulation.

In addition to increasing the storage, the static RAM simplified the design of the memory.
The common data input/output lines can tri-state and are directly connected to the bus.
This eliminates the need for the 74LS245 bus driver chip and the separate input and
output bus connects. The non-inverting outputs eliminate the need for 7404s to correct the
outputs.

The direct bus connection means that the RAM chip can't directly drive LEDs on the memory
output like the SAP-1 registers do. These aren't really missed because the bus LEDs show
the RAM data during the read cycle.

Two of the NAND gates in a 74LS00 are used to provide a memory write signal that is
synchronized with the system clock. One gate inverts the active-low memory write and the
other ANDs it with the clock and provides an active-low memory write signal. A third NAND
gate is used to invert the reset signal for the MAR.

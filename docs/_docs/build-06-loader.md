---
title: "Loader / Debugger"
permalink: /docs/loader/
excerpt: "Building the Arduino-based Loader/Debugger for the NQSAP computer"
---

[![Arduino Loader](../../assets/images/loader.jpg "loader"){:width="500px"}](../../assets/images/loader.jpg)

The program memory loader uses an Arduino Nano in place of manual-entry DIP switches on
the SAP-1.  The Loader has eight of the Arduino I/O lines connected directly to the NQSAP
host bus for read and write access.  It can select registers and also drive the CLK and
RST lines.

Beyond the ability to simply load programs into memory, the Loader can read and write all
of the NQSAP registers. This gives the Loader the capability to perform a comprehensive
system verification.  This system test helpful for catching wires that work themselves
loose.

The Loader writes a default program to the NQSAP memory at power up, allowing unattended
operation.  If a USB connection is established, the Loader provides a ROM monitor-like
command line interface to interact with the NQSAP hardware.  The following features are
available via the USB interface:

* Memory
  * Load memory from a set of programs or patterns that are hard-coded into the Loader
  * Dump the contents of memory in hex and ASCII
  * Edit memory values
  * Fill a section of memory with a value
  * Load or save memory to a file using the XMODEM protocol
* Registers
  * Read and print the value from a register
  * Write a value to a register
  * Transfer the value from one register to another
* Diagnostics
  * Test all registers with a pattern that can be visually observed
  * Test all read/write registers by reading back the patterns written
  * Test memory with a set of patterns including walking bits
  * (future) Test the ALU by writing operands and operations and verifying the result

## Self-test

<figure class="video_container">
  <video controls="true" width="50%" allowfullscreen="true" poster="../../assets/videos/self-test.png">
    <source src="../../assets/videos/self-test2.mp4" type="video/mp4">
  </video>
</figure>

## Loader Design

### Design 1 - memory access only

The initial implementation used a 74LS157 quad 2-to-1 multiplexer to share the RAM R/W and
MAR signals between the outputs of the control ROM's 3-to-8 register select decoders and
the Loader.  The Loader could take control of the WMAR, RM, and WM signals as well as the
halt, clock and reset.

### Design 2 - full register control

With the realization that the Microcode ROMs already have tri-state outputs, a second
iteration of the Loader removed the 2-to-1 multiplexers and instead connected 6 Arduino
outputs directly to the inputs of the 3-to-8 register-select decoders that are driven by
one of the microcode ROMs.  The outputs of the Loader and ROM could both drive the
decoders because the Loader can switch the Output Enable line of the ROM and selectively
tri-state its own control lines.  By connecting to the inputs of the register decoders,
the Loader gains the ability to read or write to any of the registers.

The second implementation had two problems:

* The PORTC of Arduino Nano (A0..A7) was used for the register selects.  The last two bits
of this port are analog inputs only and can't be used as digital outputs. This only left
3 bits to select the write register and 3 bits for the read register, allowing only 7
of each type of register.
* The Loader software had to be very careful to coordinate between the state of its own
register select lines and the OE line of the ROM to avoid having both drive the lines at
the same time.

### Current Design - expanded register selects


[![Arduino Loader and Control](../../assets/images/loader-and-control.jpg "loader and control logic"){:width="720px"}](../../assets/images/loader-and-control.jpg)

The current iteration of the Loader adds two 74LS173 4-bit registers to drive the inputs
of the register select decoders.  The output enable of these registers is tied to the
Loader's PGM signal and the output enable of the register-select microcode ROM is the
inverted PGM signal, ensuring that only one source will be outputting a signal at any
time. The Loader uses four Arduino outputs to drive the inputs of the registers (all four
wired to both registers) and two Arduino outputs to drive the CLK lines to load a value
into one register or the other.  This allows the Loader to select up to 15 read registers
and 15 write registers using only 6 Arduino outputs.  

Note that the NQSAP currently has only one 3-to-8 decoder to select a read register, so
the number of read registers in the system is limited to seven.  The loader supports
another bit and there is a spare bit in the microcode ROM, so the read sources could
expand to 15 (like the write registers) by simply finding the board space to wire in a
second 3-to-8 decoder.  The NQSAP has several write-only registers, but isn't currently
pushing the limits of read-write registers.

## Loader implementation

The loader uses an Arduino Nano clone.  The Nano form factor was chosen over the more
common Uno because the small form factor can be installed directly on the breadboards with
the rest of the NQSAP.  Rather than installing male pins on the Nano, female socket strips
were used to raise the Nano up higher than the neighboring chips.  This was done to make
it easier to plug in and remove the USB cable.

[![Arduino Nanos with pins and sockets](../../assets/images/arduino-nanos.jpg "Arduino Nanos"){:width="400px"}](../../assets/images/arduino-nanos.jpg) [![Loader Arduino Nano installed](../../assets/images/loader-arduino.jpg "Loader Arduino"){:width="400px"}](../../assets/images/loader-arduino.jpg)

Note that the Loader Arduino can be left in the circuit even when not connected to a
controlling computer through USB.  Upon power up, the loader will activate itself and then
load a default program into the NQSAP.  So even in standalone mode, the NQSAP will power
up into a state where it has code to execute.

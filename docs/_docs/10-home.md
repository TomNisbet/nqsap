---
title: "NQSAP Breadboard Computer"
permalink: /
excerpt: "NQSAP: the Not Quite Simple As Possible breadboard computer"
---

The Not Quite Simple As Possible Computer

<figure class="video_container">
  <video controls="true" allowfullscreen="true" poster="assets/videos/nqsap-video.png">
    <source src="assets/videos/nqsap-video.mp4" type="video/mp4">
  </video>
</figure>

The NQSAP is a breadboard TTL computer that follows the
[Ben Eater 8-bit computer (SAP-1)](https://eater.net/8bit) design with some enhancements
and extensions.  This site does not cover the entire design because that is already
extremely well documented in the Ben Eater videos.  The documentation here only covers the
areas where this computer differs from the basic SAP-1.

Highlights of the design are:

* 6502-inspired architecture set that provides equivalents to most of the instructions
and addressing modes
* 8-bit addressing extends the size of memory and number of opcodes
* 74LS181 ALU provides arithmetic and logic operations including add, subtract, AND, OR,
 and XOR
* Arduino-based loader/debugger to load programs and run interactive diagnostics
* 3-to-8 Decoders for register selection simplifies wiring and reduces the number of
  microcode bits needed while also protecting against inadvertent bus collisions
* 8-bit Stack Pointer for storage and subroutines
* X and Y registers for general purpose use and indexed address modes

The initial build of the NQSAP was similar to the Ben Eater SAP-1, but with the later addition of the stack pointer and the X and Y registers, the microcode was re-written
to emulate many of the instructions and addressing modes of the 6502.  Note that the
instructions and registers are similar, but the opcodes of the NQSAP do not map to the
same values as a 6502.  This means that the NQSAP and 6502 are somewhat compatible at the
assembly language source level, but the object code they would use would be completely
different.

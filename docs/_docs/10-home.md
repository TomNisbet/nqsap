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

The NQSAP is a breadoard TTL computer that follows the
[Ben Eater 8-bit computer (SAP-1)](https://eater.net/8bit) design with some enhancements
and extensions.  This site does not cover the entire design because that is already
extremely well documented in the Ben Eater videos.  The documentation here only covers the
areas where this computer differs from the basic SAP-1.

Highlights of the design are:

* 8-bit addressing extends the size of memory and number of opcodes
* 74LS181 ALU provides arithmetic and logic operations including add, subtract, AND, OR,
 and XOR
* Arduino-based loader/debugger to load programs and run interactive diagnostics
* 3-to-8 Decoders for register selection simplifies wiring and reduces the number of
  microcode bits needed while also protecting against inadvertent bus collisions

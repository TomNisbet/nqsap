---
title: "NQSAP Breadboard Computer"
permalink: /docs/why/
excerpt: "NQSAP: the Not Quite Simple As Possible breadboard computer"
---

The Not Quite Simple As Possible Computer

Inspired by:

* Understanding Digital Computers - Radio Shack (Forrest Mims)
* Digital Computer Electronics - Paul Malvino

## What is a TTL computer and why build one?

The breadboard computers that people are building now are a chance to learn the gritty
details of computer architecture.  They are functional computers built with no
microprocessor - every part of them is created from simple digital logic, like gates,
decoders, counters, and memories.  The resulting computer is extremely basic, suited to
tasks like numeric calculations or very simple games.  But they are computers, and with
enough breadboards and wire, they could theoretically do just about anything.

The interesting thing about these computers is that they never really have to be finished.
There's always another enhancement that could be added on: new instructions, a larger
memory space, or an interrupt controller.

I like to think of it like a ship in a bottle - it's not about seaworthiness or cargo
capacity, it's about crafting something just for the enjoyment of building it.

## How did I get here?

As a teenager, I found the _Understanding Digital Computers_ book at the local Radio Shack
and was immediately fascinated by its description of the PIP-1 computer - an extremely
basic 4-bit machine.  This book then led me to the library to find a copy of Paul
Malvino's _Digital Computer Electronics_, the book that defines the SAP-1, SAP-2, and
SAP-3 computers.

[![Understanding Digital Computers book](../../assets/images/understanding-digital-computers-rs.jpg "Understanding Digital Computers"){:width="220px"}](../../assets/images/understanding-digital-computers-rs.jpg)

At that point, I was already building electronic kits and wiring simple logic circuits on
breadboards, but didn't have the resources (or the skills!) then to actually build a SAP.
Still, the knowledge of computer architecture from those books was an excellent foundation
for later assembly language programming on Z-80 TRS-80s and 6502 assembly on Ohio
Scientific Challengers.

When I finally did build a Netronics Explorer/85 computer from a kit, the PIP-1 and SAP-1 helped me to understand the inner workings of the 8085.

Flash forward many years later to a career writing embedded software for computer
communication equipment.  In my spare time, I started playing around again with 8-bit
computers.  The first project was to dust off the Netronics Explorer/85 and then build a
[software compatible clone](https://github.com/TomNisbet/Simple8085) on a breadboard. A
supporting project for this was [TommyPROM, an Arduino-based EEPROM
programmer](https://tomnisbet.github.io/TommyPROM/) that has been used as the basis of
the Loader and the Microcode programmer for NQSAP.

After the 8085 reboot project, I soldered some great 8-bit computer kits, including the
[Gigatron](https://gigatron.io/),
[PiDP/11](https://obsolescence.wixsite.com/obsolescence/pidp-11) (not 8-bit, but still
cool), and the [IMSAI 8080 Replica from The High
Nibble](https://thehighnibble.com/imsai8080/).

The kits were a nice trip back to soldering and front-panel switches, but they didn't
really offer much to think about - the design was already done, the parts just needed to
be assembled.

Finally, while browsing the [Homebrew Computer
Club](https://www.facebook.com/groups/HomebrewComputerClubUK) on Facebook, I found the
[Ben Eater 8-bit computer](https://eater.net/8bit) and instantly recognized the SAP-1 that
I'd read about so many years ago.  This was definitely going to be my next project!  The NQSAP is my version of a TTL breadboard computer, with its own features and quirks.

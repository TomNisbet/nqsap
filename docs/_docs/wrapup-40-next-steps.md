---
title: "Next Steps"
permalink: /docs/next-steps/
excerpt: "Future enhancements to the NQSAP computer"
---

[![empty-space](../../assets/images/empty-space.jpg "lots of empty space left"){:width="720px"}](../../assets/images/empty-space.jpg)

## Hardware

With the first phase of the NQSAP complete, there is still a lot of breadboard area free
for expansion.

### Stack pointer (added Nov 2020)

One of the most useful additions to the existing computer would be a stack pointer and
its associated CALL, RET, PUSH, and POP instructions.  The hardware should be simple -
a pair of 4-bit up/down counters wired to the bus through a 74LS245 transceiver. The
microcode, particularly the CALL instruction will be the interesting part of this project.

### Additional general-purpose registers

The B register is really just a temporary ALU register, so the current system only has
A as the only general-purpose register available.  The addition of one or two additional
registers will make programming much easier.

### Memory expansion

This one could be tricky.  A wider bus, to 12 or 16 bits would be a huge effort - it would
probably be easier to just start over rather than to retrofit a new bus.

Memory could still be expanded while keeping the bus at 8 bits.  One approach would be to
widen the MAR and PC and extend the memory access instructions to 3 bytes so that they
fetch two bytes of address.  Another approach would be be implement a segment register,
like on the 8088 processors.  This is probably easier to implement, but makes the
resulting computer more difficult to program.

One tricky part of memory expansion is the CALL and RET instructions.  If the address is
16 bits and the memory is only 8 bits wide, the PC could overflow into the next page
while incrementing to get the second part of the call address.  This makes pushing the
return address more difficult.

### Memory segmentation

One simple way to increase available memory is to use separate memory areas for program,
data, and stack.  The 32K RAM chip is only using eight of the fifteen available address
lines to access only 256 bytes of memory.  Wiring two of the available address lines to
microcode ROM control lines would let the stack use its own dedicated 256 byte memory area
and separate areas could be used for program and data storage as well.

This Harvard-like architecture would mean that the NQSAP would not support self-modifying
code because the load and store operations would not be able to access program storage.
It also means that the Loader would not be able to initialize data in the memory area
unless it is able to access another control signal to select memory areas.

## Microcode

There are several interesting extensions that don't require and new hardware but add
useful capabilities to the computer.  These can all be accomplished with new instructions
and microcode.

### New ALU instructions

The current set of ALU instructions use the A register and an immediate value as the
operands. A second set of ALU instructions could use A and a value fetched from a
specified memory location.

### Indirect addressing

Some register-based addressing mode instructions are possible.  An indexed jump, using
a specified address added to the A register would allow easy implementation of jump tables.

An indexed load or save would also be useful, but will probably not be implemented until
at least one more general-purpose register is added.

---
title: "Stack Pointer"
permalink: /docs/stack-pointer/
excerpt: "Building the stack pointer of the NQSAP computer"
---

[![Stack Pointer](../../assets/images/stack-pointer.jpg "stack pointer build")](../../assets/images/stack-pointer.jpg)

The stack pointer (SP) is an 8-bit register with read/write access to the bus.  It enables
new instructions to push and pull registers (PHA, PLA) and to call and return from
subroutines (JSR, RTS).  There are also new instructions to load the SP from an immediate
value (LIS) and to transfer values from A to SP (TAS) and from SP to A (TSA).  If no stack
operations are needed, the SP can be used as a general-purpose register.

## Hardware

The SP is implemented using a pair of 4-bit up/down counters with the count controls tied
to a microcode ROM.  Output to the bus is controlled via the usual 74LS245 bus
transceiver.  In the picture above, the SP is the three chips below the clock circuit, to
the left of the two-chip MAR.

The counters used for the SP are 74LS169 4-bit up/down counters.  This chip fits nicely
with the NQSAP design because it has both a clock input and a count enable input.  The
enable signal makes it simple to initiate a count operation from the control ROMs.  This
signal, plus the up/down signal allow the control ROMs to do the increment and decrement
operations of the SP in microcode.

The 74LS169 does not have a CLR signal to reset the counter at system reset so the SP
always starts in an unknown state.  This isn't a problem, because any programs that use
the SP will want to initialize it to point to a free memory area before any stack
operations are performed.

An early design used a 74LS193 4-bit up/down counter.  While this is similar to the 169,
it lacks the count enable control.  It is possible to use this chip, but an external
gate must be used to only provide a clock pulse to the counter when the count enable
signal is asserted from the microcode ROM.  This must be designed carefully because the
ROM glitch issue can cause errant clock pulses while the ROM address lines are being
switched by the IR and Ring Counter.

## Microcode

The SP counts up when pushing values to the stack and counts down when pulling values.
There is no overflow protection, so the counter will quietly wrap if it hits the top
or bottom of memory.  The push operation uses a post-increment, so the value is stored and
then the SP is bumped to point to the next available stack address.  In other words, the
SP always points to the address after the location of the value on the top of the stack.
The pull operations pre-decrement, so the SP is moved to point to the value and then the
value is retrieved.

Note that the Jump to Subroutine (JSR) uses a few tricks in the microcode.  The value of
the PC is needed to retrieve the subroutine address, but the PC also needs to be saved
onto the stack before being overwritten with the new address.  The ALU B register is used
for temporary storage to save the subroutine address.  The B register is not directly
accessible by the user, so it is a good candidate for the microcode to use.  See the
[NQSAP-PCB stack pointer page](https://tomnisbet.github.io/nqsap-pcb/docs/program-counter-stack-pointer/)
for a more detailed explanation of the JSR instruction.

## Bill of Materials

* 74LS169 4-bit up/down counter (2)
* 74HCT245 8-bit bus transceiver (1)

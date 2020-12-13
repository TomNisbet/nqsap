---
title: "Build History"
permalink: /docs/build-history/
excerpt: "NQSAP computer build history (blog)"
---

[![empty-space](../../assets/images/empty-space.jpg "lots of empty space left"){:width="720px"}](../../assets/images/empty-space.jpg)

## Apr 2020 - Initial build

I saw the Ben Eater videos in April and immediately started ordering breadboards and LEDs.
Other than the ALU chips, most of the other 74LS parts were already on-hand.

## May 2020 - Initial Build

[![Initial build](../../assets/images/registers-1.jpg "initial NQSAP build"){:width="400px"}](../../assets/images/registers-1.jpg)

The first picture of the NQSAP shows the [system clock]("../clock/"),
[A/B registers]("../registers/"), and the [ALU]("../alu/").  The bus was built and
integrated much earlier in the build than the Ben Eater process and this helped with test
and debug.

Also pictured is a [data test board](../getting-started/#data-test-board) that allows a
value from DIP switches to be placed on the bus.  A button was later added to replace the
jumper wire that enabled bus output.

[![RAM and MAR](../../assets/images/ram-mar.jpg "RAM and Memory Address Register"){:width="400px"}](../../assets/images/ram-mar.jpg)

The next iteration added the [Memory Address Register (MAR) and the RAM]("../ram/").  The MAR is
read-only, using a pair of 74LS173 registers.  The RAM uses a 32Kx8 static RAM which is
extreme overkill, since only 256 of the 32768 bytes are used.  But it is extremely easy to
wire because it does not require a separate bus driver.

The RAM was verified by using the data test board to load values into the MAR and then
into the RAM.  The RAM values could then be read back by enabling RAM output and using the
bus LEDs.

[![PC, IR, and Loader](../../assets/images/pc-ir-loader.jpg "Program Counter, Instruction Register and Loader"){:width="400px"}](../../assets/images/pc-ir-loader.jpg)

The Program Counter, Instruction Register, and [Loader]("../loader/") were added next.  As
with other parts of the build, initial assembly used jumper wires and ribbon cables to
prove out the design before committing to cutting and placing the permanent interconnect
wires.  Parts of the ALU are still in this state with their cleanup to come later.

The ribbon in the center left of the board connects to spot for the Arduino Nano that
implements the Loader/Monitor.

The program counter uses an LED bar display from the parts drawer.  This doesn't match any
of the other displays and may be replaced later.  Unlike the discrete LEDs in the build,
the bar graph does not have built-in resistors and is connected through an external
resistor network.

The data test board is still in use and has been upgraded with a button to place its value
on the bus.  This was much more convenient than moving a jumper back and forth.  Several
of the registers also have buttons temporarily installed to allow than to be loaded.

[![Ring Counter](../../assets/images/ring-counter-build.jpg "Ring Counter"){:width="400px"}](../../assets/images/ring-counter-build.jpg)

In anticipation of the control ROMs, the [Ring Counter]("../ring-counter/") was added
next.  This is really a binary microinstruction counter but it has an attached 3-to-8
decoder that gives output that looks like a ring counter.  This output is only used for
the LED display that indicates the step - the input to the ROMs will be the binary output
of the counter. Still, the ring counter terminology is used to match the Ben Eater builds.

[![Output Register](../../assets/images/output-register-build.jpg "Output Register"){:width="400px"}](../../assets/images/output-register-build.jpg)

The final component added before the control logic is the
[Output Register]("../output-register/").  This is a 4-digit LED display that can show an
8-bit result as hex, signed decimal, or unsigned decimal.  The Ben Eater build uses a
ROM and counter to implement the output register, but NQSAP took a different direction
that uses minimal hardware.  The display is driven by an ATmega328 microcontroller that
handles the display drive as well as the data latching.  This minimal-hardware
implementation uses only the controller, display, and four resistors.

Its a bit of a cheat for a TTL computer build to use a microcontroller that has vastly
more power than the entire resulting computer.  But this was an interesting build and it
can be argued that the display is really more of a peripheral than an integrated part of
the computer.

The first picture above shows the first prototype of the display, complete with the AVR
cable used to program the 328.  The second shows the completed output register in place.
The resistors are beneath the LED display and are not visible in the picture.


### Jun 2020 - ROM and register selects

[![Control logic and Microcode ROMs](../../assets/images/control-build-1.jpg "control logic and ROMs"){:width="400px"}](../../assets/images/control-build-1.jpg)[![Control logic cleanup](../../assets/images/control-build-2.jpg "control logic cleanup"){:width="400px"}](../../assets/images/control-build-2.jpg)

The first fully-operational version of the NQSAP computer was completed in June. The
addition of the control circuits tied all of the existing components together into a
working computer that could perform simple operations.

The first picture shows the register select logic and the microcontrol ROMs.  Only two
ROMs were used in the first build.  ROM2 is dedicated to the register select logic and
ROM0 has miscellaneous housekeeping control signals like reset the ring counter and
increment the program counter.

In the second photo, the temporary register control wiring from the register selectors has
been replaced.  The Loader has also been upgraded.  The first version used 1-to-2
multiplexors to allow that Loader to control the RAM and MAR.  These were replaced with
registers that
[directly controlled the register selectors]("../loader/#current-design---expanded-register-selects"),
allowing the Loader to read or write to any system register, including the RAM.

## Oct 2020 - Stack pointer

[![Stack Pointer](../../assets/images/stack-pointer-build.jpg "stack pointer"){:width="400px"}](../../assets/images/stack pointer-build.jpg)

Added a [stack pointer]("../stack-pointer/") and its associated JSR, RTS, push, and pull
instructions.  The hardware is a pair of 4-bit up/down counters wired to the bus through a
74LS245 transceiver.

The stack pointer was placed in the previously empty area on the left side of the MAR
breadboard.

## Nov 2020 - DXY index registers

The next logical extension of the NQSAP was the addition of one or two new user-accessible
registers.  These would be general purpose registers, but they would also be used to add
some new indexed addressing modes.

In the initial build of the NQSAP, the decision was made to use 74LS181 ALU chips instead
of the simple 74LS283 adders used in the Ben Eater build.  A few of the 283 adders were
included in the initial parts buy in case the ALU chips didn't work out.  The ALU was a
success and the 283s went into the parts bin.

The adder chips found a use when the X and Y registers were implemented.  By wiring the
X and Y chips with their own dedicated adder, it was possible to easily add several new
addressing modes to the NQSAP instruction set.

This new design could be implemented using eleven chips spread across two breadboards, but
there weren't two contiguous empty boards available.  There was a free space above the ALU
and another below it.

[![before ALU move](../../assets/images/move-1.jpg "before ALU move"){:width="200px"}](../../assets/images/move-1.jpg)

The solution was to disconnect the ALU and its registers and move the assembly down one
spot to free up two boards above the A register.

[![ALU disconnect](../../assets/images/move-2.jpg "ALU disconnect"){:width="200px"}](../../assets/images/move-2.jpg)

ALU move in progress.  Other than the bus connections, most everything stayed intact.
Some LEDs that shared the power buses needed to be pried out, but they stayed more or less
together and went back in with minimal effort.

At the start, it looked like the bus connections might be able to move along with the
boards, but at some point it just because easier to pull them for later replacement.

[![ALU replaced](../../assets/images/move-3.jpg "ALU replaced"){:width="200px"}](../../assets/images/move-3.jpg)

The ALU is now in its new position with temporary bus connections.  The Loader's system
test feature really proved its worth here to verify that everything went back together
correctly.

With the new breadboard space now abailable, two new
[user-accessible registers]("../dxy-registers/") were added along with an internal D
register and a dedicated added that can add D to either X, Y, or zero.

In addition to the new hardware, the instruction set got a major reorganization.  The X
and Y registers and their new addressing modes made it possible to build a 6502-like
machine, so the existing instructions we reorganized and many new instructions and address
modes were added to implement much of the 6502 instruction set.

## Dec 2020 - Shift register

[![Shift Register](../../assets/images/shift-register-build.jpg "shift register"){:width="400px"}](../../assets/images/shift-register-build.jpg)

The initial build used ALU A register that also served as the user-accessible accumulator.
This was implemented with a pair of 74LS173 4-bit registers.  These were replaced with a
pair of 74LS194 4-bit universal shift registers.  Due to the pin layout, the chips were
almost a drop-in replacement, although they needed to be mounted facing the opposite way
as the previous chips.

Because the shift registers have a direct parallel load capability, they can be used as
general-purpose registers.  The addition of the shift features allowed for new shift and
rotate instructions.  The existing write enable from the ROMs was replaced with three new
signals.  Two of these controlled the load and shift direction and the third selected
the carry-in source of either zero or the carry register.

To test the shift register, a third control register was added to the Loader.  This allows
the loader to write to H and enable its shift functions.

A related part of this build was a new accumulator register that is not directly
connected to the ALU.  This register was needed so that some of the memory operations,
like INC,DEC, and shift, could use the shift register without disturbing the contents of
the user-accessible accumulator.  The new register is now the A register/accumulator and
the ALU's A register is now referred to as H, for sHift register.  All microinstructions
that write to A also write to H, so at the completion of any instruction, the A and H
registers always contain the same value.

The zero detect circuit was also moved so that it takes its input from the bus instead of
the ALU outputs.  This allows the Z flag to be set on non-ALU operations like register
loads and transfers.

## Future

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

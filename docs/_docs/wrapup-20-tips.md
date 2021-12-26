---
title: "Tips"
permalink: /docs/tips/
excerpt: "Build tips"
---

## Wire and wiring

### Thin wire

The NQSAP project was started with [Electronix Express 22 gauge hookup
wire](https://www.amazon.com/Electronix-Express-Hook-Wire-Solid/dp/B00B4ZRPEY/). This is
wire that I've been using with breadboards for years and it has always worked well. When
the blue wire ran out, I replaced it with [Jameco ValuePro 22 gauge hookup
wire](https://www.jameco.com/z/JMS9313-01DB-22-AWG-6-Color-Solid-Tinned-Copper-Hook-Up-Wire-100-Feet_2159189.html).
Although it is also 22 gauge, the insulation on the ValuePro wire is definitely thinner.
This made the wire much easier to work with in crowded areas.  The picture below shows
both wires on the breadboard.  The Electronix Express in light blue and the ValuePro is in
dark blue.

[![Wire size](../../assets/images/wire-size.jpg "22 and 24 guage wire"){:width="400px"}](../../assets/images/wire-size.jpg)
[![Wire insulation](../../assets/images/wire-insulation.jpg "Electronix Express vs ValuePro"){:width="400px"}](../../assets/images/wire-insulation.jpg)

If starting over, I would definitely use the ValuePro wiring over the EE for this project.

One other wire that was tried was
[Velleman 10 color 24 gauge wire](https://www.amazon.com/Velleman-MOWM-Color-Solid-Mounting/dp/B001IRVDV4/).  
This looked promising because it offered additional colors that could have
been useful to call out different functions on the board, like the register read and write
selects.  This wire was a disappointment.  It didn't hold its form as well when bent and
the insulation discolored at all of the bend points.  I ended up removing the few pieces
that were used and replacing them with the ValuePro.

### 3D wiring

[![3D wiring](../../assets/images/3d-wiring.jpg "3D wiring"){:width="400px"}](../../assets/images/3d-wiring.jpg)

Partway through the project I saw some builds that were using "3D wiring", where the ends
are bent slightly before the bare wire.  This gives a lot more flexibility when placing
wires into crowed areas like the microcode ROMs.  It was also easier to get the wires to
the correct length by placing one end and then using the pliers to bend the other end at
the target spot.  The wire could then be clipped and stripped after the bend.  Overall,
this technique gave a cleaner build and eliminated wires that were _almost_ long enough
and didn't seat well.  It should result in fewer loose connections when nearby wires are
touched.

## Power

[![Power rails](../../assets/images/nqsap.jpg "power rails"){:width="400px"}](../../assets/images/nqsap.jpg)

The initial build brought power into the top left side of the system and then used
daisy-chained wires to bring power down to each breadboard.  This can still be seen on the
boards on the right side of the photo above.  Measuring the voltage at the furthest
boards from the power input showed a drop from 5V at the input to 4.5V at the far-end.

An extra set of breadboard buses was added to the left side of the system to distribute
power to each board.  The give a cleaner look and also increased the voltage at the
far-end to 4.8V.  This design will be duplicated on the right-hand side of the system as
well.  There is also a single power bus in the middle at the top of the system.  This is
the power entry point and it also includes filter capacitors.

## Workspace

This seems like a minor point, but the build will go much smoother if some effort is spent
to keep the workspace clean.  It is very easy to accumulate clutter like spare LEDs and
bits of wire that were too short for a spot but can be used somewhere else.  Spending a
few moments to clean up after finishing a module will pay off in the long run.

One trick I picked up while doing soldering projects is to use a small scrap can to hold
all of the leads clipped from components.  For this project the scrap mostly contains LED
leads and the hundreds of insulation pieces from stripping wires.

[![scrap container](../../assets/images/scrap-container.jpg "declutter your workspace"){:width="400px"}](../../assets/images/scrap-container.jpg)

Anything will do for this - a soup can, a small food container, a spray paint cap.  I also
keep a shallow container to hold the bits of clutter like LEDs that were used for testing
and then removed.

## Tools

[![assembly tools](../../assets/images/tools.jpg "tools"){:width="400px"}](../../assets/images/tools.jpg)

### Hand tools

The bulk of the project was built using only a few hand tools. The automatic wire
strippers weren't strictly needed, but did make it easier when placing groups of wires
that were the same length. The probe was handy for removing EEPROMs and getting at wires
during debug.

### Logic probe

One tool that was unexpectedly helpful was the TTL logic probe.  It's been in the tool bin
for years (Radio Shack for the win!) but was rarely used. It turned out to be an excellent
tool for debugging the ALU and some of the other more complicated parts of the design. The
audio feedback (low and high tones for low and high logic levels) made it easy to walk
along the pins of a chip or a row of holes in the breadboards and keep attention on the
pin numbers instead of having to look away for a test result.

### Oscilliscope, multimeter, and logic analyzer

On the other hand, some tools that would have seemed useful were needed rarely, if at all.
The oscilliscope was only used for the clock circuit, and even then just for curiosity to
see the results of placing filter capacitors.  The multimeter was only used to test
voltage drops at the far ends of the power distribution rails.  Surprisingly, the logic
analyzer was never used.  Any problems in the system were usually loose or misplaced wires
that were easily found with just the logic probe.

### Ammeter

[![Ammeter](../../assets/images/ammeter.jpg "ammeter")](../../assets/images/ammeter.jpg)

During the build, it was helpful to have an inexpensive ammeter connected to the power
supply to monitor the current draw.  
[Amazon carries several for under $10](https://www.amazon.com/Eiechip0-28-Digital-display-Volt-Meter/dp/B079L33VG2/)
that can be found by searching for "LED ammeter".  The meter doesn't need to be terribly
accurate, it just needs to show a large change in the current that would happen if a chip
was installed backwards or if multiple sources are driving the bus at the same time.  It's
a good way to catch wiring mistakes before the smoke starts leaking out of the chips.  It
was also interesting to see the current draw gradually increase over time as more modules
were build into the design.

---
title: "Clock"
permalink: /docs/clock/
excerpt: "Building the clock circuit of the NQSAP computer"
---

### SAP-1 Clock

The SAP-1 clock control circuit allows a free-running clock from the astable input in Run
mode or a manual clock pulse in Stop mode.  The HALT input disables the clock output.

[![SAP-1 clock](../../assets/images/clock-control-sap1.png "SAP-1 clock")](../../assets/images/clock-control-sap1.png)

### NQSAP Clock

The NQSAP clock control circuit changes the SAP-1 design by removing the _RUN/STOP_ select
gate that prevented the manual input while in auto mode.  This seems like a problem that
didn't need to be solved, so it was removed to simplify the wiring.

The NQSAP circuit also allows the loader to take over operation of the clock.  The
_LDR_STOP_ line can be pulled low to disable the system clock.  Once in the Stop state,
the loader can inject its own clock pulses on the _LDR_CLK_ line to read and write
registers and memory locations.

[![NQSAP clock](../../assets/images/clock-control-nqsap.png "NQSAP clock")](../../assets/images/clock-control-nqsap.png)

EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 3 7
Title "NQSAP Clock Control"
Date "2021-04-17"
Rev "1.0"
Comp "github.com/TomNisbet"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 74xx:74LS08 U303
U 4 1 6010770B
P 3100 2450
F 0 "U303" H 3100 2775 50  0000 C CNN
F 1 "74LS08" H 3100 2684 50  0000 C CNN
F 2 "" H 3100 2450 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS08" H 3100 2450 50  0001 C CNN
	4    3100 2450
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS08 U303
U 1 1 6010BC3F
P 4150 2350
F 0 "U303" H 4150 2675 50  0000 C CNN
F 1 "74LS08" H 4150 2584 50  0000 C CNN
F 2 "" H 4150 2350 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS08" H 4150 2350 50  0001 C CNN
	1    4150 2350
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS04 U301
U 6 1 601146D5
P 6250 1950
F 0 "U301" H 6250 2267 50  0000 C CNN
F 1 "74LS04" H 6250 2176 50  0000 C CNN
F 2 "" H 6250 1950 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 6250 1950 50  0001 C CNN
	6    6250 1950
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS04 U301
U 3 1 60115D4E
P 7850 4600
F 0 "U301" H 7850 4917 50  0000 C CNN
F 1 "74LS04" H 7850 4826 50  0000 C CNN
F 2 "" H 7850 4600 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 7850 4600 50  0001 C CNN
	3    7850 4600
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS04 U301
U 1 1 60118154
P 6250 2550
F 0 "U301" H 6250 2867 50  0000 C CNN
F 1 "74LS04" H 6250 2776 50  0000 C CNN
F 2 "" H 6250 2550 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 6250 2550 50  0001 C CNN
	1    6250 2550
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS04 U301
U 2 1 6011957A
P 7850 4050
F 0 "U301" H 7850 4367 50  0000 C CNN
F 1 "74LS04" H 7850 4276 50  0000 C CNN
F 2 "" H 7850 4050 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 7850 4050 50  0001 C CNN
	2    7850 4050
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS04 U301
U 5 1 6011B076
P 7000 3050
F 0 "U301" H 7000 3367 50  0000 C CNN
F 1 "74LS04" H 7000 3276 50  0000 C CNN
F 2 "" H 7000 3050 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 7000 3050 50  0001 C CNN
	5    7000 3050
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS04 U301
U 4 1 6011D876
P 1250 6250
F 0 "U301" H 1250 6567 50  0000 C CNN
F 1 "74LS04" H 1250 6476 50  0000 C CNN
F 2 "" H 1250 6250 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 1250 6250 50  0001 C CNN
	4    1250 6250
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS08 U303
U 3 1 6012566A
P 1250 7500
F 0 "U303" H 1250 7825 50  0000 C CNN
F 1 "74LS08" H 1250 7734 50  0000 C CNN
F 2 "" H 1250 7500 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS08" H 1250 7500 50  0001 C CNN
	3    1250 7500
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS08 U303
U 2 1 60129F0C
P 7000 3600
F 0 "U303" H 7000 3925 50  0000 C CNN
F 1 "74LS08" H 7000 3834 50  0000 C CNN
F 2 "" H 7000 3600 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS08" H 7000 3600 50  0001 C CNN
	2    7000 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 2450 3850 2450
Wire Wire Line
	3850 2250 3700 2250
Wire Wire Line
	3700 2250 3700 2000
Wire Wire Line
	3700 2000 2650 2000
Wire Wire Line
	4700 2250 4700 1800
Wire Wire Line
	4700 1800 2650 1800
Wire Wire Line
	4900 1600 2650 1600
Text GLabel 2650 1600 0    50   Input ~ 0
LDR-CLK
Text GLabel 2650 1800 0    50   Input ~ 0
MANUAL
Text GLabel 2650 2000 0    50   Input ~ 0
ASTABLE
Text GLabel 2650 2350 0    50   Input ~ 0
~LDR-ACTIVE
Text GLabel 2650 2550 0    50   Input ~ 0
RUN-~STOP
Wire Wire Line
	2650 2350 2800 2350
Wire Wire Line
	2650 2550 2800 2550
Wire Wire Line
	6550 1950 8200 1950
Wire Wire Line
	7300 3050 8200 3050
Wire Wire Line
	6550 2550 6650 2550
Text GLabel 8200 3050 2    50   Output ~ 0
~CLK
Text GLabel 8200 1950 2    50   Output ~ 0
CLK1
Text GLabel 8200 2550 2    50   Output ~ 0
CLK2
$Comp
L Device:LED D301
U 1 1 60159E7F
P 5900 1600
F 0 "D301" H 5900 1700 50  0000 C CNN
F 1 "LED" H 5900 1800 50  0000 C CNN
F 2 "" H 5900 1600 50  0001 C CNN
F 3 "~" H 5900 1600 50  0001 C CNN
	1    5900 1600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6650 3050 6650 2550
Connection ~ 6650 2550
Wire Wire Line
	6650 2550 8200 2550
Wire Wire Line
	6650 3050 6700 3050
$Comp
L 74xx:74LS27 U302
U 2 1 60184FA8
P 5450 2250
F 0 "U302" H 5450 2575 50  0000 C CNN
F 1 "74LS27" H 5450 2484 50  0000 C CNN
F 2 "" H 5450 2250 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS27" H 5450 2250 50  0001 C CNN
	2    5450 2250
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS27 U302
U 1 1 60189415
P 2500 7450
F 0 "U302" H 2500 7775 50  0000 C CNN
F 1 "74LS27" H 2500 7684 50  0000 C CNN
F 2 "" H 2500 7450 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS27" H 2500 7450 50  0001 C CNN
	1    2500 7450
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS27 U302
U 3 1 6018BE7E
P 2500 6800
F 0 "U302" H 2500 7125 50  0000 C CNN
F 1 "74LS27" H 2500 7034 50  0000 C CNN
F 2 "" H 2500 6800 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS27" H 2500 6800 50  0001 C CNN
	3    2500 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 2150 5150 2150
Wire Wire Line
	4900 1600 4900 2150
Wire Wire Line
	4700 2250 5150 2250
Wire Wire Line
	4450 2350 5150 2350
NoConn ~ 2800 6800
NoConn ~ 2800 7450
NoConn ~ 1550 6250
Wire Wire Line
	2200 6700 2150 6700
Wire Wire Line
	2150 6700 2150 6800
Wire Wire Line
	2150 6800 2200 6800
Wire Wire Line
	2150 6800 2150 6900
Wire Wire Line
	2150 6900 2200 6900
Connection ~ 2150 6800
Wire Wire Line
	2150 6900 2150 7350
Wire Wire Line
	2150 7350 2200 7350
Connection ~ 2150 6900
Wire Wire Line
	2150 7450 2150 7350
Connection ~ 2150 7350
Wire Wire Line
	2150 7450 2200 7450
Wire Wire Line
	2150 7450 2150 7550
Wire Wire Line
	2150 7550 2200 7550
Connection ~ 2150 7450
Wire Wire Line
	2150 7550 2150 7750
Wire Wire Line
	2150 7750 850  7750
Connection ~ 2150 7550
Wire Wire Line
	850  6250 950  6250
Connection ~ 850  6250
Wire Wire Line
	850  6250 850  6050
Wire Wire Line
	950  7400 850  7400
Connection ~ 850  7400
Wire Wire Line
	850  7400 850  7600
Wire Wire Line
	850  7600 950  7600
Connection ~ 850  7600
Wire Wire Line
	850  7600 850  7750
NoConn ~ 1550 7500
Wire Wire Line
	5900 1950 5950 1950
Wire Wire Line
	5900 1950 5900 2250
Wire Wire Line
	5900 2550 5950 2550
Wire Wire Line
	850  6250 850  7400
Wire Wire Line
	6650 3050 6650 3500
Wire Wire Line
	6650 3500 6700 3500
Connection ~ 6650 3050
Wire Wire Line
	7550 4600 7500 4600
Wire Wire Line
	7500 4600 7500 4050
Wire Wire Line
	7300 3600 7500 3600
Wire Wire Line
	7550 4050 7500 4050
Connection ~ 7500 4050
Wire Wire Line
	7500 4050 7500 3600
Wire Wire Line
	8150 4050 8200 4050
Wire Wire Line
	8150 4600 8200 4600
Text GLabel 8200 4050 2    50   Output ~ 0
~GCLK1
Wire Wire Line
	5750 2250 5900 2250
Connection ~ 5900 2250
Wire Wire Line
	5900 2250 5900 2550
Wire Wire Line
	5900 1750 5900 1950
Connection ~ 5900 1950
Wire Wire Line
	5900 1400 5900 1450
Text GLabel 8200 4600 2    50   Output ~ 0
~GCLK2
Text GLabel 8200 3600 2    50   Output ~ 0
GCLK
Wire Wire Line
	7500 3600 8200 3600
Connection ~ 7500 3600
Text GLabel 6400 3700 0    50   Input ~ 0
~RC-S1
Wire Wire Line
	6400 3700 6700 3700
Text Notes 8550 2000 0    50   ~ 0
SPx2, MARx2
Text Notes 8550 2600 0    50   ~ 0
IRx2, PCx2
Text Notes 8550 3100 0    50   ~ 0
RC
Text Notes 8550 3650 0    50   ~ 0
Hx2, FLAGSx4
Text Notes 8550 4100 0    50   ~ 0
A, RAM
Text Notes 8550 4650 0    50   ~ 0
D, X, Y, B
$Comp
L power:VCC #PWR0101
U 1 1 60F5A50F
P 850 6050
F 0 "#PWR0101" H 850 5900 50  0001 C CNN
F 1 "VCC" H 865 6223 50  0000 C CNN
F 2 "" H 850 6050 50  0001 C CNN
F 3 "" H 850 6050 50  0001 C CNN
	1    850  6050
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0102
U 1 1 60F5A847
P 5900 1400
F 0 "#PWR0102" H 5900 1250 50  0001 C CNN
F 1 "VCC" H 5915 1573 50  0000 C CNN
F 2 "" H 5900 1400 50  0001 C CNN
F 3 "" H 5900 1400 50  0001 C CNN
	1    5900 1400
	1    0    0    -1  
$EndComp
$EndSCHEMATC

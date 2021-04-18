EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 5 7
Title "NQSAP Loader/Debugger"
Date "2021-04-12"
Rev "1.0"
Comp "github.com/TomNisbet"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_Nano_v2.x A501
U 1 1 61A3C7F9
P 5600 4500
F 0 "A501" V 5600 4550 50  0000 C CNN
F 1 "Arduino Nano" V 5500 4450 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 5600 4500 50  0001 C CIN
F 3 "https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf" H 5600 4500 50  0001 C CNN
	1    5600 4500
	0    -1   -1   0   
$EndComp
$Comp
L 74xx:74LS04 U504
U 1 1 624110FF
P 10000 3850
F 0 "U504" H 10000 4167 50  0000 C CNN
F 1 "74LS04" H 10000 4076 50  0000 C CNN
F 2 "" H 10000 3850 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 10000 3850 50  0001 C CNN
	1    10000 3850
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS04 U504
U 2 1 62411100
P 10000 4350
F 0 "U504" H 10000 4667 50  0000 C CNN
F 1 "74LS04" H 10000 4576 50  0000 C CNN
F 2 "" H 10000 4350 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 10000 4350 50  0001 C CNN
	2    10000 4350
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS04 U504
U 3 1 62411101
P 2500 7050
F 0 "U504" H 2500 7367 50  0000 C CNN
F 1 "74LS04" H 2500 7276 50  0000 C CNN
F 2 "" H 2500 7050 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 2500 7050 50  0001 C CNN
	3    2500 7050
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74LS04 U504
U 4 1 62411102
P 2500 5450
F 0 "U504" H 2500 5767 50  0000 C CNN
F 1 "74LS04" H 2500 5676 50  0000 C CNN
F 2 "" H 2500 5450 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 2500 5450 50  0001 C CNN
	4    2500 5450
	-1   0    0    -1  
$EndComp
$Comp
L 74xx:74LS04 U504
U 5 1 62411103
P 10000 4850
F 0 "U504" H 10000 5167 50  0000 C CNN
F 1 "74LS04" H 10000 5076 50  0000 C CNN
F 2 "" H 10000 4850 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 10000 4850 50  0001 C CNN
	5    10000 4850
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS04 U504
U 6 1 62411104
P 10000 5350
F 0 "U504" H 10000 5667 50  0000 C CNN
F 1 "74LS04" H 10000 5576 50  0000 C CNN
F 2 "" H 10000 5350 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 10000 5350 50  0001 C CNN
	6    10000 5350
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS173 U502
U 1 1 62411108
P 5200 1900
F 0 "U502" V 5250 1850 50  0000 R CNN
F 1 "74LS173" V 5150 1900 50  0000 R CNN
F 2 "" H 5200 1900 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS173" H 5200 1900 50  0001 C CNN
	1    5200 1900
	0    -1   -1   0   
$EndComp
$Comp
L 74xx:74LS173 U503
U 1 1 61A67250
P 7350 1900
F 0 "U503" V 7400 1850 50  0000 R CNN
F 1 "74LS173" V 7300 1900 50  0000 R CNN
F 2 "" H 7350 1900 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS173" H 7350 1900 50  0001 C CNN
	1    7350 1900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7950 2400 7950 2500
Wire Wire Line
	7950 2500 8300 2500
Wire Wire Line
	8300 2500 8300 1900
Wire Wire Line
	8300 1900 8250 1900
Wire Wire Line
	5800 2400 5800 2500
Wire Wire Line
	6150 1900 6100 1900
Wire Wire Line
	3650 2400 3650 2500
Wire Wire Line
	3650 2500 4000 2500
Wire Wire Line
	4000 2500 4000 1900
Wire Wire Line
	4000 1900 3950 1900
Wire Wire Line
	2950 2400 2950 2800
Wire Wire Line
	2950 2800 3050 2800
Wire Wire Line
	7350 2800 7350 2400
Wire Wire Line
	7250 2400 7250 2800
Connection ~ 7250 2800
Wire Wire Line
	7250 2800 7350 2800
Wire Wire Line
	5200 2400 5200 2800
Connection ~ 5200 2800
Wire Wire Line
	5200 2800 7250 2800
Wire Wire Line
	5100 2400 5100 2800
Connection ~ 5100 2800
Wire Wire Line
	5100 2800 5200 2800
Connection ~ 3050 2800
Wire Wire Line
	3050 2800 5100 2800
Wire Wire Line
	3050 2400 3050 2800
Wire Wire Line
	3250 2400 3250 2500
Wire Wire Line
	3250 2500 3350 2500
Connection ~ 3650 2500
Wire Wire Line
	3350 2400 3350 2500
Connection ~ 3350 2500
Wire Wire Line
	5400 2400 5400 2500
Wire Wire Line
	5400 2500 5500 2500
Connection ~ 5800 2500
Wire Wire Line
	5500 2400 5500 2500
Connection ~ 5500 2500
Wire Wire Line
	7550 2400 7550 2500
Wire Wire Line
	7550 2500 7650 2500
Connection ~ 7950 2500
Wire Wire Line
	7650 2400 7650 2500
Connection ~ 7650 2500
Wire Wire Line
	7650 2500 7950 2500
Wire Wire Line
	6000 5000 6000 5650
$Comp
L power:GND #PWR0506
U 1 1 6077A475
P 8300 2500
F 0 "#PWR0506" H 8300 2250 50  0001 C CNN
F 1 "GND" H 8305 2327 50  0000 C CNN
F 2 "" H 8300 2500 50  0001 C CNN
F 3 "" H 8300 2500 50  0001 C CNN
	1    8300 2500
	1    0    0    -1  
$EndComp
Connection ~ 8300 2500
$Comp
L power:GND #PWR0505
U 1 1 6077AC84
P 6150 2500
F 0 "#PWR0505" H 6150 2250 50  0001 C CNN
F 1 "GND" H 6155 2327 50  0000 C CNN
F 2 "" H 6150 2500 50  0001 C CNN
F 3 "" H 6150 2500 50  0001 C CNN
	1    6150 2500
	1    0    0    -1  
$EndComp
Connection ~ 6150 2500
$Comp
L power:GND #PWR0504
U 1 1 6077B145
P 4000 2500
F 0 "#PWR0504" H 4000 2250 50  0001 C CNN
F 1 "GND" H 4005 2327 50  0000 C CNN
F 2 "" H 4000 2500 50  0001 C CNN
F 3 "" H 4000 2500 50  0001 C CNN
	1    4000 2500
	1    0    0    -1  
$EndComp
Connection ~ 4000 2500
Wire Wire Line
	4050 6450 3500 6450
Wire Wire Line
	2200 6250 1950 6250
$Comp
L Switch:SW_Push SW501
U 1 1 60792870
P 4650 6950
F 0 "SW501" H 4650 7235 50  0000 C CNN
F 1 "reset" H 4650 7144 50  0000 C CNN
F 2 "" H 4650 7150 50  0001 C CNN
F 3 "~" H 4650 7150 50  0001 C CNN
	1    4650 6950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4850 6950 5050 6950
Wire Wire Line
	5050 6950 5050 7000
$Comp
L power:GND #PWR0511
U 1 1 6079859A
P 5050 7000
F 0 "#PWR0511" H 5050 6750 50  0001 C CNN
F 1 "GND" H 5055 6827 50  0000 C CNN
F 2 "" H 5050 7000 50  0001 C CNN
F 3 "" H 5050 7000 50  0001 C CNN
	1    5050 7000
	-1   0    0    -1  
$EndComp
Text GLabel 1950 6250 0    50   Output ~ 0
~LDR-RC-RST
Wire Wire Line
	6200 5000 6200 7600
Wire Wire Line
	6200 7600 1950 7600
Text GLabel 1950 7600 0    50   Output ~ 0
LDR-CLK
$Comp
L 74xx:74LS08 U505
U 1 1 607D30DF
P 3200 6350
F 0 "U505" H 3200 6675 50  0000 C CNN
F 1 "74LS08" H 3200 6584 50  0000 C CNN
F 2 "" H 3200 6350 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS08" H 3200 6350 50  0001 C CNN
	1    3200 6350
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74LS08 U505
U 2 1 607D6271
P 2500 6250
F 0 "U505" H 2500 6575 50  0000 C CNN
F 1 "74LS08" H 2500 6484 50  0000 C CNN
F 2 "" H 2500 6250 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS08" H 2500 6250 50  0001 C CNN
	2    2500 6250
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74LS08 U505
U 3 1 607D7098
P 10000 6000
F 0 "U505" H 10000 6325 50  0000 C CNN
F 1 "74LS08" H 10000 6234 50  0000 C CNN
F 2 "" H 10000 6000 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS08" H 10000 6000 50  0001 C CNN
	3    10000 6000
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS08 U505
U 4 1 607DA4CE
P 10000 6500
F 0 "U505" H 10000 6825 50  0000 C CNN
F 1 "74LS08" H 10000 6734 50  0000 C CNN
F 2 "" H 10000 6500 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS08" H 10000 6500 50  0001 C CNN
	4    10000 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2500 5800 2500
Wire Wire Line
	3350 2500 3650 2500
Wire Wire Line
	6100 3650 6500 3650
Wire Wire Line
	6100 4000 6100 3650
Wire Wire Line
	6000 4000 6000 3600
Wire Wire Line
	5900 3550 6400 3550
Wire Wire Line
	5900 4000 5900 3550
Wire Wire Line
	5800 3500 6350 3500
Wire Wire Line
	5800 4000 5800 3500
Wire Wire Line
	5700 3300 5700 4000
Wire Wire Line
	5600 2400 5600 4000
Connection ~ 4800 3000
Wire Wire Line
	4800 2400 4800 3000
Connection ~ 4900 2950
Wire Wire Line
	4900 2400 4900 2950
Connection ~ 4700 3050
Wire Wire Line
	4700 2400 4700 3050
Connection ~ 4600 3100
Wire Wire Line
	4600 2400 4600 3100
Wire Wire Line
	6750 3100 6750 2400
Wire Wire Line
	2450 3100 4600 3100
Wire Wire Line
	2450 2400 2450 3100
Wire Wire Line
	6850 3050 6850 2400
Wire Wire Line
	2550 3050 4700 3050
Wire Wire Line
	2550 2400 2550 3050
Wire Wire Line
	6950 3000 6950 2400
Wire Wire Line
	2650 3000 4800 3000
Wire Wire Line
	2650 2400 2650 3000
Wire Wire Line
	7050 2950 7050 2400
Wire Wire Line
	2750 2950 4900 2950
Wire Wire Line
	2750 2400 2750 2950
Wire Wire Line
	7750 3300 7750 2400
Wire Wire Line
	3450 2400 3450 5650
Entry Wire Line
	5100 5300 5200 5200
Entry Wire Line
	5200 5300 5300 5200
Entry Wire Line
	5300 5300 5400 5200
Entry Wire Line
	5400 5300 5500 5200
Entry Wire Line
	5500 5300 5600 5200
Entry Wire Line
	5600 5300 5700 5200
Entry Wire Line
	5700 5300 5800 5200
Entry Wire Line
	5800 5300 5900 5200
Text Label 5200 5200 1    50   ~ 0
D0
Wire Wire Line
	5200 5200 5200 5000
Wire Wire Line
	5300 5000 5300 5200
Wire Wire Line
	5400 5200 5400 5000
Wire Wire Line
	5500 5000 5500 5200
Wire Wire Line
	5600 5200 5600 5000
Wire Wire Line
	5700 5000 5700 5200
Wire Wire Line
	5800 5200 5800 5000
Wire Wire Line
	5900 5000 5900 5200
Text Label 5300 5200 1    50   ~ 0
D1
Text Label 5400 5200 1    50   ~ 0
D2
Text Label 5500 5200 1    50   ~ 0
D3
Text Label 5600 5200 1    50   ~ 0
D4
Text Label 5700 5200 1    50   ~ 0
D5
Text Label 5800 5200 1    50   ~ 0
D6
Text Label 5900 5200 1    50   ~ 0
D7
NoConn ~ 5000 5000
NoConn ~ 5100 5000
NoConn ~ 4600 4600
NoConn ~ 4600 4400
NoConn ~ 5400 4000
Text Notes 5550 5400 2    50   ~ 0
data bus
Wire Wire Line
	6300 5000 6300 6250
Wire Wire Line
	3500 6250 6300 6250
Wire Wire Line
	6100 5000 6100 5850
Wire Wire Line
	2800 6350 2850 6350
Wire Wire Line
	2850 6350 2850 6750
Wire Wire Line
	2850 6750 1950 6750
Connection ~ 2850 6350
Wire Wire Line
	2850 6350 2900 6350
Wire Wire Line
	2850 6750 2850 7050
Wire Wire Line
	2850 7050 2800 7050
Connection ~ 2850 6750
Wire Wire Line
	2200 7050 1950 7050
Text GLabel 1950 6750 0    50   Output ~ 0
~RST
Text GLabel 1950 7050 0    50   Output ~ 0
RST
Wire Wire Line
	4050 6450 4050 6950
Wire Wire Line
	4050 6950 4450 6950
Text GLabel 1950 5850 0    50   Output ~ 0
~LDR-ACTIVE
Text GLabel 1950 5450 0    50   Output ~ 0
LDR-ACTIVE
Wire Wire Line
	3050 6150 2800 6150
Wire Wire Line
	3050 2800 3050 5450
Wire Wire Line
	2800 5450 3050 5450
Connection ~ 3050 5450
Connection ~ 3050 5850
Wire Wire Line
	3050 5850 6100 5850
Wire Wire Line
	1950 5850 3050 5850
$Comp
L Device:LED_Small D502
U 1 1 60973319
P 1400 4550
F 0 "D502" H 1400 4785 50  0000 C CNN
F 1 "LDR Active" H 1400 4694 50  0000 C CNN
F 2 "" V 1400 4550 50  0001 C CNN
F 3 "~" V 1400 4550 50  0001 C CNN
	1    1400 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R501
U 1 1 60974282
P 1800 4550
F 0 "R501" V 1595 4550 50  0000 C CNN
F 1 "100" V 1686 4550 50  0000 C CNN
F 2 "" H 1800 4550 50  0001 C CNN
F 3 "~" H 1800 4550 50  0001 C CNN
	1    1800 4550
	0    1    1    0   
$EndComp
Wire Wire Line
	1500 4550 1700 4550
Wire Wire Line
	1900 4550 2150 4550
Wire Wire Line
	2150 4550 2150 5450
Wire Wire Line
	1300 4550 1150 4550
Wire Wire Line
	1150 4550 1150 4650
$Comp
L power:GND #PWR0509
U 1 1 60982B45
P 1150 4650
F 0 "#PWR0509" H 1150 4400 50  0001 C CNN
F 1 "GND" H 1155 4477 50  0000 C CNN
F 2 "" H 1150 4650 50  0001 C CNN
F 3 "" H 1150 4650 50  0001 C CNN
	1    1150 4650
	-1   0    0    -1  
$EndComp
Text Notes 3450 1750 0    50   ~ 0
AUX
Text Notes 5650 1750 0    50   ~ 0
READ
Text Notes 7750 1750 0    50   ~ 0
WRITE
Wire Wire Line
	7750 3300 5700 3300
Wire Wire Line
	6150 1900 6150 2500
Wire Wire Line
	3450 5650 6000 5650
Wire Wire Line
	5800 2500 6150 2500
Wire Wire Line
	4600 3100 6350 3100
Wire Wire Line
	4700 3050 6400 3050
Wire Wire Line
	4800 3000 6450 3000
Wire Wire Line
	4900 2950 6500 2950
Wire Wire Line
	6000 3600 6450 3600
Wire Wire Line
	6350 3500 6350 3100
Connection ~ 6350 3100
Wire Wire Line
	6350 3100 6750 3100
Wire Wire Line
	6400 3550 6400 3050
Connection ~ 6400 3050
Wire Wire Line
	6400 3050 6850 3050
Wire Wire Line
	6450 3600 6450 3000
Connection ~ 6450 3000
Wire Wire Line
	6450 3000 6950 3000
Wire Wire Line
	6500 3650 6500 2950
Connection ~ 6500 2950
Wire Wire Line
	6500 2950 7050 2950
$Comp
L Device:D_Zener D501
U 1 1 60A100B7
P 4250 4300
F 0 "D501" H 4250 4517 50  0000 C CNN
F 1 "D_Zener" H 4250 4426 50  0000 C CNN
F 2 "" H 4250 4300 50  0001 C CNN
F 3 "~" H 4250 4300 50  0001 C CNN
	1    4250 4300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4400 4300 4600 4300
Wire Wire Line
	4100 4300 4000 4300
$Comp
L power:VCC #PWR0508
U 1 1 60A1A7A6
P 4000 4150
F 0 "#PWR0508" H 4000 4000 50  0001 C CNN
F 1 "VCC" H 4015 4323 50  0000 C CNN
F 2 "" H 4000 4150 50  0001 C CNN
F 3 "" H 4000 4150 50  0001 C CNN
	1    4000 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 4150 4000 4300
$Comp
L power:VCC #PWR0501
U 1 1 60A200DD
P 2100 1850
F 0 "#PWR0501" H 2100 1700 50  0001 C CNN
F 1 "VCC" H 2115 2023 50  0000 C CNN
F 2 "" H 2100 1850 50  0001 C CNN
F 3 "" H 2100 1850 50  0001 C CNN
	1    2100 1850
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0502
U 1 1 60A207E3
P 4250 1850
F 0 "#PWR0502" H 4250 1700 50  0001 C CNN
F 1 "VCC" H 4265 2023 50  0000 C CNN
F 2 "" H 4250 1850 50  0001 C CNN
F 3 "" H 4250 1850 50  0001 C CNN
	1    4250 1850
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0503
U 1 1 60A20DB1
P 6400 1850
F 0 "#PWR0503" H 6400 1700 50  0001 C CNN
F 1 "VCC" H 6415 2023 50  0000 C CNN
F 2 "" H 6400 1850 50  0001 C CNN
F 3 "" H 6400 1850 50  0001 C CNN
	1    6400 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 1850 2100 1900
Wire Wire Line
	2100 1900 2150 1900
Wire Wire Line
	4250 1850 4250 1900
Wire Wire Line
	4250 1900 4300 1900
Wire Wire Line
	6400 1850 6400 1900
Wire Wire Line
	6400 1900 6450 1900
$Comp
L power:GND #PWR0510
U 1 1 60A30351
P 6900 4650
F 0 "#PWR0510" H 6900 4400 50  0001 C CNN
F 1 "GND" H 6905 4477 50  0000 C CNN
F 2 "" H 6900 4650 50  0001 C CNN
F 3 "" H 6900 4650 50  0001 C CNN
	1    6900 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 4400 6900 4400
Wire Wire Line
	6900 4400 6900 4650
NoConn ~ 6600 4500
NoConn ~ 5100 4000
NoConn ~ 5000 4000
Wire Wire Line
	1950 5450 2150 5450
Connection ~ 2150 5450
Wire Wire Line
	2150 5450 2200 5450
Wire Wire Line
	9700 3850 9600 3850
Wire Wire Line
	9600 3850 9600 4350
Wire Wire Line
	9600 6600 9700 6600
Wire Wire Line
	9700 6400 9600 6400
Connection ~ 9600 6400
Wire Wire Line
	9600 6400 9600 6600
Wire Wire Line
	9700 6100 9600 6100
Connection ~ 9600 6100
Wire Wire Line
	9600 6100 9600 6400
Connection ~ 9600 5900
Wire Wire Line
	9600 5900 9600 6100
Wire Wire Line
	9700 5350 9600 5350
Connection ~ 9600 5350
Wire Wire Line
	9600 5350 9600 5900
Wire Wire Line
	9700 4850 9600 4850
Connection ~ 9600 4850
Wire Wire Line
	9600 4850 9600 5350
Wire Wire Line
	9700 4350 9600 4350
Connection ~ 9600 4350
Wire Wire Line
	9600 4350 9600 4850
$Comp
L power:VCC #PWR0507
U 1 1 60A9C975
P 9600 3550
F 0 "#PWR0507" H 9600 3400 50  0001 C CNN
F 1 "VCC" H 9615 3723 50  0000 C CNN
F 2 "" H 9600 3550 50  0001 C CNN
F 3 "" H 9600 3550 50  0001 C CNN
	1    9600 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 3850 9600 3550
Connection ~ 9600 3850
NoConn ~ 10300 3850
NoConn ~ 10300 4350
NoConn ~ 10300 4850
NoConn ~ 10300 5350
NoConn ~ 10300 6000
NoConn ~ 10300 6500
Text Notes 3650 4650 0    50   ~ 0
diode prevents USB\nfrom powering NQSAP\nwhen Vcc is removed
Wire Wire Line
	3050 5850 3050 6150
Wire Wire Line
	3050 5450 3050 5850
Text Notes 750  5500 0    50   ~ 0
to control ROMs
Text Notes 700  6300 0    50   ~ 0
to ring counter
Text Notes 900  7650 0    50   ~ 0
to clock control
Text GLabel 4600 1300 1    50   Output ~ 0
MC-RR0
Text GLabel 4700 1300 1    50   Output ~ 0
MC-RR1
Text GLabel 4800 1300 1    50   Output ~ 0
MC-RR2
Text GLabel 4900 1300 1    50   Output ~ 0
MC-RR3
Wire Wire Line
	4600 1300 4600 1400
Wire Wire Line
	4700 1300 4700 1400
Wire Wire Line
	4800 1300 4800 1400
Wire Wire Line
	4900 1300 4900 1400
Text GLabel 6750 1300 1    50   Output ~ 0
MC-RW0
Text GLabel 6850 1300 1    50   Output ~ 0
MC-RW1
Text GLabel 6950 1300 1    50   Output ~ 0
MC-RW2
Text GLabel 7050 1300 1    50   Output ~ 0
MC-RW3
Wire Wire Line
	6750 1300 6750 1400
Wire Wire Line
	6850 1300 6850 1400
Wire Wire Line
	6950 1300 6950 1400
Wire Wire Line
	7050 1300 7050 1400
Text Notes 4400 800  0    50   ~ 0
to control ROM3 read\nregister decoders
Text Notes 6550 800  0    50   ~ 0
to control ROM3 write\nregister decoders
Text Notes 2300 800  0    50   ~ 0
to control ROM2\nmisc signals
Text GLabel 2450 1300 1    50   Output ~ 0
HL
Text GLabel 2550 1300 1    50   Output ~ 0
HR
Wire Wire Line
	2450 1300 2450 1400
Wire Wire Line
	2550 1300 2550 1400
$Comp
L 74xx:74LS173 U501
U 1 1 62411107
P 3050 1900
F 0 "U501" V 3100 1850 50  0000 R CNN
F 1 "74LS173" V 3000 1900 50  0000 R CNN
F 2 "" H 3050 1900 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS173" H 3050 1900 50  0001 C CNN
	1    3050 1900
	0    -1   -1   0   
$EndComp
NoConn ~ 2650 1400
NoConn ~ 2750 1400
Text Notes 700  5900 0    50   ~ 0
to clock control
NoConn ~ 6200 4000
NoConn ~ 6300 4000
Wire Wire Line
	9600 5900 9700 5900
Text Label 5050 5300 2    50   ~ 0
D[0..7]
Wire Bus Line
	4750 5300 5900 5300
$EndSCHEMATC

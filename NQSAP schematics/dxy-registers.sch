EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 7 7
Title "NQSAP DXY Registers and Adder"
Date "2021-04-23"
Rev "1.2"
Comp "github.com/TomNisbet"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 74xx:74LS245 U704
U 1 1 607AEEBA
P 1700 2000
F 0 "U704" H 1950 2800 50  0000 C CNN
F 1 "74LS245" H 1950 2700 50  0000 C CNN
F 2 "" H 1700 2000 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS245" H 1700 2000 50  0001 C CNN
	1    1700 2000
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS245 U707
U 1 1 607AFC24
P 1700 4250
F 0 "U707" H 1950 5050 50  0000 C CNN
F 1 "74LS245" H 1950 4950 50  0000 C CNN
F 2 "" H 1700 4250 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS245" H 1700 4250 50  0001 C CNN
	1    1700 4250
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS245 U710
U 1 1 607B0A23
P 1700 6500
F 0 "U710" H 1950 7300 50  0000 C CNN
F 1 "74LS245" H 1950 7200 50  0000 C CNN
F 2 "" H 1700 6500 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS245" H 1700 6500 50  0001 C CNN
	1    1700 6500
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HCT574 U702
U 1 1 607B1E76
P 4050 1700
F 0 "U702" V 4200 2400 50  0000 L CNN
F 1 "74HCT574" V 4300 2350 50  0000 L CNN
F 2 "" H 4050 1700 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HCT574" H 4050 1700 50  0001 C CNN
	1    4050 1700
	0    1    1    0   
$EndComp
$Comp
L 74xx:74HCT574 U703
U 1 1 607B26C8
P 6550 1700
F 0 "U703" V 6700 2400 50  0000 L CNN
F 1 "74HCT574" V 6800 2350 50  0000 L CNN
F 2 "" H 6550 1700 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HCT574" H 6550 1700 50  0001 C CNN
	1    6550 1700
	0    1    1    0   
$EndComp
$Comp
L 74xx:74HCT574 U711
U 1 1 607B2E71
P 4400 7000
F 0 "U711" V 4650 6250 50  0000 R CNN
F 1 "74HCT574" V 4550 6350 50  0000 R CNN
F 2 "" H 4400 7000 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HCT574" H 4400 7000 50  0001 C CNN
	1    4400 7000
	0    -1   -1   0   
$EndComp
$Comp
L 74xx:74LS283 U708
U 1 1 607B43C3
P 4100 4950
F 0 "U708" V 4250 5650 50  0000 L CNN
F 1 "74LS283" V 4350 5600 50  0000 L CNN
F 2 "" H 4100 4950 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS283" H 4100 4950 50  0001 C CNN
	1    4100 4950
	0    1    1    0   
$EndComp
$Comp
L 74xx:74LS283 U709
U 1 1 607B4E38
P 6200 4950
F 0 "U709" V 6350 5650 50  0000 L CNN
F 1 "74LS283" V 6450 5600 50  0000 L CNN
F 2 "" H 6200 4950 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS283" H 6200 4950 50  0001 C CNN
	1    6200 4950
	0    1    1    0   
$EndComp
$Comp
L 74xx:74LS157 U706
U 1 1 607B5AE1
P 6800 3350
F 0 "U706" V 6900 4150 50  0000 L CNN
F 1 "74LS157" V 7000 4100 50  0000 L CNN
F 2 "" H 6800 3350 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS157" H 6800 3350 50  0001 C CNN
	1    6800 3350
	0    1    1    0   
$EndComp
$Comp
L 74xx:74LS157 U705
U 1 1 607B6109
P 4300 3350
F 0 "U705" V 4450 4150 50  0000 L CNN
F 1 "74LS157" V 4550 4100 50  0000 L CNN
F 2 "" H 4300 3350 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS157" H 4300 3350 50  0001 C CNN
	1    4300 3350
	0    1    1    0   
$EndComp
Connection ~ 2600 2500
Wire Bus Line
	7850 6150 7850 4150
Entry Wire Line
	3800 2500 3900 2600
Entry Wire Line
	3900 2500 4000 2600
Entry Wire Line
	4100 2500 4200 2600
Entry Wire Line
	4200 2500 4300 2600
Entry Wire Line
	4000 4150 4100 4250
Entry Wire Line
	4100 4150 4200 4250
Entry Wire Line
	4500 4150 4600 4050
Entry Wire Line
	4200 5850 4300 5750
Entry Wire Line
	4450 2500 4550 2400
Wire Wire Line
	3550 1200 3550 1150
Wire Wire Line
	4100 4250 4100 4450
Wire Wire Line
	4300 5750 4300 5450
Entry Wire Line
	3800 6150 3900 6250
Entry Wire Line
	3800 7850 3900 7750
Wire Wire Line
	3600 2850 3600 2800
Wire Wire Line
	3600 2800 3400 2800
Wire Wire Line
	3700 2850 3700 2650
Wire Wire Line
	3700 2650 3400 2650
Text GLabel 3400 2650 0    50   Input ~ 0
DY
Text GLabel 3400 2800 0    50   Input ~ 0
DZ
Wire Wire Line
	3200 1150 3200 1700
Wire Wire Line
	3200 1700 3250 1700
Wire Wire Line
	3200 1150 3550 1150
Wire Wire Line
	4550 2200 4550 2400
Text Label 4300 2800 1    50   ~ 0
X6
Text Label 4600 4000 1    50   ~ 0
XY5
Text Label 4100 4400 1    50   ~ 0
XY7
Text Label 4300 5700 1    50   ~ 0
SUM7
Text Label 3900 6400 1    50   ~ 0
DQ0
Text Label 3900 7650 1    50   ~ 0
D0
Wire Wire Line
	3900 6250 3900 6500
Wire Wire Line
	3900 7500 3900 7750
Entry Wire Line
	4450 850  4550 950 
Text Label 4550 1100 1    50   ~ 0
D0
Wire Wire Line
	4550 950  4550 1200
Wire Wire Line
	4300 2600 4300 2850
Wire Wire Line
	3650 600  3650 1200
Wire Wire Line
	6150 700  6150 1200
Wire Wire Line
	6050 1200 6050 1150
Wire Wire Line
	6050 1150 5700 1150
Wire Wire Line
	5700 1150 5700 1700
Wire Wire Line
	5700 1700 5750 1700
$Comp
L 74xx:74LS02 U701
U 2 1 607DEC7E
P 8750 1500
F 0 "U701" H 8750 1183 50  0000 C CNN
F 1 "74LS02" H 8750 1274 50  0000 C CNN
F 2 "" H 8750 1500 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74ls02" H 8750 1500 50  0001 C CNN
	2    8750 1500
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74LS02 U701
U 3 1 607E1B4D
P 8750 2200
F 0 "U701" H 8750 1883 50  0000 C CNN
F 1 "74LS02" H 8750 1974 50  0000 C CNN
F 2 "" H 8750 2200 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74ls02" H 8750 2200 50  0001 C CNN
	3    8750 2200
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74LS02 U701
U 4 1 607E2CCA
P 8750 2900
F 0 "U701" H 8750 2583 50  0000 C CNN
F 1 "74LS02" H 8750 2674 50  0000 C CNN
F 2 "" H 8750 2900 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74ls02" H 8750 2900 50  0001 C CNN
	4    8750 2900
	-1   0    0    1   
$EndComp
Wire Wire Line
	9400 2100 9050 2100
Connection ~ 9400 2100
Wire Wire Line
	9400 2100 9400 2800
Wire Wire Line
	9400 2800 9050 2800
Wire Wire Line
	9050 3000 9100 3000
Wire Wire Line
	9050 1400 9400 1400
Wire Wire Line
	10100 900  10200 900 
Text GLabel 10200 900  2    50   Input ~ 0
CLK
Text GLabel 9100 1600 2    50   Input ~ 0
~WX
Text GLabel 9100 2300 2    50   Input ~ 0
~WY
Text GLabel 9100 3000 2    50   Input ~ 0
~WD
Wire Wire Line
	8450 1500 8350 1500
Wire Wire Line
	8350 1500 8350 600 
Wire Wire Line
	3650 600  8350 600 
Wire Wire Line
	8150 700  8150 2200
Wire Wire Line
	8150 2200 8450 2200
Wire Wire Line
	6150 700  8150 700 
Wire Wire Line
	8350 6500 5850 6500
Wire Wire Line
	5850 6500 5850 7700
Wire Wire Line
	5850 7700 4800 7700
Wire Wire Line
	4800 7700 4800 7500
Wire Wire Line
	5200 7000 5250 7000
Wire Wire Line
	5250 7000 5250 7550
Wire Wire Line
	5250 7550 4900 7550
Wire Wire Line
	4900 7550 4900 7500
Wire Wire Line
	5250 7000 5450 7000
Wire Wire Line
	5450 7000 5450 7050
Connection ~ 5250 7000
$Comp
L power:GND #PWR0721
U 1 1 607F831A
P 5450 7050
F 0 "#PWR0721" H 5450 6800 50  0001 C CNN
F 1 "GND" H 5455 6877 50  0000 C CNN
F 2 "" H 5450 7050 50  0001 C CNN
F 3 "" H 5450 7050 50  0001 C CNN
	1    5450 7050
	1    0    0    -1  
$EndComp
Entry Wire Line
	2600 3650 2500 3750
Wire Wire Line
	2500 3750 2200 3750
Text Label 2400 3750 2    50   ~ 0
Y0
Wire Wire Line
	4600 3850 4600 4050
$Comp
L 74xx:74LS02 U701
U 1 1 607E3CFD
P 9750 900
F 0 "U701" H 9750 583 50  0000 C CNN
F 1 "74LS02" H 9750 674 50  0000 C CNN
F 2 "" H 9750 900 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74ls02" H 9750 900 50  0001 C CNN
	1    9750 900 
	-1   0    0    1   
$EndComp
Wire Wire Line
	9050 2300 9100 2300
Wire Wire Line
	10050 800  10100 800 
Wire Wire Line
	10100 800  10100 900 
Wire Wire Line
	10100 1000 10050 1000
Connection ~ 10100 900 
Wire Wire Line
	10100 900  10100 1000
Wire Wire Line
	9450 900  9400 900 
Wire Wire Line
	8350 2900 8350 6500
Wire Wire Line
	9400 900  9400 1400
Connection ~ 9400 1400
Wire Wire Line
	9400 1400 9400 2100
Wire Wire Line
	9100 1600 9050 1600
Wire Wire Line
	8350 2900 8450 2900
Wire Wire Line
	4200 4250 4200 4450
Text Label 4200 4400 1    50   ~ 0
XY6
Entry Wire Line
	4200 4150 4300 4250
Entry Wire Line
	4300 4150 4400 4250
Wire Wire Line
	4300 4250 4300 4450
Text Label 4300 4400 1    50   ~ 0
XY5
Wire Wire Line
	4400 4250 4400 4450
Text Label 4400 4400 1    50   ~ 0
XY4
Entry Wire Line
	6100 4150 6200 4250
Entry Wire Line
	6200 4150 6300 4250
Wire Wire Line
	6200 4250 6200 4450
Text Label 6200 4400 1    50   ~ 0
XY3
Wire Wire Line
	6300 4250 6300 4450
Text Label 6300 4400 1    50   ~ 0
XY2
Entry Wire Line
	6300 4150 6400 4250
Entry Wire Line
	6400 4150 6500 4250
Wire Wire Line
	6400 4250 6400 4450
Text Label 6400 4400 1    50   ~ 0
XY1
Wire Wire Line
	6500 4250 6500 4450
Text Label 6500 4400 1    50   ~ 0
XY0
Wire Wire Line
	4600 4450 4600 4250
Wire Wire Line
	4600 4250 4750 4250
Wire Wire Line
	4750 4250 4750 4300
$Comp
L power:GND #PWR0712
U 1 1 607BE99D
P 4750 4300
F 0 "#PWR0712" H 4750 4050 50  0001 C CNN
F 1 "GND" H 4755 4127 50  0000 C CNN
F 2 "" H 4750 4300 50  0001 C CNN
F 3 "" H 4750 4300 50  0001 C CNN
	1    4750 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 4950 4950 4950
Wire Wire Line
	4950 4950 4950 4900
$Comp
L power:VCC #PWR0715
U 1 1 607C0A40
P 4950 4900
F 0 "#PWR0715" H 4950 4750 50  0001 C CNN
F 1 "VCC" H 4965 5073 50  0000 C CNN
F 2 "" H 4950 4900 50  0001 C CNN
F 3 "" H 4950 4900 50  0001 C CNN
	1    4950 4900
	1    0    0    -1  
$EndComp
NoConn ~ 4100 5450
NoConn ~ 6200 5450
Entry Wire Line
	4200 4150 4300 4250
Entry Wire Line
	4800 4150 4900 4050
Text Label 4900 4000 1    50   ~ 0
XY4
Wire Wire Line
	4900 3850 4900 4050
Entry Wire Line
	4200 4150 4300 4050
Text Label 4300 4000 1    50   ~ 0
XY6
Wire Wire Line
	4300 3850 4300 4050
Entry Wire Line
	3900 4150 4000 4050
Text Label 4000 4000 1    50   ~ 0
XY7
Wire Wire Line
	4000 3850 4000 4050
Entry Wire Line
	7000 4150 7100 4050
Text Label 7100 4000 1    50   ~ 0
XY1
Wire Wire Line
	7100 3850 7100 4050
Entry Wire Line
	7300 4150 7400 4050
Text Label 7400 4000 1    50   ~ 0
XY0
Wire Wire Line
	7400 3850 7400 4050
Entry Wire Line
	6700 4150 6800 4050
Text Label 6800 4000 1    50   ~ 0
XY2
Wire Wire Line
	6800 3850 6800 4050
Entry Wire Line
	6400 4150 6500 4050
Text Label 6500 4000 1    50   ~ 0
XY3
Wire Wire Line
	6500 3850 6500 4050
Wire Wire Line
	6700 4450 6700 4250
Wire Wire Line
	6700 4250 6850 4250
Wire Wire Line
	6850 4250 6850 4300
$Comp
L power:GND #PWR0713
U 1 1 607D09C3
P 6850 4300
F 0 "#PWR0713" H 6850 4050 50  0001 C CNN
F 1 "GND" H 6855 4127 50  0000 C CNN
F 2 "" H 6850 4300 50  0001 C CNN
F 3 "" H 6850 4300 50  0001 C CNN
	1    6850 4300
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0714
U 1 1 607D2BD5
P 7050 4850
F 0 "#PWR0714" H 7050 4700 50  0001 C CNN
F 1 "VCC" H 7065 5023 50  0000 C CNN
F 2 "" H 7050 4850 50  0001 C CNN
F 3 "" H 7050 4850 50  0001 C CNN
	1    7050 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 4950 7050 4950
Wire Wire Line
	7050 4950 7050 4850
Entry Wire Line
	6600 5850 6700 5750
Entry Wire Line
	6500 5850 6600 5750
Wire Wire Line
	6700 5450 6700 5750
Entry Wire Line
	6400 5850 6500 5750
Entry Wire Line
	6300 5850 6400 5750
Wire Wire Line
	6500 5450 6500 5750
Wire Wire Line
	6400 5750 6400 5450
Entry Wire Line
	4500 5850 4600 5750
Entry Wire Line
	4400 5850 4500 5750
Wire Wire Line
	4600 5450 4600 5750
Wire Wire Line
	4500 5750 4500 5450
Entry Wire Line
	4300 5850 4400 5750
Wire Wire Line
	4400 5450 4400 5750
Text Label 6700 5700 1    50   ~ 0
SUM0
Wire Wire Line
	6600 5750 6600 5450
Text Label 6600 5700 1    50   ~ 0
SUM1
Text Label 6500 5700 1    50   ~ 0
SUM2
Text Label 6400 5700 1    50   ~ 0
SUM3
Text Label 4600 5700 1    50   ~ 0
SUM4
Text Label 4500 5700 1    50   ~ 0
SUM5
Text Label 4400 5700 1    50   ~ 0
SUM6
Entry Wire Line
	3900 7850 4000 7750
Entry Wire Line
	4000 7850 4100 7750
Wire Wire Line
	4100 7500 4100 7750
Entry Wire Line
	4100 7850 4200 7750
Wire Wire Line
	4000 7500 4000 7750
Wire Wire Line
	4200 7750 4200 7500
Entry Wire Line
	4200 7850 4300 7750
Wire Wire Line
	4300 7500 4300 7750
Entry Wire Line
	4300 7850 4400 7750
Entry Wire Line
	4400 7850 4500 7750
Wire Wire Line
	4500 7500 4500 7750
Entry Wire Line
	4500 7850 4600 7750
Wire Wire Line
	4400 7500 4400 7750
Wire Wire Line
	4600 7750 4600 7500
Wire Wire Line
	3900 2600 3900 2850
Wire Wire Line
	4000 2850 4000 2600
Wire Wire Line
	4200 2600 4200 2850
Entry Wire Line
	4400 2500 4500 2600
Entry Wire Line
	4500 2500 4600 2600
Entry Wire Line
	4700 2500 4800 2600
Entry Wire Line
	4800 2500 4900 2600
Wire Wire Line
	4900 2600 4900 2850
Wire Wire Line
	4500 2600 4500 2850
Wire Wire Line
	4600 2850 4600 2600
Wire Wire Line
	4800 2600 4800 2850
Entry Wire Line
	6300 2500 6400 2600
Entry Wire Line
	6400 2500 6500 2600
Entry Wire Line
	6600 2500 6700 2600
Entry Wire Line
	6700 2500 6800 2600
Wire Wire Line
	6800 2600 6800 2850
Wire Wire Line
	6400 2600 6400 2850
Wire Wire Line
	6500 2850 6500 2600
Wire Wire Line
	6700 2600 6700 2850
Entry Wire Line
	6900 2500 7000 2600
Entry Wire Line
	7000 2500 7100 2600
Entry Wire Line
	7200 2500 7300 2600
Entry Wire Line
	7300 2500 7400 2600
Wire Wire Line
	7400 2600 7400 2850
Wire Wire Line
	7000 2600 7000 2850
Wire Wire Line
	7100 2850 7100 2600
Wire Wire Line
	7300 2600 7300 2850
Entry Wire Line
	6250 2500 6350 2400
Wire Wire Line
	6350 2200 6350 2400
Entry Wire Line
	6350 2500 6450 2400
Wire Wire Line
	6450 2200 6450 2400
Entry Wire Line
	6450 2500 6550 2400
Wire Wire Line
	6550 2200 6550 2400
Entry Wire Line
	6550 2500 6650 2400
Wire Wire Line
	6650 2200 6650 2400
Entry Wire Line
	6650 2500 6750 2400
Wire Wire Line
	6750 2200 6750 2400
Entry Wire Line
	6750 2500 6850 2400
Wire Wire Line
	6850 2200 6850 2400
Entry Wire Line
	6850 2500 6950 2400
Wire Wire Line
	6950 2200 6950 2400
Entry Wire Line
	6950 2500 7050 2400
Wire Wire Line
	7050 2200 7050 2400
Entry Wire Line
	3750 850  3850 950 
Wire Wire Line
	3850 950  3850 1200
Entry Wire Line
	3850 850  3950 950 
Wire Wire Line
	3950 950  3950 1200
Entry Wire Line
	3950 850  4050 950 
Wire Wire Line
	4050 950  4050 1200
Entry Wire Line
	4050 850  4150 950 
Wire Wire Line
	4150 950  4150 1200
Entry Wire Line
	4150 850  4250 950 
Wire Wire Line
	4250 950  4250 1200
Entry Wire Line
	4250 850  4350 950 
Wire Wire Line
	4350 950  4350 1200
Entry Wire Line
	4350 850  4450 950 
Wire Wire Line
	4450 950  4450 1200
Entry Wire Line
	3900 6150 4000 6250
Wire Wire Line
	4000 6250 4000 6500
Entry Wire Line
	4000 6150 4100 6250
Wire Wire Line
	4100 6250 4100 6500
Entry Wire Line
	4100 6150 4200 6250
Wire Wire Line
	4200 6250 4200 6500
Entry Wire Line
	4200 6150 4300 6250
Wire Wire Line
	4300 6250 4300 6500
Entry Wire Line
	4300 6150 4400 6250
Wire Wire Line
	4400 6250 4400 6500
Entry Wire Line
	4400 6150 4500 6250
Wire Wire Line
	4500 6250 4500 6500
Entry Wire Line
	4500 6150 4600 6250
Wire Wire Line
	4600 6250 4600 6500
Entry Wire Line
	3500 4150 3600 4250
Entry Wire Line
	3600 4150 3700 4250
Wire Wire Line
	3600 4250 3600 4450
Wire Wire Line
	3700 4250 3700 4450
Entry Wire Line
	3700 4150 3800 4250
Entry Wire Line
	3800 4150 3900 4250
Wire Wire Line
	3800 4250 3800 4450
Wire Wire Line
	3900 4250 3900 4450
Entry Wire Line
	3700 4150 3800 4250
Entry Wire Line
	5600 4150 5700 4250
Entry Wire Line
	5700 4150 5800 4250
Wire Wire Line
	5700 4250 5700 4450
Wire Wire Line
	5800 4250 5800 4450
Entry Wire Line
	5800 4150 5900 4250
Entry Wire Line
	5900 4150 6000 4250
Wire Wire Line
	5900 4250 5900 4450
Wire Wire Line
	6000 4250 6000 4450
Entry Wire Line
	5800 4150 5900 4250
Wire Wire Line
	6100 2850 6100 2800
Wire Wire Line
	6100 2800 5900 2800
Wire Wire Line
	6200 2850 6200 2650
Wire Wire Line
	6200 2650 5900 2650
Text GLabel 5900 2650 0    50   Input ~ 0
DY
Text GLabel 5900 2800 0    50   Input ~ 0
DZ
Text Label 4450 1100 1    50   ~ 0
D1
Text Label 4350 1100 1    50   ~ 0
D2
Text Label 4250 1100 1    50   ~ 0
D3
Text Label 4150 1100 1    50   ~ 0
D4
Text Label 4050 1100 1    50   ~ 0
D5
Text Label 3950 1100 1    50   ~ 0
D6
Text Label 3850 1100 1    50   ~ 0
D7
Entry Wire Line
	6950 850  7050 950 
Text Label 7050 1100 1    50   ~ 0
D0
Wire Wire Line
	7050 950  7050 1200
Entry Wire Line
	6250 850  6350 950 
Wire Wire Line
	6350 950  6350 1200
Entry Wire Line
	6350 850  6450 950 
Wire Wire Line
	6450 950  6450 1200
Entry Wire Line
	6450 850  6550 950 
Wire Wire Line
	6550 950  6550 1200
Entry Wire Line
	6550 850  6650 950 
Wire Wire Line
	6650 950  6650 1200
Entry Wire Line
	6650 850  6750 950 
Wire Wire Line
	6750 950  6750 1200
Entry Wire Line
	6750 850  6850 950 
Wire Wire Line
	6850 950  6850 1200
Entry Wire Line
	6850 850  6950 950 
Wire Wire Line
	6950 950  6950 1200
Text Label 6950 1100 1    50   ~ 0
D1
Text Label 6850 1100 1    50   ~ 0
D2
Text Label 6750 1100 1    50   ~ 0
D3
Text Label 6650 1100 1    50   ~ 0
D4
Text Label 6550 1100 1    50   ~ 0
D5
Text Label 6450 1100 1    50   ~ 0
D6
Text Label 6350 1100 1    50   ~ 0
D7
Text Label 7050 2350 1    50   ~ 0
Y0
Text Label 6950 2350 1    50   ~ 0
Y1
Text Label 6850 2350 1    50   ~ 0
Y2
Text Label 6750 2350 1    50   ~ 0
Y3
Text Label 6650 2350 1    50   ~ 0
Y4
Text Label 6550 2350 1    50   ~ 0
Y5
Text Label 6450 2350 1    50   ~ 0
Y6
Text Label 6350 2350 1    50   ~ 0
Y7
Entry Wire Line
	4350 2500 4450 2400
Wire Wire Line
	4450 2200 4450 2400
Entry Wire Line
	4250 2500 4350 2400
Wire Wire Line
	4350 2200 4350 2400
Entry Wire Line
	4150 2500 4250 2400
Wire Wire Line
	4250 2200 4250 2400
Entry Wire Line
	4050 2500 4150 2400
Wire Wire Line
	4150 2200 4150 2400
Entry Wire Line
	3950 2500 4050 2400
Wire Wire Line
	4050 2200 4050 2400
Entry Wire Line
	3850 2500 3950 2400
Wire Wire Line
	3950 2200 3950 2400
Entry Wire Line
	3750 2500 3850 2400
Wire Wire Line
	3850 2200 3850 2400
Text Label 4550 2350 1    50   ~ 0
X0
Text Label 4450 2350 1    50   ~ 0
X1
Text Label 4350 2350 1    50   ~ 0
X2
Text Label 4250 2350 1    50   ~ 0
X3
Text Label 4150 2350 1    50   ~ 0
X4
Text Label 4050 2350 1    50   ~ 0
X5
Text Label 3950 2350 1    50   ~ 0
X6
Text Label 3850 2350 1    50   ~ 0
X7
$Comp
L power:VCC #PWR0708
U 1 1 609A24DD
P 7750 3250
F 0 "#PWR0708" H 7750 3100 50  0001 C CNN
F 1 "VCC" H 7765 3423 50  0000 C CNN
F 2 "" H 7750 3250 50  0001 C CNN
F 3 "" H 7750 3250 50  0001 C CNN
	1    7750 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 3350 7750 3350
Wire Wire Line
	7750 3350 7750 3250
$Comp
L power:VCC #PWR0707
U 1 1 609AE0D9
P 5250 3250
F 0 "#PWR0707" H 5250 3100 50  0001 C CNN
F 1 "VCC" H 5265 3423 50  0000 C CNN
F 2 "" H 5250 3250 50  0001 C CNN
F 3 "" H 5250 3250 50  0001 C CNN
	1    5250 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3350 5250 3350
Wire Wire Line
	5250 3350 5250 3250
$Comp
L power:VCC #PWR0703
U 1 1 609BA2A5
P 7400 1600
F 0 "#PWR0703" H 7400 1450 50  0001 C CNN
F 1 "VCC" H 7415 1773 50  0000 C CNN
F 2 "" H 7400 1600 50  0001 C CNN
F 3 "" H 7400 1600 50  0001 C CNN
	1    7400 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 1700 7400 1700
Wire Wire Line
	7400 1700 7400 1600
$Comp
L power:VCC #PWR0702
U 1 1 609C64A7
P 4900 1600
F 0 "#PWR0702" H 4900 1450 50  0001 C CNN
F 1 "VCC" H 4915 1773 50  0000 C CNN
F 2 "" H 4900 1600 50  0001 C CNN
F 3 "" H 4900 1600 50  0001 C CNN
	1    4900 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 1700 4900 1700
Wire Wire Line
	4900 1700 4900 1600
$Comp
L power:VCC #PWR0720
U 1 1 609D29F8
P 3550 6900
F 0 "#PWR0720" H 3550 6750 50  0001 C CNN
F 1 "VCC" H 3565 7073 50  0000 C CNN
F 2 "" H 3550 6900 50  0001 C CNN
F 3 "" H 3550 6900 50  0001 C CNN
	1    3550 6900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3600 7000 3550 7000
Wire Wire Line
	3550 7000 3550 6900
$Comp
L power:GND #PWR0717
U 1 1 609DFFB2
P 5350 5000
F 0 "#PWR0717" H 5350 4750 50  0001 C CNN
F 1 "GND" H 5355 4827 50  0000 C CNN
F 2 "" H 5350 5000 50  0001 C CNN
F 3 "" H 5350 5000 50  0001 C CNN
	1    5350 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5000 5350 4950
Wire Wire Line
	5350 4950 5400 4950
$Comp
L power:GND #PWR0716
U 1 1 609ED32B
P 3250 5000
F 0 "#PWR0716" H 3250 4750 50  0001 C CNN
F 1 "GND" H 3255 4827 50  0000 C CNN
F 2 "" H 3250 5000 50  0001 C CNN
F 3 "" H 3250 5000 50  0001 C CNN
	1    3250 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 5000 3250 4950
Wire Wire Line
	3250 4950 3300 4950
$Comp
L power:GND #PWR0710
U 1 1 609FA721
P 3250 3400
F 0 "#PWR0710" H 3250 3150 50  0001 C CNN
F 1 "GND" H 3255 3227 50  0000 C CNN
F 2 "" H 3250 3400 50  0001 C CNN
F 3 "" H 3250 3400 50  0001 C CNN
	1    3250 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3400 3250 3350
Wire Wire Line
	3250 3350 3300 3350
$Comp
L power:GND #PWR0711
U 1 1 60A079AF
P 5750 3400
F 0 "#PWR0711" H 5750 3150 50  0001 C CNN
F 1 "GND" H 5755 3227 50  0000 C CNN
F 2 "" H 5750 3400 50  0001 C CNN
F 3 "" H 5750 3400 50  0001 C CNN
	1    5750 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 3400 5750 3350
Wire Wire Line
	5750 3350 5800 3350
$Comp
L power:GND #PWR0704
U 1 1 60A30BCD
P 3200 1700
F 0 "#PWR0704" H 3200 1450 50  0001 C CNN
F 1 "GND" H 3205 1527 50  0000 C CNN
F 2 "" H 3200 1700 50  0001 C CNN
F 3 "" H 3200 1700 50  0001 C CNN
	1    3200 1700
	1    0    0    -1  
$EndComp
Connection ~ 3200 1700
$Comp
L power:GND #PWR0705
U 1 1 60A31113
P 5700 1700
F 0 "#PWR0705" H 5700 1450 50  0001 C CNN
F 1 "GND" H 5705 1527 50  0000 C CNN
F 2 "" H 5700 1700 50  0001 C CNN
F 3 "" H 5700 1700 50  0001 C CNN
	1    5700 1700
	1    0    0    -1  
$EndComp
Connection ~ 5700 1700
$Comp
L power:GND #PWR0718
U 1 1 60A3153E
P 1700 5100
F 0 "#PWR0718" H 1700 4850 50  0001 C CNN
F 1 "GND" H 1705 4927 50  0000 C CNN
F 2 "" H 1700 5100 50  0001 C CNN
F 3 "" H 1700 5100 50  0001 C CNN
	1    1700 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 5100 1700 5050
$Comp
L power:GND #PWR0706
U 1 1 60A3EE9E
P 1700 2850
F 0 "#PWR0706" H 1700 2600 50  0001 C CNN
F 1 "GND" H 1705 2677 50  0000 C CNN
F 2 "" H 1700 2850 50  0001 C CNN
F 3 "" H 1700 2850 50  0001 C CNN
	1    1700 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 2850 1700 2800
$Comp
L power:GND #PWR0722
U 1 1 60A4CE2B
P 1700 7350
F 0 "#PWR0722" H 1700 7100 50  0001 C CNN
F 1 "GND" H 1705 7177 50  0000 C CNN
F 2 "" H 1700 7350 50  0001 C CNN
F 3 "" H 1700 7350 50  0001 C CNN
	1    1700 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 7350 1700 7300
$Comp
L power:VCC #PWR0709
U 1 1 60A68388
P 1700 3400
F 0 "#PWR0709" H 1700 3250 50  0001 C CNN
F 1 "VCC" H 1715 3573 50  0000 C CNN
F 2 "" H 1700 3400 50  0001 C CNN
F 3 "" H 1700 3400 50  0001 C CNN
	1    1700 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 3400 1700 3450
$Comp
L power:VCC #PWR0701
U 1 1 60A7680B
P 1700 1150
F 0 "#PWR0701" H 1700 1000 50  0001 C CNN
F 1 "VCC" H 1715 1323 50  0000 C CNN
F 2 "" H 1700 1150 50  0001 C CNN
F 3 "" H 1700 1150 50  0001 C CNN
	1    1700 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 1150 1700 1200
$Comp
L power:VCC #PWR0719
U 1 1 60AB0CC5
P 1700 5650
F 0 "#PWR0719" H 1700 5500 50  0001 C CNN
F 1 "VCC" H 1715 5823 50  0000 C CNN
F 2 "" H 1700 5650 50  0001 C CNN
F 3 "" H 1700 5650 50  0001 C CNN
	1    1700 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 5650 1700 5700
Wire Wire Line
	1200 6900 850  6900
Wire Wire Line
	850  6900 850  7350
Wire Wire Line
	850  7350 1700 7350
Text GLabel 1150 7000 0    50   Input ~ 0
~RD
Wire Wire Line
	1150 7000 1200 7000
Connection ~ 1700 7350
Wire Wire Line
	1200 4650 850  4650
Wire Wire Line
	850  4650 850  5100
Wire Wire Line
	850  5100 1700 5100
Text GLabel 1150 4750 0    50   Input ~ 0
~RY
Wire Wire Line
	1150 4750 1200 4750
Connection ~ 1700 5100
Wire Wire Line
	1200 2400 850  2400
Wire Wire Line
	850  2400 850  2850
Wire Wire Line
	850  2850 1700 2850
Text GLabel 1150 2500 0    50   Input ~ 0
~RX
Wire Wire Line
	1150 2500 1200 2500
Connection ~ 1700 2850
Entry Wire Line
	2600 3750 2500 3850
Wire Wire Line
	2500 3850 2200 3850
Entry Wire Line
	2600 3850 2500 3950
Wire Wire Line
	2500 3950 2200 3950
Entry Wire Line
	2600 3950 2500 4050
Wire Wire Line
	2500 4050 2200 4050
Entry Wire Line
	2600 4050 2500 4150
Wire Wire Line
	2500 4150 2200 4150
Entry Wire Line
	2600 4150 2500 4250
Wire Wire Line
	2500 4250 2200 4250
Entry Wire Line
	2600 4250 2500 4350
Wire Wire Line
	2500 4350 2200 4350
Entry Wire Line
	2600 4350 2500 4450
Wire Wire Line
	2500 4450 2200 4450
Entry Wire Line
	2600 1400 2500 1500
Wire Wire Line
	2500 1500 2200 1500
Text Label 2400 1500 2    50   ~ 0
X0
Entry Wire Line
	2600 1500 2500 1600
Wire Wire Line
	2500 1600 2200 1600
Entry Wire Line
	2600 1600 2500 1700
Wire Wire Line
	2500 1700 2200 1700
Entry Wire Line
	2600 1700 2500 1800
Wire Wire Line
	2500 1800 2200 1800
Entry Wire Line
	2600 1800 2500 1900
Wire Wire Line
	2500 1900 2200 1900
Entry Wire Line
	2600 1900 2500 2000
Wire Wire Line
	2500 2000 2200 2000
Entry Wire Line
	2600 2000 2500 2100
Wire Wire Line
	2500 2100 2200 2100
Entry Wire Line
	2600 2100 2500 2200
Wire Wire Line
	2500 2200 2200 2200
Entry Wire Line
	2600 5900 2500 6000
Wire Wire Line
	2500 6000 2200 6000
Text Label 2450 6000 2    50   ~ 0
SUM0
Entry Wire Line
	2600 6000 2500 6100
Wire Wire Line
	2500 6100 2200 6100
Entry Wire Line
	2600 6100 2500 6200
Wire Wire Line
	2500 6200 2200 6200
Entry Wire Line
	2600 6200 2500 6300
Wire Wire Line
	2500 6300 2200 6300
Entry Wire Line
	2600 6300 2500 6400
Wire Wire Line
	2500 6400 2200 6400
Entry Wire Line
	2600 6400 2500 6500
Wire Wire Line
	2500 6500 2200 6500
Entry Wire Line
	2600 6500 2500 6600
Wire Wire Line
	2500 6600 2200 6600
Entry Wire Line
	2600 6600 2500 6700
Wire Wire Line
	2500 6700 2200 6700
Text Label 2450 6100 2    50   ~ 0
SUM1
Text Label 2450 6200 2    50   ~ 0
SUM2
Text Label 2450 6300 2    50   ~ 0
SUM3
Text Label 2450 6400 2    50   ~ 0
SUM4
Text Label 2450 6500 2    50   ~ 0
SUM5
Text Label 2450 6600 2    50   ~ 0
SUM6
Text Label 2450 6700 2    50   ~ 0
SUM7
Text Label 2400 3850 2    50   ~ 0
Y1
Text Label 2400 3950 2    50   ~ 0
Y2
Text Label 2400 4050 2    50   ~ 0
Y3
Text Label 2400 4150 2    50   ~ 0
Y4
Text Label 2400 4250 2    50   ~ 0
Y5
Text Label 2400 4350 2    50   ~ 0
Y6
Text Label 2400 4450 2    50   ~ 0
Y7
Text Label 2400 1600 2    50   ~ 0
X1
Text Label 2400 1700 2    50   ~ 0
X2
Text Label 2400 1800 2    50   ~ 0
X3
Text Label 2400 1900 2    50   ~ 0
X4
Text Label 2400 2000 2    50   ~ 0
X5
Text Label 2400 2100 2    50   ~ 0
X6
Text Label 2400 2200 2    50   ~ 0
X7
Entry Wire Line
	700  1400 800  1500
Wire Wire Line
	800  1500 1200 1500
Entry Wire Line
	700  1500 800  1600
Wire Wire Line
	800  1600 1200 1600
Entry Wire Line
	700  1600 800  1700
Wire Wire Line
	800  1700 1200 1700
Entry Wire Line
	700  1700 800  1800
Wire Wire Line
	800  1800 1200 1800
Entry Wire Line
	700  1800 800  1900
Wire Wire Line
	800  1900 1200 1900
Entry Wire Line
	700  1900 800  2000
Wire Wire Line
	800  2000 1200 2000
Entry Wire Line
	700  2000 800  2100
Wire Wire Line
	800  2100 1200 2100
Entry Wire Line
	700  2100 800  2200
Wire Wire Line
	800  2200 1200 2200
Text Label 1050 1500 2    50   ~ 0
D0
Text Label 1050 1600 2    50   ~ 0
D1
Text Label 1050 1700 2    50   ~ 0
D2
Text Label 1050 1800 2    50   ~ 0
D3
Text Label 1050 1900 2    50   ~ 0
D4
Text Label 1050 2000 2    50   ~ 0
D5
Text Label 1050 2100 2    50   ~ 0
D6
Text Label 1050 2200 2    50   ~ 0
D7
Entry Wire Line
	700  3650 800  3750
Wire Wire Line
	800  3750 1200 3750
Entry Wire Line
	700  3750 800  3850
Wire Wire Line
	800  3850 1200 3850
Entry Wire Line
	700  3850 800  3950
Wire Wire Line
	800  3950 1200 3950
Entry Wire Line
	700  3950 800  4050
Wire Wire Line
	800  4050 1200 4050
Entry Wire Line
	700  4050 800  4150
Wire Wire Line
	800  4150 1200 4150
Entry Wire Line
	700  4150 800  4250
Wire Wire Line
	800  4250 1200 4250
Entry Wire Line
	700  4250 800  4350
Wire Wire Line
	800  4350 1200 4350
Entry Wire Line
	700  4350 800  4450
Wire Wire Line
	800  4450 1200 4450
Text Label 1050 3750 2    50   ~ 0
D0
Text Label 1050 3850 2    50   ~ 0
D1
Text Label 1050 3950 2    50   ~ 0
D2
Text Label 1050 4050 2    50   ~ 0
D3
Text Label 1050 4150 2    50   ~ 0
D4
Text Label 1050 4250 2    50   ~ 0
D5
Text Label 1050 4350 2    50   ~ 0
D6
Text Label 1050 4450 2    50   ~ 0
D7
Entry Wire Line
	700  5900 800  6000
Wire Wire Line
	800  6000 1200 6000
Entry Wire Line
	700  6000 800  6100
Wire Wire Line
	800  6100 1200 6100
Entry Wire Line
	700  6100 800  6200
Wire Wire Line
	800  6200 1200 6200
Entry Wire Line
	700  6200 800  6300
Wire Wire Line
	800  6300 1200 6300
Entry Wire Line
	700  6300 800  6400
Wire Wire Line
	800  6400 1200 6400
Entry Wire Line
	700  6400 800  6500
Wire Wire Line
	800  6500 1200 6500
Entry Wire Line
	700  6500 800  6600
Wire Wire Line
	800  6600 1200 6600
Entry Wire Line
	700  6600 800  6700
Wire Wire Line
	800  6700 1200 6700
Text Label 1050 6000 2    50   ~ 0
D0
Text Label 1050 6100 2    50   ~ 0
D1
Text Label 1050 6200 2    50   ~ 0
D2
Text Label 1050 6300 2    50   ~ 0
D3
Text Label 1050 6400 2    50   ~ 0
D4
Text Label 1050 6500 2    50   ~ 0
D5
Text Label 1050 6600 2    50   ~ 0
D6
Text Label 1050 6700 2    50   ~ 0
D7
Text Label 7400 2800 1    50   ~ 0
X0
Text Label 7100 2800 1    50   ~ 0
X1
Text Label 6800 2800 1    50   ~ 0
X2
Text Label 6500 2800 1    50   ~ 0
X3
Text Label 4900 2800 1    50   ~ 0
X4
Text Label 4600 2800 1    50   ~ 0
X5
Text Label 4000 2800 1    50   ~ 0
X7
Text Label 7300 2800 1    50   ~ 0
Y0
Text Label 7000 2800 1    50   ~ 0
Y1
Text Label 6700 2800 1    50   ~ 0
Y2
Text Label 6400 2800 1    50   ~ 0
Y3
Text Label 4800 2800 1    50   ~ 0
Y4
Text Label 4500 2800 1    50   ~ 0
Y5
Text Label 4200 2800 1    50   ~ 0
Y6
Text Label 3900 2800 1    50   ~ 0
Y7
Text Label 4000 7650 1    50   ~ 0
D1
Text Label 4100 7650 1    50   ~ 0
D2
Text Label 4200 7650 1    50   ~ 0
D3
Text Label 4300 7650 1    50   ~ 0
D4
Text Label 4400 7650 1    50   ~ 0
D5
Text Label 4500 7650 1    50   ~ 0
D6
Text Label 4600 7650 1    50   ~ 0
D7
Text Label 4000 6400 1    50   ~ 0
DQ1
Text Label 4100 6400 1    50   ~ 0
DQ2
Text Label 4200 6400 1    50   ~ 0
DQ3
Text Label 4300 6400 1    50   ~ 0
DQ4
Text Label 4400 6400 1    50   ~ 0
DQ5
Text Label 4500 6400 1    50   ~ 0
DQ6
Text Label 4600 6400 1    50   ~ 0
DQ7
Text Label 6000 4400 1    50   ~ 0
DQ0
Text Label 5900 4400 1    50   ~ 0
DQ1
Text Label 5800 4400 1    50   ~ 0
DQ2
Text Label 5700 4400 1    50   ~ 0
DQ3
Text Label 3900 4400 1    50   ~ 0
DQ4
Text Label 3800 4400 1    50   ~ 0
DQ5
Text Label 3700 4400 1    50   ~ 0
DQ6
Text Label 3600 4400 1    50   ~ 0
DQ7
Text Label 1200 850  2    50   ~ 0
D[0..7]
Text Notes 2800 850  0    50   ~ 0
DATA BUS
Text Notes 5050 2500 0    50   ~ 0
SELECTOR INPUTS
Text Notes 5050 4150 0    50   ~ 0
ADDER INPUTS
Text Notes 5050 5850 0    50   ~ 0
ADDER OUTPUTS
Text Notes 6400 1700 0    50   ~ 0
Y REGISTER
Text Notes 3850 1700 0    50   ~ 0
X REGISTER
Text Notes 4100 7000 0    50   ~ 0
D REGISTER
Text Notes 6450 3350 0    50   ~ 0
SELECTOR LOW
Text Notes 3950 3350 0    50   ~ 0
SELECTOR HIGH
Text Notes 6000 4950 0    50   ~ 0
ADDER LOW
Text Notes 3900 4950 0    50   ~ 0
ADDER HIGH
Text Notes 2550 7400 0    50   ~ 0
Note that D0..D7 refer to\nthe bus and DQ0..DQ7 refer\nto the D register outputs
Text Notes 8700 5100 0    50   ~ 0
The X and Y registers are\nthe inputs to the selector
Text Notes 8700 5600 0    50   ~ 0
The X,Y, and D registers can\nbe written from the bus
Text Notes 8700 5850 0    50   ~ 0
The X and Y registers and the\nadder result can be read to the bus
Wire Notes Line
	8600 4850 8600 6350
Wire Notes Line
	8600 6350 10300 6350
Wire Notes Line
	10300 6350 10300 4850
Wire Notes Line
	10300 4850 8600 4850
Text Notes 8700 5350 0    50   ~ 0
The selector output and D register\nare the inputs to the adder
Text Notes 8700 6000 0    50   ~ 0
DX control selects D+X or D+Y
Text Notes 8700 6250 0    50   ~ 0
DZ control selects D+0 which is used\nto read D to the bus through the adder
Wire Bus Line
	2600 5850 2600 6750
Wire Bus Line
	2600 1350 2600 2500
Wire Bus Line
	2600 2500 2600 4500
Wire Bus Line
	3750 6150 7850 6150
Wire Bus Line
	700  7850 4650 7850
Wire Bus Line
	2600 5850 6750 5850
Wire Bus Line
	700  850  7150 850 
Wire Bus Line
	3500 4150 7850 4150
Wire Bus Line
	2600 2500 7450 2500
Wire Bus Line
	700  850  700  7850
$EndSCHEMATC

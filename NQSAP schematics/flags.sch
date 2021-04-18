EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 2 7
Title "NQSAP Flags"
Date "2021-04-18"
Rev "1.8"
Comp "github.com/TomNisbet"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 74xx:74LS74 U207
U 1 1 5FD96CB1
P 6550 2700
F 0 "U207" H 6550 3181 50  0000 C CNN
F 1 "74LS74" H 6550 3090 50  0000 C CNN
F 2 "" H 6550 2700 50  0001 C CNN
F 3 "74xx/74hc_hct74.pdf" H 6550 2700 50  0001 C CNN
	1    6550 2700
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS74 U207
U 2 1 5FD989ED
P 6550 3550
F 0 "U207" H 6550 4031 50  0000 C CNN
F 1 "74LS74" H 6550 3940 50  0000 C CNN
F 2 "" H 6550 3550 50  0001 C CNN
F 3 "74xx/74hc_hct74.pdf" H 6550 3550 50  0001 C CNN
	2    6550 3550
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS08 U204
U 4 1 5FD9D94E
P 5600 1650
F 0 "U204" H 5600 1975 50  0000 C CNN
F 1 "74LS08" H 5600 1884 50  0000 C CNN
F 2 "" H 5600 1650 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS08" H 5600 1650 50  0001 C CNN
	4    5600 1650
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS08 U204
U 1 1 5FDA4688
P 5600 2250
F 0 "U204" H 5600 2575 50  0000 C CNN
F 1 "74LS08" H 5600 2484 50  0000 C CNN
F 2 "" H 5600 2250 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS08" H 5600 2250 50  0001 C CNN
	1    5600 2250
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS08 U204
U 2 1 5FDAA20C
P 5600 6350
F 0 "U204" H 5600 6675 50  0000 C CNN
F 1 "74LS08" H 5600 6584 50  0000 C CNN
F 2 "" H 5600 6350 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS08" H 5600 6350 50  0001 C CNN
	2    5600 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 6250 5300 6250
Wire Wire Line
	5200 5850 5200 6050
Connection ~ 5200 6050
Wire Wire Line
	5200 6050 5200 6250
$Comp
L 74xx:74LS74 U209
U 1 1 5FDB914B
P 6550 4450
F 0 "U209" H 6550 4931 50  0000 C CNN
F 1 "74LS74" H 6550 4840 50  0000 C CNN
F 2 "" H 6550 4450 50  0001 C CNN
F 3 "74xx/74hc_hct74.pdf" H 6550 4450 50  0001 C CNN
	1    6550 4450
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS74 U209
U 2 1 5FDB917F
P 6550 5300
F 0 "U209" H 6550 5781 50  0000 C CNN
F 1 "74LS74" H 6550 5690 50  0000 C CNN
F 2 "" H 6550 5300 50  0001 C CNN
F 3 "74xx/74hc_hct74.pdf" H 6550 5300 50  0001 C CNN
	2    6550 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 1750 5200 1750
Wire Wire Line
	5200 1750 5200 1950
Wire Wire Line
	5200 2150 5300 2150
Wire Wire Line
	5200 1950 5100 1950
Connection ~ 5200 1950
Wire Wire Line
	5200 1950 5200 2150
Wire Wire Line
	5900 1650 6150 1650
Wire Wire Line
	6150 1650 6150 2700
Wire Wire Line
	6150 2700 6250 2700
Wire Wire Line
	5900 2250 6000 2250
Wire Wire Line
	6000 2250 6000 3550
Wire Wire Line
	6000 3550 6250 3550
Wire Wire Line
	6000 5750 6000 4450
Wire Wire Line
	6000 4450 6250 4450
Wire Wire Line
	5900 6350 6200 6350
Wire Wire Line
	5900 5750 6000 5750
Wire Wire Line
	5300 5850 5200 5850
$Comp
L 74xx:74LS08 U204
U 3 1 5FDA69F7
P 5600 5750
F 0 "U204" H 5600 6075 50  0000 C CNN
F 1 "74LS08" H 5600 5984 50  0000 C CNN
F 2 "" H 5600 5750 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS08" H 5600 5750 50  0001 C CNN
	3    5600 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3450 5350 3450
Wire Wire Line
	5350 3450 5350 2600
Wire Wire Line
	5350 2600 6250 2600
Wire Wire Line
	5250 3750 5600 3750
Wire Wire Line
	5600 3750 5600 3450
Wire Wire Line
	5600 3450 6250 3450
Wire Wire Line
	5250 4050 5600 4050
Wire Wire Line
	5600 4050 5600 4350
Wire Wire Line
	5600 4350 6250 4350
$Comp
L 74xx:74HCT688 U211
U 1 1 5FE399C9
P 2550 4650
F 0 "U211" H 2900 4700 50  0000 L CNN
F 1 "74HCT688" H 2900 4600 50  0000 L CNN
F 2 "" H 2550 4650 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/cd54hc688.pdf" H 2550 4650 50  0001 C CNN
	1    2550 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 4650 1950 4650
Wire Wire Line
	1950 4650 1950 4750
Wire Wire Line
	1950 4750 2050 4750
Wire Wire Line
	1950 4850 2050 4850
Wire Wire Line
	1950 4750 1950 4850
Wire Wire Line
	1950 4950 2050 4950
Connection ~ 1950 4750
Connection ~ 1950 4850
Wire Wire Line
	1950 4850 1950 4950
Wire Wire Line
	2050 5050 1950 5050
Wire Wire Line
	1950 5050 1950 4950
Connection ~ 1950 4950
Wire Wire Line
	2050 5150 1950 5150
Wire Wire Line
	1950 5150 1950 5050
Connection ~ 1950 5050
Wire Wire Line
	2050 5250 1950 5250
Wire Wire Line
	1950 5250 1950 5150
Connection ~ 1950 5150
Wire Wire Line
	2050 5350 1950 5350
Wire Wire Line
	1950 5350 1950 5250
Connection ~ 1950 5250
Wire Wire Line
	1950 5350 1950 5550
Connection ~ 1950 5350
Wire Wire Line
	800  3850 2050 3850
Wire Wire Line
	800  3950 2050 3950
Wire Wire Line
	800  4050 2050 4050
Wire Wire Line
	800  4150 2050 4150
Wire Wire Line
	800  4250 2050 4250
Wire Wire Line
	800  4350 2050 4350
Wire Wire Line
	800  3750 2050 3750
Entry Wire Line
	700  3850 800  3950
Entry Wire Line
	700  3950 800  4050
Entry Wire Line
	700  4050 800  4150
Entry Wire Line
	700  4150 800  4250
Entry Wire Line
	700  4250 800  4350
Entry Wire Line
	700  4350 800  4450
Entry Wire Line
	700  3650 800  3750
Entry Wire Line
	700  3750 800  3850
Text Label 850  3750 0    50   ~ 0
D0
Text Label 850  3850 0    50   ~ 0
D1
Text Label 850  3950 0    50   ~ 0
D2
Text Label 850  4050 0    50   ~ 0
D3
Text Label 850  4150 0    50   ~ 0
D4
Text Label 850  4250 0    50   ~ 0
D5
Text Label 850  4350 0    50   ~ 0
D6
Text Label 850  4450 0    50   ~ 0
D7
$Comp
L 74xx:74LS151 U206
U 1 1 5FE7BA42
P 2800 1900
F 0 "U206" H 2900 2000 50  0000 C CNN
F 1 "74LS151" H 2900 1900 50  0000 C CNN
F 2 "" H 2800 1900 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS151" H 2800 1900 50  0001 C CNN
	1    2800 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 2400 2150 2400
Wire Wire Line
	2150 2400 2150 2600
Wire Wire Line
	2150 2600 2300 2600
Wire Wire Line
	2150 2600 2150 3050
Wire Wire Line
	2800 3050 2800 2900
Connection ~ 2150 2600
$Comp
L power:GND #PWR0221
U 1 1 5FEA5BF9
P 2550 5900
F 0 "#PWR0221" H 2550 5650 50  0001 C CNN
F 1 "GND" H 2555 5727 50  0000 C CNN
F 2 "" H 2550 5900 50  0001 C CNN
F 3 "" H 2550 5900 50  0001 C CNN
	1    2550 5900
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS04 U201
U 1 1 5FEAA0D0
P 3450 3750
F 0 "U201" H 3450 4067 50  0000 C CNN
F 1 "74LS04" H 3450 3976 50  0000 C CNN
F 2 "" H 3450 3750 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 3450 3750 50  0001 C CNN
	1    3450 3750
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS04 U201
U 6 1 5FEACFD9
P 9800 6300
F 0 "U201" H 9800 6617 50  0000 C CNN
F 1 "74LS04" H 9800 6526 50  0000 C CNN
F 2 "" H 9800 6300 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 9800 6300 50  0001 C CNN
	6    9800 6300
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74LS04 U201
U 3 1 5FEB002B
P 8100 5750
F 0 "U201" H 8100 6067 50  0000 C CNN
F 1 "74LS04" H 8100 5976 50  0000 C CNN
F 2 "" H 8100 5750 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 8100 5750 50  0001 C CNN
	3    8100 5750
	1    0    0    1   
$EndComp
$Comp
L 74xx:74LS04 U201
U 4 1 5FEB107A
P 5450 850
F 0 "U201" H 5450 1167 50  0000 C CNN
F 1 "74LS04" H 5450 1076 50  0000 C CNN
F 2 "" H 5450 850 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 5450 850 50  0001 C CNN
	4    5450 850 
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74LS04 U201
U 2 1 5FEB1BA6
P 3200 7300
F 0 "U201" H 3200 7617 50  0000 C CNN
F 1 "74LS04" H 3200 7526 50  0000 C CNN
F 2 "" H 3200 7300 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 3200 7300 50  0001 C CNN
	2    3200 7300
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS04 U201
U 5 1 5FEB2726
P 1550 1400
F 0 "U201" H 1500 1200 50  0000 C CNN
F 1 "74LS04" H 1500 1100 50  0000 C CNN
F 2 "" H 1550 1400 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 1550 1400 50  0001 C CNN
	5    1550 1400
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS157 U208
U 1 1 5FE0F104
P 4750 4050
F 0 "U208" H 4950 4950 50  0000 C CNN
F 1 "74LS157" H 4950 4850 50  0000 C CNN
F 2 "" H 4750 4050 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS157" H 4750 4050 50  0001 C CNN
	1    4750 4050
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS151 U210
U 1 1 5FEC38A0
P 9200 4600
F 0 "U210" H 9300 4700 50  0000 C CNN
F 1 "74LS151" H 9300 4600 50  0000 C CNN
F 2 "" H 9200 4600 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS151" H 9200 4600 50  0001 C CNN
	1    9200 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 4050 4250 4050
Wire Wire Line
	4150 3450 4250 3450
Wire Wire Line
	6850 4550 7250 4550
Wire Wire Line
	5300 1550 5100 1550
Wire Wire Line
	5300 2350 5100 2350
Text Label 6900 2600 0    50   ~ 0
C
Text Label 6900 2800 0    50   ~ 0
~C
Text Label 6900 3450 0    50   ~ 0
Z
Text Label 6900 3650 0    50   ~ 0
~Z
Text Label 6900 4350 0    50   ~ 0
V
Text Label 6900 4550 0    50   ~ 0
~V
Text Label 6900 5200 0    50   ~ 0
N
Text Label 6900 5400 0    50   ~ 0
~N
$Comp
L 74xx:74LS02 U203
U 1 1 60088FFB
P 9100 6200
F 0 "U203" H 9100 6525 50  0000 C CNN
F 1 "74LS02" H 9100 6434 50  0000 C CNN
F 2 "" H 9100 6200 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74ls02" H 9100 6200 50  0001 C CNN
	1    9100 6200
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74LS02 U203
U 2 1 600C75F9
P 7250 1200
F 0 "U203" H 7250 1525 50  0000 C CNN
F 1 "74LS02" H 7250 1434 50  0000 C CNN
F 2 "" H 7250 1200 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74ls02" H 7250 1200 50  0001 C CNN
	2    7250 1200
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0219
U 1 1 600E1AE8
P 9200 5650
F 0 "#PWR0219" H 9200 5400 50  0001 C CNN
F 1 "GND" H 9205 5477 50  0000 C CNN
F 2 "" H 9200 5650 50  0001 C CNN
F 3 "" H 9200 5650 50  0001 C CNN
	1    9200 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 5650 9200 5600
$Comp
L power:VCC #PWR0214
U 1 1 600E3605
P 9200 3700
F 0 "#PWR0214" H 9200 3550 50  0001 C CNN
F 1 "VCC" H 9215 3873 50  0000 C CNN
F 2 "" H 9200 3700 50  0001 C CNN
F 3 "" H 9200 3700 50  0001 C CNN
	1    9200 3700
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0206
U 1 1 600E56C9
P 6250 2400
F 0 "#PWR0206" H 6250 2250 50  0001 C CNN
F 1 "VCC" H 6265 2573 50  0000 C CNN
F 2 "" H 6250 2400 50  0001 C CNN
F 3 "" H 6250 2400 50  0001 C CNN
	1    6250 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0218
U 1 1 600E667D
P 4750 5050
F 0 "#PWR0218" H 4750 4800 50  0001 C CNN
F 1 "GND" H 4755 4877 50  0000 C CNN
F 2 "" H 4750 5050 50  0001 C CNN
F 3 "" H 4750 5050 50  0001 C CNN
	1    4750 5050
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0213
U 1 1 600E7842
P 2550 3400
F 0 "#PWR0213" H 2550 3250 50  0001 C CNN
F 1 "VCC" H 2565 3573 50  0000 C CNN
F 2 "" H 2550 3400 50  0001 C CNN
F 3 "" H 2550 3400 50  0001 C CNN
	1    2550 3400
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0215
U 1 1 600EAD76
P 6200 4150
F 0 "#PWR0215" H 6200 4000 50  0001 C CNN
F 1 "VCC" H 6215 4323 50  0000 C CNN
F 2 "" H 6200 4150 50  0001 C CNN
F 3 "" H 6200 4150 50  0001 C CNN
	1    6200 4150
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0211
U 1 1 600EB7D0
P 6200 3250
F 0 "#PWR0211" H 6200 3100 50  0001 C CNN
F 1 "VCC" H 6215 3423 50  0000 C CNN
F 2 "" H 6200 3250 50  0001 C CNN
F 3 "" H 6200 3250 50  0001 C CNN
	1    6200 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 2400 6550 2400
Wire Wire Line
	6200 3250 6550 3250
Wire Wire Line
	6200 4150 6550 4150
Wire Wire Line
	6200 5300 6250 5300
Wire Wire Line
	6200 5300 6200 6350
Wire Wire Line
	6250 5200 5350 5200
$Comp
L power:VCC #PWR0217
U 1 1 6013F206
P 6200 5000
F 0 "#PWR0217" H 6200 4850 50  0001 C CNN
F 1 "VCC" H 6215 5173 50  0000 C CNN
F 2 "" H 6200 5000 50  0001 C CNN
F 3 "" H 6200 5000 50  0001 C CNN
	1    6200 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 5000 6550 5000
Wire Wire Line
	6550 3850 6850 3850
Wire Wire Line
	6550 4750 6850 4750
Wire Wire Line
	6550 5600 6850 5600
$Comp
L power:VCC #PWR0210
U 1 1 60176670
P 4750 3150
F 0 "#PWR0210" H 4750 3000 50  0001 C CNN
F 1 "VCC" H 4765 3323 50  0000 C CNN
F 2 "" H 4750 3150 50  0001 C CNN
F 3 "" H 4750 3150 50  0001 C CNN
	1    4750 3150
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0201
U 1 1 60177A8E
P 2800 1000
F 0 "#PWR0201" H 2800 850 50  0001 C CNN
F 1 "VCC" H 2815 1173 50  0000 C CNN
F 2 "" H 2800 1000 50  0001 C CNN
F 3 "" H 2800 1000 50  0001 C CNN
	1    2800 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 5100 8650 5100
Wire Wire Line
	8700 5000 8650 5000
Wire Wire Line
	8700 4900 8650 4900
$Comp
L 74xx:74LS02 U203
U 3 1 601DA96D
P 3850 7400
F 0 "U203" H 3850 7725 50  0000 C CNN
F 1 "74LS02" H 3850 7634 50  0000 C CNN
F 2 "" H 3850 7400 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74ls02" H 3850 7400 50  0001 C CNN
	3    3850 7400
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS02 U203
U 4 1 601DD908
P 5500 7350
F 0 "U203" H 5500 7675 50  0000 C CNN
F 1 "74LS02" H 5500 7584 50  0000 C CNN
F 2 "" H 5500 7350 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74ls02" H 5500 7350 50  0001 C CNN
	4    5500 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 7450 5200 7450
Wire Wire Line
	4150 7400 4200 7400
Wire Wire Line
	5800 7350 5850 7350
Text GLabel 4200 7400 2    50   Output ~ 0
ALU-S0
Text GLabel 5850 7350 2    50   Output ~ 0
B-CLK
Text GLabel 2850 7300 0    50   Input ~ 0
IR-Q0
Text GLabel 5150 7450 0    50   Input ~ 0
~WB
Text GLabel 5150 7250 0    50   Input ~ 0
~CLK
Text GLabel 7600 1100 2    50   Input ~ 0
LS
Text GLabel 1050 7050 0    50   Input ~ 0
H-Q7
Text GLabel 8700 6200 0    50   Output ~ 0
~PC-LOAD
Text GLabel 8650 5100 0    50   Input ~ 0
IR-Q7
Text GLabel 8650 5000 0    50   Input ~ 0
IR-Q6
Text GLabel 8650 4900 0    50   Input ~ 0
IR-Q5
Text GLabel 5100 1950 0    50   Input ~ 0
CLK
Text GLabel 5100 2350 0    50   Input ~ 0
FZ
Text GLabel 5100 1550 0    50   Input ~ 0
FC
Text GLabel 10200 6300 2    50   Input ~ 0
~WP
Text GLabel 6150 1100 0    50   Output ~ 0
H-CIN
Text GLabel 2050 2200 0    50   Input ~ 0
C0
Text GLabel 2050 2300 0    50   Input ~ 0
C1
Wire Wire Line
	2050 2200 2300 2200
Wire Wire Line
	2050 2300 2300 2300
Wire Wire Line
	2300 1400 1850 1400
Wire Wire Line
	2300 1500 2050 1500
Wire Wire Line
	2300 1600 2050 1600
Text GLabel 2050 1500 0    50   Input ~ 0
H-Q0
Text GLabel 2050 1600 0    50   Input ~ 0
H-Q7
Wire Wire Line
	1250 1400 1250 1150
Wire Wire Line
	1250 1150 2250 1150
Wire Wire Line
	2250 1150 2250 1300
Wire Wire Line
	2250 1300 2300 1300
Text GLabel 1350 950  2    50   Input ~ 0
ALU-COUT
Wire Wire Line
	6850 3650 7850 3650
$Comp
L 74xx:74LS245 U205
U 1 1 606E8E5B
P 9400 1800
F 0 "U205" H 9100 2600 50  0000 C CNN
F 1 "74LS245" H 9100 2500 50  0000 C CNN
F 2 "" H 9400 1800 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS245" H 9400 1800 50  0001 C CNN
	1    9400 1800
	1    0    0    -1  
$EndComp
Text GLabel 5100 6450 0    50   Input ~ 0
FN
Text GLabel 5100 6050 0    50   Input ~ 0
CLK
Text GLabel 5100 5650 0    50   Input ~ 0
FV
Wire Wire Line
	5300 6450 5100 6450
Wire Wire Line
	5300 5650 5100 5650
Wire Wire Line
	5200 6050 5100 6050
$Comp
L power:VCC #PWR0202
U 1 1 608E8CA5
P 9400 1000
F 0 "#PWR0202" H 9400 850 50  0001 C CNN
F 1 "VCC" H 9415 1173 50  0000 C CNN
F 2 "" H 9400 1000 50  0001 C CNN
F 3 "" H 9400 1000 50  0001 C CNN
	1    9400 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 2000 8150 2000
Wire Wire Line
	8900 1900 8050 1900
Wire Wire Line
	8900 1500 8900 1600
Connection ~ 8900 1700
Wire Wire Line
	8900 1700 8900 1800
Connection ~ 8900 1600
Wire Wire Line
	8900 1600 8900 1700
Wire Wire Line
	5150 7250 5200 7250
Text GLabel 2850 7500 0    50   Input ~ 0
LF
Wire Wire Line
	3300 1300 4150 1300
Wire Wire Line
	4150 1300 4150 3450
Wire Wire Line
	3450 4050 3450 6150
Wire Wire Line
	3750 3750 4250 3750
Wire Wire Line
	2050 5550 1950 5550
Connection ~ 1950 5550
Wire Wire Line
	1950 5550 1950 5850
Wire Wire Line
	1350 950  1250 950 
Wire Wire Line
	1250 950  1250 1150
Connection ~ 1250 1150
Wire Wire Line
	4250 4750 4200 4750
Wire Wire Line
	4200 4750 4200 5050
Wire Wire Line
	4200 5050 4750 5050
Connection ~ 4750 5050
Text GLabel 3800 4650 0    50   Input ~ 0
FB
Text GLabel 6850 3000 2    50   Input ~ 0
~RST
Wire Wire Line
	6550 3000 6850 3000
Text GLabel 6850 3850 2    50   Input ~ 0
~RST
Text GLabel 6850 4750 2    50   Input ~ 0
~RST
Text GLabel 6850 5600 2    50   Input ~ 0
~RST
$Comp
L power:VCC #PWR0205
U 1 1 60F67C85
P 8700 2200
F 0 "#PWR0205" H 8700 2050 50  0001 C CNN
F 1 "VCC" H 8700 2350 50  0000 C CNN
F 2 "" H 8700 2200 50  0001 C CNN
F 3 "" H 8700 2200 50  0001 C CNN
	1    8700 2200
	1    0    0    -1  
$EndComp
Text GLabel 8600 2300 0    50   Input ~ 0
~RF
Wire Wire Line
	8900 2300 8600 2300
Wire Wire Line
	8700 2200 8900 2200
Wire Wire Line
	8700 4100 7550 4100
Entry Wire Line
	10050 1300 10150 1200
Entry Wire Line
	10050 1400 10150 1300
Entry Wire Line
	10050 1500 10150 1400
Entry Wire Line
	10050 1600 10150 1500
Entry Wire Line
	10050 1700 10150 1600
Entry Wire Line
	10050 1800 10150 1700
Entry Wire Line
	10050 1900 10150 1800
Entry Wire Line
	10050 2000 10150 1900
Wire Wire Line
	9900 1400 10050 1400
Wire Wire Line
	10050 1500 9900 1500
Wire Wire Line
	9900 1600 10050 1600
Wire Wire Line
	9900 1700 10050 1700
Wire Wire Line
	9900 1800 10050 1800
Wire Wire Line
	9900 1900 10050 1900
Wire Wire Line
	9900 2000 10050 2000
Text Label 9900 1250 0    50   ~ 0
D0
Text Label 9900 1350 0    50   ~ 0
D1
Text Label 9900 1450 0    50   ~ 0
D2
Text Label 9900 1550 0    50   ~ 0
D3
Text Label 9900 1650 0    50   ~ 0
D4
Text Label 9900 1750 0    50   ~ 0
D5
Text Label 9900 1850 0    50   ~ 0
D6
Text Label 9900 1950 0    50   ~ 0
D7
Text Label 4200 3550 3    50   ~ 0
D0
Text Label 4200 3850 3    50   ~ 0
D1
Text Label 4200 4150 3    50   ~ 0
D6
$Comp
L power:VCC #PWR0207
U 1 1 614465B5
P 11800 2450
F 0 "#PWR0207" H 11800 2300 50  0001 C CNN
F 1 "VCC" H 11815 2623 50  0000 C CNN
F 2 "" H 11800 2450 50  0001 C CNN
F 3 "" H 11800 2450 50  0001 C CNN
	1    11800 2450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J201
U 1 1 614765C4
P -1300 2000
F 0 "J201" H -1192 2481 50  0000 C CNN
F 1 "Conn_01x08_Male" H -1192 2390 50  0000 C CNN
F 2 "" H -1300 2000 50  0001 C CNN
F 3 "~" H -1300 2000 50  0001 C CNN
	1    -1300 2000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J202
U 1 1 61477A2C
P -1300 3100
F 0 "J202" H -1192 3581 50  0000 C CNN
F 1 "Conn_01x08_Male" H -1192 3490 50  0000 C CNN
F 2 "" H -1300 3100 50  0001 C CNN
F 3 "~" H -1300 3100 50  0001 C CNN
	1    -1300 3100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J203
U 1 1 614791BB
P -1300 4150
F 0 "J203" H -1192 4631 50  0000 C CNN
F 1 "Conn_01x08_Male" H -1192 4540 50  0000 C CNN
F 2 "" H -1300 4150 50  0001 C CNN
F 3 "~" H -1300 4150 50  0001 C CNN
	1    -1300 4150
	1    0    0    -1  
$EndComp
Text GLabel -900 2400 2    50   Input ~ 0
H-Q7
Wire Wire Line
	-1100 2300 -900 2300
Wire Wire Line
	-1100 2400 -900 2400
Wire Wire Line
	2300 1700 2300 1800
Wire Wire Line
	2300 1900 2300 2000
Wire Wire Line
	2300 1800 2300 1900
Connection ~ 2300 1800
Connection ~ 2300 1900
Wire Wire Line
	2300 1800 2100 1800
Wire Wire Line
	2100 1800 2100 1850
$Comp
L power:GND #PWR0204
U 1 1 6157D15A
P 2100 1850
F 0 "#PWR0204" H 2100 1600 50  0001 C CNN
F 1 "GND" H 2105 1677 50  0000 C CNN
F 2 "" H 2100 1850 50  0001 C CNN
F 3 "" H 2100 1850 50  0001 C CNN
	1    2100 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	-1100 3500 -900 3500
Text GLabel -900 4250 2    50   Input ~ 0
~PC-LOAD
Text GLabel -900 2800 2    50   Input ~ 0
ALU-S0
Wire Wire Line
	-1100 3950 -900 3950
Wire Wire Line
	-1100 4150 -900 4150
NoConn ~ 3300 1400
$Comp
L Device:R_Small_US R201
U 1 1 617363FA
P 8700 1500
F 0 "R201" V 8800 1500 50  0000 C CNN
F 1 "1K" V 8900 1500 50  0000 C CNN
F 2 "" H 8700 1500 50  0001 C CNN
F 3 "~" H 8700 1500 50  0001 C CNN
	1    8700 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	8800 1500 8900 1500
Connection ~ 8900 1500
$Comp
L power:GND #PWR0203
U 1 1 617FD8EF
P 8450 1550
F 0 "#PWR0203" H 8450 1300 50  0001 C CNN
F 1 "GND" H 8455 1377 50  0000 C CNN
F 2 "" H 8450 1550 50  0001 C CNN
F 3 "" H 8450 1550 50  0001 C CNN
	1    8450 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 1500 8450 1500
Wire Wire Line
	8450 1500 8450 1550
Text GLabel -900 4450 2    50   Input ~ 0
CLK
Text GLabel -900 4550 2    50   Input ~ 0
~CLK
$Comp
L power:PWR_FLAG #FLG0201
U 1 1 6191CB46
P 11450 2450
F 0 "#FLG0201" H 11450 2525 50  0001 C CNN
F 1 "PWR_FLAG" H 11450 2623 50  0000 C CNN
F 2 "" H 11450 2450 50  0001 C CNN
F 3 "~" H 11450 2450 50  0001 C CNN
	1    11450 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	11450 2450 11450 2550
Wire Wire Line
	11450 2550 11800 2550
Wire Wire Line
	11800 2550 11800 2450
$Comp
L power:PWR_FLAG #FLG0202
U 1 1 619D38D3
P 11550 3150
F 0 "#FLG0202" H 11550 3225 50  0001 C CNN
F 1 "PWR_FLAG" H 11550 3323 50  0000 C CNN
F 2 "" H 11550 3150 50  0001 C CNN
F 3 "~" H 11550 3150 50  0001 C CNN
	1    11550 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0212
U 1 1 619D3D46
P 11550 3250
F 0 "#PWR0212" H 11550 3000 50  0001 C CNN
F 1 "GND" H 11555 3077 50  0000 C CNN
F 2 "" H 11550 3250 50  0001 C CNN
F 3 "" H 11550 3250 50  0001 C CNN
	1    11550 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	11550 3150 11550 3250
Wire Wire Line
	5350 5400 5350 5200
NoConn ~ 5250 4350
Wire Wire Line
	4250 4350 4250 4450
Wire Wire Line
	4250 4450 3700 4450
Connection ~ 4250 4450
$Comp
L power:VCC #PWR0216
U 1 1 5FF2C5DC
P 3700 4450
F 0 "#PWR0216" H 3700 4300 50  0001 C CNN
F 1 "VCC" H 3715 4623 50  0000 C CNN
F 2 "" H 3700 4450 50  0001 C CNN
F 3 "" H 3700 4450 50  0001 C CNN
	1    3700 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 3450 7950 3450
Wire Wire Line
	9900 1300 10050 1300
Wire Wire Line
	8250 5400 8250 4700
Wire Wire Line
	8250 4700 8700 4700
Wire Wire Line
	8150 5200 8150 4600
Wire Wire Line
	7250 4550 7250 4500
Wire Wire Line
	7250 4500 8700 4500
Wire Wire Line
	7250 4350 7250 4400
Wire Wire Line
	7250 4400 8050 4400
Wire Wire Line
	7850 3650 7850 4300
Wire Wire Line
	7850 4300 8700 4300
Wire Wire Line
	7950 3450 7950 4200
Wire Wire Line
	7950 4200 8700 4200
Wire Wire Line
	7600 1100 7550 1100
Wire Wire Line
	7650 1300 7650 2600
Wire Wire Line
	8900 1400 7950 1400
Wire Wire Line
	7950 1400 7950 3450
Connection ~ 7950 3450
Wire Wire Line
	8050 1900 8050 4400
Connection ~ 8050 4400
Wire Wire Line
	8050 4400 8700 4400
Wire Wire Line
	8150 2000 8150 4600
Connection ~ 8150 4600
Wire Wire Line
	8150 4600 8700 4600
$Comp
L power:GND #PWR0208
U 1 1 604B38B1
P 9400 2600
F 0 "#PWR0208" H 9400 2350 50  0001 C CNN
F 1 "GND" H 9405 2427 50  0000 C CNN
F 2 "" H 9400 2600 50  0001 C CNN
F 3 "" H 9400 2600 50  0001 C CNN
	1    9400 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 4100 7550 2800
Wire Wire Line
	6850 2800 7550 2800
Connection ~ 7650 1300
Wire Wire Line
	3800 4650 4250 4650
Wire Wire Line
	6850 5400 8250 5400
Wire Wire Line
	6850 5200 8150 5200
Wire Wire Line
	6850 4350 7250 4350
NoConn ~ 600  -200
Wire Wire Line
	3500 7300 3550 7300
Wire Wire Line
	2850 7300 2900 7300
Wire Wire Line
	2850 7500 3550 7500
$Comp
L 74xx:74LS151 U216
U 1 1 60952293
P 1800 6750
F 0 "U216" H 1900 6850 50  0000 C CNN
F 1 "74LS151" H 1900 6750 50  0000 C CNN
F 2 "" H 1800 6750 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS151" H 1800 6750 50  0001 C CNN
	1    1800 6750
	1    0    0    -1  
$EndComp
NoConn ~ 2300 6250
Wire Wire Line
	1300 7450 1300 7750
Wire Wire Line
	1300 7750 1800 7750
$Comp
L power:GND #PWR0222
U 1 1 609EA1DB
P 650 7600
F 0 "#PWR0222" H 650 7350 50  0001 C CNN
F 1 "GND" H 655 7427 50  0000 C CNN
F 2 "" H 650 7600 50  0001 C CNN
F 3 "" H 650 7600 50  0001 C CNN
	1    650  7600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 4150 4250 4150
Wire Wire Line
	4100 3850 4250 3850
Wire Wire Line
	4100 3550 4250 3550
Connection ~ 4000 650 
Wire Bus Line
	4000 650  700  650 
Wire Bus Line
	4000 650  10150 650 
Entry Wire Line
	4000 4250 4100 4150
Entry Wire Line
	4000 3950 4100 3850
Entry Wire Line
	4000 3650 4100 3550
Entry Wire Line
	4000 5500 4100 5400
Wire Wire Line
	4100 5400 5350 5400
Text Label 4200 5400 3    50   ~ 0
D7
Wire Wire Line
	650  6150 1300 6150
Wire Wire Line
	650  6150 650  6350
Wire Wire Line
	650  6350 1300 6350
Wire Wire Line
	650  6350 650  6650
Wire Wire Line
	650  6650 1300 6650
Connection ~ 650  6350
Wire Wire Line
	650  6650 650  6850
Wire Wire Line
	650  6850 1300 6850
Connection ~ 650  6650
Wire Wire Line
	650  6850 650  7450
Wire Wire Line
	650  7450 1300 7450
Connection ~ 650  6850
Connection ~ 1300 7450
Wire Wire Line
	650  7450 650  7600
Connection ~ 650  7450
Text GLabel 1050 7150 0    50   Input ~ 0
B-Q7
Text GLabel 1050 7250 0    50   Input ~ 0
ALU-Q7
Wire Wire Line
	800  4450 2050 4450
Wire Wire Line
	1950 5850 2550 5850
Connection ~ 2550 5850
Wire Wire Line
	1300 6550 1100 6550
Wire Wire Line
	1100 6550 1100 6450
Wire Wire Line
	1100 6450 1300 6450
Wire Wire Line
	1300 6250 1200 6250
Wire Wire Line
	1200 6250 1200 6750
Wire Wire Line
	1200 6750 1300 6750
Wire Wire Line
	1050 7050 1300 7050
Wire Wire Line
	1050 7150 1300 7150
Wire Wire Line
	1050 7250 1300 7250
Text GLabel 1050 6450 0    50   Input ~ 0
IR-Q3
Wire Wire Line
	1050 6250 1200 6250
Connection ~ 1200 6250
Wire Wire Line
	1050 6450 1100 6450
Connection ~ 1100 6450
Text GLabel -900 3500 2    50   Input ~ 0
B-Q7
Text GLabel -900 3300 2    50   Input ~ 0
ALU-Q7
Text GLabel -900 3000 2    50   Input ~ 0
ALU-S3
Text GLabel -900 2900 2    50   Input ~ 0
ALU-S1
$Comp
L power:GND #PWR0209
U 1 1 5FE82661
P 2150 3050
F 0 "#PWR0209" H 2150 2800 50  0001 C CNN
F 1 "GND" H 2155 2877 50  0000 C CNN
F 2 "" H 2150 3050 50  0001 C CNN
F 3 "" H 2150 3050 50  0001 C CNN
	1    2150 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 3050 2800 3050
Connection ~ 2150 3050
Wire Wire Line
	2550 3400 2550 3450
$Comp
L power:VCC #PWR0220
U 1 1 60F9A40B
P 1800 5800
F 0 "#PWR0220" H 1800 5650 50  0001 C CNN
F 1 "VCC" H 1815 5973 50  0000 C CNN
F 2 "" H 1800 5800 50  0001 C CNN
F 3 "" H 1800 5800 50  0001 C CNN
	1    1800 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 5800 1800 5850
Wire Wire Line
	2300 6150 3450 6150
NoConn ~ 9700 4100
Wire Wire Line
	9700 4000 9800 4000
Wire Wire Line
	9800 4000 9800 6100
Wire Wire Line
	9800 6100 9400 6100
Wire Wire Line
	9400 6300 9500 6300
Wire Wire Line
	8700 6200 8800 6200
$Comp
L 74xx:74LS02 U202
U 1 1 60A02AB3
P 6600 1100
F 0 "U202" H 6600 1425 50  0000 C CNN
F 1 "74LS02" H 6600 1334 50  0000 C CNN
F 2 "" H 6600 1100 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74ls02" H 6600 1100 50  0001 C CNN
	1    6600 1100
	-1   0    0    1   
$EndComp
Wire Wire Line
	6900 1200 6950 1200
Wire Wire Line
	6300 1100 6250 1100
Wire Wire Line
	6900 1000 7600 1000
Text GLabel 7600 1000 2    50   Input ~ 0
LC
Wire Wire Line
	8600 5750 8400 5750
Wire Wire Line
	8600 5300 8600 5750
Wire Wire Line
	8600 5300 8700 5300
Text GLabel 7700 5750 0    50   Input ~ 0
JE
Wire Wire Line
	7700 5750 7800 5750
Wire Wire Line
	3150 3750 3050 3750
Wire Wire Line
	2550 5900 2550 5850
Text GLabel -900 2300 2    50   Input ~ 0
H-Q0
Wire Wire Line
	-1100 1700 -900 1700
Wire Wire Line
	-1100 1800 -900 1800
Wire Wire Line
	-1100 1900 -900 1900
Wire Wire Line
	-1100 2000 -900 2000
Wire Wire Line
	-1100 2200 -900 2200
NoConn ~ -1100 2100
Wire Wire Line
	-1100 2800 -900 2800
Wire Wire Line
	-1100 2900 -900 2900
Wire Wire Line
	-1100 3000 -900 3000
Wire Wire Line
	-1100 3100 -900 3100
Wire Wire Line
	-1100 3200 -900 3200
Wire Wire Line
	-1100 3300 -900 3300
Wire Wire Line
	-1100 3400 -900 3400
NoConn ~ -1100 4050
Wire Wire Line
	-1100 4550 -900 4550
Wire Wire Line
	-1100 4450 -900 4450
Wire Wire Line
	-1100 4350 -900 4350
Wire Wire Line
	-1100 4250 -900 4250
Wire Wire Line
	-1100 3850 -900 3850
Text GLabel 1050 6250 0    50   Input ~ 0
IR-Q1
Wire Wire Line
	10100 6300 10200 6300
Wire Wire Line
	7650 4000 8700 4000
Wire Wire Line
	6850 2600 7650 2600
Connection ~ 7650 2600
Wire Wire Line
	7650 2600 7650 4000
Wire Wire Line
	7550 1300 7650 1300
Wire Wire Line
	7650 1300 8900 1300
Wire Wire Line
	5750 850  6250 850 
Wire Wire Line
	6250 850  6250 1100
Connection ~ 6250 1100
Wire Wire Line
	6250 1100 6150 1100
Text GLabel 5050 850  0    50   Output ~ 0
ALU-CIN
Wire Wire Line
	5050 850  5150 850 
$Comp
L 74xx:74LS08 U214
U 1 1 61EFB129
P 13250 4800
F 0 "U214" H 13150 6000 50  0000 C CNN
F 1 "74LS08" H 13250 5034 50  0000 C CNN
F 2 "" H 13250 4800 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS08" H 13250 4800 50  0001 C CNN
	1    13250 4800
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS04 U215
U 6 1 61EFD362
P 12450 5200
F 0 "U215" H 12400 4250 50  0000 C CNN
F 1 "74LS04" H 12450 5400 50  0000 C CNN
F 2 "" H 12450 5200 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS04" H 12450 5200 50  0001 C CNN
	6    12450 5200
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS02 U213
U 1 1 61EFE20B
P 15300 4750
F 0 "U213" H 15300 3400 50  0000 C CNN
F 1 "74LS02" H 15300 4984 50  0000 C CNN
F 2 "" H 15300 4750 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74ls02" H 15300 4750 50  0001 C CNN
	1    15300 4750
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS02 U202
U 2 1 61F00AC2
P 16050 4850
F 0 "U202" H 16050 3600 50  0000 C CNN
F 1 "74LS02" H 16050 5084 50  0000 C CNN
F 2 "" H 16050 4850 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74ls02" H 16050 4850 50  0001 C CNN
	2    16050 4850
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS32 U212
U 1 1 61F04EEF
P 12450 4700
F 0 "U212" H 12550 5800 50  0000 C CNN
F 1 "74LS32" H 12450 4934 50  0000 C CNN
F 2 "" H 12450 4700 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS32" H 12450 4700 50  0001 C CNN
	1    12450 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	12750 5200 12850 5200
Wire Wire Line
	12850 5200 12850 4900
Wire Wire Line
	12850 4900 12950 4900
Wire Wire Line
	12750 4700 12950 4700
Wire Wire Line
	13550 4800 13600 4800
Wire Wire Line
	15600 4750 15750 4750
Wire Wire Line
	15750 4950 15600 4950
Wire Wire Line
	16350 4850 16400 4850
Text GLabel 14900 5050 0    50   Input ~ 0
clear
Text GLabel 14950 4850 0    50   Input ~ 0
set
Text GLabel 14950 4650 0    50   Input ~ 0
flag-in
Text GLabel 16400 4850 2    50   Output ~ 0
flag-out
Text GLabel 12100 5200 0    50   Input ~ 0
clear
Text GLabel 12100 4800 0    50   Input ~ 0
set
Text GLabel 12100 4600 0    50   Input ~ 0
flag-in
Text GLabel 13600 4800 2    50   Output ~ 0
flag-out
Wire Wire Line
	15600 4950 15600 5050
Wire Wire Line
	15600 5050 14900 5050
Wire Wire Line
	14950 4850 15000 4850
Wire Wire Line
	14950 4650 15000 4650
Wire Wire Line
	12100 4600 12150 4600
Wire Wire Line
	12100 4800 12150 4800
Wire Wire Line
	12100 5200 12150 5200
Text Notes 12000 5650 0    129  ~ 0
Carry Flag Output
Text Notes 15000 5650 0    129  ~ 0
Simplified
Text Label 1200 650  2    50   ~ 0
D[0..7]
NoConn ~ -900 2000
NoConn ~ -900 1900
NoConn ~ -900 1800
NoConn ~ -900 1700
NoConn ~ -900 3850
NoConn ~ -900 3950
NoConn ~ -900 4150
NoConn ~ -900 4350
NoConn ~ -900 3400
NoConn ~ -900 2200
NoConn ~ -900 3100
NoConn ~ -900 3200
Wire Bus Line
	4000 650  4000 5550
Wire Bus Line
	700  650  700  4450
Wire Bus Line
	10150 650  10150 2050
Text Notes 550  6000 0    50   ~ 0
IR-Q1 and IR-Q3 connect to\nthe ALU function selects and\nare used here to to indicate\naddition or subtraction
$EndSCHEMATC

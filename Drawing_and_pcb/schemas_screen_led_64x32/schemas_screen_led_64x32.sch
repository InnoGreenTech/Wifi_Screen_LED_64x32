EESchema Schematic File Version 4
LIBS:schemas_screen_led_64x32-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L wemos_mini:WeMos_mini U1
U 1 1 5E4EF739
P 8900 4350
F 0 "U1" H 8900 5093 60  0000 C CNN
F 1 "WeMos_mini" H 8900 4987 60  0000 C CNN
F 2 "D1_mini:D1_mini_board" H 9450 3650 60  0001 C CNN
F 3 "http://www.wemos.cc/Products/d1_mini.html" H 8900 4881 60  0000 C CNN
	1    8900 4350
	1    0    0    -1  
$EndComp
$Comp
L arduino:Arduino_Nano_Socket XA1
U 1 1 5E4EF7DA
P 5300 4800
F 0 "XA1" H 5300 6037 60  0000 C CNN
F 1 "Arduino_Nano_Socket" H 5300 5931 60  0000 C CNN
F 2 "Arduino:Arduino_Nano_Socket" H 7100 8550 60  0001 C CNN
F 3 "" H 7100 8550 60  0001 C CNN
	1    5300 4800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x16_Male J1
U 1 1 5E5037BA
P 2400 2800
F 0 "J1" H 2506 3678 50  0000 C CNN
F 1 "Conn_01x16_Male" H 2506 3587 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x08_P2.54mm_Vertical" H 2400 2800 50  0001 C CNN
F 3 "~" H 2400 2800 50  0001 C CNN
	1    2400 2800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 5E50D873
P 5850 2450
F 0 "J2" H 5930 2442 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 5930 2351 50  0000 L CNN
F 2 "TerminalBlock_4Ucon:TerminalBlock_4Ucon_1x02_P3.50mm_Horizontal" H 5850 2450 50  0001 C CNN
F 3 "~" H 5850 2450 50  0001 C CNN
	1    5850 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5E569377
P 3250 5300
F 0 "#PWR0101" H 3250 5050 50  0001 C CNN
F 1 "GND" H 3255 5127 50  0000 C CNN
F 2 "" H 3250 5300 50  0001 C CNN
F 3 "" H 3250 5300 50  0001 C CNN
	1    3250 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5E5693A1
P 7700 4100
F 0 "#PWR0102" H 7700 3850 50  0001 C CNN
F 1 "GND" H 7705 3927 50  0000 C CNN
F 2 "" H 7700 4100 50  0001 C CNN
F 3 "" H 7700 4100 50  0001 C CNN
	1    7700 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:Fuse F1
U 1 1 5E5693D9
P 5300 2450
F 0 "F1" H 5360 2496 50  0000 L CNN
F 1 "Fuse" H 5360 2405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0614_L14.3mm_D5.7mm_P15.24mm_Horizontal" V 5230 2450 50  0001 C CNN
F 3 "~" H 5300 2450 50  0001 C CNN
	1    5300 2450
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5E569661
P 5350 2550
F 0 "#PWR0103" H 5350 2300 50  0001 C CNN
F 1 "GND" H 5355 2377 50  0000 C CNN
F 2 "" H 5350 2550 50  0001 C CNN
F 3 "" H 5350 2550 50  0001 C CNN
	1    5350 2550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 5E569694
P 4950 2450
F 0 "#PWR0104" H 4950 2300 50  0001 C CNN
F 1 "+5V" H 4965 2623 50  0000 C CNN
F 2 "" H 4950 2450 50  0001 C CNN
F 3 "" H 4950 2450 50  0001 C CNN
	1    4950 2450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0105
U 1 1 5E5696C7
P 7550 4000
F 0 "#PWR0105" H 7550 3850 50  0001 C CNN
F 1 "+5V" H 7565 4173 50  0000 C CNN
F 2 "" H 7550 4000 50  0001 C CNN
F 3 "" H 7550 4000 50  0001 C CNN
	1    7550 4000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 5E5696F3
P 3700 5700
F 0 "#PWR0106" H 3700 5550 50  0001 C CNN
F 1 "+5V" H 3715 5873 50  0000 C CNN
F 2 "" H 3700 5700 50  0001 C CNN
F 3 "" H 3700 5700 50  0001 C CNN
	1    3700 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 2450 5450 2450
Wire Wire Line
	5150 2450 4950 2450
Wire Wire Line
	8400 4100 7700 4100
Wire Wire Line
	8400 4000 7550 4000
Wire Wire Line
	4100 5300 4000 5300
Connection ~ 4000 5300
Wire Wire Line
	4000 5300 3250 5300
Wire Wire Line
	4000 5600 3900 5600
Wire Wire Line
	3900 5600 3900 5700
Wire Wire Line
	3900 5700 3700 5700
Wire Wire Line
	5650 2550 5350 2550
$Comp
L power:GND #PWR0107
U 1 1 5E56A75F
P 3600 3600
F 0 "#PWR0107" H 3600 3350 50  0001 C CNN
F 1 "GND" H 3605 3427 50  0000 C CNN
F 2 "" H 3600 3600 50  0001 C CNN
F 3 "" H 3600 3600 50  0001 C CNN
	1    3600 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 5300 4000 5400
Text GLabel 2800 2100 2    50   Input ~ 0
R1
Text GLabel 3050 2200 2    50   Input ~ 0
G1
Text GLabel 2800 2300 2    50   Input ~ 0
B1
Text GLabel 2800 2500 2    50   Input ~ 0
R2
Text GLabel 3050 2600 2    50   Input ~ 0
G2
Text GLabel 2800 2700 2    50   Input ~ 0
B2
Text GLabel 2800 2900 2    50   Input ~ 0
A
Text GLabel 3050 3000 2    50   Input ~ 0
B
Text GLabel 2800 3100 2    50   Input ~ 0
C
Text GLabel 3050 3200 2    50   Input ~ 0
D
Text GLabel 2800 3300 2    50   Input ~ 0
CLK
Text GLabel 2800 3500 2    50   Input ~ 0
OE
Text GLabel 3050 3400 2    50   Input ~ 0
LAT
Wire Wire Line
	2800 2100 2600 2100
Wire Wire Line
	3050 2200 2600 2200
Wire Wire Line
	2800 2300 2600 2300
Wire Wire Line
	2800 2500 2600 2500
Wire Wire Line
	3050 2600 2600 2600
Wire Wire Line
	2800 2700 2600 2700
Wire Wire Line
	2800 2900 2600 2900
Wire Wire Line
	3050 3000 2600 3000
Wire Wire Line
	2800 3100 2600 3100
Wire Wire Line
	3050 3200 2600 3200
Wire Wire Line
	2800 3300 2600 3300
Wire Wire Line
	3050 3400 2750 3400
Wire Wire Line
	2800 3500 2750 3500
Wire Wire Line
	2600 3600 3600 3600
Wire Wire Line
	2600 2400 3600 2400
Wire Wire Line
	3600 2400 3600 2800
Connection ~ 3600 3600
Wire Wire Line
	2600 2800 3600 2800
Connection ~ 3600 2800
Wire Wire Line
	3600 2800 3600 3600
Text GLabel 9600 4400 2    50   Input ~ 0
R1
Text GLabel 8100 4200 0    50   Input ~ 0
G1
Text GLabel 8300 4300 0    50   Input ~ 0
B1
Text GLabel 9800 4100 2    50   Input ~ 0
R2
Text GLabel 9600 4200 2    50   Input ~ 0
G2
Text GLabel 9800 4300 2    50   Input ~ 0
B2
Text GLabel 3700 4900 0    50   Input ~ 0
A
Text GLabel 3500 4800 0    50   Input ~ 0
B
Text GLabel 3700 4700 0    50   Input ~ 0
C
Text GLabel 3500 4600 0    50   Input ~ 0
D
Text GLabel 9800 4500 2    50   Input ~ 0
CLK
Text GLabel 7000 4700 2    50   Input ~ 0
LAT
Wire Wire Line
	4000 4600 3500 4600
Wire Wire Line
	4000 4700 3700 4700
Wire Wire Line
	4000 4800 3500 4800
Wire Wire Line
	4000 4900 3700 4900
Wire Wire Line
	8400 4500 7000 4500
Wire Wire Line
	7000 4700 7000 4500
Connection ~ 7000 4500
Wire Wire Line
	7000 4500 6600 4500
Wire Wire Line
	2750 3400 2750 3500
Connection ~ 2750 3400
Wire Wire Line
	2750 3400 2600 3400
Connection ~ 2750 3500
Wire Wire Line
	2750 3500 2600 3500
Wire Wire Line
	8400 4200 8100 4200
Wire Wire Line
	8400 4300 8300 4300
Wire Wire Line
	9400 4100 9800 4100
Wire Wire Line
	9400 4200 9600 4200
Wire Wire Line
	9400 4300 9800 4300
Wire Wire Line
	9400 4400 9600 4400
Wire Wire Line
	9800 4500 9400 4500
$EndSCHEMATC

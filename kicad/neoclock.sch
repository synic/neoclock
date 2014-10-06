EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:synic
LIBS:Tag-Connect
LIBS:neoclock-cache
EELAYER 24 0
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
L BATTERY BT1
U 1 1 54207155
P 1650 4800
F 0 "BT1" H 1650 5000 50  0000 C CNN
F 1 "3v" H 1650 4610 50  0000 C CNN
F 2 "synicpretty:BK-755_12mm_coincell" H 1650 4800 60  0001 C CNN
F 3 "" H 1650 4800 60  0000 C CNN
	1    1650 4800
	-1   0    0    1   
$EndComp
$Comp
L C C6
U 1 1 542083CF
P 1300 2300
F 0 "C6" H 1300 2400 40  0000 L CNN
F 1 "10nF" H 1306 2215 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 1338 2150 30  0001 C CNN
F 3 "" H 1300 2300 60  0000 C CNN
	1    1300 2300
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 54208406
P 1100 2300
F 0 "C2" H 1100 2400 40  0000 L CNN
F 1 "1uF" H 1106 2215 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 1138 2150 30  0001 C CNN
F 3 "" H 1100 2300 60  0000 C CNN
	1    1100 2300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 54208488
P 750 2500
F 0 "#PWR01" H 750 2500 30  0001 C CNN
F 1 "GND" H 750 2430 30  0001 C CNN
F 2 "" H 750 2500 60  0000 C CNN
F 3 "" H 750 2500 60  0000 C CNN
	1    750  2500
	0    1    1    0   
$EndComp
$Comp
L C C8
U 1 1 542087D7
P 1700 1450
F 0 "C8" H 1700 1550 40  0000 L CNN
F 1 "100nF" H 1706 1365 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 1738 1300 30  0001 C CNN
F 3 "" H 1700 1450 60  0000 C CNN
	1    1700 1450
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 5420885C
P 1500 1450
F 0 "C7" H 1500 1550 40  0000 L CNN
F 1 "100nF" H 1506 1365 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 1538 1300 30  0001 C CNN
F 3 "" H 1500 1450 60  0000 C CNN
	1    1500 1450
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 5420887A
P 1300 1450
F 0 "C5" H 1300 1550 40  0000 L CNN
F 1 "100nF" H 1306 1365 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 1338 1300 30  0001 C CNN
F 3 "" H 1300 1450 60  0000 C CNN
	1    1300 1450
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 54208897
P 1100 1450
F 0 "C1" H 1100 1550 40  0000 L CNN
F 1 "4.7uF" H 1106 1365 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 1138 1300 30  0001 C CNN
F 3 "" H 1100 1450 60  0000 C CNN
	1    1100 1450
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR02
U 1 1 54208993
P 700 1700
F 0 "#PWR02" H 700 1800 30  0001 C CNN
F 1 "VDD" H 700 1810 30  0000 C CNN
F 2 "" H 700 1700 60  0000 C CNN
F 3 "" H 700 1700 60  0000 C CNN
	1    700  1700
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR03
U 1 1 54208ACA
P 1100 1750
F 0 "#PWR03" H 1100 1750 30  0001 C CNN
F 1 "GND" H 1100 1680 30  0001 C CNN
F 2 "" H 1100 1750 60  0000 C CNN
F 3 "" H 1100 1750 60  0000 C CNN
	1    1100 1750
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 54208F05
P 1600 2650
F 0 "R1" V 1680 2650 40  0000 C CNN
F 1 "10k" V 1607 2651 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 1530 2650 30  0001 C CNN
F 3 "" H 1600 2650 30  0000 C CNN
	1    1600 2650
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 54208F51
P 1600 2750
F 0 "R2" V 1680 2750 40  0000 C CNN
F 1 "10k" V 1607 2751 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 1530 2750 30  0001 C CNN
F 3 "" H 1600 2750 30  0000 C CNN
	1    1600 2750
	0    1    1    0   
$EndComp
$Comp
L CRYSTAL X1
U 1 1 5420907D
P 1700 3300
F 0 "X1" H 1700 3450 60  0000 C CNN
F 1 "32.768KHz" H 1700 3150 60  0000 C CNN
F 2 "synic:2_SMD_CRYSTAL_3.2x1.5" H 1700 3300 60  0001 C CNN
F 3 "" H 1700 3300 60  0000 C CNN
	1    1700 3300
	0    1    1    0   
$EndComp
$Comp
L GND #PWR04
U 1 1 5420967D
P 1200 4800
F 0 "#PWR04" H 1200 4800 30  0001 C CNN
F 1 "GND" H 1200 4730 30  0001 C CNN
F 2 "" H 1200 4800 60  0000 C CNN
F 3 "" H 1200 4800 60  0000 C CNN
	1    1200 4800
	0    1    1    0   
$EndComp
$Comp
L TC2030-CTX P1
U 1 1 54209975
P 3100 5050
F 0 "P1" H 3050 4850 40  0000 L CNN
F 1 "TC2030-CTX" H 3100 5250 40  0000 C CNN
F 2 "Tag-Connect:TC2030_SMALL" H 3100 5050 60  0001 C CNN
F 3 "" H 3100 5050 60  0000 C CNN
	1    3100 5050
	1    0    0    -1  
$EndComp
NoConn ~ 3550 5150
Text GLabel 1950 2900 0    60   Input ~ 0
NRST
Text GLabel 2500 5050 0    60   Output ~ 0
NRST
Text GLabel 4300 2350 2    60   Input ~ 0
SWDIO
Text GLabel 4300 2450 2    60   Input ~ 0
SWCLK
Text GLabel 3650 4950 2    60   Output ~ 0
SWDIO
Text GLabel 3650 5050 2    60   Output ~ 0
SWCLK
$Comp
L GND #PWR05
U 1 1 5420A383
P 2600 5150
F 0 "#PWR05" H 2600 5150 30  0001 C CNN
F 1 "GND" H 2600 5080 30  0001 C CNN
F 2 "" H 2600 5150 60  0000 C CNN
F 3 "" H 2600 5150 60  0000 C CNN
	1    2600 5150
	0    1    1    0   
$EndComp
$Comp
L VDD #PWR06
U 1 1 5420A409
P 2600 4950
F 0 "#PWR06" H 2600 5050 30  0001 C CNN
F 1 "VDD" H 2600 5060 30  0000 C CNN
F 2 "" H 2600 4950 60  0000 C CNN
F 3 "" H 2600 4950 60  0000 C CNN
	1    2600 4950
	0    -1   -1   0   
$EndComp
$Comp
L CONN_3 K1
U 1 1 5420A63C
P 6950 1950
F 0 "K1" V 6900 1950 50  0000 C CNN
F 1 "NEO" V 7000 1950 40  0000 C CNN
F 2 "synic:jst-3-pth-ra" H 6950 1950 60  0001 C CNN
F 3 "" H 6950 1950 60  0000 C CNN
	1    6950 1950
	1    0    0    -1  
$EndComp
$Comp
L BARREL_JACK CON1
U 1 1 5420A944
P 1150 7200
F 0 "CON1" H 1150 7450 60  0000 C CNN
F 1 "1.2mm 5v" H 1150 7000 60  0000 C CNN
F 2 "synicpretty:BARREL_JACK_SMD" H 1150 7200 60  0001 C CNN
F 3 "" H 1150 7200 60  0000 C CNN
	1    1150 7200
	1    0    0    -1  
$EndComp
$Comp
L CP1 C10
U 1 1 5420A98D
P 2700 7300
F 0 "C10" H 2750 7400 50  0000 L CNN
F 1 "10uF" H 2750 7200 50  0000 L CNN
F 2 "Capacitors_SMD:c_elec_4x4.5" H 2700 7300 60  0001 C CNN
F 3 "" H 2700 7300 60  0000 C CNN
	1    2700 7300
	1    0    0    -1  
$EndComp
$Comp
L CP1 C9
U 1 1 5420AA5E
P 2650 6500
F 0 "C9" H 2700 6600 50  0000 L CNN
F 1 "100uF" H 2700 6400 50  0000 L CNN
F 2 "Capacitors_SMD:c_elec_5x5.3" H 2650 6500 60  0001 C CNN
F 3 "" H 2650 6500 60  0000 C CNN
	1    2650 6500
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR07
U 1 1 5420B298
P 5100 7100
F 0 "#PWR07" H 5100 7200 30  0001 C CNN
F 1 "VDD" H 5100 7210 30  0000 C CNN
F 2 "" H 5100 7100 60  0000 C CNN
F 3 "" H 5100 7100 60  0000 C CNN
	1    5100 7100
	0    1    1    0   
$EndComp
$Comp
L GND #PWR08
U 1 1 5420B326
P 5150 7500
F 0 "#PWR08" H 5150 7500 30  0001 C CNN
F 1 "GND" H 5150 7430 30  0001 C CNN
F 2 "" H 5150 7500 60  0000 C CNN
F 3 "" H 5150 7500 60  0000 C CNN
	1    5150 7500
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR09
U 1 1 5420B529
P 2650 6850
F 0 "#PWR09" H 2650 6850 30  0001 C CNN
F 1 "GND" H 2650 6780 30  0001 C CNN
F 2 "" H 2650 6850 60  0000 C CNN
F 3 "" H 2650 6850 60  0000 C CNN
	1    2650 6850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 5420B549
P 6600 1950
F 0 "#PWR010" H 6600 1950 30  0001 C CNN
F 1 "GND" H 6600 1880 30  0001 C CNN
F 2 "" H 6600 1950 60  0000 C CNN
F 3 "" H 6600 1950 60  0000 C CNN
	1    6600 1950
	0    1    1    0   
$EndComp
Wire Wire Line
	1950 2400 1700 2400
Wire Wire Line
	1700 2400 1700 2100
Wire Wire Line
	1700 2100 800  2100
Connection ~ 1300 2100
Connection ~ 1100 2100
Wire Wire Line
	750  2500 1950 2500
Wire Wire Line
	1100 2500 1300 2500
Connection ~ 1300 2500
Connection ~ 1100 2500
Connection ~ 1700 1250
Connection ~ 1500 1250
Wire Wire Line
	800  2100 800  1250
Connection ~ 1100 1250
Wire Wire Line
	800  1700 700  1700
Connection ~ 800  1700
Wire Wire Line
	1950 1650 1950 1850
Connection ~ 1950 1750
Wire Wire Line
	1100 1650 1950 1650
Connection ~ 1950 1650
Connection ~ 1700 1650
Connection ~ 1500 1650
Wire Wire Line
	1100 1650 1100 1750
Connection ~ 1300 1250
Connection ~ 1300 1650
Connection ~ 1100 1650
Connection ~ 1350 2650
Wire Wire Line
	1850 2650 1950 2650
Wire Wire Line
	1850 2750 1950 2750
Wire Wire Line
	1950 3000 1950 3100
Wire Wire Line
	1950 3600 1950 3500
Wire Wire Line
	1950 4450 1950 4800
Wire Wire Line
	1950 2750 1950 2900
Wire Wire Line
	2650 5050 2500 5050
Wire Wire Line
	4300 2350 4150 2350
Wire Wire Line
	4300 2450 4150 2450
Wire Wire Line
	3550 4950 3650 4950
Wire Wire Line
	3650 5050 3550 5050
Wire Wire Line
	2650 5150 2600 5150
Wire Wire Line
	2600 4950 2650 4950
Wire Wire Line
	2100 7100 3650 7100
Connection ~ 2700 7100
Wire Wire Line
	2350 6300 2350 7100
Wire Wire Line
	1450 7500 5150 7500
Wire Wire Line
	4050 7500 4050 7400
Connection ~ 2700 7500
Connection ~ 4050 7500
Connection ~ 4650 7100
Connection ~ 4650 7500
Wire Wire Line
	5500 1850 6600 1850
Wire Wire Line
	2650 6700 2650 6850
Wire Wire Line
	2350 6300 3200 6300
Connection ~ 2350 6850
Connection ~ 2650 6300
Text GLabel 3200 6300 2    60   Output ~ 0
VCC5V
Text GLabel 6100 2200 3    60   Input ~ 0
VCC5V
Wire Wire Line
	4150 1050 4900 1050
$Comp
L VDD #PWR011
U 1 1 5420CFFF
P 5200 1050
F 0 "#PWR011" H 5200 1150 30  0001 C CNN
F 1 "VDD" H 5200 1160 30  0000 C CNN
F 2 "" H 5200 1050 60  0000 C CNN
F 3 "" H 5200 1050 60  0000 C CNN
	1    5200 1050
	0    1    1    0   
$EndComp
Wire Wire Line
	5100 1050 5200 1050
$Comp
L GND #PWR012
U 1 1 5420D0BD
P 4150 900
F 0 "#PWR012" H 4150 900 30  0001 C CNN
F 1 "GND" H 4150 830 30  0001 C CNN
F 2 "" H 4150 900 60  0000 C CNN
F 3 "" H 4150 900 60  0000 C CNN
	1    4150 900 
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 5420D0CA
P 4500 900
F 0 "R3" V 4580 900 40  0000 C CNN
F 1 "10k" V 4507 901 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 4430 900 30  0001 C CNN
F 3 "" H 4500 900 30  0000 C CNN
	1    4500 900 
	0    1    1    0   
$EndComp
Wire Wire Line
	4750 1050 4750 900 
Wire Wire Line
	4250 900  4150 900 
$Comp
L CONN_2 P2
U 1 1 5420D3A0
P 5000 700
F 0 "P2" V 4950 700 40  0000 C CNN
F 1 "PHOTOR" V 5050 700 40  0000 C CNN
F 2 "synic:jst-2-pth-ra" H 5000 700 60  0001 C CNN
F 3 "" H 5000 700 60  0000 C CNN
	1    5000 700 
	0    -1   -1   0   
$EndComp
Connection ~ 4750 1050
$Comp
L SW_PUSH SW1
U 1 1 5420D6C8
P 5650 750
F 0 "SW1" H 5800 860 50  0000 C CNN
F 1 "HOUR" H 5650 670 50  0000 C CNN
F 2 "synic:KMR2_MICROMINIATURE_BUTTON" H 5650 750 60  0001 C CNN
F 3 "" H 5650 750 60  0000 C CNN
	1    5650 750 
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 5420D7C1
P 5650 1250
F 0 "SW2" H 5800 1360 50  0000 C CNN
F 1 "MINUTE" H 5650 1170 50  0000 C CNN
F 2 "synic:KMR2_MICROMINIATURE_BUTTON" H 5650 1250 60  0001 C CNN
F 3 "" H 5650 1250 60  0000 C CNN
	1    5650 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 1150 4150 1150
Wire Wire Line
	5350 750  5350 1150
Wire Wire Line
	4150 1250 5350 1250
$Comp
L GND #PWR013
U 1 1 5420D9A5
P 6450 1250
F 0 "#PWR013" H 6450 1250 30  0001 C CNN
F 1 "GND" H 6450 1180 30  0001 C CNN
F 2 "" H 6450 1250 60  0000 C CNN
F 3 "" H 6450 1250 60  0000 C CNN
	1    6450 1250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5950 1250 6450 1250
NoConn ~ 4150 1350
NoConn ~ 4150 1450
NoConn ~ 4150 1550
NoConn ~ 4150 1650
NoConn ~ 4150 1750
NoConn ~ 4150 1850
NoConn ~ 4150 1950
NoConn ~ 4150 2150
NoConn ~ 4150 2250
NoConn ~ 4150 2550
NoConn ~ 4150 2950
NoConn ~ 4150 3050
NoConn ~ 4150 3150
NoConn ~ 4150 3250
NoConn ~ 4150 3350
NoConn ~ 4150 3450
NoConn ~ 4150 3550
NoConn ~ 4150 3650
NoConn ~ 4150 3750
NoConn ~ 4150 3850
NoConn ~ 4150 3950
NoConn ~ 4150 4050
NoConn ~ 4150 4150
NoConn ~ 4150 4250
NoConn ~ 4150 4450
Wire Wire Line
	1950 1250 1950 1050
Connection ~ 1950 1150
Wire Wire Line
	800  1250 1950 1250
Wire Wire Line
	4450 7100 5100 7100
Connection ~ 1950 1250
$Comp
L stm32f303x U1
U 1 1 5420ED70
P 3050 2850
F 0 "U1" H 3050 4800 60  0000 C CNN
F 1 "stm32f303x" H 3050 1450 60  0000 C CNN
F 2 "lqfp48:LQFP48" H 3050 2850 60  0001 C CNN
F 3 "" H 3050 2850 60  0000 C CNN
	1    3050 2850
	1    0    0    -1  
$EndComp
NoConn ~ 1950 3850
NoConn ~ 1950 4250
Wire Wire Line
	1700 3000 1950 3000
Wire Wire Line
	1950 3600 1700 3600
Wire Wire Line
	1200 4800 1350 4800
$Comp
L TLV702xx U2
U 1 1 54231228
P 4050 7150
F 0 "U2" H 4200 6954 60  0000 C CNN
F 1 "TLV702xx" H 4050 7350 60  0000 C CNN
F 2 "SMD_Packages:SOT-23-5" H 4050 7150 60  0001 C CNN
F 3 "" H 4050 7150 60  0000 C CNN
	1    4050 7150
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 54231407
P 3300 7200
F 0 "R4" V 3380 7200 40  0000 C CNN
F 1 "10k" V 3307 7201 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 3230 7200 30  0001 C CNN
F 3 "" H 3300 7200 30  0000 C CNN
	1    3300 7200
	0    1    1    0   
$EndComp
Wire Wire Line
	3550 7200 3650 7200
Wire Wire Line
	3050 7200 3050 7100
Connection ~ 3050 7100
$Comp
L FUSE F1
U 1 1 542316DE
P 1850 7100
F 0 "F1" H 1950 7150 40  0000 C CNN
F 1 "FUSE" H 1750 7050 40  0000 C CNN
F 2 "synic:1206_polyfuse" H 1850 7100 60  0001 C CNN
F 3 "" H 1850 7100 60  0000 C CNN
	1    1850 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 7200 1450 7500
Connection ~ 1450 7300
Wire Wire Line
	1450 7100 1600 7100
Connection ~ 2350 7100
Connection ~ 5350 1000
$Comp
L C C3
U 1 1 542323A3
P 4650 7300
F 0 "C3" H 4650 7400 40  0000 L CNN
F 1 "1uF" H 4656 7215 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4688 7150 30  0001 C CNN
F 3 "" H 4650 7300 60  0000 C CNN
	1    4650 7300
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG014
U 1 1 54232740
P 1100 1700
F 0 "#FLG014" H 1100 1795 30  0001 C CNN
F 1 "PWR_FLAG" H 1100 1880 30  0000 C CNN
F 2 "" H 1100 1700 60  0000 C CNN
F 3 "" H 1100 1700 60  0000 C CNN
	1    1100 1700
	0    -1   -1   0   
$EndComp
Connection ~ 1100 1700
Wire Wire Line
	1350 2650 1350 2750
Wire Wire Line
	1350 2750 1200 2750
$Comp
L R R5
U 1 1 543168EB
P 5150 2750
F 0 "R5" V 5230 2750 40  0000 C CNN
F 1 "330" V 5157 2751 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 5080 2750 30  0001 C CNN
F 3 "" H 5150 2750 30  0000 C CNN
	1    5150 2750
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 54316977
P 5150 2850
F 0 "R6" V 5230 2850 40  0000 C CNN
F 1 "330" V 5157 2851 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 5080 2850 30  0001 C CNN
F 3 "" H 5150 2850 30  0000 C CNN
	1    5150 2850
	0    1    1    0   
$EndComp
$Comp
L LED D1
U 1 1 54316A27
P 4550 2750
F 0 "D1" H 4550 2850 50  0000 C CNN
F 1 "RED" H 4550 2650 50  0000 C CNN
F 2 "LEDs:LED-0805" H 4550 2750 60  0001 C CNN
F 3 "" H 4550 2750 60  0000 C CNN
	1    4550 2750
	1    0    0    -1  
$EndComp
$Comp
L LED D2
U 1 1 54316A80
P 4550 2850
F 0 "D2" H 4550 2950 50  0000 C CNN
F 1 "GREEN" H 4550 2750 50  0000 C CNN
F 2 "LEDs:LED-0805" H 4550 2850 60  0001 C CNN
F 3 "" H 4550 2850 60  0000 C CNN
	1    4550 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2750 4350 2750
Wire Wire Line
	4750 2750 4900 2750
Wire Wire Line
	4150 2850 4350 2850
Wire Wire Line
	4750 2850 4900 2850
Wire Wire Line
	5400 2750 5400 2850
$Comp
L GND #PWR015
U 1 1 54316E51
P 5500 2850
F 0 "#PWR015" H 5500 2850 30  0001 C CNN
F 1 "GND" H 5500 2780 30  0001 C CNN
F 2 "" H 5500 2850 60  0000 C CNN
F 3 "" H 5500 2850 60  0000 C CNN
	1    5500 2850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5400 2850 5500 2850
Connection ~ 5400 2850
$Comp
L TXS0101 U3
U 1 1 5431C46F
P 5100 1900
F 0 "U3" H 5100 1600 60  0000 C CNN
F 1 "TXS0101" H 5100 2100 60  0000 C CNN
F 2 "SMD_Packages:SOT-23-6" H 5100 1900 60  0001 C CNN
F 3 "" H 5100 1900 60  0000 C CNN
	1    5100 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2050 4700 2050
Wire Wire Line
	6100 1850 6100 2200
Connection ~ 6100 1850
$Comp
L GND #PWR016
U 1 1 5431CCFA
P 4450 1950
F 0 "#PWR016" H 4450 1950 30  0001 C CNN
F 1 "GND" H 4450 1880 30  0001 C CNN
F 2 "" H 4450 1950 60  0000 C CNN
F 3 "" H 4450 1950 60  0000 C CNN
	1    4450 1950
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 1550 4700 1850
$Comp
L C C4
U 1 1 5431D491
P 4550 1750
F 0 "C4" H 4550 1850 40  0000 L CNN
F 1 "100nF" H 4556 1665 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4588 1600 30  0001 C CNN
F 3 "" H 4550 1750 60  0000 C CNN
	1    4550 1750
	1    0    0    -1  
$EndComp
Connection ~ 4550 1550
$Comp
L C C11
U 1 1 5431D76D
P 6350 2050
F 0 "C11" H 6350 2150 40  0000 L CNN
F 1 "100nF" H 6356 1965 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 6388 1900 30  0001 C CNN
F 3 "" H 6350 2050 60  0000 C CNN
	1    6350 2050
	1    0    0    -1  
$EndComp
Connection ~ 6350 1850
$Comp
L GND #PWR017
U 1 1 5431D7F0
P 6350 2300
F 0 "#PWR017" H 6350 2300 30  0001 C CNN
F 1 "GND" H 6350 2230 30  0001 C CNN
F 2 "" H 6350 2300 60  0000 C CNN
F 3 "" H 6350 2300 60  0000 C CNN
	1    6350 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 2300 6350 2250
Wire Wire Line
	5500 2050 5500 2550
Wire Wire Line
	5500 2550 6600 2550
Wire Wire Line
	6600 2550 6600 2050
$Comp
L TESTPOINT U4
U 1 1 5431DE36
P 6100 3300
F 0 "U4" H 6100 3200 60  0000 C CNN
F 1 "NEO" H 6100 3500 60  0000 C CNN
F 2 "synicpretty:TESTPOINT" H 6200 3300 60  0001 C CNN
F 3 "" H 6200 3300 60  0000 C CNN
	1    6100 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3250 5800 2550
Connection ~ 5800 2550
$Comp
L TESTPOINT U5
U 1 1 5431DF40
P 6100 3700
F 0 "U5" H 6100 3600 60  0000 C CNN
F 1 "GND" H 6100 3900 60  0000 C CNN
F 2 "synicpretty:TESTPOINT" H 6200 3700 60  0001 C CNN
F 3 "" H 6200 3700 60  0000 C CNN
	1    6100 3700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 5431DFE3
P 5700 3650
F 0 "#PWR018" H 5700 3650 30  0001 C CNN
F 1 "GND" H 5700 3580 30  0001 C CNN
F 2 "" H 5700 3650 60  0000 C CNN
F 3 "" H 5700 3650 60  0000 C CNN
	1    5700 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	5700 3650 5800 3650
$Comp
L TESTPOINT U6
U 1 1 5431E082
P 1850 6450
F 0 "U6" H 1850 6350 60  0000 C CNN
F 1 "VCC5V" H 1850 6650 60  0000 C CNN
F 2 "synicpretty:TESTPOINT" H 1950 6450 60  0001 C CNN
F 3 "" H 1950 6450 60  0000 C CNN
	1    1850 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 6400 1550 6400
Wire Wire Line
	5950 1250 5950 750 
Wire Wire Line
	4450 1550 5600 1550
Wire Wire Line
	4450 1950 4700 1950
Connection ~ 4550 1950
$Comp
L VDD #PWR019
U 1 1 5431F998
P 4450 1550
F 0 "#PWR019" H 4450 1650 30  0001 C CNN
F 1 "VDD" H 4450 1660 30  0000 C CNN
F 2 "" H 4450 1550 60  0000 C CNN
F 3 "" H 4450 1550 60  0000 C CNN
	1    4450 1550
	0    -1   -1   0   
$EndComp
$Comp
L VDD #PWR020
U 1 1 5431FA98
P 1200 2750
F 0 "#PWR020" H 1200 2850 30  0001 C CNN
F 1 "VDD" H 1200 2860 30  0000 C CNN
F 2 "" H 1200 2750 60  0000 C CNN
F 3 "" H 1200 2750 60  0000 C CNN
	1    1200 2750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1450 6400 1450 7100
Connection ~ 1450 7100
Wire Wire Line
	5500 1950 5600 1950
Wire Wire Line
	5600 1950 5600 1550
Connection ~ 4700 1550
$EndSCHEMATC

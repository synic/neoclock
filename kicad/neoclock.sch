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
LIBS:ds1307timer
LIBS:open-project
LIBS:neoclock-cache
EELAYER 24 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "NeoClock"
Date ""
Rev "0"
Comp "Adam Olsen <arolsen@gmail.com>"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 1550 3450
Connection ~ 1550 3550
$Comp
L GND #PWR01
U 1 1 534351EA
P 1550 3650
F 0 "#PWR01" H 1550 3650 30  0001 C CNN
F 1 "GND" H 1550 3580 30  0001 C CNN
F 2 "" H 1550 3650 60  0000 C CNN
F 3 "" H 1550 3650 60  0000 C CNN
	1    1550 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 1250 1550 1550
Connection ~ 1550 1550
Connection ~ 1550 1250
Wire Wire Line
	1550 1250 1150 1250
$Comp
L VCC #PWR02
U 1 1 53435261
P 1150 1250
F 0 "#PWR02" H 1150 1350 30  0001 C CNN
F 1 "VCC" H 1150 1350 30  0000 C CNN
F 2 "" H 1150 1250 60  0000 C CNN
F 3 "" H 1150 1250 60  0000 C CNN
	1    1150 1250
	0    -1   -1   0   
$EndComp
$Comp
L C C2
U 1 1 534352CE
P 1300 1850
F 0 "C2" H 1300 1950 40  0000 L CNN
F 1 "100nF" H 1306 1765 40  0000 L CNN
F 2 "Capacitors_SMD:c_0805" H 1338 1700 30  0001 C CNN
F 3 "" H 1300 1850 60  0000 C CNN
	1    1300 1850
	0    1    1    0   
$EndComp
$Comp
L VCC #PWR03
U 1 1 534352E0
P 1050 1850
F 0 "#PWR03" H 1050 1950 30  0001 C CNN
F 1 "VCC" H 1050 1950 30  0000 C CNN
F 2 "" H 1050 1850 60  0000 C CNN
F 3 "" H 1050 1850 60  0000 C CNN
	1    1050 1850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1050 1850 1100 1850
Wire Wire Line
	1500 1850 1550 1850
$Comp
L VCC #PWR04
U 1 1 53435302
P 850 2050
F 0 "#PWR04" H 850 2150 30  0001 C CNN
F 1 "VCC" H 850 2150 30  0000 C CNN
F 2 "" H 850 2050 60  0000 C CNN
F 3 "" H 850 2050 60  0000 C CNN
	1    850  2050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 5343530D
P 850 2550
F 0 "#PWR05" H 850 2550 30  0001 C CNN
F 1 "GND" H 850 2480 30  0001 C CNN
F 2 "" H 850 2550 60  0000 C CNN
F 3 "" H 850 2550 60  0000 C CNN
	1    850  2550
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 53435318
P 850 2300
F 0 "C1" H 850 2400 40  0000 L CNN
F 1 "100nF" H 856 2215 40  0000 L CNN
F 2 "Capacitors_SMD:c_0805" H 888 2150 30  0001 C CNN
F 3 "" H 850 2300 60  0000 C CNN
	1    850  2300
	-1   0    0    1   
$EndComp
Wire Wire Line
	850  2500 850  2550
Wire Wire Line
	850  2100 850  2050
$Comp
L CRYSTAL X1
U 1 1 534353C5
P 4100 1900
F 0 "X1" H 4100 2050 60  0000 C CNN
F 1 "16Mhz" H 4100 1750 60  0000 C CNN
F 2 "synic:2_SMD_CRYSTAL_5.0x3.20" H 4100 1900 60  0001 C CNN
F 3 "" H 4100 1900 60  0000 C CNN
	1    4100 1900
	0    1    1    0   
$EndComp
$Comp
L C C5
U 1 1 534353D7
P 4500 1600
F 0 "C5" H 4500 1700 40  0000 L CNN
F 1 "22pF" H 4506 1515 40  0000 L CNN
F 2 "Capacitors_SMD:c_0805" H 4538 1450 30  0001 C CNN
F 3 "" H 4500 1600 60  0000 C CNN
	1    4500 1600
	0    1    1    0   
$EndComp
$Comp
L C C6
U 1 1 534353E2
P 4500 2200
F 0 "C6" H 4500 2300 40  0000 L CNN
F 1 "22pF" H 4506 2115 40  0000 L CNN
F 2 "Capacitors_SMD:c_0805" H 4538 2050 30  0001 C CNN
F 3 "" H 4500 2200 60  0000 C CNN
	1    4500 2200
	0    1    1    0   
$EndComp
Wire Wire Line
	3450 1850 3800 1850
Wire Wire Line
	3800 1850 3800 1600
Wire Wire Line
	3800 1600 4300 1600
Connection ~ 4100 1600
Wire Wire Line
	3800 2200 4300 2200
Wire Wire Line
	3450 1950 3800 1950
Wire Wire Line
	3800 1950 3800 2200
Connection ~ 4100 2200
$Comp
L GND #PWR06
U 1 1 53435439
P 4750 1600
F 0 "#PWR06" H 4750 1600 30  0001 C CNN
F 1 "GND" H 4750 1530 30  0001 C CNN
F 2 "" H 4750 1600 60  0000 C CNN
F 3 "" H 4750 1600 60  0000 C CNN
	1    4750 1600
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR07
U 1 1 53435444
P 4750 2200
F 0 "#PWR07" H 4750 2200 30  0001 C CNN
F 1 "GND" H 4750 2130 30  0001 C CNN
F 2 "" H 4750 2200 60  0000 C CNN
F 3 "" H 4750 2200 60  0000 C CNN
	1    4750 2200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4700 2200 4750 2200
Wire Wire Line
	4700 1600 4750 1600
$Comp
L VCC #PWR08
U 1 1 53435693
P 8500 1150
F 0 "#PWR08" H 8500 1250 30  0001 C CNN
F 1 "VCC" H 8500 1250 30  0000 C CNN
F 2 "" H 8500 1150 60  0000 C CNN
F 3 "" H 8500 1150 60  0000 C CNN
	1    8500 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 1150 8500 1200
NoConn ~ 9600 2250
$Comp
L GND #PWR09
U 1 1 534356BB
P 8500 3850
F 0 "#PWR09" H 8500 3850 30  0001 C CNN
F 1 "GND" H 8500 3780 30  0001 C CNN
F 2 "" H 8500 3850 60  0000 C CNN
F 3 "" H 8500 3850 60  0000 C CNN
	1    8500 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 3800 8500 3850
$Comp
L BATTERY BT1
U 1 1 534356E2
P 10200 1950
F 0 "BT1" H 10200 2150 50  0000 C CNN
F 1 "BATTERY" H 10200 1760 50  0000 C CNN
F 2 "synic:BK-755_12mm_coincell" H 10200 1950 60  0001 C CNN
F 3 "" H 10200 1950 60  0000 C CNN
	1    10200 1950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 534356F4
P 10600 1950
F 0 "#PWR010" H 10600 1950 30  0001 C CNN
F 1 "GND" H 10600 1880 30  0001 C CNN
F 2 "" H 10600 1950 60  0000 C CNN
F 3 "" H 10600 1950 60  0000 C CNN
	1    10600 1950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9600 1950 9900 1950
Wire Wire Line
	10500 1950 10600 1950
$Comp
L VCC #PWR011
U 1 1 53435736
P 9800 2750
F 0 "#PWR011" H 9800 2850 30  0001 C CNN
F 1 "VCC" H 9800 2850 30  0000 C CNN
F 2 "" H 9800 2750 60  0000 C CNN
F 3 "" H 9800 2750 60  0000 C CNN
	1    9800 2750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5343573C
P 9800 3250
F 0 "#PWR012" H 9800 3250 30  0001 C CNN
F 1 "GND" H 9800 3180 30  0001 C CNN
F 2 "" H 9800 3250 60  0000 C CNN
F 3 "" H 9800 3250 60  0000 C CNN
	1    9800 3250
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 53435742
P 9800 3000
F 0 "C7" H 9800 3100 40  0000 L CNN
F 1 "100nF" H 9806 2915 40  0000 L CNN
F 2 "Capacitors_SMD:c_0805" H 9838 2850 30  0001 C CNN
F 3 "" H 9800 3000 60  0000 C CNN
	1    9800 3000
	-1   0    0    1   
$EndComp
Wire Wire Line
	9800 3200 9800 3250
Wire Wire Line
	9800 2800 9800 2750
$Comp
L CRYSTAL X2
U 1 1 5343574A
P 6950 2950
F 0 "X2" H 6950 3100 60  0000 C CNN
F 1 "32.768kHz" H 6950 2800 60  0000 C CNN
F 2 "synic:2_SMD_CRYSTAL_3.2x1.5" H 6950 2950 60  0001 C CNN
F 3 "" H 6950 2950 60  0000 C CNN
	1    6950 2950
	0    1    1    0   
$EndComp
Wire Wire Line
	6950 2650 7350 2650
Wire Wire Line
	7350 2650 7350 2750
Wire Wire Line
	6950 3250 7350 3250
Wire Wire Line
	7350 3250 7350 3150
Text GLabel 3600 2500 2    60   Output ~ 0
I2CSDA
Text GLabel 3600 2600 2    60   Output ~ 0
I2CSCL
Wire Wire Line
	3450 2500 3600 2500
Wire Wire Line
	3450 2600 3600 2600
Text GLabel 7150 2250 0    60   Input ~ 0
I2CSDA
Text GLabel 7150 1950 0    60   Input ~ 0
I2CSCL
Wire Wire Line
	7150 1950 7350 1950
Wire Wire Line
	7150 2250 7350 2250
$Comp
L R R2
U 1 1 53435901
P 3750 2700
F 0 "R2" V 3830 2700 40  0000 C CNN
F 1 "10k" V 3757 2701 40  0000 C CNN
F 2 "Resistors_SMD:Resistor_SMD0805_ReflowWave" V 3680 2700 30  0001 C CNN
F 3 "" H 3750 2700 30  0000 C CNN
	1    3750 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	3450 2700 3500 2700
$Comp
L VCC #PWR013
U 1 1 5343593A
P 4100 2700
F 0 "#PWR013" H 4100 2800 30  0001 C CNN
F 1 "VCC" H 4100 2800 30  0000 C CNN
F 2 "" H 4100 2700 60  0000 C CNN
F 3 "" H 4100 2700 60  0000 C CNN
	1    4100 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	4000 2700 4100 2700
$Comp
L R R1
U 1 1 5343F9D2
P 2250 850
F 0 "R1" V 2330 850 40  0000 C CNN
F 1 "330" V 2257 851 40  0000 C CNN
F 2 "Resistors_SMD:Resistor_SMD0805_ReflowWave" V 2180 850 30  0001 C CNN
F 3 "" H 2250 850 30  0000 C CNN
	1    2250 850 
	0    1    1    0   
$EndComp
$Comp
L LED D1
U 1 1 5343F9E6
P 1700 850
F 0 "D1" H 1700 950 50  0000 C CNN
F 1 "PWR" H 1700 750 50  0000 C CNN
F 2 "LEDs:LED-0805" H 1700 850 60  0001 C CNN
F 3 "" H 1700 850 60  0000 C CNN
	1    1700 850 
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR014
U 1 1 5343F9F8
P 2600 850
F 0 "#PWR014" H 2600 950 30  0001 C CNN
F 1 "VCC" H 2600 950 30  0000 C CNN
F 2 "" H 2600 850 60  0000 C CNN
F 3 "" H 2600 850 60  0000 C CNN
	1    2600 850 
	0    1    1    0   
$EndComp
$Comp
L GND #PWR015
U 1 1 5343FA03
P 1400 850
F 0 "#PWR015" H 1400 850 30  0001 C CNN
F 1 "GND" H 1400 780 30  0001 C CNN
F 2 "" H 1400 850 60  0000 C CNN
F 3 "" H 1400 850 60  0000 C CNN
	1    1400 850 
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 850  1500 850 
Wire Wire Line
	1900 850  2000 850 
Wire Wire Line
	2500 850  2600 850 
$Comp
L BARREL_JACK CON1
U 1 1 5343FA98
P 3400 850
F 0 "CON1" H 3400 1100 60  0000 C CNN
F 1 "2.1mm 5V" H 3400 650 60  0000 C CNN
F 2 "synic:BARREL_JACK_SMD" H 3400 850 60  0001 C CNN
F 3 "" H 3400 850 60  0000 C CNN
	1    3400 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 850  3700 1150
$Comp
L CP1 C4
U 1 1 5343FAEF
P 4600 950
F 0 "C4" H 4650 1050 50  0000 L CNN
F 1 "10uF" H 4650 850 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeA_EIA-3216_Reflow" H 4600 950 60  0001 C CNN
F 3 "" H 4600 950 60  0000 C CNN
	1    4600 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 1150 4950 1150
Connection ~ 3700 950 
$Comp
L GND #PWR016
U 1 1 5343FBB9
P 4950 1150
F 0 "#PWR016" H 4950 1150 30  0001 C CNN
F 1 "GND" H 4950 1080 30  0001 C CNN
F 2 "" H 4950 1150 60  0000 C CNN
F 3 "" H 4950 1150 60  0000 C CNN
	1    4950 1150
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR017
U 1 1 5343FBC4
P 4950 750
F 0 "#PWR017" H 4950 850 30  0001 C CNN
F 1 "VCC" H 4950 850 30  0000 C CNN
F 2 "" H 4950 750 60  0000 C CNN
F 3 "" H 4950 750 60  0000 C CNN
	1    4950 750 
	0    1    1    0   
$EndComp
Connection ~ 4600 750 
Connection ~ 4600 1150
$Comp
L CONN_3 K1
U 1 1 5343FC4E
P 5400 4050
F 0 "K1" V 5350 4050 50  0000 C CNN
F 1 "NEOPIXEL" V 5450 4050 40  0000 C CNN
F 2 "synic:jst-3-pth-ra" H 5400 4050 60  0001 C CNN
F 3 "" H 5400 4050 60  0000 C CNN
	1    5400 4050
	0    1    1    0   
$EndComp
$Comp
L VCC #PWR018
U 1 1 5343FC65
P 5500 3600
F 0 "#PWR018" H 5500 3700 30  0001 C CNN
F 1 "VCC" H 5500 3700 30  0000 C CNN
F 2 "" H 5500 3600 60  0000 C CNN
F 3 "" H 5500 3600 60  0000 C CNN
	1    5500 3600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 5343FC70
P 5400 3600
F 0 "#PWR019" H 5400 3600 30  0001 C CNN
F 1 "GND" H 5400 3530 30  0001 C CNN
F 2 "" H 5400 3600 60  0000 C CNN
F 3 "" H 5400 3600 60  0000 C CNN
	1    5400 3600
	-1   0    0    1   
$EndComp
Wire Wire Line
	3450 3450 5300 3450
Wire Wire Line
	5300 3450 5300 3700
Wire Wire Line
	5400 3600 5400 3700
Wire Wire Line
	5500 3600 5500 3700
$Comp
L CONN_3X2 P1
U 1 1 5343FD28
P 6150 1300
F 0 "P1" H 6150 1550 50  0000 C CNN
F 1 "ICSP" V 6150 1350 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03" H 6150 1300 60  0001 C CNN
F 3 "" H 6150 1300 60  0000 C CNN
	1    6150 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 1150 5100 1150
Wire Wire Line
	5100 1150 5100 1350
Wire Wire Line
	5100 1350 3700 1350
Wire Wire Line
	3700 1350 3700 1650
Wire Wire Line
	3700 1650 3450 1650
$Comp
L VCC #PWR020
U 1 1 5343FD7A
P 6650 1150
F 0 "#PWR020" H 6650 1250 30  0001 C CNN
F 1 "VCC" H 6650 1250 30  0000 C CNN
F 2 "" H 6650 1150 60  0000 C CNN
F 3 "" H 6650 1150 60  0000 C CNN
	1    6650 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	6550 1150 6650 1150
Wire Wire Line
	5750 1250 5150 1250
Wire Wire Line
	5150 1250 5150 1400
Wire Wire Line
	5150 1400 3750 1400
Wire Wire Line
	3750 1400 3750 1750
Wire Wire Line
	3750 1750 3450 1750
Wire Wire Line
	6550 1250 6850 1250
Wire Wire Line
	6850 1250 6850 1000
Wire Wire Line
	6850 1000 5050 1000
Wire Wire Line
	5050 1000 5050 1300
Wire Wire Line
	5050 1300 3650 1300
Wire Wire Line
	3650 1300 3650 1550
Wire Wire Line
	3650 1550 3450 1550
Wire Wire Line
	5750 1350 5500 1350
Wire Wire Line
	5500 1350 5500 2800
Wire Wire Line
	5500 2800 3500 2800
Wire Wire Line
	3500 2800 3500 2700
Connection ~ 3500 2700
$Comp
L GND #PWR021
U 1 1 5343FEAD
P 6600 1350
F 0 "#PWR021" H 6600 1350 30  0001 C CNN
F 1 "GND" H 6600 1280 30  0001 C CNN
F 2 "" H 6600 1350 60  0000 C CNN
F 3 "" H 6600 1350 60  0000 C CNN
	1    6600 1350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6550 1350 6600 1350
NoConn ~ 3450 2100
NoConn ~ 3450 2200
NoConn ~ 3450 1450
NoConn ~ 3450 1350
NoConn ~ 3450 1250
NoConn ~ 3450 3550
$Comp
L PHOTOR PHOTOR1
U 1 1 53440FCF
P 5200 2000
F 0 "PHOTOR1" V 5280 2000 50  0000 C CNN
F 1 "PHOTOR" V 5200 2000 50  0000 C CNN
F 2 "synic:PHOTORESISTOR" H 5200 2000 60  0001 C CNN
F 3 "" H 5200 2000 60  0000 C CNN
	1    5200 2000
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 53440FF1
P 4950 2550
F 0 "R3" V 5030 2550 40  0000 C CNN
F 1 "10k" V 4957 2551 40  0000 C CNN
F 2 "Resistors_SMD:Resistor_SMD0805_ReflowWave" V 4880 2550 30  0001 C CNN
F 3 "" H 4950 2550 30  0000 C CNN
	1    4950 2550
	0    1    1    0   
$EndComp
$Comp
L VCC #PWR022
U 1 1 53441003
P 5200 1650
F 0 "#PWR022" H 5200 1750 30  0001 C CNN
F 1 "VCC" H 5200 1750 30  0000 C CNN
F 2 "" H 5200 1650 60  0000 C CNN
F 3 "" H 5200 1650 60  0000 C CNN
	1    5200 1650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 5344100E
P 4600 2550
F 0 "#PWR023" H 4600 2550 30  0001 C CNN
F 1 "GND" H 4600 2480 30  0001 C CNN
F 2 "" H 4600 2550 60  0000 C CNN
F 3 "" H 4600 2550 60  0000 C CNN
	1    4600 2550
	0    1    1    0   
$EndComp
Wire Wire Line
	5200 1650 5200 1750
Wire Wire Line
	5200 2250 5200 2550
Wire Wire Line
	4600 2550 4700 2550
Wire Wire Line
	5200 2400 3450 2400
Connection ~ 5200 2400
$Comp
L SW_PUSH SW1
U 1 1 53441535
P 4750 3150
F 0 "SW1" H 4900 3260 50  0000 C CNN
F 1 "HOUR" H 4750 3070 50  0000 C CNN
F 2 "synic:SMD_PUSHBUTTON_MINI" H 4750 3150 60  0001 C CNN
F 3 "" H 4750 3150 60  0000 C CNN
	1    4750 3150
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 53441547
P 5550 3150
F 0 "SW2" H 5700 3260 50  0000 C CNN
F 1 "MINUTE" H 5550 3070 50  0000 C CNN
F 2 "synic:SMD_PUSHBUTTON_MINI" H 5550 3150 60  0001 C CNN
F 3 "" H 5550 3150 60  0000 C CNN
	1    5550 3150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR024
U 1 1 53441552
P 5050 3250
F 0 "#PWR024" H 5050 3250 30  0001 C CNN
F 1 "GND" H 5050 3180 30  0001 C CNN
F 2 "" H 5050 3250 60  0000 C CNN
F 3 "" H 5050 3250 60  0000 C CNN
	1    5050 3250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 5344155D
P 5850 3250
F 0 "#PWR025" H 5850 3250 30  0001 C CNN
F 1 "GND" H 5850 3180 30  0001 C CNN
F 2 "" H 5850 3250 60  0000 C CNN
F 3 "" H 5850 3250 60  0000 C CNN
	1    5850 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 3250 3650 3250
Wire Wire Line
	3650 3250 3650 3150
Wire Wire Line
	3650 3150 4450 3150
Wire Wire Line
	5050 3150 5050 3250
Wire Wire Line
	3450 3150 3600 3150
Wire Wire Line
	3600 3150 3600 3100
Wire Wire Line
	3600 3100 4500 3100
Wire Wire Line
	4500 3100 4500 3000
Wire Wire Line
	4500 3000 5250 3000
Wire Wire Line
	5250 3000 5250 3150
Wire Wire Line
	5850 3150 5850 3250
NoConn ~ 3450 2950
NoConn ~ 3450 3050
$Comp
L PWR_FLAG #FLG026
U 1 1 53441864
P 10550 1950
F 0 "#FLG026" H 10550 2045 30  0001 C CNN
F 1 "PWR_FLAG" H 10550 2130 30  0000 C CNN
F 2 "" H 10550 1950 60  0000 C CNN
F 3 "" H 10550 1950 60  0000 C CNN
	1    10550 1950
	1    0    0    -1  
$EndComp
Connection ~ 10550 1950
$Comp
L PWR_FLAG #FLG027
U 1 1 5344187A
P 750 2100
F 0 "#FLG027" H 750 2195 30  0001 C CNN
F 1 "PWR_FLAG" H 750 2280 30  0000 C CNN
F 2 "" H 750 2100 60  0000 C CNN
F 3 "" H 750 2100 60  0000 C CNN
	1    750  2100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	750  2100 850  2100
Connection ~ 850  2100
Connection ~ 5500 2800
$Comp
L DS1307 U1
U 1 1 53435651
P 8500 2500
F 0 "U1" H 8600 1300 60  0000 C CNN
F 1 "DS1307" H 8500 2550 60  0000 C CNN
F 2 "SOIC_Packages:SOIC-8_N" H 8500 2500 60  0001 C CNN
F 3 "" H 8500 2500 60  0000 C CNN
	1    8500 2500
	1    0    0    -1  
$EndComp
NoConn ~ 3450 3350
NoConn ~ 3450 2300
NoConn ~ 3450 2850
$Comp
L FUSE F1
U 1 1 53AD8508
P 3950 750
F 0 "F1" H 4050 800 40  0000 C CNN
F 1 "FUSE" H 3850 700 40  0000 C CNN
F 2 "synic:1206_polyfuse" H 3950 750 60  0001 C CNN
F 3 "" H 3950 750 60  0000 C CNN
	1    3950 750 
	1    0    0    -1  
$EndComp
Connection ~ 3700 750 
$Comp
L ATMEGA328P-MM IC1
U 1 1 53C2DE6E
P 2450 2350
F 0 "IC1" H 1700 3600 40  0000 L BNN
F 1 "ATMEGA328P-MM" H 2800 950 40  0000 L BNN
F 2 "SMD_Packages:QFN28" H 2450 2350 30  0000 C CIN
F 3 "" H 2450 2350 60  0000 C CNN
	1    2450 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 750  4950 750 
Wire Wire Line
	1550 3450 1550 3650
$Comp
L VCC #PWR028
U 1 1 53C41ECF
P 6600 1600
F 0 "#PWR028" H 6600 1700 30  0001 C CNN
F 1 "VCC" H 6600 1700 30  0000 C CNN
F 2 "" H 6600 1600 60  0000 C CNN
F 3 "" H 6600 1600 60  0000 C CNN
	1    6600 1600
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 53C41EF9
P 6150 1900
F 0 "R4" V 6230 1900 40  0000 C CNN
F 1 "4.7k" V 6157 1901 40  0000 C CNN
F 2 "Resistors_SMD:Resistor_SMD0805_ReflowWave" V 6080 1900 30  0001 C CNN
F 3 "" H 6150 1900 30  0000 C CNN
	1    6150 1900
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 53C41F57
P 6450 1900
F 0 "R5" V 6530 1900 40  0000 C CNN
F 1 "4.7k" V 6457 1901 40  0000 C CNN
F 2 "Resistors_SMD:Resistor_SMD0805_ReflowWave" V 6380 1900 30  0001 C CNN
F 3 "" H 6450 1900 30  0000 C CNN
	1    6450 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 1650 6600 1650
Connection ~ 6450 1650
Connection ~ 7250 1950
Wire Wire Line
	7250 2250 7250 2350
Wire Wire Line
	7250 2350 6150 2350
Wire Wire Line
	6150 2350 6150 2150
Connection ~ 7250 2250
Wire Wire Line
	7250 1950 7250 2150
Wire Wire Line
	7250 2150 6450 2150
Wire Wire Line
	6600 1650 6600 1600
$EndSCHEMATC

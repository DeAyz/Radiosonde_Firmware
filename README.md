# Project_Radiosonde

## Projektplan

## Beschreibung

Für eine im Institut entwickelte Radiosonde soll auf Basis einer entwickelten Radiobibliothek eine Firmware entwickelt werden,
die einen Betrieb als konventionelle Radiosonde erlaubt. 
Dazu soll eine Bibliothek zur Kommunikation mit einem GPS-Modul im NMEA auf der STM32 Plattform (BareMetal, kein HAL)geschrieben werden,
und eine Beispielanwendung entwickelt werden, die zur VaisalaRS41 kompatible Telemetrie sendet.

Es soll eine Firmware entwickelt werden, der die Dynamische Werte vom GPS-Modul zum Microcontroller überträgt.
Die Firmware soll so entwickelt werden, dass man die in jedem beliebigen Microcontroller der STM32 Reihe portieren kann.

## Hardware

	- PC

	- Microcontroller (STM32f100) + Radio IC + GNSS Emüfänger
	
	- GNSS Empfänger (Für den PC)
	
	- GPS-Repeater (Zum Empfangen von GPS-Signalen)
	
## Software

	- CrossWorks CrossStudio for ARM (Hauptentwicklungsplattform für die Firmware)
	
	- u-Center (Für Funktionsweise und Parametrierung der GNSS-Module)



## Hardware Zusammenschaltung:

	STM32f100	:::::	uBlox GNSS Repeater

	VCC 3.3V	<--->	Vcc 3.3V
	PA10(RX)	<--->	TX
	PA9 (TX)	<--->	RX
	GND			<--->	GND

## Software: 
	
Um die GPS Positionen vom GNSS in dem Microcontroller zu speichern, wird zunächste die entsprechende Register und Ports aktiviert.
Laut Reference Manual wie gefolgt:

	1. Alternate funtion aktivieren. 
		RCC->APB2ENR |= (1<<0);
		
	2. PortA fregeben.
		RCC->APB2ENR |= (1<<2);
		
	3. USART1 aktivieren.
		RCC->APB2ENR |= (1<<14);
		
	4. PA.9 und PA.10 aktivieren.
		Die Einstellung, die gebraucht wird:
		MODE9	[1,1]	-	Output mode, max speed 50 MHZ
		CNF9 	[1,0]	-	Alternate function output Push-Pull
		MODE10 	[0,0]	-	Input mode
		CNF10 	[0,1]	-	Floating Input
		
		GPIOA->CRH |= (1<<4);        
		GPIOA->CRH |= (1<<5);         
		GPIOA->CRH |= (1<<7);       
		GPIOA->CRH &= ~(1<<0);        
		GPIOA->CRH &= ~(1<<8);       
		GPIOA->CRH &= ~(1<<9);        
		GPIOA->CRH |= (1<<10);      
		GPIOA->CRH &= ~(1<<11);    
		
	5. Baudrate einstellen.
		-24 MHz Max. frequenz
		-9600 Baudrate * 16
		Rechnung:
		24.000.000 / (16 * 9600)
		= 156,25 -> HEX: 9C
		0,25*16 = 4 -> Hex: 4
		
		USART1->BRR = 0x9C4;
		
	6. Den Transmitter und Reciever aktivieren.
		USART1->CR1 |= (1<<2);
		USART1->CR1 |= (1<<3);
		
	7. UART aktivieren.
		USART1->CR1 |= (1<<13);
		
	8. Zuletzt die Flags aktivieren.
		USART1->CR1 |= (1<<7);
		USART1->CR1 |= (1<<5);

		Wenn im Status Register,
		TXE 	= 1 	-> Senden
		RXNE 	= 1 	-> Daten Register leer


Nun muss  abgefragt werden ob der Daten Register leer ist. (Code im Anhang)
Voll -> ASCII Zeichen mit Variable deklarieren (character).
Leer -> Warten bis Daten im Daten Register sind.
Als nächstes werden die GPS Daten in ASCII Zeichen aus dem Daten Register gelesen und mit einer Variable deklariert und zeitgleich wird es gelöscht (In Schleife setzen.).

Nun soll die Variable mit den ASCII Zeichen nach Längen und Breitengrad ausgegeben. (Code im Anhang, nur in C++)
	- Zunächst wird das character mit dem $GNRMC.... rausgefiltert.
	- Da es die erforderliche Daten verfügt (Latitude, Longtitude, indicator) die gebraucht wird.
	- Nun werden die character für dan Breiten- und Längengrad in einem neuen String Kopiert.
	- Dann werden die ASCII Zeichen in fließkommazahlen konvertiert.
	- Nach der konvertierung werden die nach den Längen- und Breitengrade umgerechnet.
	- Ausgabe in Breiten- und Längengrad.

 
## Eckdaten

# Projektstart:

[X]	- 03.06.21	Anleitung für Hardware und Software und erste Betriebsnahme											
	
[X]	- 09.06.21	Github Repository und erste Markdown mit Projektverlauf anlegen.					
	
[X]	- 10.06.21	Vorstellung: Zwischenstand+Projektplanung											
	
	
# Projektmitte:

[X]	- 13.06.21	Einstieg: Mit Microcontroller vertraut machen. LED Blinken und Daten Transmitte,Recieve
	
[X]	- 18.06.21	Firmware entwicklung (Programmierung)												
	
[X]	- 25.06.21	Zwischenstand ggf. Rücksprache bei Probleme											
	
[X]	- 29.06.21	Firmware entwicklung (Programmierung)												
	
[X]	- 01.07.21	Vorstellung: Projektfortschritt														
	

# Projektende:

[X]	- 06.07.21	Firmware entwicklung ggf, Rücksprache bei Probleme									
	
[X]	- 10.07.21	Firmware entwicklung

[ ] - 13.07.21 	Ende der Firmware entwicklung. Dokumentationen in Git-Repository				
	
[ ]	- 15.07.21	Abschlusspräsentation																
	
[ ]	- 18.07.21	Projektabgabe																		
	


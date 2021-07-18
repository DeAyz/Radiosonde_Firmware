# Project_Radiosonde

## Projektplan

## Beschreibung

Für eine im Institut entwickelte Radiosonde soll auf Basis einer entwickelten Radiobibliothek eine Firmware entwickelt werden,
die einen Betrieb als konventionelle Radiosonde erlaubt. 
Dazu soll eine Bibliothek zur Kommunikation mit einem GPS-Modul im NMEA auf der STM32 Plattform (BareMetal, kein HAL)geschrieben werden,
und eine Beispielanwendung entwickelt werden, die zur VaisalaRS41 kompatible Telemetrie sendet.

Es soll eine Firmware entwickelt werden, der die Dynamische Werte vom GPS-Modul zum Microcontroller überträgt.
Die Firmware soll so entwickelt werden, dass man die in jedem beliebigen Microcontroller der STM32 Reihe portieren kann.

## Aufgabenstellung

1. Ein Board code programmieren um die GPS Daten vom GPS Repeater mithilfe von einem uBlox GNSS Empfänger zu empfangen und im Microcontroller zu speichern.
Anschließend sollen die Daten abrufbar sein und in den NMEA übersetzungscode weiterverarbeitet werden.
2. Ein NMEA konvertierungscode schreiben, der die entsprechende Koordinaten im Daten Register des microcontrollers STM32f100 in Längen- und Breitengrad ausgibt.
Die Daten müssen als erstes von ASCII Zeichen in fließkommazahlen konvertiert werden und mit den entsprechenden Rechnungen in Längen- und Breitengrad ausgeben.

## Hardware

	- PC

	- Microcontroller (STM32f100) + Radio IC + GNSS Empfänger
	
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
	GND		<--->	GND 

## Software (Dokumentation): 
	
Um die GPS Positionen vom GNSS in dem Microcontroller zu speichern, wird zunächste die entsprechende Register und Ports aktiviert.
Laut Reference Manual wie gefolgt:

	1. Clock Einstellen. -> Systemclock auf 24 MHz + 8 MHz HSE Ocscillator
		RCC->CFGR |= (0b0001<<16);  // PLL entry clock source (HSI oscillator clock / 2 selected as PLL input clock)
		RCC->CFGR |= (0b0001<<18); 	// PLL multiplication factor (PLL input clock x 3)
		RCC->CFGR |= (0b10<<0); 	// System clock switch (PLL selected as system clock)
		
	2. 	Alternate funtion aktivieren. 
		RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
		
	3. PortA fregeben.
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		
	4. USART1 aktivieren.
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		
	5. PA.9 und PA.10 aktivieren.
		Die Einstellung, die gebraucht wird:
		MODE9	[1,1]	-	Output mode, max speed 50 MHZ
		CNF9 	[1,0]	-	Alternate function output Push-Pull
		MODE10 	[0,0]	-	Input mode
		CNF10 	[0,1]	-	Floating Input
		
		GPIOA->CRH |= 0b0000010010110000;    
		
	6. Baudrate einstellen.
		-24 MHz Max. frequenz
		-9600 Baudrate * 16
		Berechnung:
		24.000.000 / (16 * 9600)
		= 156,25 -> HEX: 9C
		0,25*16 = 4 -> Hex: 4
		
		USART1->BRR = 0x9C4;
		
	7. Den Transmitter und Reciever aktivieren.
		USART1->CR1 |= (0b001<<2);       // Receiver enable (Receiver is enabled and begins searching for a start bit)
		USART1->CR1 |= (0b001<<3);       // Transmitter enable (Transmitter is enabled)
		
	8. UART aktivieren.
		USART1->CR1 |= (0b001<<13);       // USART enable (USART enabled)
		
	9. Zuletzt die Interrupts aktivieren.
		USART1->CR1 |= (0b001<<7);     // TXE interrupt enable (An USART interrupt is generated whenever TXE=1 in the USART_SR register)
		USART1->CR1 |= (0b001<<5);      // RXNE interrupt enable (An USART interrupt is generated whenever ORE=1 or RXNE=1 in the USART_SR register)

		Wenn im Status Register,
		TXE 	= 1 	-> Senden
		RXNE 	= 1 	-> Daten Register leer


Nun muss  abgefragt werden ob der Daten Register leer ist. (Code im Anhang)  <br>
	Voll -> ASCII Zeichen mit Variable deklarieren (character).  <br>
	Leer -> Warten bis Daten im Daten Register sind.  <br>

Da die Informationen in mehrer NMEA Sentences sind, muss man die richtige Sentences rausfiltern. <br>
In dem Fall die RMC - Recommended Minimum Specific GNSS Data
	
	Format: $--RMC,hhmmss.sss,x,llll.lll,a,yyyyy.yyy,a,x.x,u.u,xxxxxx,,,v*hh<CR><LF> 
	llll.lll -> Latitude.
	yyyyy.yyy -> Longtitude.
	A -> Indicator für N,S,W,E

Mit dieser Funktion werden die NMEA Senctences: $GNRMC gefiltern, da es die erforderlichen Informationen beinhaltet. <br>

	void FilterSentences(int* Zeichen) // Funktion um $GNRMC zu Filtern
	{
	  int* Filter;
	  strcpy(Filter, GPS);
	  Filter = (int*)strstr((const char*)Zeichen, "$GNRMC");
	}
Als nächstes werden die GPS Daten in ASCII Zeichen aus dem Daten Register gelesen und mit einer Variable deklariert und zeitgleich wird es gelöscht. (Code im Anhang) <br>
	
Nun soll die Variable mit den ASCII Zeichen nach Längen und Breitengrad ausgegeben werdem. (Code im Anhang, C++ und C)  <br>
		- Zunächst wird das character mit dem $GNRMC.... rausgefiltert.  <br>
		- Da es die erforderliche Daten verfügt (Latitude, Longtitude, indicator) die gebraucht wird.  <br>
		- Nun werden die character für dan Breiten- und Längengrad in einem neuen String Kopiert.  <br>
		- Dann werden die ASCII Zeichen in fließkommazahlen konvertiert.  <br>
		- Nach der konvertierung werden die nach den Längen- und Breitengrade umgerechnet.  <br>
		- Ausgabe in Breiten- und Längengrad.  <br>

## Probleme:

Es gab zunächst einige Probleme beim Projektstart.

	Kaum brauchbare GPS Daten. -> Lösung: Standortwechsel(Anderes Zimmer).
	Projektaufgabe falsch verstanden. -> Lösung: Meeting mit Projektgeber.
			
Zum Mitte des Projekts.

	CrossStudion: Register beim builden wurden nicht aktiviert. -> Lösung: Softwarefehler =>  Mehrmals hintereinander Builden.
	NMEA Converter code in Programmiersprach C. -> Lösung: Code erst in C++ geschrieben und in C schrittweise umschrieben.
			 
Am Ende des Projekts 

	Board Code empfängt keine Vollständige GPS Daten. -> Mögliche Lösungen: Interruptfunktion überfordert(zu schnell)?; Baudrate und Clock falsch?; 
	Durch falsche Verkabelung, das Board beschädigt. -> Lösung: Hardware muss ausgetauscht werden.
	Board kaputt -> Keine Finale lösung zum Projekt möglich.
		
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

[X] - 13.07.21 	Ende der Firmware entwicklung. Dokumentationen in Git-Repository				
	
[X]	- 15.07.21	Abschlusspräsentation																
	
[X]	- 18.07.21	Projektabgabe																		
	


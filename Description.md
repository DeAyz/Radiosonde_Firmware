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
 
## Eckdaten

# Projektstart:

[X]	- 03.06.21	Anleitung für Hardware und Software													
	
[ ]	- 09.06.21	Einsteig: Mit Microcontroller vertraut machen. Übung: Blinklicht					
	
[ ]	- 10.06.21	Vorstellung: Zwischenstand+Projektplanung											
	
	
# Projektmitte:

[ ]	- 14.06.21	Einstieg: Mit Microcontroller vertraut machen. Übung: Kommunikation pc zum Board	
	
[ ]	- 18.06.21	Firmware entwicklung (Programmierung)												
	
[ ]	- 25.06.21	Zwischenstand ggf. Rücksprache bei Probleme											
	
[ ]	- 29.06.21	Firmware entwicklung (Programmierung)												
	
[ ]	- 01.07.21	Vorstellung: Projektfortschritt														
	

# Projektende:

[ ]	- 06.07.21	Firmware entwicklung ggf, Rücksprache bei Probleme									
	
[ ]	- 10.07.21	Ende der Firmware entwicklung. Dokumentationen in Git-Repository					
	
[ ]	- 15.07.21	Abschlusspräsentation																
	
[ ]	- 18.07.21	Projektabgabe																		
	


#include "stm32f10x.h"
#include "string.h"
#include "stdlib.h"
#include "stdarg.h"
#include <stdint.h>
#include "stdio.h"


void EnableTxRx(void){

  // RCC Config. :: Set SYSCLK to 24 MHz, Using external 8 MHz HSE Oscillator.
  RCC->CFGR |= (1<<16);   // PLL entry clock source (HSI oscillator clock / 2 selected as PLL input clock)
  RCC->CFGR |= (0b0001<<18); // PLL multiplication factor (PLL input clock x 3)
  RCC->CFGR |= (0b10<<0); // System clock switch (PLL selected as system clock)


  // APB2 peripheral clock enable register (RCC_APB2ENR)
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // AFIOEN: Alternate function I/O clock enable (Alternate Function I/O clock enabled)       
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // IOPAEN: I/O port A clock enable (I/O port A clock enabled)
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;    // USART1EN (USART1 clock enabled)

  // Port configuration register high
  // MODE9 = 11 I Output mode, max speed 50 MHZ (Bit: 4, 5)
  // CNF9 = 10 I Alternate function output Push-Pull (Bit: 7, ~6)
  // MODE10 = 00 I Inpute mode (Bit: ~9, ~8)
  // CNF10 = 01 I Floating Input (Bit: 10, ~11)
  GPIOA->CRH |= 0b00000010010110000;

  // Baud rate register
  // Clock = 24MHZ, Baudrate = 9600
  // 24MHZ / (16*9600) =  156,25 -> HEX: 9C 
  // 0,25*16 = 4 -> HEX: 4
  USART1->BRR = 0x9C4;

  // Control register 1
  USART1->CR1 |= (0b001<<2);       // Receiver enable (Receiver is enabled and begins searching for a start bit)
  USART1->CR1 |= (0b001<<3);       // Transmitter enable (Transmitter is enabled)
  USART1->CR1 |= (0b001<<13);       // USART enable (USART enabled)
  USART1->CR1 |= (0b001<<7);     // TXE interrupt enable (An USART interrupt is generated whenever TXE=1 in the USART_SR register)
  USART1->CR1 |= (0b001<<5);      // RXNE interrupt enable (An USART interrupt is generated whenever ORE=1 or RXNE=1 in the USART_SR register)


  NVIC_EnableIRQ(USART1_IRQn);
}

void FilterSentences(int* Zeichen) // Funktion um $GNRMC zu Filtern
{
  int* Filter;
  strcpy(Filter, GPS);
  Filter = (int*)strstr((const char*)Zeichen, "$GNRMC");
}


#define MAX_LEN 256
unsigned char counter = 0;
void clear(void);
char Daten[MAX_LEN];  // String mit Max länger 

int main(void) {
  EnableTxRx();
  
  while(1) {
    if (counter == 255) {  
      for (int i = 0; i < 255; i++) {    
        printf("%", Daten[i]);     
      }    
    }
    void FilterSentences(); //$GNRMC gefiltert
    char NMEA[255];
    strcpy(NMEA, Filter);   // String: FIlter kopieren an String: NMEA + String: Filter löschen.
    
    if (strchr(NMEA, '-')) {  // Negatives Vorzeichen ?
        char Min[] = "-";
        int Len = strcspn(NMEA, Min);

        // Plus, Minus
        if (Len > 25) { // Vorzeichen im ersten Koordinate
            char name[10];
            int data[12];
            sscanf (NMEA, "%[^,] %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s", name, &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7], &data[8], &data[9], &data[10], &data[11], &data[12]);
            char NMEA3[10];
            char x[10];
            strncpy(x, strtok(&data[6], NMEA3), 13);
            char NMEA2[10];

            double Term1 = atof(strtok(&data[3], NMEA2+1)); // Term 1 = Latitude in float
            double Term2 = atof(&x[1]); // Term 2 = Longtitude in float

            int LaG;
            double GLaG;
            double Eg;
            double Eg2;
            int Eg22;
            double Eg3;
            double Eg33;
            int Eg4;
            double Eg5;
            double Eg55;

            int LnG;
            double GLnG;
            double EgL;
            double EgL2;
            int EgL22;
            double EgL3;
            double EgL33;
            int EgL4;
            double EgL5;
            double EgL55;

            // Umrechnung
            int Egg = (int)Eg;
            Egg = (Term1 / 100);
            Eg2 = (Term1 / 100);
            Eg3 = (Eg2 - Egg);
            Eg33 = Eg3 * 60;
            int Egg33 = (int)Eg33;
            Eg5 = Eg33 - Egg33;
            Eg55 = Eg5 * 60;

            if (Term1 > 0) {
                printf("Laengengrad: %d* %d'%f N \n", Egg, Egg33, Eg55);
            } else {
                printf("Laengengrad: %d* %d'%f S \n", Egg, Egg33, Eg55);
            }

            int EggL = (int)EgL;
            EggL = (Term2 / 100)*-1;
            EgL2 = (Term2 / 100)*-1;
            EgL3 = (EgL2 - EggL);
            EgL33 = EgL3 * 60;
            int EggL33 = (int)EgL33;
            EgL5 = EgL33 - EggL33;
            EgL55 = EgL5 * 60;

            if (Term2 < 0) {
                printf("Breitengrad: %d* %d'%f W \n", EggL, EggL33, EgL55);
            } else {
                printf("Breitengrad: %d* %d'%f E \n", EggL, EggL33, EgL55);
            }
        }

        // Minus, Plus
        if (Len < 25) {
            char name[10];
            int data[12];
            sscanf (NMEA, "%[^,] %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s", name, &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7], &data[8], &data[9], &data[10], &data[11], &data[12]);
            char NMEA3[10];
            char x[10];
            strncpy(x, strtok(&data[6], NMEA3), 13);
            char NMEA2[10];
            double Term1 = atof(strtok(&data[3], NMEA2+1));
            double Term2 = atof(&x[2]);

            int LaG;
            double GLaG;
            double Eg;
            double Eg2;
            int Eg22;
            double Eg3;
            double Eg33;
            int Eg4;
            double Eg5;
            double Eg55;

            int LnG;
            double GLnG;
            double EgL;
            double EgL2;
            int EgL22;
            double EgL3;
            double EgL33;
            int EgL4;
            double EgL5;
            double EgL55;

            int Egg = (int)Eg;
            Egg = (Term1 / 100)*-1;
            Eg2 = (Term1 / 100)*-1;
            Eg3 = (Eg2 - Egg);
            Eg33 = Eg3 * 60;
            int Egg33 = (int)Eg33;
            Eg5 = Eg33 - Egg33;
            Eg55 = Eg5 * 60;

            if (Term1 > 0) {
                printf("Laengengrad: %d* %d'%f N \n", Egg, Egg33, Eg55);
            } else {
                printf("Laengengrad: %d* %d'%f S \n", Egg, Egg33, Eg55);
            }
            if (Term2 < 0) {
            int EggL = (int)EgL;
            EggL = (Term2 / 100)*-1;
            EgL2 = (Term2 / 100)*-1;
            EgL3 = (EgL2 - EggL);
            EgL33 = EgL3 * 60;
            int EggL33 = (int)EgL33;
            EgL5 = EgL33 - EggL33;
            EgL55 = EgL5 * 60;

            if (Term1 < 0) {
                printf("Laengengrad: %d* %d'%f W \n", EggL, EggL33, EgL55);
            } else {
                printf("Laengengrad: %d* %d'%f E \n", EggL, EggL33, EgL55);
            }
            } else {
            int EggL = (int)EgL;
            EggL = (Term2 / 100);
            EgL2 = (Term2 / 100);
            EgL3 = (EgL2 - EggL);
            EgL33 = EgL3 * 60;
            int EggL33 = (int)EgL33;
            EgL5 = EgL33 - EggL33;
            EgL55 = EgL5 * 60;

            if (Term2 < 0) {
                printf("Breitengrad: %d* %d'%f W \n", EggL, EggL33, EgL55);
            } else {
                printf("Breitengrad: %d* %d'%f E \n", EggL, EggL33, EgL55);
            }
            }

        }

    } else {

    // Plus Plus
    char name[10];
    int data[12];
    sscanf (NMEA, "%[^,] %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s", name, &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7], &data[8], &data[9], &data[10], &data[11], &data[12]);
    char NMEA3[10];
    char x[10];
    strncpy(x, strtok(&data[6], NMEA3), 13);
    char NMEA2[10];

    double Term1 = atof(strtok(&data[3], NMEA2+1));
    double Term2 = atof(&x[1]);

    int LaG;
    double GLaG;
    double Eg;
    double Eg2;
    int Eg22;
    double Eg3;
    double Eg33;
    int Eg4;
    double Eg5;
    double Eg55;

    int LnG;
    double GLnG;
    double EgL;
    double EgL2;
    int EgL22;
    double EgL3;
    double EgL33;
    int EgL4;
    double EgL5;
    double EgL55;

    int Egg = (int)Eg;
    Egg = (Term1 / 100);
    Eg2 = (Term1 / 100);
    Eg3 = (Eg2 - Egg);
    Eg33 = Eg3 * 60;
    int Egg33 = (int)Eg33;
    Eg5 = Eg33 - Egg33;
    Eg55 = Eg5 * 60;

    if (Term1 > 0) {
        printf("Laengengrad: %d* %d'%f N \n", Egg, Egg33, Eg55);
    } else {
        printf("Laengengrad: %d* %d'%f S \n", Egg, Egg33, Eg55);
    }
    int EggL = (int)EgL;
    EggL = (Term2 / 100);
    EgL2 = (Term2 / 100);
    EgL3 = (EgL2 - EggL);
    EgL33 = EgL3 * 60;
    int EggL33 = (int)EgL33;
    EgL5 = EgL33 - EggL33;
    EgL55 = EgL5 * 60;

    if (Term2 < 0) {
        printf("Breitengrad: %d* %d'%f W \n", EggL, EggL33, EgL55);
    } else {
        printf("Breitengrad: %d* %d'%f E \n", EggL, EggL33, EgL55);
    }

    }
  }
}




void USART1_IRQHandler(void) {
  int *pos;
    if (USART1->SR & USART_SR_RXNE) {
      char GPS = USART1->DR;     // Daten aus Daten Register and NMEA
      Daten[counter] = GPS; 
      counter++;
    }
}


void clear(void) {  // RX Zurücksetzen/Löschen
  int i;
  for (i = 0; i < MAX_LEN; i++) Daten[i] = 0;
  counter = 0;
}

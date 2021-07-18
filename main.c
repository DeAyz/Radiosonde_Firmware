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
  }
}




void USART1_IRQHandler(void) {
  int *pos;
    if (USART1->SR & USART_SR_RXNE) {
      char NMEA = USART1->DR;     // Daten aus Daten Register and NMEA
      Daten[counter] = NMEA; 
      counter++;
      printf("%c", NMEA);
    }
}



void clear(void) {  // RX Zurücksetzen/Löschen
  int i;
  for (i = 0; i < MAX_LEN; i++) Daten[i] = 0;
  counter = 0;
}

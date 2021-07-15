#include "stm32f10x.h"
#include "string.h"
#include "stdlib.h"
#include "stdarg.h"
#include <stdint.h>
#include "stdio.h"


void EnableTxRx(void){

// 1. Alternate Function f�r Pins Aktivieren und PORT A aktivieren.

RCC->APB2ENR |= (1<<0);     //Bit 0 (AF) 


RCC->APB2ENR |= (1<<2);     // Bit 2 (PORTA)
//

// 2. USART 1 aktivieren.
RCC->APB2ENR |= (1<<14);    // BIT 14

// 3. Pins PA9 and PA10 aktivieren. (PA10 Rx / PA9 Tx )
// MODE9 = 11 I Output mode, max speed 50 MHZ;
// CNF9 = 10 I Alternate function output Push-Pull
// MODE10 = 00 I Inpute mode
// CNF10 = 01 I Floating Input


GPIOA->CRH |= (1<<4);         // Bit 4
GPIOA->CRH |= (1<<5);         // Bit 5
GPIOA->CRH |= (1<<7);         // BIT 7
GPIOA->CRH &= ~(1<<0);        // BIT 0



GPIOA->CRH &= ~(1<<8);        // Bit 8
GPIOA->CRH &= ~(1<<9);        // Bit 9
GPIOA->CRH |= (1<<10);       // BIT 10
GPIOA->CRH &= ~(1<<11);       // BIT 11

// 4. Baudrate auf 9600 festlegen
// Clock = 24MHZ, Baudrate = 9600
// 24MHZ / (16*9600) =  156,25 -> HEX: 9C 
// 0,25*16 = 4 -> HEX: 4

USART1->BRR = 0x9C4;





// 5. USART Transmitter aktivieren
USART1->CR1 |= (1<<2);       // BIT 2

// 6.  USART1 Reciever aktivieren
USART1->CR1 |= (1<<3);       // Bit 3

// 7. USART1 aktivieren
USART1->CR1 |= (1<<13);       // Bit 13

USART1->CR1 |= (1<<7);     //TXE Enabled    // Wenn SR TXE = 1, dann senden
USART1->CR1 |= (1<<5);      //RXNE Enabled  // WENN SR RXNE =1, dann Lese daten register nicht voll


NVIC_EnableIRQ(USART1_IRQn);

}


int main(void) {

EnableTxRx();

}



void USART1_IRQHandler(void) {
while (1) {

if (USART1->SR & USART_SR_RXNE) {
uint8_t temp = USART1->DR;
USART1->DR = temp;
printf("%c", temp);
for(int i = 0; i < 500000; i++)


//for(i = 0; i < strlen(temp); i++){
//USART1->DR = temp;
//printf("An: \n", temp);
//}


while (! (USART1->SR & USART_SR_TC));
}

if (USART1->SR & USART_SR_TXE) {}
  }
}


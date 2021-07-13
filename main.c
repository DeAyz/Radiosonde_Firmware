#include "stm32f10x.h"

 


void EnableTxRx(void){

// 1. Alternate Function für Pins Aktivieren und PORT A aktivieren.

RCC->APB2ENR |= (1<<0);     //Bit 0 (AF) 


RCC->APB2ENR |= (1<<2);     // Bit 2 (PORTA)
//

// 2. USART 1 aktivieren.
RCC->APB2ENR |= (1<<14);    // BIT 14

// 3. Pins PA9 and PA10 aktivieren. (PA10 Input +pull up + ständiges reset) (PA9 Output)
// OUTPUT(CNF9 0:1)   ANALOG(MODE9 0:0)   INPUT(CNF10 1:0)  FL.RESET(MODE10 0:1)

GPIOA->CRH |= (1<<6);        // BIT 6
GPIOA->CRH |= (1<<8);        // BIT 8
GPIOA->CRH |= (1<<11);       // BIT 11

// 4. Baudrate auf 9600 festlegen
USART1->BRR |= (1<<2);          // BIT 2
USART1->BRR |= (1<<3);          // BIT 3
USART1->BRR |= (1<<6);          // BIT 6
USART1->BRR |= (1<<8);          // BIT 8
USART1->BRR |= (1<<10);         // Bit 10
USART1->BRR |= (1<<11);         // BIT 11
USART1->BRR |= (1<<12);         // BIT 12


// 5. USART Transmitter aktivieren
USART1->CR1 |= (1<<2);       // BIT 2

// 6.  USART1 Reciever aktivieren
USART1->CR1 |= (1<<3);       // Bit 3

// 7. USART1 aktivieren
USART1->CR1 |= (1<<13);       // Bit 13

USART1->CR1 |= (1<<7);     //TXE Enabled    // Wenn SR TXE = 1, dann senden
USART1->CR1 |= (1<<5);      //RXNE Enabled  // WENN SR RXNE =1, dann Lese daten register nicht voll

}

uint8_t Info(void) {

uint8_t x;

while (!(USART1->SR & (1<<5)));  // wait for rxne bit to set
x = USART1->DR; // Read the data, thos clears rxne too

return x;
}




int main(void) {

EnableTxRx();
    
  while(1) {

  uint8_t x = Info();

  }

return 0;
}
#include "./inc/main.h"
extern uint16_t bufStr[100];
extern uint16_t lenBuf;

void USART3_IRQHandler(void);

#define TxHelSize   (sizeof(hel) - 1)

char hel[] = "Hello Valera Diken hello!\r\n";

__IO uint8_t TxCounter1 = 0x00;
const char newline[] = "\r\n";

int main(void){
  USART_InitTypeDef USART_InitStructure;

  /* System Clocks Configuration */
  RCC_Configuration();
       
  /* NVIC configuration */
  NVIC_Configuration();

  /* Configure the GPIO ports */
  GPIO_Configuration();
  
  /* UART configuration */
  UART_Configuratuin();

  SystemInit();// 72MHz

  //USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

  while (1){
    ;
  }
}
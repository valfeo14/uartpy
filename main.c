#include "./inc/ur.h"

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

  SystemInit();// 72MHz

  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART3, &USART_InitStructure);
  USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
  USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
  USART_Cmd(USART3, ENABLE);

  while (1){
  	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
  	while(TxCounter1 < TxHelSize);
  	TxCounter1 = 0x00;
  	endStop();
  	delay(1000);
  }
}


void USART3_IRQHandler(void){
  if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET){
    /* Write one byte to the transmit data register */
    USART_SendData(USART3, hel[TxCounter1++]);

    if(TxCounter1 == TxHelSize)
    {
      /* Disable the USARTy Transmit interrupt */
      USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
    } 
                // func(); - функция обработчик*/
    }
}
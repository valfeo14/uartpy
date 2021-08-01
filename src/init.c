#include "../inc/init.h"


void RCC_Configuration(void){
   
  /* Enable GPIO clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
}

void GPIO_Configuration(void) {

  //USART3 :
  //pb10 TxD
  //pb11 RxD

  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Configure USART3 Rx as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
  
  /* Configure USART3 Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void UART_Configuratuin(void) {

  USART_InitTypeDef USART_InitStructure;
  
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART3, &USART_InitStructure);
  USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);// ENABLE ?
  //USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
  USART_Cmd(USART3, ENABLE);
}

void NVIC_Configuration(void) {

  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

  /* Enable the USART3 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

#include "../inc/uart_tool.h"

static uint16_t bufStr[100];
static uint16_t lenBuf;

uint16_t * get_bufStr(void){
	return (uint16_t *) bufStr;
}

uint16_t get_lenBuf(void){
	return lenBuf;
}

void set_lenBuf(uint16_t lB){
	lenBuf = lB;
}

void UART_sendChar(char ch){
	USART3->DR = ch;
	while(USART3->SR & USART_SR_TC);
}

void UART_SendStr(uint16_t lB){
	char * pointStr = (char *)bufStr;
	while(lB--){
		UART_sendChar(* pointStr);
		pointStr++;
	}
}

char UART_receiveChar(void){
	return (uint16_t)(USART3->DR & (uint16_t)0x01FF);
}

uint16_t UART_receiveStr(void){
	char data = (char)0x00;            // var data
	int16_t booly = (uint16_t)0x0000; // bool var
	uint16_t lB = (uint16_t)0x0000;    //len of buffer
	char * pointStr = (char *)bufStr;  // pointer to top ofbuffer

	while(booly >= 0){
		while(USART3->SR & USART_SR_RXNE);
		data = UART_receiveChar();
		* pointStr = data;
		switch(data){
			case '\r' :
				booly = 1;
				break;
			case '\n' :
				if (booly == 1) booly = -1;
				break;
			default :
				booly = 0;
		}
		pointStr++;
		lB++;
	}

	return lB;
}

void USART3_IRQHandler(void){
	//USART_ClearITPendingBit(USART3, USART_IT_RXNE);	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET){

		USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
		lenBuf = UART_receiveStr();
		UART_SendStr(lenBuf);
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	}
}

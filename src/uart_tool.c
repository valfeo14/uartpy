void UART_sendChar(char ch){
	USART3->DR = ch;
	while(USART3->SR & USART_SR_TC);
}

void UART_SendStr(char * str){
	while(*str) UART_sendChar(*str++);
}

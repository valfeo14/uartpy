#include "stm32f10x.h"
#include "stm32f10x_usart.h"

char * get_bufStr(void);
uint16_t get_lenBuf(void);
void set_lenBuf(uint16_t lB);
void UART_sendChar(char ch);
void UART_SendStr(uint16_t lB);
char UART_receiveChar(void);
uint16_t UART_receiveStr(void);
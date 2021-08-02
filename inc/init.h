#include "stm32f10x.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "system_stm32f10x.h" //void SystemInit(void)

void RCC_Configuration(void);
void GPIO_Configuration(void);
void UART_Configuratuin(void);
void NVIC_Configuration(void);
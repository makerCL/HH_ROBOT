/**
 *  @file  : main.c
 *
 *  @brief : Default main.c
 *
 *  @author: Francesco Varani
 *  @date  : 13 nov 2020
 */

#include "lib_uart.h"
#include "delay.h"
#include "apds9660.h"

#include "stm32f4xx.h"
#include "string.h"

			

int main(void)
{
	Delay_init();
	UART_lib_config(e_UART_2, DISABLE, 0, 0);
	apds_init();

	UART_lib_sendData("START\n", strlen("START\n"));

	while(1)
	{
		//__WFI();
	}
}

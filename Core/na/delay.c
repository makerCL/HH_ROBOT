/*
 *  @file  : delay.c
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 11 nov 2020
 */
#include "stm32f4xx.h"
#include "delay.h"
#include "lib_systick.h"

volatile uint32_t _req_delay_us;

/**
 * @brief Initializes the sys tick freq
 */
void Delay_init(void)
{
	_req_delay_us = 0;
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000000);
}

/**
 * @brief
 * @param delay
 */
void Delay_ms(uint16_t delay)
{
	do
	{
		Delay_us(1000);
		delay--;
	}while(delay);
}

/**
 * @brief
 * @param delay
 */
void Delay_us(uint16_t delay)
{
	_req_delay_us = delay;

	while(_req_delay_us);
}

/**
 * @brief The systick handler. In this case it lower the delay variable if was set
 * @note period is 1us
 */
void SysTick_Handler(void)
{
	if(_req_delay_us != 0)
	{
		_req_delay_us--;
	}
}

/*
 * line_driver.c
 *
 *  Created on: May 31, 2023
 *      Author: johna
 */

#include "line_driver.h"
#include "string.h"

void update_Line(line_drv_t* line_drv){
	if(GPIO_PIN_RESET == HAL_GPIO_ReadPin (line_drv->GPIOx, line_drv->GPIO_Pin)){
		line_drv->state = '0';
	} else if(GPIO_PIN_SET == HAL_GPIO_ReadPin (line_drv->GPIOx, line_drv->GPIO_Pin)){
		line_drv->state = '1';
	}
}

void print_LineF(line_drv_t* line_drv, UART_HandleTypeDef* huart){
	char recieved[25] = "\nLine:";
	HAL_UART_Transmit(huart,(uint8_t*) &recieved, strlen(recieved),1000);
	char state = (char)(line_drv->state);
	HAL_UART_Transmit(huart,(uint8_t*) &state, 1,1000);
	char line[25] = "\n\n\r";
	HAL_UART_Transmit(huart,(uint8_t*) &line, strlen(line),1000);
}


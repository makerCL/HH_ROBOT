/*
 * bluetooth_driver.c
 *
 *  Created on: May 23, 2023
 *      Author: johna
 */

#include "bluetooth_driver.h"
#include "string.h"

void updateStatus(blue_drv_t* blue_drv){
	if(*(blue_drv->blue_char_ptr) == '0'){
		blue_drv->status = '0';
	} else {
		blue_drv->status = '1';
	}
	*(blue_drv->blue_char_ptr) = '0';
}

void print_Blue(blue_drv_t* blue_drv, UART_HandleTypeDef* huart){
	char recieved[25] = "\nBlue: ";
	HAL_UART_Transmit(huart,(uint8_t*) &recieved, strlen(recieved),1000);
	char status = (char)(blue_drv->status);
	HAL_UART_Transmit(huart,(uint8_t*) &status, 1,1000);
	char line[25] = "\n\n\r";
	HAL_UART_Transmit(huart,(uint8_t*) &line, strlen(line),1000);
}


/*
 * encoder_driver.cpp
 *
 *  Created on: Jun 5, 2023
 *      Author: johna
 */

#include "encoder_driver.h"
#include "string.h"

encoder_drv_t init_encoder(uint16_t	GPIO_Pin1, GPIO_TypeDef* GPIOx1, uint16_t GPIO_Pin2, GPIO_TypeDef* GPIOx2, TIM_HandleTypeDef* htim, int32_t TPR){
	uint16_t TIME_LAST = __HAL_TIM_GET_COUNTER(htim);
	encoder_drv_t encoder_drv = {0,0, GPIO_Pin1, GPIOx1, GPIO_Pin2,	GPIOx2, htim, TIME_LAST, TPR, 0, 0};
	encoder_drv.LAST_COUNT = NewState(&encoder_drv);
	return encoder_drv;
}

void update_encoder(encoder_drv_t* encoder_drv){
	calc_Velocity_And_Timer_Update(encoder_drv, __HAL_TIM_GET_COUNTER(encoder_drv->htim));
	uint8_t NEW_COUNT = NewState(encoder_drv);
	if (NEW_COUNT - encoder_drv->LAST_COUNT == 1){
		encoder_drv->TOTAL_COUNT++;
	} else if (encoder_drv->LAST_COUNT - NEW_COUNT == 1 || (NEW_COUNT == 3 & encoder_drv->LAST_COUNT == 0)){
		encoder_drv->TOTAL_COUNT--;
	} else if (NEW_COUNT == 0 && encoder_drv->LAST_COUNT == 3){
		encoder_drv->TOTAL_COUNT++;
	}
	encoder_drv->LAST_COUNT = NEW_COUNT;
	calc_Position(encoder_drv);
}

void zero(encoder_drv_t* encoder_drv){
	encoder_drv->TOTAL_COUNT = 0;
}

/*void print_encoder(encoder_drv_t* encoder_drv, UART_HandleTypeDef* huart)
	char recieved[25] = "\nencoder: ";
	HAL_UART_Transmit(huart,(uint8_t*) &recieved, strlen(recieved),1000);
	char status = (char)(blue_drv->status);
	HAL_UART_Transmit(huart,(uint8_t*) &status, 1,1000);
	char line[25] = "\n\n\r";
	HAL_UART_Transmit(huart,(uint8_t*) &line, strlen(line),1000);
}*/


// private functions
void calc_Position(encoder_drv_t* encoder_drv){
	encoder_drv->pos = encoder_drv->TOTAL_COUNT/encoder_drv->TPR;
}


void calc_Velocity_And_Timer_Update(encoder_drv_t* encoder_drv, uint16_t time){
	encoder_drv->vel = 1/encoder_drv->TPR/(time - encoder_drv->TIME_LAST);
	encoder_drv->TIME_LAST = time;
}

uint8_t NewState(encoder_drv_t* encoder_drv){
	uint8_t gray = (HAL_GPIO_ReadPin (encoder_drv->GPIOx1, encoder_drv->GPIO_Pin1) << 1) | HAL_GPIO_ReadPin (encoder_drv->GPIOx2, encoder_drv->GPIO_Pin2);
    uint8_t binary = 0;
	while (gray != 0) {
        binary ^= gray;
        gray >>= 1;
    }
	return binary;
}


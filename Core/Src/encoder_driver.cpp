/*
 * encoder_driver.cpp
 *
 *  Created on: Jun 5, 2023
 *      Author: johna
 */

#include "encoder_driver.h"
#include "string.h"

encoder_drv_t init_encoder(uint16_t	GPIO_Pin1, GPIO_TypeDef* GPIOx1, uint16_t GPIO_Pin2, GPIO_TypeDef* GPIOx2, int32_t TPR){
	encoder_drv_t encoder_drv = {0,0,0, GPIO_Pin1, GPIOx1, GPIO_Pin2,	GPIOx2, TPR, 0};
	encoder_drv.LAST_ENCODER_COUNT = NewState(&encoder_drv);
	return encoder_drv;
}

void update_encoder(encoder_drv_t* encoder_drv){
	uint8_t NEW_COUNT = NewState(encoder_drv);
	if (NEW_COUNT - encoder_drv->LAST_ENCODER_COUNT == 1){
		encoder_drv->TOTAL_COUNT++;
	} else if ((encoder_drv->LAST_ENCODER_COUNT - NEW_COUNT == 1) || (NEW_COUNT == 3 && encoder_drv->LAST_ENCODER_COUNT == 0)){
		encoder_drv->TOTAL_COUNT--;
	} else if (NEW_COUNT == 0 && encoder_drv->LAST_ENCODER_COUNT == 3){
		encoder_drv->TOTAL_COUNT++;
	} else {
		//zero(encoder_drv);
	}
	encoder_drv->LAST_ENCODER_COUNT = NEW_COUNT;
}

void Update_Encoder_State(encoder_drv_t* encoder_drv){
//	uint16_t time = __HAL_TIM_GET_COUNTER(encoder_drv->htim);
//	encoder_drv->vel = (encoder_drv->TOTAL_COUNT - encoder_drv->LAST_COUNT)/encoder_drv->TPR/(time - encoder_drv->LAST_TIME);
//	encoder_drv->LAST_TIME = time;
//	encoder_drv->LAST_COUNT = encoder_drv->TOTAL_COUNT;
	encoder_drv->pos = encoder_drv->TOTAL_COUNT/encoder_drv->TPR;
}


void zero(encoder_drv_t* encoder_drv){
	encoder_drv->TOTAL_COUNT = 0;
	encoder_drv->LAST_COUNT = 0;
}

// private functions


uint8_t NewState(encoder_drv_t* encoder_drv){
	uint8_t gray = (HAL_GPIO_ReadPin(encoder_drv->GPIOx1, encoder_drv->GPIO_Pin1) << 1) | HAL_GPIO_ReadPin(encoder_drv->GPIOx2, encoder_drv->GPIO_Pin2);
    uint8_t binary = 0;
	while (gray != 0) {
        binary ^= gray;
        gray >>= 1;
    }
	return binary;
}


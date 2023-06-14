/*
 * motor_drive.c
 *
 *  Created on: May 23, 2023
 *      Author: johna
 */

#include "motor_driver.h"

void enable(motor_drv_t* motor_drv){
	HAL_TIM_PWM_Start(motor_drv->htim,motor_drv->chan_1);
	HAL_TIM_PWM_Start(motor_drv->htim,motor_drv->chan_2);
}

void disable(motor_drv_t* motor_drv){
	HAL_TIM_PWM_Stop(motor_drv->htim,motor_drv->chan_1);
	HAL_TIM_PWM_Stop(motor_drv->htim,motor_drv->chan_2);
}

void scaleNewPulse(motor_drv_t* motor_drv, int8_t val_8){
	motor_drv->pulse = ((int32_t)val_8)*(2*(int32_t)motor_drv->htim->Init.Period + 1)/256;
}

void NewPulse(motor_drv_t* motor_drv, int32_t val_32){
	if(val_32 >= (int32_t)motor_drv->htim->Init.Period){
		motor_drv->pulse =  motor_drv->htim->Init.Period/2;
	} else if (-val_32 >= (int32_t)motor_drv->htim->Init.Period){
		motor_drv->pulse =  -motor_drv->htim->Init.Period/2;
	} else {
		motor_drv->pulse = val_32/2;
	}

}

void setPWM(motor_drv_t* motor_drv){
	uint32_t ch1_pulse = 0;
	uint32_t ch2_pulse = 0;
	if(motor_drv->pulse > (int32_t) motor_drv->htim->Init.Period){
		ch1_pulse = motor_drv->htim->Init.Period;
		ch2_pulse = 0;
	}
	else if(-motor_drv->pulse > (int32_t) motor_drv->htim->Init.Period){
		ch1_pulse = 0;
		ch2_pulse = motor_drv->htim->Init.Period;
	}
	else if(motor_drv->pulse >= 0){
		ch1_pulse =  motor_drv->htim->Init.Period;
		ch2_pulse =  motor_drv->htim->Init.Period - (uint32_t)(motor_drv->pulse);
	}
	else if(motor_drv->pulse < 0){
		ch1_pulse =  motor_drv->htim->Init.Period - (uint32_t)(-motor_drv->pulse);
		ch2_pulse =  motor_drv->htim->Init.Period;
	}


	if (motor_drv->pulse >= 0) {
		ch1_pulse = motor_drv->htim->Init.Period;
		ch2_pulse = motor_drv->htim->Init.Period - motor_drv->pulse;
	} else {
		ch1_pulse = motor_drv->htim->Init.Period + motor_drv->pulse;
		ch2_pulse = motor_drv->htim->Init.Period;
	}

	if (ch1_pulse > motor_drv->htim->Init.Period) {
		ch1_pulse = motor_drv->htim->Init.Period;
		ch2_pulse = 0;
	} else if (ch2_pulse > motor_drv->htim->Init.Period) {
		ch1_pulse = 0;
		ch2_pulse = motor_drv->htim->Init.Period;
	}

	__HAL_TIM_SET_COMPARE(motor_drv->htim, motor_drv->chan_1, ch1_pulse);
	__HAL_TIM_SET_COMPARE(motor_drv->htim, motor_drv->chan_2, ch2_pulse);
}


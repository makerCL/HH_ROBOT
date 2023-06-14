/*
 * Navigation.h
 *
 *  Created on: Jun 13, 2023
 *      Author: johna
 */

#ifndef INC_NAVIGATION_H_
#define INC_NAVIGATION_H_

#include "stdint.h"
#include "stm32f4xx_hal.h"

typedef struct nav_drv {
	int32_t			x_tot_pos = 0;
	int32_t         y_tot_pos = 1000;
	int32_t			theta = 90;

	motor_drv_t* 	motor1;
	motor_drv_t* 	motor2;
	encoder_drv_t* 	encoder1;
	encoder_drv_t* 	encoder2;

	world_drv_t*	world;

	uint8_t			flag = 0;

} nav_drv_t;


typedef struct world_drv {
	int32_t			r_max = 1000;
	int32_t			r_min =	5;

	int32_t			x_home = 0;
	int32_t         y_home = 0;

} world_drv_t;

nav_drv_t nav_Init(motor_drv_t* motor1, motor_drv_t* motor2, encoder_drv_t* encoder1, encoder_drv_t*, encoder2);

void nav_Rot(nav_drv_t* nav_drv_t);

void nav_Lin(nav_drv_t* nav_drv_t);

void nav_Is_Task_Complete(nav_drv_t* nav_drv_t);

int32_t nav_Line_If_Rot(nav_drv_t* nav_drv_t, int32_t theta);



void nav_Move(nav_drv_t* nav_drv_t);

void nav_Is_Valid_Command(nav_drv_t* nav_drv_t);





#endif /* INC_NAVIGATION_H_ */

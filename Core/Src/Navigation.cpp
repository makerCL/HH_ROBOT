/*
 * Position.cpp
 *
 *  Created on: Jun 13, 2023
 *      Author: johna
 */



#include "Navigation.h"

nav_drv_t nav_Init(motor_drv_t* motor1, motor_drv_t* motor2, encoder_drv_t* encoder1, encoder_drv_t*, encoder2){

}

void nav_Rot(nav_drv_t* nav_drv_t);

void nav_Lin(nav_drv_t* nav_drv_t);

void nav_Is_Task_Complete(nav_drv_t* nav_drv_t);

int32_t nav_Line_If_Rot(nav_drv_t* nav_drv_t, int32_t theta);



void nav_Move(nav_drv_t* nav_drv_t);

void nav_Is_Valid_Command(nav_drv_t* nav_drv_t);



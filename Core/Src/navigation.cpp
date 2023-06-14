/*
 * Position.cpp
 *
 *  Created on: Jun 13, 2023
 *      Author: johna
 */



#include "navigation.h"

MotorController::MotorController(){
}

uint8_t MotorController::runController(float curr_posn) {
	float error = setpoint - curr_posn;
	error_sum = error_sum + error;

	uint8_t PWM = k_p * error + k_i * error_sum + k_d * (error - last_error);
	last_error = error;

	return PWM;
}


nav_drv_t nav_Init(motor_drv_t* motor1, motor_drv_t* motor2, encoder_drv_t* encoder1, encoder_drv_t* encoder2){
	int32_t y_start = 1000;

	MotorController PID1 = MotorController();
	PID1.k_p = 1;
	PID1.k_i = 0;
	PID1.k_d = 1;

	MotorController PID2 = MotorController();
	PID2.k_p = 1;
	PID2.k_i = 0;
	PID2.k_d = 1;

	world_drv_t world = {0,y_start,90,5, y_start, 0, y_start,10000,10000};

	return {motor1,motor2,encoder1,encoder2,&PID1,&PID2,&world,0};
}

void nav_Rot(nav_drv_t* nav_drv, float dtick){
	if(nav_drv->flag == 0){
		zero(nav_drv->encoder1);
		zero(nav_drv->encoder2);

		nav_drv->PID1->setpoint = -dtick;
		nav_drv->PID2->setpoint =  dtick;

		nav_drv->flag = 1;
	}
}

void nav_Lin(nav_drv_t* nav_drv, float dtick){
	if(nav_drv->flag == 0){
		zero(nav_drv->encoder1);
		zero(nav_drv->encoder2);

		nav_drv->PID1->setpoint =  dtick;
		nav_drv->PID2->setpoint =  dtick;

		nav_drv->flag = 1;
	}
}

void nav_Update_PID(nav_drv_t* nav_drv){
	scaleNewPulse(nav_drv->motor1,(*nav_drv->PID1).runController(nav_drv->encoder1->TOTAL_COUNT));
	scaleNewPulse(nav_drv->motor2,(*nav_drv->PID2).runController(nav_drv->encoder2->TOTAL_COUNT));
}

void nav_Update_Flag(nav_drv_t* nav_drv){
	float tolerance = 5;
	if((nav_drv->PID1->last_error <= tolerance && -nav_drv->PID1->last_error <= tolerance)||
	   (nav_drv->PID2->last_error <= tolerance && -nav_drv->PID2->last_error <= tolerance)){
		nav_drv->flag = 0;
	}
}



int32_t nav_Line_If_Rot(nav_drv_t* nav_drv, int32_t theta){

}


void nav_Update_World(nav_drv_t* nav_drv){

}

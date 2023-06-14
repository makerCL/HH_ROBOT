/*
 * Position.cpp
 *
 *  Created on: Jun 13, 2023
 *      Author: johna
 */



#include "navigation.h"
#include <cmath>


void nav_Rot(nav_drv_t* nav_drv, float deg){
	if(nav_drv->flag == 0){
		zero(nav_drv->encoder1);
		zero(nav_drv->encoder2);

		nav_drv->PID1->setpoint = -deg*nav_drv->world->ticksPerDeg;
		nav_drv->PID2->setpoint =  deg*nav_drv->world->ticksPerDeg;
		nav_drv->PID1->last_error = 100;
		nav_drv->PID2->last_error = 100;

		nav_drv->flag = 1;

		nav_drv->world->theta += deg;
	}
}

void nav_Lin(nav_drv_t* nav_drv, float inches){
	if(nav_drv->flag == 0){
		zero(nav_drv->encoder1);
		zero(nav_drv->encoder2);

		nav_drv->PID1->setpoint =  inches*nav_drv->world->ticksPerinch;
		nav_drv->PID2->setpoint =  inches*nav_drv->world->ticksPerinch;
		nav_drv->PID1->last_error = 100;
		nav_drv->PID2->last_error = 100;

		nav_drv->flag = 1;

		nav_drv->world->x_tot_pos += inches*cos(nav_drv->world->theta * M_PI / 180.0);
		nav_drv->world->y_tot_pos += inches*sin(nav_drv->world->theta * M_PI / 180.0);
	}
}

void nav_Update_PID(nav_drv_t* nav_drv){
	NewPulse(nav_drv->motor1,PID_runController(nav_drv->PID1,nav_drv->encoder1->TOTAL_COUNT));
	NewPulse(nav_drv->motor2,PID_runController(nav_drv->PID2,nav_drv->encoder2->TOTAL_COUNT));
}

void nav_Update_Flag(nav_drv_t* nav_drv){
	if((nav_drv->flag != 0) &&
	   (nav_drv->PID1->last_error <= nav_drv->PID1->tol && -nav_drv->PID1->last_error <= nav_drv->PID1->tol) &&
	   (nav_drv->PID2->last_error <= nav_drv->PID2->tol && -nav_drv->PID2->last_error <= nav_drv->PID2->tol)){
		nav_drv->flag = 0;
	}
}

int32_t PID_runController(PID_drv_t* PID_drv, int32_t curr_posn){
	int32_t error = PID_drv->setpoint - curr_posn;
	PID_drv->error_sum = PID_drv->error_sum + error;

	int32_t PWM = PID_drv->k_p * error + PID_drv->k_i * PID_drv->error_sum + PID_drv->k_d * (error - PID_drv->last_error);
	PID_drv->last_error = error;

	return PWM;
}

int16_t nav_Line_If_Rot(nav_drv_t* nav_drv, int16_t theta){
	return 7;
}


void nav_Update_World(nav_drv_t* nav_drv){

}

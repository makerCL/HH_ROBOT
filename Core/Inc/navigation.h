#ifndef INC_NAVIGATION_H_
#define INC_NAVIGATION_H_

#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "motor_driver.h"
#include "encoder_driver.h"

class MotorController {
	public:
		MotorController();
		float last_error = 0; // for derivative control
		float error_sum = 0;
		float setpoint = 0;

		float k_p = 0;
		float k_i = 0;
		float k_d = 0;

		uint8_t runController(float curr_posn);
	private:
};

typedef struct world_drv{
	int32_t			x_tot_pos;
	int32_t         y_tot_pos;
	int32_t			theta;

	int32_t			r_max;
	int32_t			r_min;

	int32_t			x_home;
	int32_t         y_home;

	int32_t			ticksPerDeg;
	int32_t         ticksPerinch;

} world_drv_t;

typedef struct nav_drv{
	motor_drv_t* 	motor1;
	motor_drv_t* 	motor2;
	encoder_drv_t* 	encoder1;
	encoder_drv_t* 	encoder2;
	MotorController* PID1;
	MotorController* PID2;

	world_drv_t*	world;
	uint8_t			flag;

} nav_drv_t;

nav_drv_t nav_Init(motor_drv_t* motor1, motor_drv_t* motor2, encoder_drv_t* encoder1, encoder_drv_t* encoder2);

void nav_Rot(nav_drv_t* nav_drv, float dtick);

void nav_Lin(nav_drv_t* nav_drv, float dtick);

void nav_Update_PID(nav_drv_t* nav_drv);

void nav_Update_Flag(nav_drv_t* nav_drv);



int32_t nav_Line_If_Rot(nav_drv_t* nav_drv, int32_t theta);

void nav_Update_World(nav_drv_t* nav_drv);







#endif /* INC_NAVIGATION_H_ */


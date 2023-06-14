#include "navigation.h"

MotorController::MotorController(){
};

uint8_t runController(float curr_posn) {
	float error = setpoint - curr_posn;
	error_sum = error_sum + error;

	uint8_t PWM = k_p * error + k_i * error_sum + k_d * (error - last_error);
	last_error = error;

	return PWM;
}

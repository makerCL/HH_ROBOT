#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "stm32f4xx_hal.h"

class MotorController {
	public:
		float last_error = 0; // for derivative control
		float error_sum = 0;
		float setpoint = 0;

		float k_p = 0;
		float k_i = 0;
		float k_d = 0;
	private:
};

#endif

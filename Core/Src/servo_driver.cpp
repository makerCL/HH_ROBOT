
#include "servo_driver.h"




Servo::Servo(TIM_HandleTypeDef* timerHandle, uint32_t channel) : htim(timerHandle), timer_channel(channel){
	initialize();
}

void Servo::initialize(){
	HAL_TIM_PWM_Start(htim, timer_channel);
	// Set the initial position of the servo to 90 degrees
	clock_freq = HAL_RCC_GetHCLKFreq();
	prescaler = htim->Init.Prescaler;
	ARR = htim->Instance->ARR;

    setPulseWidth(90);
}

void Servo::setPulseWidth(uint32_t position_deg) {
	  // Ensure the input is within the valid range
	  if (position_deg > max_rot) {
		  position_deg = max_rot;
	  }

	  // Compute pulse width based on desired position
	  float pulse_width_ms = min_pulse + (max_pulse - min_pulse) * position_deg / max_rot;

	  // Compute compare register value
	  uint32_t compare_value = static_cast<uint32_t>((clock_freq / (prescaler + 1)) * pulse_width_ms / 1000);

	  __HAL_TIM_SET_COMPARE(htim, timer_channel, compare_value);
}

#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

#include "stm32f4xx_hal.h"


class Servo {
public:

  Servo(TIM_HandleTypeDef* PWMHandle, uint32_t channel, TIM_HandleTypeDef* StopwatchHandle);
  void initialize();
  void setPulseWidth(uint32_t position_deg);

  float min_pulse = 0.5; //ms
  float max_pulse = 2.5; //ms
  uint16_t max_rot = 180; //degrees

  uint8_t processing_flag; // used to indicate if servo is in motion

  void startTimer();
  float elapsedTime();

private:
  TIM_HandleTypeDef* htim;
  uint32_t timer_channel;
  TIM_HandleTypeDef* hSW;


  uint32_t clock_freq;
  uint32_t prescaler;
  uint32_t ARR;

  uint32_t start_time;
};


#endif

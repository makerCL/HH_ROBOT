/*
 * bluetooth_driver.c
 *
 *  Created on: May 23, 2023
 *      Author: johna
 */

#include "bluetooth_driver_motor.h"

void updateStatusMotor(blue_drv_t* blue_drv){
	if(blue_drv->blue_char[0] == '0' &&  blue_drv->blue_char[1] == '\0' &&
	   blue_drv->blue_char[2] == '\0' && blue_drv->blue_char[3] == '\0'){
		blue_drv->status = '0';
	} else {
		blue_drv->status = '1';
	}
}


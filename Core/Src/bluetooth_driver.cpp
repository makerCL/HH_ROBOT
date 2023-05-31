/*
 * bluetooth_driver.c
 *
 *  Created on: May 23, 2023
 *      Author: johna
 */

#include "bluetooth_driver.h"

void updateStatus(blue_drv_t* blue_drv){
	if(*(blue_drv->blue_char_ptr) == '0'){
		blue_drv->status = '0';
	} else {
		blue_drv->status = '1';
	}
	*(blue_drv->blue_char_ptr) = '0';
}

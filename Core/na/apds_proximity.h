/*
 *  @file  : apds_proximity.h
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 13 nov 2020
 */

#ifndef INC_APDS_PROXIMITY_H_
#define INC_APDS_PROXIMITY_H_

#include <stdint.h>

typedef enum
{
	e_proximity_error_none,
	e_proximity_error_saturation,
	e_proximity_error_data_not_valid,
	e_proximity_error_max
}t_proximity_error;

extern void apds_start_proximity_engine(void);
extern void apds_proximity_read_result(uint8_t from_interrupt);

extern void apds_proximity_set_ppulse(uint8_t flag);
extern void apds_proximity_set_control(uint8_t flag);
extern void apds_proximity_set_config2(uint8_t flag);
extern void apds_proximity_set_config3(uint8_t flag);
extern void apds_proximity_set_proximity_low_threshold(uint8_t flag);
extern void apds_proximity_set_proximity_high_threshold(uint8_t flag);
extern void apds_proximity_set_proximity_offset_ur(uint8_t flag);
extern void apds_proximity_set_proximity_offset_dl(uint8_t flag);


#endif /* INC_APDS_PROXIMITY_H_ */

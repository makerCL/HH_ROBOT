/*
 *  @file  : apds_register.h
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 13 nov 2020
 */

#ifndef INC_APDS_REGISTER_H_
#define INC_APDS_REGISTER_H_

#include <stdint.h>

#define APDS_READ_FROM_INTERRUPT	(1u)
#define APDS_READ_FROM_POLLING		(0u)

typedef enum
{
	e_register_ENABLE = 0x80,
	e_register_ATIME = 0x81,
	e_register_WTIME = 0x83,
	e_register_AILTL = 0x84,
	e_register_AILTH = 0x85,
	e_register_AIHTL = 0x86,
	e_register_AIHTH = 0x87,
	e_register_PILT = 0x89,
	e_register_PIHT = 0x8B,
	e_register_PERS = 0x8C,
	e_register_CONFIG1 = 0x8D,
	e_register_PPULSE = 0x8E,
	e_register_CONTROL = 0x8F,
	e_register_CONFIG2 = 0x90,
	e_register_ID = 0x92,		/* ID Register (0x92) */
	e_register_STATUS = 0x93,
	e_register_CDATAL = 0x94,
	e_register_CDATAH = 0x95,
	e_register_RDATAL = 0x96,
	e_register_RDATAH = 0x97,
	e_register_GDATAL = 0x98,
	e_register_GDATAH = 0x99,
	e_register_BDATAL = 0x9A,
	e_register_BDATAH = 0x9B,
	e_register_PDATA = 0x9C,
	e_register_POFFSET_UR = 0x9D,
	e_register_POFFSET_DL = 0x9E,
	e_register_CONFIG3 = 0x9F,
	e_register_GPENTH = 0xA0,
	e_register_GEXTH = 0xA1,
	e_register_GCONF1 = 0xA2,
	e_register_GCONF2 = 0xA3,
	e_register_GOFFSET_U = 0xA4,
	e_register_GOFFSET_D = 0xA5,
	e_register_GOFFSET_L = 0xA7,
	e_register_GOFFSET_R = 0xA9,
	e_register_GPULSE = 0xA6,
	e_register_GCONF3 = 0xAA,
	e_register_GCONF4 = 0xAB,
	e_register_GFLVL = 0xAE,
	e_register_GSTATUS = 0xAF,
	e_register_IFORCE = 0xE4,
	e_register_PICLEAR = 0xE5,
	e_register_CICLEAR = 0xE6,
	e_register_AICLEAR = 0xE7,
	e_register_GFIFO_U = 0xFC,
	e_register_GFIFO_D = 0xFD,
	e_register_GFIFO_L = 0xFE,
	e_register_GFIFO_R = 0xFF,
}t_list_apds_register;

typedef struct
{
	t_list_apds_register	id;
	uint8_t					adress;
}t_struct_apds_register;

#endif /* INC_APDS_REGISTER_H_ */

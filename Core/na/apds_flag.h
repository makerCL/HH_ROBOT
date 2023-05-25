/*
 *  @file  : apds_flag.h
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 13 nov 2020
 */

#ifndef INC_APDS_FLAG_H_
#define INC_APDS_FLAG_H_

/* Enable register 0x80 */
#define ENABLE_REGISTER_GEN		(1<<6)	/* Gesture Enable */
#define ENABLE_REGISTER_PIEN	(1<<5)	/* Proximity Interrupt Enable. */
#define ENABLE_REGISTER_AIEN	(1<<4)	/* ALS Interrupt Enable.  */
#define ENABLE_REGISTER_WEN		(1<<3)	/* Wait Enable.  */
#define ENABLE_REGISTER_PEN		(1<<2)	/* Proximity Detect Enable.  */
#define ENABLE_REGISTER_AEN		(1<<1)	/* ALS Enable. */
#define ENABLE_REGISTER_PON		(1<<0)	/* Power ON */

/* Persistence Register (0x8C) */
#define PERSISTENCE_REGISTER_PPERS (0xF0)	/* Proximity Interrupt Persistence. Controls rate of proximity interrupt to the host processor. */
#define PERSISTENCE_REGISTER_APERS (0x0F)	/* ALS Interrupt Persistence. Controls rate of Clear channel interrupt to the host processor. */

/* Configuration Register One (0x8D) */
#define CONFIG1_REGISTER_WLONG	(1<<1)

/* Proximity Pulse Count Register (0x8E) */
#define PROXIMITY_PULSE_REGISTER_PPLEN	(0xC0)
#define PROXIMITY_PULSE_REGISTER_PPULS	(0x3F)

/* Control Register One (0x8F) */
#define CONTROL_REGISTER_ONE_LDRIVE		(0xC0)
#define CONTROL_REGISTER_ONE_PGAIN		(0x0C)
#define CONTROL_REGISTER_ONE_AGAIN		(0x03)

/* Configuration Register Two (0x90) */
#define CONFIG2_PSIEN		(1<<7)	/* Proximity Saturation Interrupt Enable */
#define CONFIG2_LDRIVE		(1<<6)	/* Clear Photodiode Saturation Interrupt Enable */
#define CONFIG2_LED_BOOST	(0x30)	/* Additional LDR current during proximity and gesture LED pulses */

#define CONFIG2_PROXIMITY_VALID_FLAG	(CONFIG2_PSIEN | CONFIG2_LED_BOOST)

/* Status Register 0x93 */
#define STATUS_REGISTER_CPSAT	(1<<7)	/* Clear Photodiode Saturation */
#define STATUS_REGISTER_PGSAT	(1<<6)	/* Indicates that an analog saturation event occurred during a previous proximity or gesture cycle.  */
#define STATUS_REGISTER_PINT	(1<<5)	/* Proximity Interrupt.  */
#define STATUS_REGISTER_AINT	(1<<4)	/* ALS Interrupt.  */
#define STATUS_REGISTER_GINT	(1<<2)	/* Gesture Interrupt. */
#define STATUS_REGISTER_PVALID	(1<<1)	/* Proximity Valid. */
#define STATUS_REGISTER_AVALID	(1<<0)	/* ASL Valid. */

/* Configuration Three Register (0x9F) */
#define CONFIG3_PCMP			(1<<5)
#define CONFIG3_SAI				(1<<4)
#define CONFIG3_PMASK_U			(1<<3)
#define CONFIG3_PMASK_D			(1<<2)
#define CONFIG3_PMASK_L			(1<<1)
#define CONFIG3_PMASK_R			(1<<0)

/* Gesture Configuration One Register (0xA2) */
#define GESTURE_CONFIG1_REGISTER_GFIFOTH	(0xC0)
#define GESTURE_CONFIG1_REGISTER_GEXMSK		(0x3C)
#define GESTURE_CONFIG1_REGISTER_GEXPERS	(0x03)

/* Gesture Configuration Two Register (0xA3) */
#define GESTURE_CONFIG2_REGISTER_GGAIN		(0x60)
#define GESTURE_CONFIG2_REGISTER_GLDRIVE	(0x18)
#define GESTURE_CONFIG2_REGISTER_GWTIME		(0x05)

/* Gesture Pulse Count and Length Register (0xA6) */
#define GESTURE_PULSE_COUNT_LENGTH_REGISTER_GPLEN	(0xC0)
#define GESTURE_PULSE_COUNT_LENGTH_REGISTER_GPULSE	(0x3F)

/* Gesture Configuration Three Register (0xAA) */
#define GESTURE_CONFIG3_GDIMS	(0x03)

/* Gesture Configuration Four Register (0xAB) */
#define GESTURE_CONFIG4_GIEN	(1<<1)
#define GESTURE_CONFIG4_GMODE	(1<<0)

/* Gesture Status Register (0xAF) */
#define GESTURE_STATUS_REGISTER_GFOV	(1<<1)
#define GESTURE_STATUS_REGISTER_GVALID	(1<<0)

#endif /* INC_APDS_FLAG_H_ */

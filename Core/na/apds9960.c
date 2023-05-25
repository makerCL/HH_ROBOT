/**
 *  @file  : apds9960.c
 *	
 *  @brief : Source code to interface an apds9960
 *
 *  @author: Francesco Varani
 *  @date  : 13 nov 2020
 */
#include "lib_i2c.h"
#include "apds9660.h"
#include "apds_flag.h"
#include "delay.h"

#include "apds_proximity.h"

/** ---------------------------------- DEFINE ------------------------ */
#define		I2C_OWN_ADDRESS	(0x00)
#define		APDS_ADDRESS	(0x39)

/* Turn on pin*/
#define APDS_INTERRUPT_PIN		GPIO_Pin_11
#define APDS_INTERRUPT_PORT		GPIOA
#define APDS_INTERRUPT_SOURCE	EXTI_PinSource11
#define APDS_EXT_LINE			EXTI_Line11

/** ---------------------------------- PRIVATE DATA ------------------------ */
static volatile t_apds_status _apds_actual_status;
static const t_i2c_number	_apds_i2c = e_i2c_1;
static uint8_t				_apds_engine = e_apds_engine_none;

/** ---------------------------------- PUBLIC FUNCTIONS IMPLEMENTATION ------------------------ */
/**
 * @brief Initialize the communcation channel with the sensor and the input pin to receive interrupt on falling edge
 */
ErrorStatus apds_init(void)
{
	ErrorStatus apds_initialized = ERROR;
	uint8_t		read_data;
	uint8_t 	byte_read;

	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Enable SYSCFG's APB interface clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_EXTIT, ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);
	EXTI_StructInit(&EXTI_InitStructure);

	/* Init interrupt pin*/
	GPIO_InitStructure.GPIO_Pin = APDS_INTERRUPT_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(APDS_INTERRUPT_PORT, &GPIO_InitStructure);

	/* connect pin to ext */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, APDS_INTERRUPT_SOURCE);

	/* set ext  12 */
	EXTI_InitStructure.EXTI_Line = APDS_EXT_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;		/* yeah rising or falling ? */
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* INTERRUPT Init */
	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	/* to check ! */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			/* to check ! */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* init i2c 1*/
	lib_I2C_init(_apds_i2c, I2C_OWN_ADDRESS, Delay_us);

	/* Initialzie time 5.7ms */
	Delay_ms(6u);
	_apds_actual_status = e_apds_sleep;

	byte_read = apds_read_generic(e_register_ID, &read_data);
	if ((byte_read != 0)
		&& (read_data == APDS_IDENTIFICATION))
	{
		apds_initialized = SUCCESS;
	}

	return apds_initialized;
}

/**
 *
 * @return
 */
t_apds_status apds_get_state(void)
{
	return _apds_actual_status;
}

/**
 *
 * @param address
 * @param data
 */
void apds_write_generic(uint8_t address, uint8_t data)
{
	uint8_t command[] = {address, data};

	lib_I2C_write_nbyte(_apds_i2c, command, 2, APDS_ADDRESS);
}

/**
 *
 * @param address
 * @param data
 * @return
 */
uint8_t apds_read_generic(uint8_t address, uint8_t* data)
{
	uint8_t byte_read = 0;
	uint8_t data_read[] = {address, *data};

	byte_read = lib_I2C_read_nbyte(_apds_i2c, data_read, APDS_ADDRESS);

	return byte_read;
}

/**
 *
 */
void apds_start_engine(uint8_t engine_flag)
{
	if ((engine_flag & e_apds_engine_proximity) == e_apds_engine_proximity)
	{
		apds_start_proximity_engine();
		_apds_actual_status = e_apds_prox;
	}

	if ((engine_flag & e_apds_engine_gesture) == e_apds_engine_gesture)
	{

	}

	if ((engine_flag & e_apds_engine_color) == e_apds_engine_color)
	{

	}

	_apds_engine = engine_flag;
}
/** ---------------------------------- IRQ HANDLER IMPLEMENTATION ------------------------ */
/**
 * @note From datasheet - INT pin Interrupt - open drain (active low)
 */
void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(APDS_EXT_LINE) == SET)
	{
		EXTI_ClearITPendingBit(APDS_EXT_LINE);

		if (GPIO_ReadInputDataBit(APDS_INTERRUPT_PORT, APDS_INTERRUPT_PIN) == RESET)
		{
			/*
			 * what to do?
			 * depends on the engine running?
			 * so the status ?
			 */
			switch(_apds_actual_status)
			{
				case e_apds_sleep:
				{
					/* */
					apds_write_generic(e_register_PICLEAR, 0x00);
				}
				break;
				case e_apds_idle:
				{
					/* */
					apds_write_generic(e_register_CICLEAR, 0x00);
				}
				break;
				case e_apds_prox:
				{
					/* */
					apds_proximity_read_result(APDS_READ_FROM_INTERRUPT);
					apds_write_generic(e_register_PICLEAR, 0x00);
				}
				break;
				case e_apds_gesture:
				{
					/* */
					apds_write_generic(e_register_CICLEAR, 0x00);
				}
				break;
				case e_apds_wait:
				{
					/* */
					apds_write_generic(e_register_CICLEAR, 0x00);
				}
				break;
				case e_apds_color:
				{
					/* */
					apds_write_generic(e_register_CICLEAR, 0x00);
				}
				break;
				default:
				case e_apds_max:
				{
					/* */
					apds_write_generic(e_register_CICLEAR, 0x00);
				}
				break;
			}
		}

	}
}

/*------------------------------------------------------------------------------
File Name: sensor.h
Author: Sunny Taksande
Date: 27 June 2011
Pupose: Header file for sensor apis.
------------------------------------------------------------------------------*/

#ifndef _SENSOR
#define _SENSOR

/*------------ Include header files ------------------------------------------*/

#include "sensor_common.h"

/* Enumerated types for sensor Addresses */
typedef enum {
	SMOKE = 0x01,
	LPG = 0x02,

//	SMOKE_02 = 0x02,
	SMOKE_03 = 0x03,
	SMOKE_04 = 0x04,
	SMOKE_05 = 0x05,
	SMOKE_06 = 0x06,
	SMOKE_07 = 0x07,
	SMOKE_08 = 0x08,
	SMOKE_09 = 0x09,
	SMOKE_0A = 0x0A,
	SMOKE_0B = 0x0B,
	SMOKE_0C = 0x0C,
	SMOKE_0D = 0x0D,
	SMOKE_0E = 0x0E,
	SMOKE_0F = 0x0F,
	
	LPG_01 = 0x11,
	LPG_02 = 0x12,
	LPG_03 = 0x13,
	LPG_04 = 0x14,
	LPG_05 = 0x15,
	LPG_06 = 0x16,
	LPG_07 = 0x17,
	LPG_08 = 0x18,
	LPG_09 = 0x19,
	LPG_0A = 0x1A,
	LPG_0B = 0x1B,
	LPG_0C = 0x1C,
	LPG_0D = 0x1D,
	LPG_0E = 0x1E,
	LPG_0F = 0x1F

	
} SNSR_NAME;

/* Enumerated types for LPG sensor valve status */
typedef enum {
	OPEN  = 0x01,
	CLOSE = 0x02
} LPG_VALVE_STATUS;

/* Enumerated types for sensor alarm  */
typedef enum {
	ALARM_PRESENT  = 0x01,
	NO_ALARM = 0x02
} ALARM_AVAILABLE;

/* Enumerated types for sensor alarm status */
typedef enum {
	ON  = 0x01,
	STOP = 0x02
} ALARM_STATUS;

/*------------ Function Declarations------------------------------------------*/

int sensor_detect_kahuna(SNSR_NAME name);
int sensor_turn_off(SNSR_NAME name);
int sensor_turn_on(SNSR_NAME name);
int sensor_read_threshold(SNSR_NAME name, uint8_t *threshvalue);
int sensor_set_threshold(SNSR_NAME name, uint8_t threshvalue);
int sensor_read_alarm(SNSR_NAME name, ALARM_AVAILABLE *alarmAvailable);
int sensor_stop_alarm(SNSR_NAME name);
int sensor_LPG_detectvalve(SNSR_NAME name, LPG_VALVE_STATUS *valveStatus);
int sensor_LPG_closevalve(SNSR_NAME name);
int sensor_init(int ionum );
int rs485_init(int ionum );

#endif

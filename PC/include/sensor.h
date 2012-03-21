/*------------------------------------------------------------------------------
File Name: sensor.h
Author: Sunny Taksande
Date: 27 June 2011
Pupose: Header file for sensor apis.
------------------------------------------------------------------------------*/

#ifndef _SENSOR
#define _SENSOR

/*------------ Include header files ------------------------------------------*/

#include "common.h"

/* Enumerated types for sensor Addresses */
typedef enum {
	SMOKE = 0x02,
	LPG = 0x01,
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
int sensor_LPG_detectvalve(LPG_VALVE_STATUS *valveStatus);
int sensor_LPG_closevalve();

#endif

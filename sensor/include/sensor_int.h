/*------------------------------------------------------------------------------
File Name: sensor_int.h
Author: Sunny Taksande
Date: 27 June 2011
Purpose: Header File for sensor internal functions
------------------------------------------------------------------------------*/

#ifndef _SENSOR_INT
#define _SENSOR_INT

/*------------ Include header files ------------------------------------------*/
#include "sensor.h"

/*------------ Macros and Global variables -----------------------------------*/

#define CODESIZE 8

/* Enumerated types for sensor function codes */
typedef enum {
	/* func code for checking health of snsr */
	DETECT_SNSR = 0x01,

	/* func code for checking if the snsr is Kahuna */
        DETECT_KAHUNA_SNSR = 0x02,

	/* func codes for reading and setting threshold */
        SET_THRESHOLD = 0x03,
        GET_THRESHOLD = 0x04,

	/* func codes for reading and stoping alarm */
	READ_ALARM = 0x05,
	STOP_ALARM = 0x06,

        /* func code for getting LPG valve status */
	LPG_GETVALVE_STATUS = 0x07,

        /* func code for closing LPG valve */
        LPG_CLOSE_VALVE = 0x08,

        /* func codes to turn sensing on/off */
	TURN_OFF = 0x09,
	TURN_ON = 0x0A
} SNSR_FUNC_CODES;

/* Enumerated types for Error failures */
typedef enum {
        LRC_FAILURE = 0x01,
        FUNC_CODE_UNSUPPORTED = 0x02,
        THRESHOLD_VALUE_UNSUPPORTED = 0x03,
        VALVE_CONTROL_UNSUPPORTED = 0x04,
	ALARM_FAILURE = 0x05,
	COMMUNICATION_FAILURE = 0x06,
	NON_KAHUNA_SENSOR = 0x07
} SNSR_ERR_CODES;

/*----------------- Function Declarations -----------------------------------*/
int rs485_slave_detect(SNSR_NAME name);
int rs485_slave_config(SNSR_NAME name, SNSR_FUNC_CODES funCode);
int rs485_slave_read(SNSR_NAME name, SNSR_FUNC_CODES funCode, u_char* value,
                        uint8_t length);
int rs485_slave_write(SNSR_NAME name, SNSR_FUNC_CODES funCode, u_char* value,
                        uint8_t length);

#endif

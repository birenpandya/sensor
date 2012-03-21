/*------------------------------------------------------------------------------
File Name: sensor.c
Author: Sunny Taksande
Date: 27 June 2011
Pupose: Implementation of master slave sensor library apis.
------------------------------------------------------------------------------*/

/*------------ Include Files -------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "sensor_int.h"


/*------------ Function definitions-------------------------------------------*/

/*
Functions to send the command to a particular sensor.
*/

int sensor_detect_kahuna(SNSR_NAME name)
{
  return (rs485_slave_detect(name));
}

int sensor_turn_off(SNSR_NAME name)
{
  return (rs485_slave_config(name, TURN_OFF)); 
}

int sensor_turn_on(SNSR_NAME name)
{
  return (rs485_slave_config(name, TURN_ON));
}

int sensor_set_threshold(SNSR_NAME name, uint8_t threshvalue)
{
 return (rs485_slave_write(name, SET_THRESHOLD, &threshvalue, 1));
}

int sensor_read_threshold(SNSR_NAME name, uint8_t* threshvalue)
{
  return (rs485_slave_read(name, GET_THRESHOLD, threshvalue, 1));
}

int sensor_read_alarm(SNSR_NAME name, ALARM_AVAILABLE *alarmAvailable)
{
int i = RETRY_COUNT;
int status = SUCCESS;
while(i)
{	
	status = rs485_slave_read(name, READ_ALARM, (u_char*)alarmAvailable, 1);
	if( status == SUCCESS )
	{
		break;
	}
	else {
		i--;
	}
}
return status;
}

int sensor_stop_alarm(SNSR_NAME name)
{
  return (rs485_slave_config(name, STOP_ALARM));
}

int sensor_LPG_detectvalve(SNSR_NAME name, LPG_VALVE_STATUS *valveStatus)
{
 return (rs485_slave_read(name, LPG_GETVALVE_STATUS, (u_char*)valveStatus, 1));
}

int sensor_LPG_closevalve(SNSR_NAME name)
{
 return (rs485_slave_config(name, LPG_CLOSE_VALVE));
}

int sensor_init(int ionum)
{
	return rs485_init(ionum);
}

/*------------------------------------------------------------------------------
File Name: modbus_rs485.h
Author: Biren Pandya
Date: 22 June 2011
Pupose: Header file for exposed apis of modbus RS485 communication
------------------------------------------------------------------------------*/

#ifndef _MODBUS_RS485
#define _MODBUS_RS485

#include "sensor_common.h"

/*------------ Macros --------------------------------------------------------*/
#define MAX_ASCIIFRAME_SIZE 40

/*------------ Function Declarations------------------------------------------*/

int modbusRS485_init(int);
int modbusRS485_exit(int);
int modbusRS485_send(u_char address, u_char function, u_char *data, uint8_t nbytes);
int modbusRS485_recv(u_char *address, u_char *function, u_char *data, uint8_t* nbytes);

#endif

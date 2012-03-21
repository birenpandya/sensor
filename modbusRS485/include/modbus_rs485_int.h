/*------------------------------------------------------------------------------
File Name: modbus_rs485_int.h
Author: Biren Pandya
Date: 22 June 2011
Purpose: Header file for internal functions used in modbus RS485 communication
------------------------------------------------------------------------------*/

#ifndef _MODBUS_RS485_INT
#define _MODBUS_RS485_INT

#include "sensor_common.h"

/*------------ Macros --------------------------------------------------------*/

#define START_BYTE ':'
#define END_BYTE1 0x0D
#define END_BYTE2 0x0A

#define ADDR_INDEX 0
#define FUNC_INDEX 1
#define DATALEN_INDEX 2
#define DATA_INDEX 3

#define LRC_BYTE_SIZE 1
#define ASCII_CODE_SIZE 2       
#define START_BYTE_OFFSET 0 
#define ADDRESS_OFFSET 1
#define FUNCTION_OFFSET (ADDRESS_OFFSET + ASCII_CODE_SIZE)
#define DATA_OFFSET  (FUNCTION_OFFSET + ASCII_CODE_SIZE)

/*------------ Function Declarations------------------------------------------*/

void  byte2ascii(u_char byte, u_char *ascii);
void bytes2ascii(u_char* source, u_char* destination, uint8_t nbytes);
u_char get_hexByte(u_char asciiCode);
void ascii2byte(u_char *source, u_char *destination);
void ascii2bytes(u_char *source, u_char *destination, uint8_t nbytes);
u_char compute_LRCByte(u_char *data, uint8_t nbytes);
u_char get_LRCByte(u_char address, u_char function, u_char *data, uint8_t nbytes);
void ascii_dump(u_char *asciiBuffer, uint8_t nbytes);
void hex_dump(u_char address, u_char function, u_char *data, uint8_t nbytes);
void str_copy(void* dest, const void* src, size_t count) ;
int decode_recv_data( u_char *asciiFrameBuffer,u_char *address, u_char *function, u_char *data,uint8_t *nbytes, int num_bytes);

#endif

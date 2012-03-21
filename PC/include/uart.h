/*------------------------------------------------------------------------------
File Name: uart.h
Author: Biren Pandya
Date: 22 June 2011
------------------------------------------------------------------------------*/
#ifndef _UART
#define _UART

#include "common.h"

/*------------ Function Declarations------------------------------------------*/

int uart_init(void);
int uart_exit(void);
int uart_read(u_char* buffer, uint8_t nbytes);
int uart_write(u_char* buffer, uint8_t nbytes);

#endif 

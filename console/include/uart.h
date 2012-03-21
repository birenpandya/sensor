/*------------------------------------------------------------------------------
File Name: uart.h
Author: Biren Pandya
Date: 22 June 2011
------------------------------------------------------------------------------*/
#ifndef _UART
#define _UART

#include "sensor_common.h"
/*------------ Macros and Global variables -----------------------------------*/
#define UART_DEVICE "/dev/ttyS0"
#define MILLI_SECONDS 1000


//#define MIN_NUM_BYTES_TO_READ 1
#define MIN_NUM_BYTES_TO_READ 11
#define WAIT_DATA_TO_READ 0

/* Defined timeout for Select Call for uart read */
#define TIME_IN_SEC 1
#define TIME_IN_MILLSEC 000
#define TIME_IN_UCSEC TIME_IN_MILLSEC * 1000

//static int uart_fd = -1;

struct uart_port_with_fd
{
        const char *name;
        int uart_fd;

};


/*------------ Function Declarations------------------------------------------*/

int uart_init(int ionum);
int uart_exit(int ionum);
int uart_read(int ionum,u_char* buffer, uint8_t nbytes);
int uart_write(int ionum,u_char* buffer, uint8_t nbytes);
int ptz_init(void);
int ptz_write(int);
int ptz_exit(void);

#endif 

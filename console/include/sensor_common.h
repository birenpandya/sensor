/*------------------------------------------------------------------------------
File Name: common.h
Author: Sunny Taksande
Date: 22 June 2011
Purpose: Common header file for common definitions
------------------------------------------------------------------------------*/

#ifndef _SENSOR_COMMON
#define _SENSOR_COMMON

/*------------ Include Files -------------------------------------------------*/

#include <stdint.h>
#include <stdlib.h>
#include "common.h"

/*********************system settings***************/


#define PTZ_GPIO_DEVICE "/dev/ptz"
#define RETRY_COUNT 5
#define PTZLIB_SUCCESS 1     
#define PTZLIB_FAILURE 0       
#define ERROR_PRINTS 0

#define RS232_DEVICE  0x01
#define RS485_DEVICE  0x02
#define RS485_DEVICE_READ_MODE 0x03
#define RS485_DEVICE_WRITE_MODE 0x04


//#define DETECT 1
#define MODBUS_DEBUG 0
#define KEEP_GPIO_SET 0

int baud_rate;
//#define BAUD_RATE B19200
//#define BAUD_RATE B9600


#define SNSR_NW_1 0 /* snsr01 &02  */
#define SNSR_NW_2 1 /* snsr 11,12,04,05 */

#define EUART_SUCCESS 1
#define MODBUS_SUCCESS 1

#define EUART_PORT_NUM     		-1      /* PORT NUMBR not permitted */
#define EUART_OPEN_FD           	-2      /* No such file FD */
#define EUART_OPEN_SIG           	-3      /* No such process */
#define EUART_OPEN_SETATTR            	-4      /* Interrupted system call */
#define EUART_EXIT_FD			-5	/* PORT NUMBER not permitted */
#define EUART_EXIT_CLOSE              	-6      /* Write CLOSE error */
#define EUART_WRITE_FD            	-7      /* list too long */
#define EUART_WRITE_BUFF          	-8      /* Invalid Write Buffer or number of bytes */
#define EUART_WRITE_FLUSH	        -9      /* Write Flush error */
#define EUART_WRITE_FAIL          	-10     /* No child processes */
#define EUART_READ_FD          		-11     /* Read fd fails */
#define EUART_READ_BUFF          	-12     /* Memory is invalid */
#define EUART_READ_TIMEOUT          	-13     /* READ time out denied */
#define EUART_READ_FLUSH          	-14      /* Bad address */
#define EMODBUS_INIT        	 	-15      /* uart init failed  */
#define EMODBUS_EXIT           		-16      /* modbus exit failed  */
#define EMODBUS_ADDR_FUNC          	-17      /* Wrong ADD or Func is passed  */
#define EMODBUS_WRITE           	-18      /*  */
#define EMODBUS_LRC          		-19      /* Wrong LRC recived  */
#define EMODBUS_FRAME_LEN               -20      /* wrong  data received */ 
#define EMODBUS_END_BYTES               -21       /*  no End bytes found in frame */    
#define ESNSR_SEND_FUN_MISMATCH		-22	/*Function code not supported */
#define EUART_GPIO_FAIL			-23    /*Function for gpioset failed */





#endif

/*------------------------------------------------------------------------------
File Name: sensor_int.c
Author: Sunny Taksande
Date: 27 June 2011
Pupose: Implementation of internal functions for master slave sensor library.
------------------------------------------------------------------------------*/

/*------------ Include Files -------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "sensor_int.h"
#include "modbus_rs485.h"

/*------------ Macros and global variables------------------------------------*/

u_char kahunaSerialNo[CODESIZE] = {'a', 'u', 'r', 'i', 'o', 'n', '0', '1'};
int errorNo = 0;
int ioport=0;
//#define DELAY_ 1

/*------------ Function definitions------- -----------------------------------*/

int rs485_init(int ionum)
{
return (modbusRS485_init(ionum));
}	


/*
Function to check whether the sensor is alive.
*/



int rs485_slave_detect(SNSR_NAME name)
{
  uint8_t recvAddr, recvFun, length; 	
  u_char slaveSerialNo[CODESIZE] = {0};
  int status = SUCCESS;	

  length = CODESIZE;

/*  if (modbusRS485_init(ioport) != SUCCESS) {
        printf("\n rs485_slave_detect: modbusRS485_init failed %d", ioport);
	errorNo = COMMUNICATION_FAILURE;
        return FAILURE;
  }
*/
  /* Send the command */
  if (modbusRS485_send(name, DETECT_KAHUNA_SNSR, NULL, 0) != SUCCESS) {
        printf("\n rs485_slave_detect: modbusRS485_send failed\n");
	errorNo = COMMUNICATION_FAILURE;
        status = FAILURE;
	goto RETURN;
  }

  /* Receive the response */
  if (modbusRS485_recv(&recvAddr, &recvFun, slaveSerialNo, &length)
	 != SUCCESS) {
        printf("\n rs485_slave_detect: modbusRS485_recv failed\n");
	errorNo = COMMUNICATION_FAILURE;
        status = FAILURE;
	goto RETURN;
  }

  /* Check the response */
  if (recvFun != DETECT_KAHUNA_SNSR) {
        printf("\n rs485_slave_detect: Error Code : %02x\n", slaveSerialNo[0]);
	errorNo = slaveSerialNo[0];
        status = FAILURE;
	goto RETURN;
  }

  /* Compare the serial no to confirm whether the device is a Kahuna device */
  if (memcmp(slaveSerialNo, kahunaSerialNo, CODESIZE) != 0) {
        printf("\n rs485_slave_detect: Serial No not matched\n");
	errorNo = NON_KAHUNA_SENSOR;
        status = FAILURE;
  }

RETURN:

  /*if (modbusRS485_exit() != SUCCESS) {
        printf("\n rs485_slave_detect: modbusRS485_exit failed");
  }*/	

  return status;
}

/*
Function to configure the slave sensor.
*/
int rs485_slave_config(SNSR_NAME name, SNSR_FUNC_CODES funCode)
{
  uint8_t recvAddr, recvFun, errCode, length; 	
  int status = SUCCESS;	

  length = sizeof(errCode);

#ifdef DETECT
  if (rs485_slave_detect(name) != SUCCESS) {
        printf("\n rs485_slave_config: rs485_slave_detect failed\n");
        return FAILURE;
  }
#endif

#ifdef DELAY_

sleep(DELAY_);

#endif


 /* if (modbusRS485_init(ioport) != SUCCESS) {
        printf("\n rs485_slave_config: modbusRS485_init failed");
	errorNo = COMMUNICATION_FAILURE;
        return FAILURE;
  }*/

  /* Send the command */
  if (modbusRS485_send(name, funCode, NULL, 0) != SUCCESS) {
        printf("\n rs485_slave_config: modbusRS485_send failed\n");
	errorNo = COMMUNICATION_FAILURE;
        status = FAILURE;
	goto RETURN;
  }

  /* Receive the response */
  if (modbusRS485_recv(&recvAddr, &recvFun, &errCode, &length) != SUCCESS) {
        printf("\n rs485_slave_config: modbusRS485_recv failed\n");
	errorNo = COMMUNICATION_FAILURE;
        status = FAILURE;
	goto RETURN;
  }

  /* Check the response */
  if (recvFun != funCode) {
        printf("\n rs485_slave_config: Error Code : %02x\n", errCode);
	errorNo = errCode;
        status = FAILURE;
  }

RETURN:
/*
  if (modbusRS485_exit() != SUCCESS) {
        printf("\n rs485_slave_config: modbusRS485_exit failed");
  }	
*/
  return status;
}


/*
Function to read from slave sensor.
*/
int rs485_slave_read(SNSR_NAME name, SNSR_FUNC_CODES funCode, u_char* value, 
			uint8_t length)
{
  uint8_t recvAddr, recvFun; 	
  int status = SUCCESS;	
  recvAddr = '\0';
  recvFun = '\0';

#ifdef DETECT
	 status = rs485_slave_detect(name)
	if(status < SUCCESS) {
		#if ERROR_PRINTS       
		 printf("\n rs485_slave_read: rs485_slave_detect failed\n");
		#endif
        return status;
 	 }
#endif

#ifdef DELAY_

sleep(DELAY_);

#endif

  /* Send the command */

      status = modbusRS485_send(name, funCode, NULL, 0);
        if(status  < SUCCESS) {
                #if ERROR_PRINTS
                printf("\n rs485_slave_read: modbusRS485_send failed\n");
                #endif
                errorNo = status;
         }
        else {   
                 status = modbusRS485_recv(&recvAddr, &recvFun, value, &length);
                if(status  < SUCCESS) {
                        #if ERROR_PRINTS      
                        printf("\n rs485_slave_read: modbusRS485_recv failed\n");
                        #endif
                        errorNo = status;
                }
                else if (recvFun != funCode) {
                    #if ERROR_PRINTS 
                         printf("\n rs485_slave_read: Error Code : %02x recvFun code: %02x \n", value[0],recvFun);
                  #endif
                         errorNo = value[0];
                         status = ESNSR_SEND_FUN_MISMATCH ;
                }
        }
  return status;
}

/*
Function to write into slave sensor.
*/
int rs485_slave_write(SNSR_NAME name, SNSR_FUNC_CODES funCode, u_char* value, 
			uint8_t length)
{

  uint8_t recvAddr, recvFun, errCode; 	
  int status = SUCCESS;	

#ifdef DETECT
  if (rs485_slave_detect(name) != SUCCESS) {
        printf("\n rs485_slave_write: rs485_slave_detect failed\n");
        return FAILURE;
  }
#endif

#ifdef DELAY_

sleep(DELAY_);

#endif
 
 /* if (modbusRS485_init(ioport) != SUCCESS) {
        printf("\n rs485_slave_write: modbusRS485_init failed");
	errorNo = COMMUNICATION_FAILURE;
        return FAILURE;
  }*/

  /* Send the command */
  if (modbusRS485_send(name, funCode, value, length) <= SUCCESS) {
        printf("\n rs485_slave_write: modbusRS485_send failed\n");
	errorNo = COMMUNICATION_FAILURE;
        status = FAILURE;
	goto RETURN;
  }

  length = sizeof(errCode);

  /* Receive the response */
  if (modbusRS485_recv(&recvAddr, &recvFun, &errCode, &length) <= SUCCESS) {
        printf("\n rs485_slave_write: modbusRS485_recv failed\n");
	errorNo = COMMUNICATION_FAILURE;
        status = FAILURE;
	goto RETURN;
  }

  /* Check the response */
  if (recvFun != funCode) {
        printf("\n rs485_slave_write: Error Code : %02x\n", errCode);
	errorNo = errCode;
        status = FAILURE;
  }

RETURN:
/*
  if (modbusRS485_exit() != SUCCESS) {
        printf("\n rs485_slave_write: modbusRS485_exit failed");
  }
*/
  return status;
}

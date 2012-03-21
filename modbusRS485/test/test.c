/*------------------------------------------------------------------------------
       
File Name: test.c
Author: Sunny Taksande
Date: 23 June 2011
Purpose: sample program for testing modbus RS485 communication
------------------------------------------------------------------------------*/

/*------------ Include Files -------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "modbus_rs485.h"


/*------------ Function definitions ------------------------------------------*/

int main(void)
{
//	u_char data[2]={0x06,0x07};
	char data[50];	
	u_char address, function;	
	uint8_t size;
	int status = 1;
	

	if (modbusRS485_init(0) != 1)
		{

		printf("test main: modbusRS485_init failed \n");
		status = FAILURE;
		}

	size = sizeof(data);
while(1)
{
//	memset(data,'\0',sizeof(data));

#if 1
	status = modbusRS485_send((u_char)0x05, (u_char)0x05,NULL,(uint8_t)0);
		if(status <= 0)
		 {
		printf("test main: modbusRS485_send failed [%d]\n",status);
		status = FAILURE;
		}
#endif
#if 1
		status =modbusRS485_recv((u_char*)&address, (u_char*)&function, data, &size);
		if(status <= 0){
			printf("test main: modbusRS485_recv failed[%d]\n ",status);
			status = FAILURE;
		}
#endif
#if 0
	sleep(1);

	 if (modbusRS485_send((u_char)0x02, (u_char)0x05,NULL,(uint8_t)0)
                 != SUCCESS) {

                printf("test main: modbusRS485_send failed \n");
                status = FAILURE;
        }
        size = sizeof(data);
	memset(data,'\0',sizeof(data));

        if (modbusRS485_recv((u_char*)&address, (u_char*)&function, data, &size)
                 != SUCCESS) {

                printf("test main: modbusRS485_recv failed \n");
                status = FAILURE;
        }

        sleep(1);


	
         if (modbusRS485_send((u_char)0x02, (u_char)0x08,NULL,(uint8_t)0)
                 != SUCCESS) {

                printf("test main: modbusRS485_send failed \n");
                status = FAILURE;
        }
        size = sizeof(data);
	memset(data,'\0',sizeof(data));

        if (modbusRS485_recv((u_char*)&address, (u_char*)&function, data, &size)
                 != SUCCESS) {

                printf("test main: modbusRS485_recv failed \n");
                status = FAILURE;
        }





        sleep(1);

         if (modbusRS485_send((u_char)0x13, (u_char)0x04,NULL,(uint8_t)0)
                 != SUCCESS) {

                printf("test main: modbusRS485_send failed \n");
                status = FAILURE;
        }
        size = sizeof(data);
	uint8_t no_bytes = 30;
	memset(data,'\0',sizeof(data));
        if (modbusRS485_recv((u_char*)&address, (u_char*)&function, data, &no_bytes)
                 != SUCCESS) {

                printf("test main: modbusRS485_recv failed \n");
                status = FAILURE;
        }
#endif
        sleep(1);
	printf("++\n");


}
/*
        if (modbusRS485_exit() != SUCCESS) {

		printf("test main: modbusRS485_init failed \n");
		status = FAILURE;
	}
	
*/
	return status;
}

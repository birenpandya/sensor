/*------------------------------------------------------------------------------
File Name: test.c
Author: Sunny Taksande
Date: 23 June 2011
Purpose: sample program for testing uart communication
------------------------------------------------------------------------------*/

/*------------ Include Files -------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "sensor_common.h"
#include "uart.h"

#define UART_PORT 0

/*------------ Function definitions ------------------------------------------*/
u_char buffer_t1[30];
unsigned int tp = 0  ;

void test_write();


       u_char rr[9]="012345678";
       u_char r1[11]=":040500F7\r\n";
       u_char s1[13]=":04050102F4\r\n";
       u_char r2[11]=":050500F6\r\n";
       u_char s2[13]=":05050102F3\r\n";
       u_char r3[11]=":060500F5\r\n";
       u_char s3[13]=":06050102F2\r\n";
       u_char rx[11]=":010500FA\r\n";
        u_char sx[13]=":01050101F8\r\n";

        u_char r0[11]=":020500F9\r\n";
        u_char s0[13]=":02050101F7\r\n";
        u_char r4[11]=":110500EA\r\n";
        u_char s4[13]=":11050102E7\r\n";
        u_char r5[11]=":120500E9\r\n";
        u_char s5[13]=":12050102E6\r\n";
        u_char r6[11]=":130500E8\r\n";
        u_char s6[17]=":13050102E5\r\n";
        int status;

//#define BAUD_RATE B19200

int main(int argc, char *argv[])
{

	unsigned long count;
	count = 0;
	int temp = 0;
	int i =0 ;       
	int reset = 0;
	int bd = atoi(argv[1]);
        int dc1 = atoi(argv[2]);
        int dc2 = atoi(argv[3]);

	baud_rate = bd;
	printf("bd is set to %d\n",baud_rate);
	ptz_init();
	ptz_write(RS485_DEVICE_WRITE_MODE);
	status = uart_init(UART_PORT) ;
	printf("\n V.2.2: delay: %d \n",dc1);
	if(status <= 0 )
	{
                printf("\nmodbusRS485_init: uart_init failed:%d \n",status);
                return  FAILURE;
        }
		dc2 =dc2*1000;
		dc1 =dc1*1000;
	printf("Delay set is Before write %d \t after write %d \n",dc1,dc2);
	while(1)
	{
//	ptz_write(RS485_DEVICE_WRITE_MODE);
          //      usleep(dc);
#if 1
	status = uart_write(UART_PORT,r2,11);
	if(status < SUCCESS){
                printf("\nsensor write failed Error:%d \n ",status);
                status = FAILURE;
         }
	usleep(dc1);
#endif
	ptz_write(RS485_DEVICE_READ_MODE);
     // usleep(dc2);
#if 1 
	temp = uart_read(UART_PORT,buffer_t1, 1);
         if(temp > 0){
		printf("\nbuff contains : \n");
		  for(i = 0; i <= temp; i++)
			  printf("\t%c\t ",buffer_t1[i]);
	 }
	 else{
		printf("uart read : error %d \n",temp);
	}

     #endif 
//	usleep(500);
//	ptz_write(RS485_DEVICE_WRITE_MODE);
	sleep(1);
	printf("\n ++ %d \n",++tp);


	}
}


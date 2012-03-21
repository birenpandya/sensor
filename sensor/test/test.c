/*------------------------------------------------------------------------------
File Name: test.c
Author: Sunny Taksande
Date: 27 June 2011
Purpose: sample program for testing master slave sensor communication
------------------------------------------------------------------------------*/

/*------------ Include Files -------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include "sensor.h"


#define DELAY_ 	1
#define uDELAY 1000000

/*------------ Function definitions ------------------------------------------*/

int main(int argc, char **argv)
{
	int status = SUCCESS;
	uint8_t threshold_value = 0x10 ;
	ALARM_AVAILABLE snsr_alarm_available = NO_ALARM;
	SNSR_NAME SNSR = LPG_01;

	LPG_VALVE_STATUS valve_status = 0;
        int i = 0;

	printf("v1.3 %s %d\n", argv[1], argc);
	i = atoi(argv[1]);
	#if 1 
	if(argc > 2)
	{
		switch(argv[1][0]) {
			case '0':
				i = 0;
				break;

			case '1':
				i = 1;
				break;
			case '2':
				i = 2;
				break;
			case '3':
				i = 3;
				break;
			case '4':
				i = 4;
				break;
			case '5':
				i = 5;
				break;
			case '6':
				i = 6;
				break;
			case '7':
				i = 7;
				break;
			default:
				i = 0;
				break;
		}
	}
#endif
	printf(" port data: %s [%d]\n", argv[1], i);
	sensor_init(i);
int x;
while (1) {
//for( x=0;x<10;x++ ){
#if 1

#ifdef DELAY_

	usleep(uDELAY);

#endif

        status = sensor_read_alarm(SNSR, &snsr_alarm_available) ;
          
	    if(status < SUCCESS){
                printf("For [%d] -sensor_read_alarm error:%d.\n",SNSR,status);
                status = FAILURE;
        }

	else if(snsr_alarm_available== 1 )
		{
			printf("Alaram");
		} 
        else {
                printf("sensor_alarm value : %2x \n\n",snsr_alarm_available);
        }
#endif


#if  0
	if( sensor_read_threshold(SNSR, &threshold_value)!= SUCCESS) {
		printf("test main(): sensor_read_threshold failed \n");
		status = FAILURE;
	}
	else {  
		printf("test main():sensor_read_threshold value: %2x \n",threshold_value);
	}


#endif


#if 0
	if( sensor_set_threshold(SNSR, threshold_value) != SUCCESS) {
        	printf("test main(): sensor_set_thresold failed \n");
		status = FAILURE;
	}
	else {
		printf("test main():sensor_set_threshold value: %2x \n",threshold_value);
	}	
	

#endif
	

#if 0
	if(sensor_LPG_detectvalve(SNSR, &valve_status) != SUCCESS) {
        	printf("test main(): sensor_get valve status failed \n");
		status = FAILURE;
		}
	else {
		printf("test main():sensor_valve status value : %2x \n",valve_status);
	}
	
#endif

#if 0
	if(sensor_LPG_closevalve(SNSR) != SUCCESS ) {
		printf("test_main():sensor_SNSR_closevalve failed.\n");
		status = FAILURE;
	}	
	else {
		printf("test_main(): senser_SNSR_valve closed.\n");
	}

#endif

#if 0 
        if(sensor_stop_alarm(SNSR) != SUCCESS ) {
                printf("test_main():sensor_stop_alarm failed.\n");
                status = FAILURE;
        }       
        else {
                printf("test_main(): senser_alarm stop.\n");
        }

#endif

#if 0
       if (sensor_turn_on(SNSR) != SUCCESS) {
                printf("test main(): sensor_turn_on failed \n");
                status = FAILURE;
        }       

#endif 
        

#if 0 
        if (sensor_turn_off(SNSR) != SUCCESS) {
                printf("test main(): sensor_turn_off failed \n");
                status = FAILURE;
        }       

#endif
	//printf("Executed :%d  time \n", i);
//	printf(" :%d \n", i);
#if 0
switch (i)
{
        case 1:         SNSR = SMOKE;
                break;
        case 2:         SNSR = LPG;
                break;
        default :
                i=0;
                printf("++\n");
                break;
        }

#endif

# if SNSR_NW_2

	switch (i) 
{
	case 1:		SNSR = LPG_02;
		break;
	case 2: 	SNSR = LPG_07;
		break;	
	case 3:		SNSR = SMOKE_05;
		break;
/*	case 4:		SNSR = LPG_01;
		break;
	case 5:
			SNSR = SMOKE_08;
		break;
	case 6:
			SNSR = LPG_07;
		break; 
*/	default : 
		i=0;	
		printf("\n++\n");
		break;
	}
#endif
#if SNSR_NW_1

        switch (i)
{
        case 1:         SNSR = SMOKE;
                break;
        case 2:         SNSR = LPG;
                break;
 default :
                i=0;
                printf("++\n");
                break;
}
#endif
	i++;
	}

}

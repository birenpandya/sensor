/*------------------------------------------------------------------------------
File Name: modbus_rs485_int.h
Author: Biren Pandya
Date: 22 June 2011
Purpose: Function definitions for modbus internal functions.
------------------------------------------------------------------------------*/

/*------------ Include Files -------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#include "modbus_rs485_int.h"

/*------------ Function Definitions-------------------------------------------*/

void bytes2ascii(u_char* source, u_char* destination, uint8_t nbytes)
{
        int i,j;
        u_char ascii_tab[16] = {48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70};
	j=1;
	for(i = 0; i < nbytes; i++)
        {
        for (j = 1; j >= 0; j--)
	 {
		 *(destination+j) = *(source+i) & 0x0F;
                    destination[j] = ascii_tab[destination[j]];
                    source[i] = source[i] >> 4;
                 }
	 	 destination += ASCII_CODE_SIZE;
        }
}


/*
Function to get hexbyte of an ascii character.
*/
u_char get_hexByte(u_char asciiCode)
{

      u_char ascii[23]= {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
      u_char  i;
	for(i=0;i<22;i++)
	{
		if (asciiCode ==ascii[i])
		{
               	 return (u_char)i;
		}
	}
}




/*
Function to convert an ascii byte/char to a hex byte.

void ascii2byte(u_char *source, u_char *destination)
{
	*(destination) = (get_hexByte(source[0]) << 4);
	*(destination) = *(destination) | (get_hexByte(source[1]));
}
 
//	Function to convert n number of ascii bytes/chars to hex bytes.
void ascii2bytes(u_char *source, u_char *destination, uint8_t nbytes)
{
	u_int i;
	for (i = 0; i < nbytes; i++) {
		ascii2byte(&source[i * ASCII_CODE_SIZE], &destination[i]);
	}
}
*/
/*
Function to convert n number of ascii bytes/chars to hex bytes.
*/
void ascii2bytes(u_char *source, u_char *destination, uint8_t nbytes)
{
       int i;
        for (i = 0; i < nbytes; i++) {
        destination[i] = (get_hexByte(source[(i * ASCII_CODE_SIZE)+ 0]) << 4);
        destination[i] = destination[i] | (get_hexByte (source[(i * ASCII_CODE_SIZE) +1]));

        }
}

/*
Function to compute LRC on a data buffer.
*/
u_char compute_LRCByte(u_char *data, uint8_t nbytes)
{
        u_int i;
        u_char nLRC = 0;

        for (i = 0; i < nbytes; i++) {
                nLRC += *data++;
        }
        return (u_char)(-nLRC);
}

/*
Function to create the buffer and return LRC byte .
*/
u_char get_LRCByte(u_char address, u_char function, u_char* data, uint8_t nbytes)
{
       int i;
        u_char aduBuffer[50] = {0};

        /* put the ADU in buffer and compute LRC */
        aduBuffer[0] = address;
        aduBuffer[1] = function;

	if (data != NULL) {
               /* 2 bytes for address and function */
               for (i = 2; i < (nbytes + 2); i++) {
                        aduBuffer[i] = data[i - 2];
                }
        } else {
		/* in case if there is no data */
		aduBuffer[2] = 0 ;
		nbytes = 1;
	}
        return (compute_LRCByte(aduBuffer, nbytes + 2));	
}

/*
Function to print the ascii buffer.
*/
void ascii_dump(u_char *asciiBuffer, uint8_t nbytes)
{
        u_int i;

        for (i = 0; i < nbytes; i++) {
                printf(" %c", asciiBuffer[i]);
        }
}
/*
Function to print the hex bytes
*/
void hex_dump(u_char address, u_char function, u_char *data, uint8_t nbytes)
{
        u_int i;
        printf("Address: %02x, Function: %02x, Data: ", address, function);

	if (data != NULL) {
	        for (i = 0; i < nbytes; i++) {
        	        printf(" %02x ", data[i]);
	        }
	}
        printf("\n");
}


void str_copy(void* dest, const void* src, size_t count) {
        char* dst8 = (char*)dest;
        char* src8 = (char*)src;

        while (count--) {
            *dst8++ = *src8++;
        }
    }

/*   removed Functions
******************
//Function to create the buffer and return LRC byte .
u_char get_LRCByte(u_char address, u_char function, u_char* data, uint8_t nbytes)
{
        u_int i;
        u_char aduBuffer[50] = {0};

        // put the ADU in buffer and compute LRC 
        aduBuffer[0] = address;
        aduBuffer[1] = function;

        if (data != NULL) {
               // 2 bytes for address and function 
               for (i = 2; i < (nbytes + 2); i++) {
                        aduBuffer[i] = data[i - 2];
                }
        } else {
                // in case if there is no data 
                aduBuffer[2] = 0 ;
                nbytes = 1;
        }

        return (compute_LRCByte(aduBuffer, nbytes + 2));

}


 
Function to ascii encode a single hex byte.

void  byte2ascii(u_char byte, u_char *ascii)
{
        int i;
        u_char ascii_tab[16] = {48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70};

        for (i = 1; i >= 0; i--)
        {
                ascii[i] = byte & 0x0F;
                ascii[i] = ascii_tab[ascii[i]];
                byte = byte >> 4;
        }
}
void bytes2ascii(u_char* source, u_char* destination, uint8_t nbytes)
{
        u_int i;

        for(i = 0; i < nbytes; i++)
        {
                byte2ascii(source[i], destination);
                destination += ASCII_CODE_SIZE;
        }
}
*/




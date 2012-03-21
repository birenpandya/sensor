/*------------------------------------------------------------------------------
File Name: common.h
Author: Sunny Taksande
Date: 22 June 2011
Purpose: Common header file for common definitions
------------------------------------------------------------------------------*/

#ifndef _COMMON
#define _COMMON

/*------------ Include Files -------------------------------------------------*/

#include <stdint.h>
#include <stdlib.h>


/*Enumeration for return status */

typedef enum {
	TIMEOUT = -2,
        FAILURE = -1,
        SUCCESS = 1
} RETURN_STATUS;

extern int errorNo;

#endif

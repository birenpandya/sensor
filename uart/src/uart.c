/*------------------------------------------------------------------------------
File Name: uart.c
Author: Biren Pandya
Date: 22 June 2011
Purpose: implemntation of serial device read and write functions
------------------------------------------------------------------------------*/

/*------------ Include Files -------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <termios.h>
#include <sys/mman.h>




/*************** User Defined HEADER file *************************************/

#include "uart.h"
#include "sensor_common.h"

#define MODBUSPIN_FD "/dev/irqlat"
#define MEMFED "/dev/mem"

/*------------ Function Definitions-------------------------------------------*/
static int ptzgpio_fd = -1; //gpio device

static  int modbuspin_fd = -1;
static int mem_fd = -1;

/*
A dummy signal handler for FASYNC
*/

void signal_handler_IO (int status)
{
	;
}


int setnonblock(int sock) {
   int flags;
   flags = fcntl(sock, F_GETFL, 0);
   if (-1 == flags)
   {
        printf("Flag set to -1 \n");
        return -1;
   }
   return fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}


struct uart_port_with_fd uart_ports[] = {
        {"/dev/tts/1", -1},
        {"/dev/ttyS1", -1},
        {"/dev/ttyS2", -1},
        {"/dev/ttyS3", -1},
        {"/dev/ttyS4", -1},
        {"/dev/ttyS5", -1},
        {"/dev/ttyS6", -1},
        {"/dev/ttyS7", -1}
};


/*
Function to initialize serial terminal device. 
*/
int uart_init(int ionum)
{
	ionum = 0;
   	struct sigaction saio;
	struct termios my_termios;
	int status = EUART_SUCCESS;

        /* return if already initialized */
	if (uart_ports[ionum].uart_fd != -1) {
		status = EUART_PORT_NUM;
	//	return status;
	}
	else
	{
		uart_ports[ionum].uart_fd = open(uart_ports[ionum].name, O_RDWR | O_NOCTTY);
		printf("Opening %d %s \n", ionum, uart_ports[ionum].name);
        	if (uart_ports[ionum].uart_fd < 0) {
                	printf("uart_init: Failed to open device %s\n", uart_ports[ionum].name);
                	status = EUART_OPEN_FD;
		}
		else {
	        /* install the serial handler before making the device asynchronous */
	        saio.sa_handler = signal_handler_IO;
	        sigemptyset(&saio.sa_mask);   //saio.sa_mask = 0;
	        saio.sa_flags = 0;
	        saio.sa_restorer = NULL;
		if( sigaction(SIGIO, &saio, NULL) != 0){
			status = EUART_OPEN_SIG;
		}
		else{

			/* allow the process to receive SIGIO */
			fcntl(uart_ports[ionum].uart_fd, F_SETOWN, getpid());
			/* Make the file descriptor asynchronous (the manual page says only
			O_APPEND and O_NONBLOCK, will work with F_SETFL...) */
			fcntl(uart_ports[ionum].uart_fd, F_SETFL, FASYNC);

			tcgetattr(uart_ports[ionum].uart_fd, &my_termios);
			// NOTE: you may want to save the port attributes 
			tcflush(uart_ports[ionum].uart_fd, TCIFLUSH);
	
		//	cfsetispeed(&my_termios, baud_rate);
		//	cfsetospeed(&my_termios, baud_rate);

			if(baud_rate == 9600)
			{		
			        printf("baudrate  is set to 9600\n");
				cfsetispeed(&my_termios, B9600);
				cfsetospeed(&my_termios, B9600);
			}
			  else if(baud_rate == 2400)
                        {               
                                printf("baudrate  is set to 9600\n");
                                cfsetispeed(&my_termios, B2400);
                                cfsetospeed(&my_termios, B2400);
                        }

			else if(baud_rate==19200 )
			{
			        printf("baud rate is set to 19200 \n");
				cfsetispeed(&my_termios, B19200);
                        	cfsetospeed(&my_termios, B19200);
			}

			else
			{
				cfsetispeed(&my_termios, B9600);
                        	cfsetospeed(&my_termios, B9600);
			}
			/* set baud rate, enable the receiver and keep the ownership local */                            
			my_termios.c_cflag |= CREAD | CLOCAL; 

			/* Disable parity */
			my_termios.c_cflag &= ~PARENB;
			my_termios.c_cflag &= ~CSTOPB;
			my_termios.c_cflag &= ~CSIZE;
			my_termios.c_cflag |= CS8;

			/* Enable parity and stripping of parity bits (Not working with control board)
			my_termios.c_iflag |= (INPCK);
			*/
			my_termios.c_iflag |= IGNPAR ;

			/* Disable mapping of CR to NL and vice versa for input */
			my_termios.c_iflag &= ~(ICRNL | INLCR);

			/* Enable raw input */
			my_termios.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

                	/* Enable raw output */
                	my_termios.c_oflag &= ~OPOST;

			/* Set appropriate timeouts */
			/* VMIN minimum number of bytes to read */
			/* VTIME amount ot time in 10nths of seconds to wait for data to read */
	   		my_termios.c_cc[VMIN] = MIN_NUM_BYTES_TO_READ;
                	my_termios.c_cc[VTIME] = WAIT_DATA_TO_READ;
		
			/* Set the options */
			if(tcsetattr(uart_ports[ionum].uart_fd, TCSANOW, &my_termios) != 0){
				status = EUART_OPEN_SETATTR;
			}
			}	
//		 setnonblock(uart_ports[ionum].uart_fd); 
		}
        } 
        return status;
}

/*
Function to close serial terminal device. 
*/
int uart_exit(int ionum)
{
	int status = EUART_SUCCESS;

        if(uart_ports[ionum].uart_fd == -1) {
		printf("uart_exit:  uart device not initilized \n");
		status = EUART_EXIT_FD;
        } 
	else if(close(uart_ports[ionum].uart_fd) == -1) {
        	printf("uart_exit: Failed to close \n");
                status = EUART_EXIT_CLOSE;
       		}
		else{	/* uninitialize the file descriptor */
			uart_ports[ionum].uart_fd = -1;
        	}

	return status;
}

/*
Function to write data to serial terminal.
*/
int uart_write(int ionum, u_char* buffer, uint8_t nbytes)
{
	int status = EUART_SUCCESS;
	if(ionum > 9 || uart_ports[ionum].uart_fd == -1){
		status = EUART_WRITE_FD;
	}
	else if ((buffer == NULL) || !(nbytes)) {
                printf("uart_write: Empty buffer \n");
                status = EUART_WRITE_BUFF;
        }
//      else if (tcflush(uart_ports[ionum].uart_fd, TCIOFLUSH) != 0){  	
		/*The input and output queues have been flushed */
//         	printf("tcflush error");
//        	status = FAILURE;
//        }
else if (write(uart_ports[ionum].uart_fd, buffer, nbytes) != nbytes) {
                printf("uart_write: Failed to write data [%s]\n",
                strerror(errno));
                status = FAILURE;
        }
    	return status;	
}

/*
Function to read data from serial terminal.
*/
int uart_read(int ionum,u_char* buffer, uint8_t nbytes)
{
	int i;
   	int read_cnt = 0, status = EUART_SUCCESS;
	fd_set rfds;
        struct timeval  tv;
	int select_ret;

	if(ionum > 9 || uart_ports[ionum].uart_fd == -1){
                status = EUART_READ_FD;
        }
        else if ((buffer == NULL) || !(nbytes)) {
		printf("uart_read: Empty buffer \n");
                status = EUART_READ_BUFF;
	 }
	else if (tcflush(uart_ports[ionum].uart_fd, TCIFLUSH) != 0){
          printf("The input and output queues have been flushed.n\n");
                 perror("tcflush error\n");
		 status = EUART_READ_FLUSH;	
      }
	else{		
		tv.tv_sec = TIME_IN_SEC;
		tv.tv_usec = TIME_IN_UCSEC;
		/* set the file descriptor in readfds since we are reading */
        	FD_ZERO(&rfds);
       		FD_SET(uart_ports[ionum].uart_fd, &rfds);
	
        	select_ret = select(uart_ports[ionum].uart_fd + 1, &rfds, NULL, NULL, &tv);
		if(select_ret)
        	{
			read_cnt = read(uart_ports[ionum].uart_fd, buffer, nbytes);
		#if 0 	
			printf("\n %s read [%d]\n",buffer,read_cnt);
		#endif 
			/* Compare read bytes with required bytes */
		#if 0			
			if(read_cnt != nbytes) {
				printf("uart_read: Failed to read data [%s]: read data=%d\n",strerror(errno),read_cnt);
			}
		#endif 
			status = read_cnt;
		}
		else{
		#if ERROR_PRINTS
			printf("Select Timeout\n");
		#endif 
			status = EUART_READ_TIMEOUT;
		}
	}
	return status;
}


int ptz_init(void)
{

	int status = EUART_SUCCESS;

        ptzgpio_fd = open(PTZ_GPIO_DEVICE, O_RDWR);
        if (ptzgpio_fd < 0)
         {
                printf("Error while opening ptz gpio device %s\n", PTZ_GPIO_DEVICE);
                status = EUART_GPIO_FAIL;
        }
        return status;
}


int  ptz_write(int device_select)
{
        int status = EUART_SUCCESS;

      if(device_select == RS232_DEVICE)
        {
                if(write(ptzgpio_fd,&device_select,device_select) != 1)
                {
                        printf(" gpio device failure\n");
                        status = EUART_GPIO_FAIL;
                }
        }
        else if(device_select == RS485_DEVICE_WRITE_MODE || device_select == RS485_DEVICE_READ_MODE)
        {
                if(write(ptzgpio_fd,&device_select,device_select) != 1)
                {
                        printf("gpio device failure\n");
                        status = EUART_GPIO_FAIL;
                }
        }
        return status;

}

	int ptz_exit(void )
{
        int status = EUART_SUCCESS;

        if(ptzgpio_fd == -1)
        {
          printf(" PTZ LIB is not initilized\n");
           status= EUART_GPIO_FAIL;
        }
        else
        {
                if(close(ptzgpio_fd) == -1)
                {
                        printf("Failed to close the /dev/ptz\n");
                        status = EUART_GPIO_FAIL;
                }
        }
        return status;
}

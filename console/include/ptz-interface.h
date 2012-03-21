

#ifndef _PTZLIB_INTERFACE_H
	#define _PTZLIB_INTERFACE_H

#define PTZ_UART_DEVICE "/dev/tts/1"
#define PTZ_GPIO_DEVICE "/dev/ptz"

#define PTZLIB_SUCCESS 1     
#define PTZLIB_FAILURE 0       

#define RS232_DEVICE  0x01
#define RS485_DEVICE  0x02
#define RS485_DEVICE_READ_MODE 0x03
#define	RS485_DEVICE_WRITE_MODE 0x04

/**********initilize the ptz library************/
int ptzlib_init(void);
/********Write the buffer on ptz at given length on specified device***********
 * device_type = RS232_DEVICE or RS485_DEVICE*/
 
int ptzlib_write(unsigned int device_type, unsigned char* buffer, unsigned int bufflen);
/********Read the buffer on ptz at given length from specified device***********
 *  * device_type = RS232_DEVICE or RS485_DEVICE*/
int ptzlib_read(unsigned int device_type, unsigned char* buffer, unsigned int bufflen);

#endif // end of _ptzlib_h

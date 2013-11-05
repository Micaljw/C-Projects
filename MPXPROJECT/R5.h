#ifndef R5_h_
#define R5_h_

// The libraries included
#include <dos.h>
#include <stdio.h>
#include <stddef.h>
//#include "mpx_supt.h"

// The ring buffer size
#define RING_BUFFER_SIZE 1024

// status constants
#define DCB_IDLE 30
#define DCB_READING 31
#define DCB_WRITING 32

//event flag (for the open or closed) constants
#define DCB_OPEN 1 
#define DCB_CLOSED 0

//event flag (for the done or not done) constants
#define EVENT_FLAG_DONE 1
#define EVENT_FLAG_NOT_DONE 0

// interrupt constants
#define PIC_MASK 0x21
#define PIC_CMD 0x20
#define EOI 0x20

// Addresses needed for COM1
#define COM1_INT_ID 0x0c 
#define COM1_BASE 0x3F8					 //Base Address
#define COM1_INT_EN COM1_BASE+1			 //interrupt enable
#define COM1_BRD_LSB COM1_BASE			 //COM1 LSB
#define COM1_BRD_MSB COM1_BASE+1		 //COM1 MSB
#define COM1_INT_ID_REG COM1_BASE+2		 //interrupt ID register
#define COM1_LC COM1_BASE+3				 //Line Control Register
#define COM1_MC COM1_BASE+4 			 //modem control
#define COM1_LS COM1_BASE+5 			 //line status
#define COM1_MS COM1_BASE+6 		  	 //Modem Status

// Errors generated
#define ERROR_INVALID_EVENT_FLAG -101 			// invalid event flag pointer (in com_open)
#define ERROR_INVALID_BAUD_RATE -102 			//invalid baud rate divisor (in com_open)
#define ERROR_READ_PORT_OPEN -103				//port already open (in com_open)
#define ERROR_SERIAL_PORT_NOT_OPEN -201   	    //serial port not open
#define ERROR_READ_PORT_NOT_OPEN -301 			//port not open while reading
#define ERROR_READ_INVALID_BUFFER_ADDR -302 	//error invalid buffer address while reading
#define ERROR_READ_INVALID_COUNT -303 			//error invalid count address or count value while reading
#define ERROR_READ_DEVICE_BUSY -304 			//error device is busy while reading
#define ERROR_WRITE_PORT_NOT_OPEN -401 			//port not open while writing
#define ERROR_WRITE_INVALID_BUFFER_ADDR -402 	//error invalid buffer address while writing
#define ERROR_WRITE_INVALID_COUNT -403 			//error invalid count address or count value while writing
#define ERROR_WRITE_DEVICE_BUSY -404 			//error device is busy

typedef struct DCB{
	int open; 							
	int *event_flag; 					
	int status; 						
	char *in_buff; 						
	int *in_count; 						
	int in_done; 						
	char *out_buff; 					
	int *out_count; 					
	int out_done; 						
	char ring_buffer[RING_BUFFER_SIZE]; 
	int ring_buffer_in; 				
	int ring_buffer_out; 				
	int ring_buffer_num; 				
} DCB;


/*************************** Functions *****************************/

int com_open (int *eflag_p, int baud_rate);
int com_close();
int com_read(char *buf_p, int *count_p);
int com_write(char *buf_p, int *count_p);
void interrupt com_interrupt_handler();
void read_interrupt();
void write_interrupt();


#endif

#include<stdio.h>
#include<string.h>
#include "R5.h"
#include "mpx_supt.h"

/************************* Global Variables **************************/
DCB * dcbptr;
void interrupt (*old_interrupt_function) (void);

/**************************** Functions *****************************/


int com_read(char *buf_p, int *count_p) {
	
	if(dcbptr->open == DCB_CLOSED)
		return ERROR_READ_PORT_NOT_OPEN;
	if( dcbptr->status != DCB_IDLE)
		return ERROR_READ_DEVICE_BUSY;
	
	if(buf_p == NULL)
		return ERROR_READ_INVALID_BUFFER_ADDR;
	if(count_p == NULL)
		return ERROR_READ_INVALID_COUNT;
	
	// Initialize the input buffer
	dcbptr->in_buff = buf_p;
	dcbptr->in_count = count_p;
	dcbptr->in_done = 0;
	
	*dcbptr->event_flag = EVENT_FLAG_NOT_DONE;
	
	// Disable interrupts
	disable();
	
	dcbptr->status= DCB_READING;
	
	// Copy characters from the ring buffer to the requestor's buffer
	while((dcbptr->ring_buffer_num > 0) && (dcbptr->in_done < *dcbptr->in_count) && (dcbptr->ring_buffer[dcbptr->ring_buffer_in]) != '\r'){ 
		dcbptr->in_buff[dcbptr->in_done] = dcbptr->ring_buffer[dcbptr->ring_buffer_in];

		dcbptr->in_done++;
		dcbptr->ring_buffer_in++;
		dcbptr->ring_buffer_num--;
	}
	
	// Re-enable interrupts
	enable();

	if(dcbptr->in_done < *dcbptr->in_count)
		return 0;
	
	dcbptr->in_buff[dcbptr->in_done] = '\0';
	
	dcbptr->status= DCB_IDLE;
	*dcbptr->in_count = dcbptr->in_done;
	*dcbptr->event_flag= EVENT_FLAG_DONE;
	
	return dcbptr->in_done;
}

int com_write(char *buf_p, int *count_p){
	int mask;
	
	if(dcbptr->open == DCB_CLOSED)
		return ERROR_WRITE_PORT_NOT_OPEN;
	if( dcbptr->status != DCB_IDLE)
		return ERROR_WRITE_DEVICE_BUSY;
	if(buf_p == NULL)
		return ERROR_WRITE_INVALID_BUFFER_ADDR;
	if(count_p == NULL)
		return ERROR_WRITE_INVALID_COUNT;

	dcbptr->out_count = count_p;
	dcbptr->out_buff = buf_p;
	dcbptr->out_done = 0;
	
	dcbptr->status= DCB_WRITING;

	*dcbptr->event_flag = EVENT_FLAG_NOT_DONE;
	
	 outportb(COM1_BASE, *dcbptr->out_buff);
	
	dcbptr->out_buff++;
	dcbptr->out_done++;
	
	disable();
	mask = inportb(COM1_INT_EN);
	mask = mask | 0x02;
	outportb(COM1_INT_EN,mask);
	enable();
	
	return 0;
}


void interrupt com_interrupt_handler(){
	int interrupt_cause;
	
	if(dcbptr->open != DCB_OPEN)
		outportb(PIC_CMD, EOI);	// Send EOI to Command Register
	else{
		interrupt_cause = inportb(COM1_INT_ID_REG);
		interrupt_cause = interrupt_cause & 0x07;	// Perform bitwise operation

		if(interrupt_cause == 0x02)
			write_interrupt();
			
		else if(interrupt_cause == 0x04)
			read_interrupt();
			
		outportb(PIC_CMD, EOI);
	}
}

/* Second-Level Interrupt Reading */
void read_interrupt(){
	char input_register;
	
	input_register = inportb(COM1_BASE);
	
	if(dcbptr->status != DCB_READING){
		if(dcbptr->ring_buffer_num >= RING_BUFFER_SIZE)
			return;
			
		dcbptr->ring_buffer[dcbptr->ring_buffer_in] = input_register; 
		dcbptr->ring_buffer_in++; 
		dcbptr->ring_buffer_num++;
	}
	
	// Store the character in the input buffer and increment the count
	if(dcbptr->in_done < *dcbptr->in_count && input_register != '\r'){
		dcbptr->in_buff[dcbptr->in_done] = input_register;
		dcbptr->in_done++;
		return;
	}
		
	dcbptr->in_buff[dcbptr->in_done] = '\0';

	dcbptr->status= DCB_IDLE;
	*dcbptr->in_count = dcbptr->in_done;
	
	*dcbptr->event_flag= EVENT_FLAG_DONE; 
}


/* Second-Level Interrupt Reading */
void write_interrupt(){
	int mask;
	
	if(dcbptr->status != DCB_WRITING)
		return;
		
	if(dcbptr->out_done < *dcbptr->out_count){
		outportb(COM1_BASE, *dcbptr->out_buff); 
		dcbptr->out_done++;
		dcbptr->out_buff++;
		return;
	}
	
	dcbptr->status=DCB_IDLE;
	
	*dcbptr->event_flag= EVENT_FLAG_DONE; 
	
	disable();
	mask = inportb(COM1_INT_EN);
	mask = mask & ~0x02;
	outportb(COM1_INT_EN ,mask);
	enable();
}


int com_open (int *eflag_p, int baud_rate){
	
	int* evt_flag;
	int baud_rate_div;
	int mask;

	if(eflag_p == NULL)
		return ERROR_INVALID_EVENT_FLAG;
	if(baud_rate == NULL || baud_rate < 0)
		return ERROR_INVALID_BAUD_RATE;

	dcbptr = (DCB*)sys_alloc_mem(sizeof(DCB));	
	dcbptr->open = DCB_OPEN; 					
	evt_flag = dcbptr->event_flag; 				
	dcbptr->event_flag = eflag_p;			
	dcbptr->status = DCB_IDLE; 				
	
	dcbptr->ring_buffer_in = 0;
	dcbptr->ring_buffer_out = 0;
	dcbptr->ring_buffer_num = 0;
	
	old_interrupt_function = getvect(COM1_INT_ID); 	
	setvect(COM1_INT_ID, &com_interrupt_handler);	

	baud_rate_div = 115200 / (long) baud_rate; 

	//Store 0x80 in the line control register, this will allow you to change the BRD registers
	outportb(COM1_LC, 0x80);
	
	//Set the baud rate divisor in the registers
	outportb(COM1_BRD_LSB, baud_rate_div&0xFF);
	outportb(COM1_BRD_MSB ,(baud_rate_div >> 8) & 0xFF);
	
	outportb(COM1_LC, 0x03); 

	disable();
	mask = inportb(PIC_MASK);
	mask = mask & ~0x10;
	outportb(PIC_MASK, mask);
	enable();

	outportb(COM1_MC, 0x08); 
	
	// Store 0x01 in the interrupt enable register. This will enable input ready interrupts
	outportb(COM1_INT_EN, 0x01);
	
	return 0;
}

int com_close(){
	int mask;
	
	if(dcbptr->open != DCB_OPEN)
		return ERROR_SERIAL_PORT_NOT_OPEN;
	
	dcbptr->open = DCB_CLOSED;

	disable();
	mask = inportb(PIC_MASK);
	mask = mask | 0x10;
	outportb(PIC_MASK, mask);
	enable();
	
	outportb(COM1_MS, 0x00); 
	outportb(COM1_INT_EN, 0x00);

	// Restore the original interrupt vector
	setvect(COM1_INT_ID, old_interrupt_function);
	sys_free_mem(dcbptr);
	
	return 0;
}
/* Team :) 
 * Michael Woods
 * Hajar
 *
 *
*/

#include<stdio.h>
#include<string.h>
#include "R1.h"
#include "R2.h"
#include "R3.h"
#include "R4.h"
#include "R5.h"
#include "mpx_supt.h"
#include "dos.h"
#include "TRMDRIVE.H"
#include "TRMDRIVE.C"

void main(){
	
	PCB* TEST1, TEST2;
	int e_flag;	/* event flag */
	int ix;		/* loop index */
	int rc;		/* function return code */
	
	context *context1;
	context *context2;
	
	//Call Init functions
	sys_init(MODULE_F + MODULE_R2 + MODULE_R3);
	sys_set_vec(sys_call);
	
	// initialize DCBs, IOCBs
	// initialize PCB ready/blocked queues
	FIFO_init();
	
	/*Open device drivers*/
	rc = trm_open((int *) &e_flag);
	
	if (rc != 0) {
		print("\nOpen failed!\n");
 		print("Error code = %d\n", rc);
		sys_exit();
	}
	
	rc = com_open((int *) &e_flag, 1200); 
	
	if (rc != 0) {
		print("\nOpen failed!\n");
 		print("Error code = %d\n", rc);
		sys_exit();
	}
	
	/*Install command handler as a process*/
	TEST1 = Setup_PCB("com_hand", proc_syst, 127);
	context1 = (context*)TEST1 -> stack_top;
	context1 -> IP = FP_OFF(&com_hand_R3);
	context1 -> CS = FP_SEG(&com_hand_R3);
	context1 -> FLAGS = 0x200;
	context1 -> DS = _DS;
	context1 -> ES = _ES;
	TEST1 -> state = state_ready;
	Insert_PCB(TEST1, TEST1 -> state);
	
	/*Load IDLE*/
	TEST2 = Load_Program("IDLE.mpx", -128);
	TEST2 -> pclass = proc_syst;
	resume(TEST2 -> name);
	
	/*Calls dispatcher- runs com_hand*/
	
	
	
	/*Close device drivers*/
	rc = trm_close();
	
	if(rc != 0){
		printf("\ntrm_close failed!\n");
 		printf("Error code = %d\n",rc);
		sys_exit();
	}
	
	rc = com_close();
	
	if(rc != 0){
		printf("\ncom_close failed!\n");
 		printf("Error code = %d\n",rc);
		sys_exit();
	}
	
	Delete_All();	//Clear queues and all allocated memory is de-allocated
	
	/*Free memory for the IOCB for each device*/
	
	
	sys_exit();
}
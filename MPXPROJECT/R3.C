#include<stdio.h>
#include<string.h>
#include "R1.h"
#include "R2.h"
#include "R3.h"
#include "mpx_supt.h"
#include "dos.h"

//variables to manipulate the stack segment(ss) and the stack pointer(sp)
unsigned short ss_save = NULL;
unsigned short sp_save = NULL;
unsigned short new_ss = NULL;
unsigned short new_sp = NULL;

context* context_ptr;
PCB* cop; //cop: current operating process
params* param_ptr;

unsigned char sys_stack[SYS_STACK_SIZE];

//------------------------------interrupt sys_call function---------------------
void interrupt sys_call(){
	 // Access parameters that sys_req() placed on the stack for us
	cop->stack_top = (unsigned char *)MK_FP(_SS, _SP);
	param_ptr = (params*)(cop->stack_top + sizeof(context));
	//switching to temporary stack
	new_ss = FP_SEG(&sys_stack);
	new_sp = FP_OFF(&sys_stack)+ SYS_STACK_SIZE;
	_SS = new_ss;
	_SP = new_sp;
	switch(param_ptr->op_code){
		case IDLE:	cop->state = state_ready;
					Insert_PCB(cop, cop->state);
			break;
		case EXIT: Free_PCB(cop);
				   cop = NULL;
		default:
				break;
	} // end switch	
	dispatch(); //call the dispatch function
}
	
//-------------------------interrupt dispatch function-----------------------


void interrupt dispatch(){
	//PCB *head; //ready queue head
	
	if(sp_save == NULL){
		ss_save = _SS;
		sp_save = _SP;
	}//end if sp_save == NULL
	
	cop = get_readyQ()->head;
	
	if(cop != NULL){
		Remove_PCB(cop->state, cop);
		cop->state = state_running;
		new_ss = FP_SEG(cop->stack_top);
		new_sp = FP_OFF(cop->stack_top);
		_SP = new_sp;
		_SS = new_ss;
	}else{
		cop = NULL;
		_SP = sp_save;
		_SS = ss_save;
		sp_save = NULL;
		ss_save = NULL;
	}
	
}// end interrupt dispatch function


//--------------------------R3_TEST function------------------------------------

void test_R3(){
	PCB *TEST1;
	PCB *TEST2;
	PCB *TEST3;
	PCB *TEST4;
	PCB *TEST5;

	context *context1; //one context for all 5 tests
	context *context2;
	context *context3;
	context *context4;
	context *context5;
		
	//test #1
	TEST1 = Setup_PCB("test1", proc_app, 0); //setting up testone PCB with name "test1", priority = 0, and pclass = 10 which means its an APPLICATION
	context1 = (context*)TEST1->stack_top;
	context1->IP = FP_OFF(&test1_R3);
	context1->CS = FP_SEG(&test1_R3);
	context1->FLAGS = 0x200;
	context1->DS = _DS;
	context1->ES = _ES;
	TEST1->state= state_ready;
	Insert_PCB(TEST1, TEST1->state);
	
	//test #2
	TEST2 = Setup_PCB("test2", proc_app, 0); //setting up testtwo PCB with name "test2", priority = 0, and pclass = 10 which means its an APPLICATION
	context2 = (context*)TEST2->stack_top;
	context2->IP = FP_OFF(&test2_R3);
	context2->CS = FP_SEG(&test2_R3);
	context2->FLAGS = 0x200;
	context2->DS = _DS;
	context2->ES = _ES;
	TEST2->state= state_ready;
	Insert_PCB(TEST2, TEST2->state);
	
	//test #3
	TEST3 = Setup_PCB("test3", proc_app, 0); //setting up testthree PCB with name "test3", priority = 0, and pclass = 10 which means its an APPLICATION
	context3 = (context*)TEST3->stack_top;
	context3->IP = FP_OFF(&test3_R3);
	context3->CS = FP_SEG(&test3_R3);
	context3->FLAGS = 0x200;
	context3->DS = _DS;
	context3->ES = _ES;
	TEST3->state= state_ready;
	Insert_PCB(TEST3, TEST3->state);
	
	//test #4
	TEST4 = Setup_PCB("test4", proc_app, 0); //setting up testfour PCB with name "test4", priority = 0, and pclass = 10 which means its an APPLICATION
	context4 = (context*)TEST4->stack_top;
	context4->IP = FP_OFF(&test4_R3);
	context4->CS = FP_SEG(&test4_R3);
	context4->FLAGS = 0x200;
	context4->DS = _DS;
	context4->ES = _ES;	
	TEST4->state= state_ready;
	Insert_PCB(TEST4, TEST4->state);
	
	//test #5
	TEST5 = Setup_PCB("test5", proc_app, 0); //setting up testfive PCB with name "test5", priority = 0, and pclass = 10 which means its an APPLICATION
	context5 = (context*)TEST5->stack_top;
	context5->IP = FP_OFF(&test5_R3);
	context5->CS = FP_SEG(&test5_R3);
	context5->FLAGS = 0x200;
	context5->DS = _DS;
	context5->ES = _ES;	
	TEST5->state= state_ready;
	Insert_PCB(TEST5, TEST5->state);  
		
	dispatch();
	//test1_R3();
	//test2_R3();
	//test3_R3();
	//test4_R3();
//	test5_R3();
}


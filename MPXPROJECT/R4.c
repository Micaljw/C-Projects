//module R4 c file

#include<stdio.h>
#include<string.h>
#include "R1.h"
#include "R2.h"
#include "R3.h"
#include "R4.h"
#include "mpx_supt.h"
#include "dos.h"



void Load_Program(char filename[], int priorty){

	PCB *PCB_prog_load;
	context *con_prog_load;
	int prog_len_p;
	int start_offset_p;
	unsigned char *load_add;
	unsigned char *exec_add;
	int length;
	char buff[60];
	int errorcode;

	if(priorty >127 || priorty < (-128)){
		printf("Priority entered is invalid.\n");
		return;
		}

	if(filename == NULL){
		printf("Name is an empty string, so name not valid.\n");
		return;
		}
	
	if(Find_PCB(filename) != NULL){
		printf("Name already exists\n");
		return;
		}
	
	if(strlen(filename) >50){
		printf("Name provided exceeds the maximum characters limit./n");
		return;
		}
		
	errorcode = sys_check_program("\0", filename, &prog_len_p,  &start_offset_p);  
	if(errorcode != 0){
		length = sprintf(buff, "An error occured : %d\n", errorcode);
		sys_req(WRITE, TERMINAL, buff, &length);
		err_hand(errorcode);	
		return;
	}
	////////////////////////////////////////////
	PCB_prog_load= Setup_PCB( filename, proc_app,priorty);
	
	if(PCB_prog_load==NULL){
		print("PCB could not be created");
		return ;
		}
	
	PCB_prog_load->state=state_sus_ready;
	load_add = (unsigned char*)sys_alloc_mem(prog_len_p);
	exec_add = load_add + start_offset_p;
	
	
	errorcode = sys_load_program(load_add, prog_len_p, "\0", filename);
	if(errorcode != 0){
		length = sprintf(buff, "The following error occurred while loading the program: %d\n", errorcode);
		sys_req(WRITE, TERMINAL, buff, &length);
		err_hand(errorcode);	
		return;
	}
	
	PCB_prog_load->memsize = prog_len_p;
	PCB_prog_load->load_add = load_add;
	PCB_prog_load->exec_add = exec_add;
	
	con_prog_load = (context *)PCB_prog_load->stack_top;
	con_prog_load->IP = FP_OFF(PCB_prog_load->exec_add);
	con_prog_load->CS = FP_SEG(PCB_prog_load->exec_add);
	con_prog_load->DS = _DS;
	con_prog_load->ES = _ES;
	con_prog_load->FLAGS = 0x200;
		
	if(errorcode != 0){
		printf("The PCB was not inserted correctly while loading\n");
	}
	else{
		Insert_PCB(PCB_prog_load, PCB_prog_load->state);
	}
}

void Terminate_Program(char* pcbName){
		PCB *PCBptr;
		PCBptr = Find_PCB(pcbName);
		if(	PCBptr->pclass == proc_syst)
			print("Cannot terminate a SYSTEM process\n");
		else{	
			if(PCBptr == NULL){
				printf("Process not found\n");
				return;
			}else{
				Remove_PCB(PCBptr->state, PCBptr);
				Free_PCB(PCBptr);
			return;
			}
		}		
}
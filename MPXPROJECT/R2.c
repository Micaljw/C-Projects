#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "R2.h"
#include "R3.h"
#include "MPX_SUPT.H"

FIFO_Queue blocked;
FIFO_Queue sus_ready;
FIFO_Queue sus_blocked;
FIFO_Queue ready; 

int CNT_LINES_PRINTED;
char USER_INPUT;


void FIFO_init(){
	ready.head=NULL;
	ready.tail=NULL;
	blocked.head=NULL;
	blocked.tail=NULL;
	sus_ready.head=NULL;
	sus_ready.tail=NULL;	
	sus_blocked.head=NULL;
	sus_blocked.tail=NULL;	
}

void print2 (char* str){
	int buff_size=strlen(str);
	sys_req(WRITE, TERMINAL, str, &buff_size);
}

void pagination2(){
	CNT_LINES_PRINTED++;
	//Check to see if a new page is required
	if(CNT_LINES_PRINTED == 25){
		CNT_LINES_PRINTED = 0;
		//wait for the user to press enter before continuing to the next page
		printf("\nHit enter to see more");
		USER_INPUT =  getchar();
		if(USER_INPUT == '\r')
			print("\f");
	}
}

/*
 ============================================================================
 Function Name      : Allocate_PCB
 Parameters         : none
 Description        : This function allocates memory for a PCB structure and for
                      its associated stack.
 ============================================================================
 */

PCB* Allocate_PCB () {
    PCB* newPCB;
    newPCB= (PCB*)sys_alloc_mem(sizeof(PCB));
    if (newPCB == NULL)
	return NULL;
    newPCB->stack_down=(unsigned char*) sys_alloc_mem(1024);
	newPCB->stack_top = newPCB -> stack_down +1024 - sizeof(context);
    return newPCB;
}

/*
 ============================================================================
 Function Name      : Free_PCB
 Parameters         : a pointer to a structure of PCB
 Description        : This function de-allocates memory for a PCB structure and
                      for its associated stack.
 ============================================================================
 */

int Free_PCB (PCB* PCBptr){	
	if(sys_free_mem (&(PCBptr->stack_top))!=0)
	return Top_Stack_free_Error;
    if(sys_free_mem (&(PCBptr->stack_down))!=0)
	return Down_Stack_free_Error;
    if(sys_free_mem (&(PCBptr))!=0)
	return PCB_free_Error;
	/**************** R4 changes  ****************/
	if(sys_free_mem (&(PCBptr->load_add))!=0)
	return Load_Address_free_Error;
	if(sys_free_mem (&(PCBptr->exec_add))!=0)
	return Execution_Address_free_Error;
	/**************** R4 end of changes  ****************/
    return 0;
}

/*
 ============================================================================
 Function Name      : Setup_PCB
 Parameters         : a pointer to a character
		      as the PCB name, and two integers as the PCB class and
		      as the PCb priority
 Description        : This function sets up the information regarding a PCB. It
		      takes the PCB passed as parameter and sets the name (if not
		      already exisiting) the class and the priority (if valid) from
		      the parameters passed by.
 ============================================================================
 */

PCB* Setup_PCB( char* PCBname, int PCBclass, int PCBpriority){
	PCB* PCBptr=NULL;
	PCBptr= Allocate_PCB();
	if(PCBptr==NULL){
		print2("PCB not able to be allocated");
		return NULL;
		}
   if(Find_PCB(PCBname)!=NULL){
		print2("PCB name already exisiting");
				return NULL;
		}
	strcpy(PCBptr->name,PCBname);
    if(PCBclass!=10 && PCBclass!=11){
		print2("PCB class is incorrect. Only 10 and 11 are accepted");
		return NULL;
	}
    else
	PCBptr->pclass=PCBclass;
    if(PCBpriority<-128 || PCBpriority>127){
		print2("PCB priority is incorrect. Only the range from -128 to 127 is accepted");
		return NULL;
	}
    else
	PCBptr->priority=PCBpriority;
    PCBptr->state=state_ready;
    PCBptr->memsize=0;
    PCBptr->next=NULL;
    PCBptr->prev=NULL;
    return PCBptr; // PCB successfully set up
}

/*
 ============================================================================
 Function Name      : Show_PCB
 Parameters         : a pointer to a character as the PCB name, 
 Description        : This command is used to display all information contained
					 in a single PCB for a process	specified by name.
 ============================================================================
 */

void Show_PCB(char* PCBname){
	PCB* pcb_to_show;
	pcb_to_show=Find_PCB(PCBname);
	if(pcb_to_show==NULL){
		print2("Process not found. Check the process's name\n");
		return;
	}
	/*-------------------- name printing --------------------*/
	printf("%40s  |", pcb_to_show->name);

	/*-------------------- class printing --------------------*/
	if(pcb_to_show->pclass == proc_syst)
		print2("SYSTEM      |");
	else
		print2("APPLICATION |");

	/*-------------------- state printing --------------------*/
	if(pcb_to_show->state == state_ready)
		print2("READY             |");
	else if(pcb_to_show->state == state_blocked)
		print2("BLOCKED           |");
	else if(pcb_to_show->state == state_sus_ready)
		print2("SUSPENDED READY   |");
	else if(pcb_to_show->state == state_sus_blocked)
		print2("SUSPENDED BLOCKED |");
	
	printf("%d\n", pcb_to_show->priority);
}

/*
 ============================================================================
 Function Name      : Show_Ready
 Parameters         : none
 Description        : This command is used to display all information about
					 all the PCBs currently in the ready and suspended ready queue.
 ============================================================================
 */

void Show_Ready(){
	int i;
	PCB* walker=NULL;
	print2("\nSHOW READY\n");
	print2("                  NAME                    ");
	print2("   CLASS   ");print2("      STATE     ");
	print2("PRIORITY");
	pagination2();
	// Showing the PCB information concerning the ready queue
	walker=ready.head;
	while(walker!=NULL){
			Show_PCB(walker->name);
			walker=walker->next;
	}
	// Showing the PCB information concerning the suspended ready queue
	walker=sus_ready.head;
	while(walker!=NULL){
			Show_PCB(walker->name);
			walker=walker->next;
	}
}

/*
 ============================================================================
 Function Name      : Show_Blocked
 Parameters         : none
 Description        : This command is used to display all information about
					 all the PCBs currently in the blocked and suspended
					 blocked queue.
 ============================================================================
 */
void Show_Blocked(){
	PCB* walker=NULL;
	print2("\nSHOW BLOCKED\n");
	print2("                  NAME                    ");
	print2("   CLASS   ");print2("      STATE     ");
	print2("PRIORITY");
	pagination2();

	walker=blocked.head;
	while(walker!=NULL){
			Show_PCB(walker->name);
			walker=walker->next;
	}

	walker=sus_blocked.head;
	while(walker!=NULL){
			Show_PCB(walker->name);
			walker=walker->next;
	}
}

/*
 ============================================================================
 Function Name      : Show_All
 Parameters         : none
 Description        : This command is used to display all information about
					 all the PCBs currently in the blocked and suspended
					 blocked queue.
 ============================================================================
 */
void Show_All(){
	Show_Ready();
	Show_Blocked();
}

 /*
 ============================================================================
 Function Name      : Find_PCB
 Parameters         : a character array corresponding to the PCB name to be found
 Description        : The function starts by searching the PCB in the ready queue
					and moves to the each other queues when it does not find it in
					the previous queue. At the end, the function returns the result
					of the last search as a PCB pointer (either a NULL or the found PCB)
 ============================================================================
 */

PCB* Find_PCB(char PCBname[]){
// the search will be performed over the different queues
	int i;
	PCB *walker;
	walker=ready.head;
	//search for the PCB in the ready queue
	while(walker!=NULL){
		if(strcmp( walker->name, PCBname)==0)
			return walker;
		else
			walker=walker->next;
	}
	if(walker==NULL){//if not found in the ready queue, search for the PCB in the blocked queue
		walker=blocked.head;
		while(walker!=NULL){
			if(strcmp( walker->name, PCBname)==0)
				return walker;
			else
				walker=walker->next;
		}
			if(walker==NULL){//if not found in the blocked queue, search for the PCB in the suspended blocked queue
				 walker=sus_blocked.head;
				while(walker!=NULL){
					if(strcmp( walker->name, PCBname)==0)
						return walker;
					else
					walker=walker->next;
				}
				if(walker==NULL){//if not found in the suspended blocked queue, search for the PCB in the suspended ready queue
					   walker=sus_ready.head;
					   while(walker!=NULL){
						 if(strcmp( walker->name, PCBname)==0)
						return walker;
					else
						walker=walker->next;
					}

				}
			}
	}
	return walker; // will return either a NULL (PCB not found in the suspended ready queue) or a PCB pointer ( PCB found in the suspended ready queue)
}

/*
 ============================================================================
 Function Name      : Insert_PCB
 Parameters         : a pointer to a PCB ( process control block), and an integer
					corresponding to an identifier of the queue
 Description        : The function inserts the PCB passed by as a parameter to
 to the queue that corresponds the integer identifier passed by as a parameter.
 The identifiers are the states of a PCB. For example, if a PCB pointer and the value
 20 are passed as parameters, the function will insert the PCB in the blocked queue
 since 20 corresponds to the blocked state. The function returns -1 in case of failure
 and 0 otherwise.
 ============================================================================
 */

int Insert_PCB(PCB* process, int queue){
	PCB *temp = NULL;
	int insert=0;
	switch(queue){
		case state_ready:if(ready.head == NULL && ready.tail == NULL){ //if the queue is empty
							ready.head = process;
							ready.tail = process;
						break;
						}else{ 
							temp = ready.head;		
						}				
						while(temp != NULL && temp->priority >= process->priority){ //otherwise, we have to put the PCB in the order according to its priority
							temp = temp->next;									   
						}
						if(temp == ready.head){ //if the PCB has a the highest priority, it will be put at the front
							process->next = ready.head;
							ready.head->prev = process;
							ready.head = process;
							break;
						}else if(temp == NULL){ //if the PCB has a the highest priority, it will be put at the end
							ready.tail->next = process;
							process->prev = ready.tail;
							ready.tail = process;
						}else{ //if the PCB is in the middle
							temp->prev->next = process;
							process->prev = temp->prev;
							temp->prev = process;
							process->next = temp;
						}break;
		case state_blocked: if(blocked.head == NULL && blocked.tail == NULL){ // if the queue is empty
									blocked.head = process;
									blocked.tail = process;
								}else{// if the queue has some elements
									(blocked.tail) -> next = process;
									  blocked.tail = process;
									  process->next=NULL;
									  process->prev = blocked.tail;
								   }
			break;
		case state_sus_ready:if(sus_ready.head == NULL && sus_ready.tail == NULL){// if the queue is empty
									sus_ready.head = process;
									sus_ready.tail = process;
								}else{// if the queue has some elements
									(sus_ready.tail) -> next = process;
									  sus_ready.tail = process;
									  process->next=NULL;
									  process->prev = sus_ready.tail;
								   }
			break;
		case state_sus_blocked:if(sus_blocked.head == NULL && sus_blocked.tail == NULL){// if the queue is empty
									sus_blocked.head = process;
									sus_blocked.tail = process;
								}else{// if the queue has some elements
									(sus_blocked.tail) -> next = process;
									  sus_blocked.tail = process;
									  process->next=NULL;
									  process->prev = sus_blocked.tail;
								   }
			break;
		default: insert=-1;
			break;
	}
	return insert;
}

/*
 ============================================================================
 Function Name      : Remove_PCB
 Parameters         : a pointer to a PCB ( process control block), and an integer
					corresponding to an identifier of the queue
 Description        : The function removes the PCB passed by as a parameter to
 from the queue that corresponds the integer identifier passed by as a parameter.
 For example, if a PCB pointer and the value 20 are passed as parameters, the function
 will remove the PCB from the blocked queue since 20 corresponds to the blocked state.
 The function returns -1 in case of failure and 0 otherwise.
 ============================================================================
 */

int Remove_PCB(int queue, PCB* process){
	int removed=0;
	switch(queue){
		case state_ready:if(process == ready.head && process->next == NULL){  //if the queue contains only one PCB
							ready.head = NULL; ready.tail = NULL;
							process->next = NULL; process->prev = NULL;

						}else if(process == ready.head && process->next != NULL){  //if the queue contains more PCBs and the PCB is at the head of the queue
							ready.head = process->next;	ready.head->prev = NULL;
							process->next = NULL;  process->prev = NULL;

						}else if(process == ready.tail){ // if the PCB is at the tail of the queue
							ready.tail = process->prev;	ready.tail->next = NULL;
							process->next = NULL;	process->prev = NULL;

						}else{ // if the PCB is in the middle of the queue
							process->prev->next = process->next;
							process->next->prev = process->prev;
							process->next = NULL;	process->prev = NULL;
						}
			break;
		case state_blocked: 	if(process == blocked.head && process->next == NULL){   //if the queue contains only one PCB
									blocked.head = NULL; blocked.tail = NULL;
									process->next = NULL; process->prev = NULL;

								}else if(process == blocked.head && process->next != NULL){  //if the queue contains more PCBs and the PCB is at the head of the queue
									blocked.head = process->next;
									blocked.head->prev = NULL;
									process->next = NULL; process->prev = NULL;

								}else if(process == blocked.tail){ // if the PCB is at the tail of the queue
									blocked.tail = process->prev;
									blocked.tail->next = NULL;
									process->next = NULL; process->prev = NULL;

								}else{ // if the PCB is in the middle of the queue
									process->prev->next = process->next;
									process->next->prev = process->prev;
									process->next = NULL;	process->prev = NULL;
								}
			break;
		case state_sus_ready:	if(process == sus_ready.head && process->next == NULL){   //if the queue contains only one PCB
									sus_ready.head = NULL;	sus_ready.tail = NULL;
									process->next = NULL;	process->prev = NULL;

								} else if(process == sus_ready.head && process->next != NULL){  //if the queue contains more PCBs and the PCB is at the head of the queue
									sus_ready.head = process->next;
									sus_ready.head->prev = NULL;
									process->next = NULL;	process->prev = NULL;

								} else if(process == sus_ready.tail){ // if the PCB is at the tail of the queue
									sus_ready.tail = process->prev;
									sus_ready.tail->next = NULL;
									process->next = NULL; process->prev = NULL;

								} else{ // if the PCB is in the middle of the queue
									process->prev->next = process->next;
									process->next->prev = process->prev;
									process->next = NULL;	process->prev = NULL;
								}
			break;
		case state_sus_blocked:if(process == sus_blocked.head && process->next == NULL){   //if the queue contains only one PCB
								sus_blocked.head = NULL; sus_blocked.tail = NULL;
								process->next = NULL; process->prev = NULL;

							}else if(process == sus_blocked.head && process->next != NULL){ //if the queue contains more PCBs and the PCB is at the head of the queue
								sus_blocked.head = process->next;
								sus_blocked.head->prev = NULL;
								process->next = NULL; process->prev = NULL;

							}else if(process == sus_blocked.tail){ // if the PCB is at the tail of the queue
								sus_blocked.tail = process->prev;
								sus_blocked.tail->next = NULL;
								process->next = NULL; process->prev = NULL;

							}else{ // if the PCB is in the middle of the queue
								process->prev->next = process->next;
								process->next->prev = process->prev;
								process->next = NULL;	process->prev = NULL;
							}
				break;
		default: removed=-1;
			break;
	}
	return removed;
}

/*
 ============================================================================
 Function Name      : block
 Parameters         : char pointer that points to the users help command
 Description        : This function blocks the PCB which name was specified in 
					parameter of the function. The PCB blocked is removed from
					its corresponding ready queue and then inserted in the 
					corresponding blocked queue
 ============================================================================
 */

void block(char PCBname[]){
		PCB *temp;
		temp = Find_PCB(PCBname); //searches for the PCB which the name was entered by the user
		
		if(temp == NULL){  //PCB  not found
			print2("Error Blocking: the PCB name was not found\n");
	
		
		}else{  //PCB found
			if(temp->state==state_ready){ // PCB is in the ready queue
					Remove_PCB(temp->state, temp);
					temp->state=state_blocked;
					Insert_PCB(temp, temp->state);	
			}else{ // PCB is in the suspended ready queue
					Remove_PCB(temp->state, temp);
					temp->state=state_sus_blocked;
					Insert_PCB(temp, temp->state);
			}	
		print2("PCB successfully blocked\n");
		}
}

/*
 ============================================================================
 Function Name      : unblock
 Parameters         : char pointer that points to the users help command
 Description        : This function unblocks the PCB which name was specified in 
					parameter of the function. The PCB unblocked is removed from
					its corresponding blocked queue and then inserted in the 
					corresponding ready queue
 ============================================================================
 */

void unblock(char PCBname[]){
	PCB *temp;
	temp = Find_PCB(PCBname); //searches for the PCB which the name was entered by the user

	if(temp == NULL){  //PCB not found
		print2("Error Unblocking: the PCB name was not found\n");

	}
	else{  //PCB found
		if(temp->state==state_blocked){ // PCB is in the blocked queue
					Remove_PCB(temp->state, temp);
					temp->state=state_ready;
					Insert_PCB(temp, temp->state);	
			}else{// PCB is in the suspended blocked queue
					Remove_PCB(temp->state, temp);
					temp->state=state_sus_ready;
					Insert_PCB(temp, temp->state);
			}	
		print2("PCB successfully unblocked\n");
	
	}
}

/*
 ============================================================================
 Function Name      : resume
 Parameters         : char pointer that points to the users help command
 Description        : This function resumes the PCB which name was specified in 
					parameter of the function. The PCB suspended is removed from
					its corresponding suspended queue and then inserted in the 
					corresponding unsuspended queue
 ============================================================================
 */
void resume(char PCBname[]){
	PCB *temp;
	temp = Find_PCB(PCBname); //searches for the PCB which the name was entered by the user

	if(temp == NULL){  //PCB does not exist
		printf("Error Resuming: the PCB name was not found\n");
	
	}
	else{  // PCB found
		if(temp->state==state_sus_blocked){// PCB is in the suspended blocked queue
					Remove_PCB(temp->state, temp);
					temp->state=state_blocked;
					Insert_PCB(temp, temp->state);	
			}else{// PCB is in the suspended ready queue
					Remove_PCB(temp->state, temp);
					temp->state=state_ready;
					Insert_PCB(temp, temp->state);
			}
		print2("PCB successfully resumed\n");
	
	}
}

/*
 ============================================================================
 Function Name      : suspend
 Parameters         : char pointer that points to the users help command
 Description        : This function suspends the PCB which name was specified in 
					parameter of the function. The PCB unsuspended is removed from
					its corresponding unsuspended queue and then inserted in the 
					corresponding suspended queue
 ============================================================================
 */
void suspend(char PCBname[]){
	PCB *temp;
	temp = Find_PCB(PCBname); //searches for the PCB which name was entered by the user

	if(temp == NULL){  //PCB not found
		print2("Error Unblocking: the PCB name was not found\n");

	}
	else{// PCB found
		if(temp->state==state_blocked){// PCB is in the blocked queue
					Remove_PCB(temp->state, temp);
					temp->state=state_sus_blocked;
					Insert_PCB(temp, temp->state);
			}else{// PCB is in the ready queue
					Remove_PCB(temp->state, temp);
					temp->state=state_sus_ready;
					Insert_PCB(temp, temp->state);
			}
		print2("PCB successfully suspended\n");
	}
}


/*
 ============================================================================
 Function Name      : Create_PCB
 Parameters         : a pointer to a character as the process name and two
					integers as the process class and its priority
 Description        : the function creates a PCB with the correspnding parameters
					passed by. Its state is by default ready.
 ============================================================================
 */

PCB* Create_PCB(char * name, int pclass, int priority){
		PCB* temp;
		temp=Setup_PCB(name, pclass,priority);
	    if(temp==NULL)
			print2("PCB not set up correctly");
		else{// if PCB set up correctly, its state is set by default to ready, and it is inserted to the ready queue
			temp->state=state_ready;
			Insert_PCB(temp, state_ready);
		}
		return temp;
}
/*
 ============================================================================
 Function Name      : Delete_PCB
 Parameters         : a pointer to a character as the process name
 Description        : the function deletes a PCB corresponding to the PCB name
					passed by.
 ============================================================================
 */
int Delete_PCB( char* name){
	PCB* temp;
	temp=Find_PCB(name);  //searches for the PCB which name was entered by the user
	if(temp==NULL){
		print2("PCB not Found\n");
		return -1;
	}
	Remove_PCB(temp->state, temp); // removes the PCb from its corresponding queue
	Free_PCB (temp); // frees the memory of the PCB
	print2("PCB succesfully deleted");
	return 0;
}

/*
 ============================================================================
 Function Name      : set_priority
 Parameters         : char pointer that points to the users help command, and 
					an integer representing the new priority
 Description        : This function sets the new priority for the PCB which name 
					was specified in the parameter with the priority specified
					in the parameters
 ============================================================================
 */
void set_priority(char processName[], int newPriority){
	PCB* temp=NULL;
	temp=Find_PCB(processName);//searches for the PCB which name was entered by the user
	if(temp ==NULL){
		print2("Process not foundProcess not found");
		return;

	}else{// if the priority is out of the range accepted
		if(newPriority>127 || newPriority<-128){
			print2("Priority incorrect");
			return;
		}
		Remove_PCB(temp->state,temp); // PCB is removed from its corresponding queue
		temp->priority = newPriority;// PCB has its priority set
		Insert_PCB(temp, temp->state); //then PCB is inserted again to its corresponding queue
		print2("PCB priority successfully set\n");
	}
}

/*
 ============================================================================
 Function Name      : Delete_All
 Parameters         : none
 Description        : This function deletes all the PCb available in all the 
					queues
 ============================================================================
 */
void Delete_All(){
	PCB* walker;
	walker=ready.head;
	while(walker!=NULL){
		Remove_PCB(walker->state, walker);
		Free_PCB (walker);
		walker=ready.head;
	}
	walker=blocked.head;
	while(walker!=NULL){
		Remove_PCB(walker->state, walker);
		Free_PCB (walker);
		walker=ready.head;
	}
	walker=sus_ready.head;
	while(walker!=NULL){
		Remove_PCB(walker->state, walker);
		Free_PCB (walker);
		walker=ready.head;
	}
	walker=sus_blocked.head;
	while(walker!=NULL){
		Remove_PCB(walker->state, walker);
		Free_PCB (walker);
		walker=ready.head;
	}
}

FIFO_Queue* get_readyQ(){
		return &ready;
	}

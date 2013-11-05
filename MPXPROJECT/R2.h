#ifndef R2_H_
#define R2_H_




/*-----------------------The errors--------------------------*/
#define PCB_free_Error              -1
#define Top_Stack_free_Error      	-2
#define Down_Stack_free_Error      	-3
#define PCB_Null                  	-4
#define PCB_Name_Exisiting          -5
#define PCB_Class_Unavailable     	-6
#define PCB_Priority_Unavailable 	-7
#define Load_Address_free_Error		-8
#define Execution_Address_free_Error -9
/*-----------------------The process types--------------------------*/
#define proc_syst                  10
#define proc_app                  11
/*-----------------------The process states-------------------------*/
#define state_blocked              20 //blocked state
#define state_ready                21 //ready state
#define state_sus_ready            22
#define state_sus_blocked          23
#define state_running              24 //running state

/* define some macros */
#define SYS_STACK_SIZE 2048

	
typedef struct PCBs {
    char name[40]; // a character array that can contain at most 39 characters (plus a trailing null).
    int pclass; // a code identifying the process as an application process or a system process.
    int priority; // an integer of appropriate size representing priority values, which will be in the range -128 through +127
    int state; //A representation for the process state
    // We used an unsigned char since the byte type is not defined in C.
    unsigned char* stack_top;
    unsigned char* stack_down;
    int memsize; // This information describes the memory to be used for the actual instruction code and static data for the process
    unsigned char* load_add;
    unsigned char* exec_add;	
    struct PCBs * next;
    struct PCBs * prev;
} PCB;
/*   the  FIFO queue structure    */
typedef struct queue{
	int size;		
	PCB *head;
	PCB *tail;
} FIFO_Queue;

// our queues



// our PCB functions

PCB* Allocate_PCB ();
int Free_PCB (PCB* PCBptr);
PCB* Setup_PCB( char* PCBname, int PCBclass, int PCBpriority);
void Show_PCB(char* PCBname);
void Show_Ready();
void Show_Blocked();
void Show_All();
PCB* Find_PCB(char PCBname[]);
int Insert_PCB(PCB* PCBptr, int queue);
int Remove_PCB(int queue, PCB *process);
PCB* Create_PCB(char * name, int pclass, int priority);
int Delete_PCB( char* name);
void block(char PCBname[]);
void unblock(char PCBname[]);
void suspend(char PCBname[]);
void resume(char PCBname[]);
void set_priority(char processName[], int newPriority);
void Delete_All();
FIFO_Queue* get_readyQ();

void print (char* str);
void pagination();
#endif


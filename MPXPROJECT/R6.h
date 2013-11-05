typedef struct IOD(
	
	//Name of the process (PCB) requesting the I/O operation (char[])
	char[] PCB_name;
	//Pointer to the PCB requesting the I/O operation
	PCB* process_req;
	//Request type: what kind of I/O request (i.e. IDLE, READ, WRITE, CLEAR) (int)
	int request_type;
	//Location of the transfer buffer (char*)
	char* location;
	//Pointer to the count variable of the buffer (int*)
	int* buff_counter;
	//Pointer to the next IOD in the waiting queue
	iod* next;

)

typedef struct IOCB(
	
	//will hold the current event_flag for the device
	int event_flag;
	//number of IOD’s in the queue
	int count;
	//pointer to the first IOD in the waiting queue
	iod* head;
	//pointer to the last IOD in the waiting queue
	iod* tail;
)
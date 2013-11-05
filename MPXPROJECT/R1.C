#include "mpx_supt.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "time.h"
#include "R1.h"
#include "R2.h"
#include "R3.h"
#include "R4.h"

/*The main function is in charge of handling the interface
 * between the user and our OS. cmd_hand takes a command from the user,
 * analyzes it, and executes it.
 *
 *Input: none
 *Output: none
 *functions called: directory(), date(), change_date(), version(), help(), terminate()
 *functions calling: main()
 ***/
 int NUM_LINES_HELPI = 16;
//Global variable to keep track of the number of pages outputed to the screen
int COUNT_LINES_PRINTED;
char USERINPUT;
int BUFFERSIZE;
 
void main(){
	char* command;
	char pro_name[40];
	char buff[80];
	char date[20];
	char cmd[1750];
	int buff_size = 1750;
	int priority;
	int pclass;
	int user_input;
	int buff_size_ptr;
	int com_size;
	int i;
	int value;
	time_t start;
	time_t current;
	FILE *fPtr; // file used to hold the history of the current session
	
	COUNT_LINES_PRINTED = 0;
	
	fPtr = fopen( "history.txt", "w+" );// file used to hold the history of the current session
	
	//initialize
    sys_init(MODULE_R3);
	sys_set_vec(sys_call);

    command= (char*) sys_alloc_mem(80*sizeof(char));
	buff_size = strlen("memory allocation error");
     if(command==NULL) print("memory allocation error");
	//display opening message
	//system("cls");
	print("************************************\n");
	print("|   Welcome to the cs 450 project  |\n");
	print("|   =============================  |\n");
	print("|   ==>    	MPX-OS 	         <==  |\n");
	print("|   =============================  |\n");
	print("************************************\n");
	/**************** starting the while loop *******************/
	do{
		// display prompt
		print("\n>");
/*		print("|(type the command's name, as displayed)|\n");
		print("|	 	     -> display_directory|\n ");
		print("|	 	     -> display_date				|\n");
		print("|	 	     -> change_date					|\n");
		print("|	 	     -> display_version				|\n");
		print("|	 	     -> help					 	|\n");
		print("|	 	     -> terminate					|\n");
*/
		//accept command
		user_input = sys_req (READ, TERMINAL, command, &buff_size_ptr);
	       //	printf("user input is %d\n", user_input);
		// in order to put an end of string instead of the new line
		if(user_input > 80)
			print("This is too large for a command, type 'help' if you're having problems.\n");
		else{
			command = format(command);
			fprintf(fPtr, "%s ", command);
			
				if(strcmp(command,"display_directory")==0)
					directory();
				else if(strcmp(command, "display_version")==0)
					version();
				else if(strncmp(command, "change_date", 11)==0){
					strncpy(date, &command[11], 11);
					setDate(date);
				}
				else if(strcmp(command, "display_date")==0)
					displayDate();
				else if(strcmp(command, "help")==0)
					help();             	    
				else if(strcmp(command, "terminate")==0)	
					terminateMpx();
				else if(strncmp(command, "help!", 5) ==0){
					strncpy(cmd, &command[5], 30);
					help_info(cmd);
/**************************  R4 Changes (removing create_PCB) ************************
				}else if(strcmp(command, "create_pcb")==0){
					print("Please enter the name of the PCB to be created: ");
					user_input = sys_req (READ, TERMINAL, command, &buff_size_ptr);
					if(user_input > 80)
						print("This is too large for a command, type 'help' if you're having problems.\n");
					else { 
						command[strlen(command)-1]='\0'; // in order to remove the new line by a null character
						fprintf(fPtr, "%s ", command);
						strcpy(pro_name,&command[0]);
						print("Please enter the PCB's class (type only 10 or 11): ");
						user_input = sys_req (READ, TERMINAL, command, &buff_size_ptr);
						if(user_input > 80)
							print("This is too large for a command, type 'help' if you're having problems.\n");
						else{
							pclass=atoi(command);
							fprintf(fPtr, "%d ", pclass);
							print("Please enter the PCB's priority ( between -128 and 127): ");
							user_input = sys_req (READ, TERMINAL, command, &buff_size_ptr);
							if(user_input > 80)
								print("This is too large for a command, type 'help' if you're having problems.\n");
							else{
								priority=atoi(command);
								fprintf(fPtr, "%d ", priority);
								Create_PCB(pro_name, pclass, priority);
							}
						}
					}
				}else if(strcmp(command, "delete_pcb")==0){
					print("Please enter the process's name to be deleted: ");
					user_input = sys_req (READ, TERMINAL, command, &buff_size_ptr);
					if(user_input > 40)
						print("This is too large for a command, type 'help' if you're having problems.\n");
					else {
						command[strlen(command)-1]='\0'; // in order to remove the new line by a null character
						fprintf(fPtr, "%s ", command);
						Delete_PCB(command);
					}
				}
 **************************  R4 Changes (removing create_PCB) ************************/
				}else if(strcmp(command, "block")==0){
					print("Please enter the process's name to be blocked: ");
					user_input = sys_req (READ, TERMINAL, command, &buff_size_ptr);
					if(user_input > 40)
						print("This is too large for a command, type 'help' if you're having problems.\n");
					else {
						command[strlen(command)-1]='\0'; // in order to remove the new line by a null character
						fprintf(fPtr, "%s ", command);
						block(command);
					}
				}else if(strcmp(command, "unblock")==0){
					print("Please enter the process's name to be unblocked: ");
					user_input = sys_req (READ, TERMINAL, command, &buff_size_ptr);
					if(user_input > 40)
						print("This is too large for a command, type 'help' if you're having problems.\n");
					else {
						command[strlen(command)-1]='\0'; // in order to remove the new line by a null character
						fprintf(fPtr, "%s ", command);
						unblock(command);
					}
				}else if(strcmp(command, "suspend")==0){
					print("Please enter the process's name to be suspended: ");
					user_input = sys_req (READ, TERMINAL, command, &buff_size_ptr);
					if(user_input > 40)
						print("This is too large for a command, type 'help' if you're having problems.\n");
					else {
						command[strlen(command)-1]='\0'; // in order to remove the new line by a null character
						fprintf(fPtr, "%s ", command);
						suspend(command);
					}
				}else if(strcmp(command, "resume")==0){
					print("Please enter the process's name to be resumed: ");
					user_input = sys_req (READ, TERMINAL, command, &buff_size_ptr);
					if(user_input > 40)
						print("This is too large for a command, type 'help' if you're having problems.\n");
					else {
						command[strlen(command)-1]='\0'; // in order to remove the new line by a null character
						fprintf(fPtr, "%s ", command);
						resume(command);
					}
				}else if(strcmp(command, "set_priority")==0){
					print("Please enter the process's name to change the priority: ");
					user_input = sys_req (READ, TERMINAL, command, &buff_size_ptr);
					if(user_input > 40)
						print("This is too large for a command, type 'help' if you're having problems.\n");
					else {
						command[strlen(command)-1]='\0'; // in order to remove the new line by a null character
						fprintf(fPtr, "%s ", command);
						strcpy(pro_name,&command[0]);
						print("Please enter the new PCB's priority (between -128 and 127): ");
						user_input = sys_req (READ, TERMINAL, command, &buff_size_ptr);
						if(user_input > 80)
							print("This is too large for a command, type 'help' if you're having problems.\n");
						else{
							priority=atoi(command);
							set_priority(pro_name, priority);
						}
					}
				}else if(strcmp(command,"show_all") == 0){
					Show_All();
				}
				else if(strcmp(command,"show_rdy") == 0){
					Show_Ready();
				}
				else if(strcmp(command,"show_block") == 0){
					Show_Blocked();
				}else if(strcmp(command, "show_pcb")==0){
					print("Please enter the process's name to be shown: ");
					user_input = sys_req (READ, TERMINAL, command, &buff_size_ptr);
					if(user_input > 40)
						print("This is too large for a command, type 'help' if you're having problems.\n");
					else {
						command[strlen(command)-1]='\0'; // in order to remove the new line by a null character
						fprintf(fPtr, "%s ", command);
						Show_PCB(command);
					}
				}else if(strcmp(command,"history") == 0){
					rewind(fPtr);
					fgets(command, 80, fPtr);
					while(!feof(fPtr)){
							value = sprintf(buff, "%s", command);
							sys_req(WRITE, TERMINAL, buff, &value);
							pagination();
							fgets(command, 80, fPtr);
					}
/**************************************  R3 part  **************************************/
				}else if(strcmp(command,"test_r3") == 0){
						test_R3();
/**************************************  R4 part  **************************************/
				}else if(strcmp(command, "load_prog")==0){
					print("Please enter the name of the program to be loaded: ");
					user_input = sys_req (READ, TERMINAL, command, &buff_size_ptr);
					if(user_input > 80)
						print("This is too large for a command, type 'help' if you're having problems.\n");
					else { 
						command[strlen(command)-1]='\0'; // in order to remove the new line by a null character
						fprintf(fPtr, "%s ", command);
						strcpy(pro_name,&command[0]);
						print("Please enter the program's priority ( between -128 and 127): ");
						user_input = sys_req (READ, TERMINAL, command, &buff_size_ptr);
						if(user_input > 80)
							print("This is too large for a command, type 'help' if you're having problems.\n");
						else{
							priority=atoi(command);
							fprintf(fPtr, "%d ", pclass);
							Load_Program(pro_name, priority);
							}
						}
				}else if(strcmp(command, "terminate_prog")==0){
					print("Please enter the name of the program to be terminated: ");
					user_input = sys_req (READ, TERMINAL, command, &buff_size_ptr);
					if(user_input > 80)
						print("This is too large for a command, type 'help' if you're having problems.\n");
					else { 
						command[strlen(command)-1]='\0'; // in order to remove the new line by a null character
						fprintf(fPtr, "%s ", command);
						Terminate_Program(command);
						}
				}else if(strcmp(command,"dispatch") == 0){
						dispatch();
				}else	
					print("invalid command");	
				
		}
		fputc('\n', fPtr);
		sys_free_mem(command);
			
	}while(strcmp(command, "terminate")!=0);
	/***************** ending the while loop********************/	
		fclose(fPtr);
	return;
}

void err_hand(int error_num){

		switch(error_num){
			case OK: 
				break;
			case ERR_SUP_INVDEV:print("Do not know");
				break;
			case ERR_SUP_INVOPC: print("invalid device id");
				break;

			case ERR_SUP_INVPOS: print("invalid character position");
				break;
			 case ERR_SUP_RDFAIL:  print(" read failed ");
				break;
			case ERR_SUP_WRFAIL :  print(" write failed ");
				break;
			case ERR_SUP_INVMEM :  print(" invalid memory block pointer ");
				break;
			case ERR_SUP_FRFAIL :  print(" free failed ");
				break;
			case ERR_SUP_INVDAT :  print(" invalid date ");
				break;
			case ERR_SUP_DATNCH :  print(" date not changed ");
				break;
			case ERR_SUP_INVDIR :  print(" invalid directory name  ");
				break;
			case ERR_SUP_DIROPN :  print(" directory open error ");
				break;
			case ERR_SUP_DIRNOP :  print(" no directory is open ");
				break;
			case ERR_SUP_NOENTR :  print(" no more directory entries ");
				break;
			case ERR_SUP_NAMLNG :  print(" name too long for buffer ");
				break;
			case ERR_SUP_DIRCLS :  print(" directory close error ");
				break;
			case ERR_SUP_LDFAIL :  print(" program load failed ");
				break;
			case ERR_SUP_FILNFD :  print(" file not found ");
				break;
			case ERR_SUP_FILINV :  print(" file invalid ");
				break;
			case ERR_SUP_PROGSZ :  print(" program size error ");
				break;	
			case ERR_SUP_LDADDR :  print(" invalid load address ");
				break;
			case ERR_SUP_NOMEM :  print(" memory allocation error ");
				break;
			case ERR_SUP_MFREE :  print(" memory free error ");
				break;
			case ERR_SUP_INVHAN :  print(" invalid handler address ");
				break;
			default: print("Unbelievable error after all the checking.");
				break;
		}
}

/*
 ============================================================================
 Function Name      : displayDate
 Parameters         : none
 Description        : displays the value stored in the global variable for 
					  system date
 ============================================================================
 */
void displayDate(){
	char buff[80];
	int length;
	
	date_rec *datePtr;
	datePtr = (date_rec*)sys_alloc_mem(3 * sizeof(int));
	sys_get_date(datePtr);
	//Display the date
	length = sprintf(buff, "\n\nDate: %d/%d/%d", datePtr->month, datePtr->day, datePtr->year);
	sys_req(WRITE, TERMINAL, buff, &length);
	pagination();
	sys_free_mem(datePtr);
	
}//end displayDate

/*
 ============================================================================
 Function Name      : setDate
 Parameters         : character array that contains the date in the form 
					  mm/dd/yyyy
 Description        : changes the value of the system date
 ============================================================================
 */
void setDate(char date[11]){
	date_rec *datePtr;
	int error = 0;
	int leapYear = 0;
	char dd[3], mm[3], yyyy[5], buff[80];
	int m, d, y;
       //	int buflen = 80;

	if(strlen(date) != 10){
		print("Error! The date entered is invalid");
		return;
	}

	if(date[2] != '/' || date[5] != '/'){
		print("Error! The date entered is invalid");
		return;
	}

	mm[0] = date[0]; mm[1] = date[1]; mm[2] = '\0';
	m = atoi(mm);
	dd[0] = date[3]; dd[1] = date[4]; dd[2] = '\0';
	d = atoi(dd);
	yyyy[0] = date[6]; yyyy[1] = date[7]; yyyy[2] = date[8]; yyyy[3] = date[9]; yyyy[4] = '\0';
	y = atoi(yyyy);
	

	//REMOVE BEFORE SUBMITTING
	//buflen = sprintf(buff, "The date entered is %d/%d/%d", m, d, y);
	//sys_req(WRITE, TERMINAL, buff, &buflen);

	if(m < 1 || m > 12){
		print("Error! The month entered must have a value in the range 1-12");
		return;
	}
	if(d < 1 || m > 31){
		print("Error! The day entered must have a value in the range 1-31");
		return;
	}
	if(y < 1940){
		print ("Computers were not invented before 1940 silly!");
		return;
	}

	//Check leap year - the year is either divisible by both 100 and 4
	//OR its only divisible by 4 not by hundred
	if(y%400 == 0 || (y%100!=0 && y%4==0) ){
		leapYear = 1;
	}

	//Check the number of days in February
	if(m == 02){
		if(leapYear==1){
		  if(d > 29){
			 
		     print("Error! The day entered must have a value less than or equal to 29.");
		     return;
		  }
		}
		else{
			
			if(d > 28){
				print("Error! The day entered must have a value less than or equal to 28.");
				return;
			}
			
		}
	
	}//end check Febrary

	//Check the months with 30 days
	if(m == 4 || m == 9 || m == 11){
		if(d > 30){
		    print("Error! The month entered only has 30 days.");
			return;
		}
	}

	//Check the months with 31 days
	if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12){
		if(d > 31){
			
		    print("Error! The month entered only has 31 days.");
			return;
		}
	}

	//Store the inputted values into date_rec structure
	datePtr->month = m;
	datePtr->day = d;
	datePtr->year = y;

	error = sys_set_date(datePtr);
	if(error == 0)
		return;

	//check for error codes
	if(error == -108){
		print("Error! The date is invalid.");
	}
	if(error == -109){
		print("Error! The date was not properly changed.");
	}
}//end setDate

/*
 ============================================================================
 Function Name      : version
 Parameters         : none
 Description        : This function prints the version we are actually working on.
					  We could change it manually. It is now 1.0
 ============================================================================
 */
void version(){
print("MPX Version is 3.0");
}

/*
 ============================================================================
 Function Name      : terminateMpx
 Parameters         : none
 Description        : This function terminates the program after asking for
					  the user's confirmation
 ============================================================================
 */
void terminateMpx(){
// Buffer and Temp Arrays  are used to hold the input and format it
	char buffer[80];
	char temp[80];int buf_size;

	//writing to the screen via the sys req
	print("Are you sure you want to exit MPX?\n");
	print("Please type yes or no\n>");
	//Getting input from the user using stdin
	sys_req(READ, TERMINAL,temp, &buf_size);
	
	//Deleting possible spaces
	strcpy(buffer, format(&temp[0]));

	//If the user enter a word other than yes (Even if it is an error), the system will not exit
	if(strcmp(buffer,"yes") == 0){
		//terminating the program
		sys_exit();
	}//end if
	
}//close terminateMpx()


/*
 ============================================================================
 Function Name      : format
 Parameters         : character array
 Description        : This function deletes the spaces and /n characters
					  entered by the user. This is useful when comparing
					  input and command.
 ============================================================================
 */
char * format(char instring[])
{
	int i;
	int j=0;
	char outstring[80];
    
	for(i=0; instring[i]!='\0'; i++)
	{
	// Treatment of cases using switch statement
		switch(instring[i])
		{
		case ' ':
			break;
		case '\n':
			break;
		default :
	
		// we need also to lower the output string
		outstring[j] = tolower(instring[i]);
		j++;
		}
	}
	outstring[j]='\0';
	return outstring;

}//end format function

/*
 ============================================================================
 Function Name      : help
 Parameters         : none
 Description        : This function displays the available commands and calls 
						function command_sep if user requires help info.
 ============================================================================
 */
void help(){ 

	int err, i, value, size;
	int counter = 1;
	char command[20];
	char user_input[80];
	char buff[50];
	FILE *fPtr;

	print("The following MPX commands are defined internally. Type \"help\" to see this list.");
	print("Type \"help! 'name'\" to find out more about the function 'name'.\n\n"); 

	if((fPtr = fopen( "helpc.txt", "r" )) == NULL){
		print("File could not be accessed.");
	}
	else{
		/*reads file & displays list of available commands*/
		fgets(command, sizeof(command), fPtr);
		while(!feof(fPtr)){
			value = sprintf(buff, "%s", command);
			sys_req(WRITE, TERMINAL, buff, &value);
			pagination();
			fgets(command, sizeof(command), fPtr);
		}
		fclose(fPtr);
	}
	
	// print("Or enter 'x' to go back.\n>");
	// char key = getchar();
	// getchar();
	
	// if(key == 'x')
		// return;
	// else{
		// size = sizeof(user_input);
		// err = sys_req(READ, TERMINAL, user_input, &size);
	// }
	// /*tests for user input*/
	// if(err >= 0){
		
		// /*concats '\0' char to end of user input for seperation*/
        // for(i = 0; i < sizeof(user_input); i++){
            // if(user_input[i] == '\n'){
                // user_input[i] = '\0';
                // break;
            // }
        // }
		
		// /*tests for num of spaces user input*/
        // for(i = 0; i < sizeof(user_input); i++){
            // if(user_input[i] == ' ')
                // counter++;
        // }
		
		// /*checks for a valid command*/
        // if(counter > 2){
            // print("Error: Command not recognized.");
		// }
        // else
            // command_sep(user_input);
    // }
} //end help

/*
 ============================================================================
 Function Name      : command_sep
 Parameters         : char array that contains the users command
 Description        : This functions grabs the users help command and calls
						the function help_info.
 ============================================================================
 */
// void command_sep(char input[])
// {
	// unsigned num;
    // char *split_comm;
    // int counter = 1;
	
	// split_comm = (char *)sys_alloc_mem(80 * sizeof(char));
	// split_comm = strtok(input, "!");
	
	// /*tests for available memory to allocate*/
	// if(split_comm == NULL){
		// print("Allocation of memory failed.");
	// }
	
	// /*splits and grabs the users command from help*/
	// while( split_comm != NULL ){
		// if(counter == 2){
		 // help_info(split_comm);
		// }
		// split_comm = strtok(NULL, " ");
		// counter++;
	// }
	// sys_free_mem(split_comm);
// } //end command_sep

/*
 ============================================================================
 Function Name      : help_info
 Parameters         : char pointer that points to the users help command
 Description        : This function reads in the file containing help
						commands and displays the users selected command info.
 ============================================================================
 */
void help_info(char *command)
{
	char read_com[20];
	char line[80];
	FILE *fPtr;
	int value;
	char buff[50];
	int counter = 0;

	if((fPtr = fopen( "helpi.txt", "r" )) == NULL){
		print("File could not be accessed.");
	}
	else{
		fscanf(fPtr, "%s", read_com);
		
		/*reads helpi file and looks for users command*/
		while(!feof(fPtr)){
			if(!strcmp(command, read_com)){
				fgets(line, sizeof(line), fPtr);
				value = sprintf(buff, "%s%s", read_com, line);
				sys_req(WRITE, TERMINAL, buff, &value);
				pagination();
				break;
			}
			else{
				counter++;
				fgets(line, sizeof(line), fPtr);
				if(counter == NUM_LINES_HELPI){
					print("Help command not recognized.");
				}
			}

			fscanf(fPtr, "%s", read_com);
		}
		fclose(fPtr);
		
	}
} //end help_info

void print (char* str){
	int buff_size=strlen(str);
	char buff;
	
	sys_req(WRITE, TERMINAL, str, &buff_size);
	pagination();
}

void pagination(){
	COUNT_LINES_PRINTED++;
	//Check to see if a new page is required
	if(COUNT_LINES_PRINTED == 25){
		COUNT_LINES_PRINTED = 0;
		//wait for the user to press enter before continuing to the next page
		print("Hit enter to see more"); //-----------------------------------------------------------------------------------------------------------------------------
		USERINPUT =  getchar();
		if(USERINPUT == '\r')
			print("\f");
	}
}

 /*
 ============================================================================
 Function Name      : directory
 Parameters         : none
 Description        : displays in the current directory the files' name ending
					with the .MPX extension along with their size
 ============================================================================
 */
void directory(){
    int buff_size_ptr;
    int buff_size=30;
    char buffer [80];
    char buf_name[50];
    int* buf_size_ptr;
    long* file_size_ptr;
	char *cmd;

    print("Please enter the directory path: ");
	sys_req(READ, TERMINAL, buffer , &buff_size_ptr);
	cmd= (char*) sys_alloc_mem(buff_size_ptr);
	cmd = strtok(buffer, "\n"); //cuts off the "enter" hit by the user to enter the command	
	
	//cmd=format (&buffer[0]);
	if(sys_open_dir(cmd)== 0)
	{
	    print( "FileName         Size(in bytes)\n");
		file_size_ptr= (long*) sys_alloc_mem(sizeof(long));
	    while (sys_get_entry(buf_name , buff_size, file_size_ptr)== 0){
			sprintf(buffer, "%-20s   %-10d \n", buf_name, *file_size_ptr);
			print(buffer);
			pagination();
		}
	}else
		print( "There is an error with opening the directory");
    if(sys_close_dir ()!=0)
        print( "There was an error with closing the file");
		
	sys_free_mem(cmd);
}

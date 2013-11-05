//R3 header file

#ifndef R3_h
#define R3_h

#include <stdio.h>
#include <string.h>
#include <dos.h>

// The context and params structure
typedef struct context{
unsigned int BP, DI, SI, DS, ES;
unsigned int DX, CX, BX, AX;
unsigned int IP, CS, FLAGS;
} context;

typedef struct params{
int op_code; // operation code.....either IDLE or EXIT
int device_id;  //TERMINAL, COM_PORT
unsigned char *buff_addr; //buffer address
int *count_addr; //size of the buffer
} params;


// The functions' prototype

void interrupt sys_call();
void interrupt dispatch();
void test_R3();
void test1_R3(void);
void test2_R3(void);
void test3_R3(void);
void test4_R3(void);
void test5_R3(void);

#endif
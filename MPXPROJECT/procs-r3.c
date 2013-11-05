/***********************************************************
	MPX: The MultiProgramming eXecutive
	Project to Accompany
	A Practical Approach to Operating Systems
	Malcolm G. Lane & James D. Mooney
	Copyright 1993, P.W.S. Kent Publishing Co., Boston, MA.

	File Name: procs-r3.c

	Author: M.G.Lane, J. Mooney
	Version: 2.0
	Date: 01/03/93

	Purpose: Process Management command procedures


	Environments: This file is system independent.
		
	Procedures:
                             test1_R3 - test process
                             test2_R3 - test process
                             test3_R3 - test process
                             test4_R3 - test process
                             test5_R3 - test process

*****************************************************************************

  Change Log:

	05/16/88  mgl	Initial Version
	07/17/88  mgl	Final documentation changes
	08/13/92  jdm	Update for Version 2.0
	12/23/92  jdm	Revised count values
  	12/28/92  jdm	changed file name, moved to support
	01/03/93  jdm	changed test procedure names

*****************************************************************************/

#include "mpx_supt.h"
#include "R3.h"

/* loop counts */

#define RC_1 1
#define RC_2 2
#define RC_3 3
#define RC_4 4
#define RC_5 5






/*
	Procedures: testx_R3 (x = 1, 2, 3, 4, 5)

	Purpose: test processes for Module R3


	Parameters: none	

	Return value: none

	Calls:	sys_req
        	printf

	Globals: none

	Algorithm:

	   Each process prints a message to the screen and gives up
           control to the dispatcher using sys_req.  Each process
           loops a certain number of times, displaying a message to
           the screen inside the loop.  (test1 loops 5 times, test2
           loops 10, test3 loops 15, test4 loops 20, and test5 loops
           25 times).  Each test process eventually requests
           termination.  If a dispatcher dispatches a test process
           after it requested termination, it prints a message
           indicating so, and the process starts over.
*/


void test1_R3()
{
 	int ix;	/* loop index */
 	
        /* repeat forever if termination fails */
 	while (TRUE) {

                /* loop for the prescribed number of times */
 		for (ix=1; ix <= RC_1; ix++) {

			/* give up control to the dispatcher */
			printf("test1 dispatched; loop count = %d\n",ix);
			sys_req(IDLE, NO_DEV, NULL, 0);
		}
		
 		/* request termination */
		sys_req(EXIT, NO_DEV, NULL, 0);

                /* display error message if dispatched again */
		printf ("test1 dispatched after it exited!!!\n");
	}
 }

void test2_R3()
{
 	int ix;	/* loop index */
 	
        /* repeat forever if termination fails */
 	while (TRUE) {

                /* loop for the prescribed number of times */
 		for (ix=1; ix <= RC_2; ix++) {

			/* give up control to the dispatcher */
			printf("test2 dispatched; loop count = %d\n",ix);
			sys_req(IDLE, NO_DEV, NULL, 0);
		}

 		/* request termination */
		sys_req(EXIT, NO_DEV, NULL, 0);

                /* display error message if dispatched again */
		printf ("test2 dispatched after it exited!!!\n");
	}
 }

void test3_R3()
{
 	int ix;	/* loop index */
 	
        /* repeat forever if termination fails */
 	while (TRUE) {

                /* loop for the prescribed number of times */
 		for (ix=1; ix <= RC_3; ix++) {

			/* give up control to the dispatcher */
			printf("test3 dispatched; loop count = %d\n",ix);
			sys_req(IDLE, NO_DEV, NULL, 0);
		}

 		/* request termination */
		sys_req(EXIT, NO_DEV, NULL, 0);

                /* display error message if dispatched again */
		printf ("test3 dispatched after it exited!!!\n");
	}
 }

void test4_R3()
{
 	int ix;	/* loop index */
 	
        /* repeat forever if termination fails */
 	while (TRUE) {

                /* loop for the prescribed number of times */
 		for (ix=1; ix <= RC_4; ix++) {

			/* give up control to the dispatcher */
			printf("test4 dispatched; loop count = %d\n",ix);
			sys_req(IDLE, NO_DEV, NULL, 0);
		}

 		/* request termination */
		sys_req(EXIT, NO_DEV, NULL, 0);

                /* display error message if dispatched again */
		printf ("test4 dispatched after it exited!!!\n");
	}
 }

void test5_R3()
{
 	int ix;	/* loop index */
 	
        /* repeat forever if termination fails */
 	while (TRUE) {

                /* loop for the prescribed number of times */
 		for (ix=1; ix <= RC_5; ix++) {

			/* give up control to the dispatcher */
			printf("test5 dispatched; loop count = %d\n",ix);
			sys_req(IDLE, NO_DEV, NULL, 0);
		}

 		/* request termination */
		sys_req(EXIT, NO_DEV, NULL, 0);

                /* display error message if dispatched again */
		printf ("test5 dispatched after it exited!!!\n");
	}
 }

/* END OF FILE */
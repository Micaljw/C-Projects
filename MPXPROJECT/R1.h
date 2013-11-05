#ifndef R1_H_
#define R1_H_
#include "mpx_supt.h"

void sys_get_date(date_rec *date_p);
int sys_set_date(date_rec *date_p);
void displayDate();
void setDate(char[]);
char* format(char instring[]);
void version();
void terminateMpx();
void help_info(char *user_command);
void command_sep(char in[]);
void help();
void cmd_hand();
void err_hand(int error_num);
void directory();
void print (char* str);
void pagination();

#endif
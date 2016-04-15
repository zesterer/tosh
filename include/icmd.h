#ifndef TOSH_ICMD
#define TOSH_ICMD

int tosh_icmd_cd(char* args[]);
int tosh_icmd_help(char* args[]);
int tosh_icmd_exit(char* args[]);

int tosh_num_internal_cmd();

char* internal_cmd_str[];
int (*internal_cmd_func[])(char**);

#endif

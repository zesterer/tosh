// local
#include "icmd.h"
#include "error.h"

// standard
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"

int internal_cmd_count = 3;
char* internal_cmd_str[] = {"cd",
							"help",
							"exit"};

int (*internal_cmd_func[])(char**) = {&tosh_icmd_cd,
									&tosh_icmd_help,
									&tosh_icmd_exit};

int tosh_num_internal_cmd()
{
	return internal_cmd_count;
}

int tosh_icmd_cd(char* args[])
{
	if (args[1] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("tosh");
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("tosh");
		}
	}

	return 1;
}

int tosh_icmd_help(char* args[])
{
	printf("TOSH - Terribly Ordinary SHell\n");
	printf("Run a command, followed by arguments separated by spaces\n");
	printf("Built in commands:\n");

	for(int i = 0; i < tosh_num_internal_cmd(); i ++)
	{
		printf("--> %s\n", internal_cmd_str[i]);
	}

	printf("Type 'man tosh' for more information.\n");
	return 1;
}

int tosh_icmd_exit(char* args[])
{
	return 0;
}

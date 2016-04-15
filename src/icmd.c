// local
#include "icmd.h"
#include "error.h"
#include "exec.h"
#include "color.h"

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
	if (args[1] != NULL)
	{
		args[0] = "man";
		return tosh_launch(args);
	}

	printf("%sTosh%s - %sThe Terribly Ordinary Shell%s\n",
			TOSH_ANSI_CODE_LIGHT_BLUE,
			TOSH_ANSI_CODE_RESET,
			TOSH_ANSI_CODE_LIGHT_GREEN,
			TOSH_ANSI_CODE_RESET);
	printf("Run a command, followed by arguments separated by spaces\n");
	printf("Internal commands:\n");

	for(int i = 0; i < tosh_num_internal_cmd(); i ++)
	{
		printf("--> %s%s%s\n", TOSH_ANSI_CODE_YELLOW, internal_cmd_str[i], TOSH_ANSI_CODE_RESET);
	}

	printf("Type %shelp %s<manpage>%s for more information.\n",
			TOSH_ANSI_CODE_YELLOW,
			TOSH_ANSI_CODE_LIGHT_RED,
			TOSH_ANSI_CODE_RESET);
	return 1;
}

int tosh_icmd_exit(char* args[])
{
	return 0;
}

// local
#include "tosh.h"
#include "read.h"
#include "exec.h"
#include "color.h"

// standard
#include "stdlib.h"
#include "stdio.h"

void tosh_init()
{
	printf("Welcome to tosh, the Terribly Ordinary Shell\n");
	printf("Type %shelp%s for instructions\n", TOSH_ANSI_CODE_YELLOW, TOSH_ANSI_CODE_RESET);
}

void tosh_loop()
{
	char* line;
	char** args;
	int status;

	do
	{
		printf("%s%s%s@%s%s%s$ ",
				TOSH_ANSI_CODE_LIGHT_RED,
				getenv("USERNAME"),
				TOSH_ANSI_CODE_RESET,
				TOSH_ANSI_CODE_LIGHT_GREEN,
				getenv("PWD"),
				TOSH_ANSI_CODE_RESET);

		line = tosh_read_line();
		args = tosh_split_line(line);

		status = tosh_execute(args);

		free(line);
		free(args);
	} while (status);
}

int tosh_end()
{
	// End
	return EXIT_SUCCESS;
}

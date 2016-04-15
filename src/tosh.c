// local
#include "tosh.h"
#include "read.h"
#include "exec.h"

// standard
#include "stdlib.h"
#include "stdio.h"

void tosh_init()
{
	// Init
}

void tosh_loop()
{
	char* line;
	char** args;
	int status;

	do
	{
		printf("$ ");

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

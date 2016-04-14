// Sys
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"

// Local
#include "command.h"

int toshCommand(const char* command, char* out, int max_len)
{
	FILE* stream = popen(command, "r");

	unsigned int pos = 0;
	while (!feof(stream))
	{
		char cchar;

		if(pos < max_len)
		{
			cchar = fgetc(stream);
			out[pos] = cchar;
			pos ++;
		}
		else
			break;
	}
	out[pos - 1] = '\0';
	fclose(stream);

	//printf("Command : %s\n", out);

	return 0;
}

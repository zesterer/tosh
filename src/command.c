// Sys
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "errno.h"

// Local
#include "command.h"
#include "config.h"

int toshCommand(const char* command, char* out, int max_len)
{
	if (strncmp(command, "cd", 2) == 0)
	{
		char location[MAX_LINE];
		strcpy(location, command + 3);
		int loc_len = strlen(location);
		if (location[loc_len - 1] == '\n')
			location[loc_len - 1] = '\0';

		if (loc_len != 0)
		{
			if (chdir(location) != 0)
				printf("%s\n", strerror(errno));
		}
		else
		{
			if (chdir(getenv("HOME")) != 0)
				printf("%s\n", strerror(errno));
		}
		out[0] = '\0';
	}
	else
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
	}

	return 0;
}

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "errno.h"
#include "unistd.h"

// Local
#include "interpret.h"
#include "config.h"

#define MAX_LINE_LENGTH 512

enum
{
	PS_TOKEN,
	PS_WHITESPACE,
};

enum
{
	CMD_NONE,
	CMD_CD,
};

void interpret(const char* line)
{
	char tmp[MAX_LINE_LENGTH];

	bool do_parse = true;
	unsigned int state = 0;
	unsigned int last_pos = 0;
	unsigned int pos = 0;
	unsigned int command = CMD_NONE;

	while (do_parse)
	{
		switch(line[pos])
		{
			case ' ':
			case '\t':
			case '\0':
				if (state == PS_TOKEN)
				{
					memcpy(tmp, line + last_pos, pos - last_pos);

					if (tmp[pos - last_pos - 1] == '\n')
						tmp[pos - last_pos - 1] = '\0';
					else
						tmp[pos - last_pos] = '\0';
					//printf("%s\n", tmp);

					if (strcmp(tmp, "cd") == 0)
					{
						command = CMD_CD;
						//printf("Found command cd!\n");
					}
					else if (last_pos == 0)
						system(line);

					if (command != CMD_NONE)
					{
						switch (command)
						{
							case CMD_CD:
								chdir(tmp);
								//printf("Change directory to %s!\n", tmp);
								break;
							default:
								break;
						}
					}
				}
				state = PS_WHITESPACE;

				if (line[pos] == '\0')
					do_parse = false;
				break;

			default:
				if (state == PS_WHITESPACE)
				{
					last_pos = pos;
				}
				state = PS_TOKEN;
				break;
		}

		pos ++;
	}
}

int main(int argc, char* argv[])
{
	char line[MAX_LINE_LENGTH];

	printf("Welcome to TOSH!\n");

	setenv("PROMPT_SCRIPT", "echo -n \"{tput setaf 6}{date \"+%H:%M:%S\"}\x1B[0m{tput setaf 9}{echo -n $USERNAME}\x1B[0m@{tput setaf 2}{echo -n $PWD}\x1B[0m$ \"", 1);

	while (true)
	{
		char prompt[MAX_LINE_LENGTH];
		toshEval(getenv("PROMPT_SCRIPT"), prompt, MAX_LINE);
		printf("%s", prompt);

		if (!fgets(line, MAX_LINE_LENGTH, stdin))
			break;

		char tmp[MAX_LINE];
		int result = toshEval(line, tmp, MAX_LINE);
		if (result == 0)
			printf("%s", tmp);
	}

	return 0;
}

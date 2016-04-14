#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "errno.h"
#include "unistd.h"

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
	
	printf("Welcome to Thoth Shell.\n");
	
	while (1)
	{
		char username[64];
		char wd[MAX_LINE_LENGTH];
		cuserid(username);
		printf("\x1b[31m%s\x1b[0m@\x1b[32m%s\x1b[0m$ ", username, getcwd(wd, MAX_LINE_LENGTH));
		
		if (!fgets(line, MAX_LINE_LENGTH, stdin))
			break;
		
		interpret(line);
	}
	
	return 0;
}

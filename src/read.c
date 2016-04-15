// local
#include "read.h"
#include "conf.h"
#include "error.h"

// standard
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

char* tosh_read_line()
{
	int buff_size = TOSH_RL_BUFFSIZE;
	int pos = 0;
	char* buffer = malloc(sizeof(char) * buff_size);
	int c;

	if (!buffer)
	{
		tosh_error("tosh: Error when allocating line buffer");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		c = getchar();

		if (c == EOF || c == '\n')
		{
			buffer[pos] = '\0';
			return buffer;
		}
		else
		{
			buffer[pos] = c;
		}

		pos ++;

		if (pos >= buff_size)
		{
			buff_size += TOSH_RL_BUFFSIZE;
			buffer = realloc(buffer, buff_size);

			if (!buffer)
			{
				tosh_error("tosh: Error when reallocating line buffer");
				exit(EXIT_FAILURE);
			}
		}
	}
}

char** tosh_split_line(const char* line)
{
	int buff_size = TOSH_TOK_BUFFSIZE;
	int pos = 0;
	char** tokens = malloc(sizeof(char*) * buff_size);
	char* token;

	if (!tokens)
	{
		tosh_error("tosh: Error when allocating token buffer");
		exit(EXIT_FAILURE);
	}

	token = strtok((char*)line, TOSH_TOK_DELIM);
	while (token != NULL)
	{
		tokens[pos] = token;
		pos ++;

		if (pos >= buff_size)
		{
			buff_size += TOSH_TOK_BUFFSIZE;
			tokens = realloc(tokens, sizeof(char*) * buff_size);

			if (!tokens)
			{
				tosh_error("tosh: Error when reallocating token buffer");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOSH_TOK_DELIM);
	}

	tokens[pos] = NULL;
	return tokens;
}

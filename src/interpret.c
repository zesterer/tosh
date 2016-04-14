// Sys
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

// Local
#include "interpret.h"
#include "command.h"
#include "config.h"

int toshEval(const char* expr, char* out, int len)
{
	unsigned int cpos = 0;
	unsigned int lpos = 0;
	unsigned int opos = 0;
	char cchar, lchar;
	lchar = '\0';

	bool do_parse = true;

	bool found_bracket = false;
	int bracket_level = 0;

	int str_len = strlen(expr);
	if (str_len < len)
		len = str_len;

	while (do_parse && cpos < len)
	{
		switch(cchar = expr[cpos])
		{
			case '\0':
				do_parse = false;
				break;

			case '{':
				if (lchar == '\\')
				{
					if (!found_bracket)
					{
						out[opos] = cchar;
						opos ++;
						out[opos] = '\0';
					}
				}
				else
				{
					if (!found_bracket)
					{
						found_bracket = true;
						bracket_level = 0;
						lpos = cpos;
					}
					bracket_level ++;
				}
				break;

			case '}':
				if (lchar == '\\')
				{
					if (!found_bracket)
					{
						out[opos] = cchar;
						opos ++;
						out[opos] = '\0';
					}
				}
				else
				{
					if (!found_bracket)
					{
						printf("%s\n", expr);
						printf("Error: unexpected character '%c' at position %i\n", cchar, cpos + 1);
						return 1;
					}
					else
					{
						bracket_level --;
						if (bracket_level == 0)
						{
							char tmpMsg[MAX_LINE];
							int result = toshEval(expr + lpos + 1, tmpMsg, cpos - lpos - 1);
							if (result == 0)
							{
								strcat(out, tmpMsg);
								opos += strlen(tmpMsg);
							}

							found_bracket = false;
						}
					}
				}
				break;

			default:
				if (!found_bracket)
				{
					out[opos] = cchar;
					opos ++;
					out[opos] = '\0';
				}
				break;
		}
		lchar = cchar;

		cpos ++;
	}

	out[opos] = '\0';

	char msg[MAX_LINE];
	memcpy(msg, expr, len);
	msg[len] = '\0';

	toshCommand(out, out, MAX_LINE);

	//printf("Evaluated '%s' to '%s'\n", msg, out);

	return 0;
}

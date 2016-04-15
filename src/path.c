// local
#include "path.h"

char* tosh_path_append(const char* path0, const char* path1, char* out)
{
	int cpos = 0;
	int opos = 0;
	int do_parse = 1;
	char c;
	char lc;

	do
	{
		lc = c;
		c = path0[cpos];

		switch(c)
		{
			case '\0':
				if (lc != '/')
				{
					out[opos] = '/';
					opos ++;
				}
				do_parse = 0;
				break;

			default:
				out[opos] = c;
				opos ++;
				break;
		}

		cpos ++;
	} while(do_parse && c != '\0' && c != '\n');

	cpos = 0;
	do_parse = 1;
	c = '\0';

	do
	{
		lc = c;
		c = path1[cpos];

		switch(c)
		{
			case '/':
				if (lc != '\0')
				{
					out[opos] = c;
					opos ++;
				}
				break;

			default:
				out[opos] = c;
				opos ++;
				break;
		}

		cpos ++;
	} while(do_parse && c != '\0' && c != '\n');

	if (c != '\0')
		out[opos] = '\0';

	return out;
}

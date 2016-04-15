// local
#include "error.h"
#include "color.h"

// standard
#include "stdio.h"

int tosh_error(const char* msg)
{
	fprintf(stderr, "%stosh: %s%s\n", TOSH_ANSI_CODE_RED, msg, TOSH_ANSI_CODE_RESET);
	return 0;
}

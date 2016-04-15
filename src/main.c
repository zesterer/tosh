// local
#include "tosh.h"
#include "error.h"

// standard
#include "stdlib.h"

int main(int argc, char* argv[])
{
	tosh_init();
	tosh_loop();

	return tosh_end();
}

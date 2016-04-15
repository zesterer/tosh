// local
#include "exec.h"
#include "icmd.h"

// standard
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"

int tosh_execute(char* args[])
{
	if (args[0] == NULL)
		return 1;

	for(int i = 0; i < tosh_num_internal_cmd(); i ++)
	{
		if (strcmp(args[0], internal_cmd_str[i]) == 0)
			return (*internal_cmd_func[i])(args);
	}

	return tosh_launch(args);
}

int tosh_launch(char* args[])
{
	pid_t pid;
	pid_t wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("tosh");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("tosh");
	}
	else
	{
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

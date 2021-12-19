#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
	char	*cat[4];
	char	*args[4];
	int pid;

	cat[0] = "/bin/cat";
	cat[1] = 0;
	args[0] = "----";
	args[1] = "test";
	args[2] = "test2";
	args[3] = 0;

	pid = fork();
	if (!pid)
	{
		execve(cat[0], args, envp);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
	return (0);
}


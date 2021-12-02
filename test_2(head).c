
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void	ft_pipe(char ***argcc, int i, char **envp)
{
	int		pid;
	int		pipe_1[2];

	pipe(pipe_1);
	pid = fork();
	if (!pid)
	{
		close(pipe_1[0]);
		dup2(pipe_1[1], 1);
		close(pipe_1[1]);
		execve(argcc[i][0], argcc[i], envp);
		exit(0);
	}
	else
	{
		close(pipe_1[1]);
		dup2(pipe_1[0], 0);
		close(pipe_1[0]);
		//waitpid(pid, NULL, 0);
	}
}

void	ft_return(char ***argcc, char **envp)
{
	int		pipe_1[2];

		if (!fork())
		{
			dup2(pipe_1[0], 0);
			close(pipe_1[1]);
			close(pipe_1[0]);
			execve(argcc[2][0], argcc[2], envp);
		}
}


int	main(int argc, char **argv, char **envp)
{
	char	**argcc[3];
	char	*yes[2];
	char	*head[2];
	char	*wc[2];

	yes[0] = "/usr/bin/yes";
	yes[1] = 0;
	head[0] = "/usr/bin/head";
	head[1] = 0;
	wc[0] = "/usr/bin/wc";
	wc[1] = 0;
	argcc[0] = yes;
	argcc[1] = head;
	argcc[2] = wc;
	ft_pipe(argcc, 0, envp);
	ft_pipe(argcc, 1, envp);
	ft_return(argcc, envp);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
}

//int	main(int argc, char **argv, char **envp)
//{
//	char	**argcc[3];
//	int		pipe_1[2];
//	int		pipe_2[2];
//	char	*yes[2];
//	char	*head[2];
//	char	*wc[2];
//	int		pipe_count = 2;
//	int		i;
//
//	yes[0] = "/usr/bin/yes";
//	yes[1] = 0;
//	head[0] = "/usr/bin/head";
//	head[1] = 0;
//	wc[0] = "/usr/bin/wc";
//	wc[1] = 0;
//	argcc[0] = yes;
//	argcc[1] = head;
//	argcc[2] = wc;
//	pipe(pipe_1);
//	if (!fork())
//	{
//		dup2(pipe_1[1], 1);
//		close(pipe_1[1]);
//		close(pipe_1[0]);
//		execve(argcc[0][0], argcc[0], envp);
//	}
//	pipe(pipe_2);
//	if (!fork())
//	{
//		dup2(pipe_1[0], 0);
//		close(pipe_1[1]);
//		close(pipe_1[0]);
//		dup2(pipe_2[1], 1);
//		close(pipe_2[1]);
//		close(pipe_2[0]);
//		execve(argcc[1][0], argcc[1], envp);
//	}
//	close(pipe_1[1]);
//	close(pipe_1[0]);
//	if (!fork())
//	{
//		dup2(pipe_2[0], 0);
//		close(pipe_2[1]);
//		close(pipe_2[0]);
//		execve(argcc[2][0], argcc[2], envp);
//	}
//	close(pipe_2[0]);
//	close(pipe_2[1]);
//	wait(0);
//	wait(0);
//	wait(0);
//}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_4(<<).c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 20:05:35 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/03 21:27:10 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

int	ft_strncmp2(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	count = 0;
	//printf("s1: %s\n", s1);
	//printf("s2: %s\n", s2);
//	if (s1 == NULL)
//		return (1);
	while (count < n && *(s1 + count) && *(s2 + count))
	{
		if (*(s1 + count) != *(s2 + count))
			return ((unsigned char)*(s1 + count)
					- (unsigned char)*(s2 + count));
		count++;
	}
	if (count < n)
	{
		if (*(s1 + count) != *(s2 + count))
			return ((unsigned char)*(s1 + count)
					- (unsigned char)*(s2 + count));
	}
	return ((unsigned char)0);
}

size_t	ft_strlen(char *str)
{
	size_t	size;

	size = 0;
	while (*str)
	{
		size++;
		str++;
	}
	return (size);
}

void ft_heredoc(char **argv, char **envp)
{
	int		pip[2];
	int		pid;
	char	*args_str;

	pipe(pip);
	pid = fork();
	if (!pid)
	{
		args_str = readline("> ");
		while (ft_strncmp2(args_str, argv[1], ft_strlen(argv[1])))
		{
			write(pip[1], args_str, ft_strlen(args_str));
			write(pip[1], "\n", 1);
			args_str = readline("> ");
		}
		close(pip[1]);
		close(pip[0]);
		exit (0);
	}
	else
	{
		close(pip[1]);
		dup2(pip[0], 0);
		close(pip[0]);
		waitpid(0, NULL, 0);
	}
}

void	ft_pipe(char **path, char **envp)
{
	int		pid;
	int		pip[2];

	pipe(pip);
	pid = fork();
	if (!pid)
	{
		close(pip[0]);
		dup2(pip[1], 1);
		close(pip[1]);
		execve(path[0], path, envp);
		exit(0);
	}
	else
	{
		close(pip[1]);
		dup2(pip[0], 0);
		close(pip[0]);
		//waitpid(pid, NULL, 0);
	}
}

void	ft_return(char **path, char **envp)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
//		dup2(pip[0], 0);
//		close(pip[0]);
//		close(pip[1]);
		execve(path[0], path, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		pip[2];
	int		status;
	char	*cat[3];
	char	*wc[3];

	cat[0] = "/bin/cat";
	cat[1] = 0;
	cat[2] = 0;
	wc[0] = "/usr/bin/wc";
	wc[1] = 0;
	wc[2] = 0;
	ft_heredoc(argv, envp);
	ft_pipe(wc, envp);
	ft_return(cat, envp);
	close(pip[0]);
	close(pip[1]);
	//waitpid(0, &status, 0);
	waitpid(0, &status, 0);
	waitpid(0, &status, 0);
}


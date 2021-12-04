/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_4(<<).c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 20:05:35 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/03 22:20:59 by eveiled          ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	int		pid;
	int		pip[2];
	char	*args_str;
	int		status;
	char	*cat[3];

	cat[0] = "/bin/cat";
	cat[1] = 0;
	cat[2] = 0;
	pipe(pip);
	if (pid < 0)
	{
		printf("pipe error in ft_exec\n");
		exit(1);
	}
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
		waitpid(0, &status, 0);
	}
	//pipe(pip_2);
	pid = fork();
	if (pid == 0)
	{
		write(2, "--\n", 3);
//		dup2(pip[0], 0);
//		close(pip[0]);
//		close(pip[1]);
		write(2, "++\n", 3);
		execve(cat[0], cat, envp);
	}
	close(pip[0]);
	close(pip[1]);
	//waitpid(0, &status, 0);
	waitpid(0, &status, 0);
}

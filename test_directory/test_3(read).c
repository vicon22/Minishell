/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_3(read).c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:57:59 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/02 19:04:32 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

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

void	ft_add(char **cat, char **argv, char **envp)
{
	int		pip[2];
	int		fd;
	int		pid;

	pipe(pip);
	fd = open(argv[2], O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd == -1)
	{
		write(2, "Error with open\n", 16);
		exit(1);
	}
	pid = fork();
	if (!pid)
	{
		dup2(fd, 1);
		execve(cat[0], cat, envp);
	}
	else
		waitpid(pid, NULL, 0);
}

void	ft_rewrite(char **cat, char **argv, char **envp)
{
	int		pip[2];
	int		fd;
	int		pid;

	pipe(pip);
	fd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
	{
		write(2, "Error with open\n", 16);
		exit(1);
	}
	pid = fork();
	if (!pid)
	{
		dup2(fd, 1);
		execve(cat[0], cat, envp);
	}
	else
		waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cat[3];

	cat[0] = "/bin/cat";
	cat[1] = 0;
	cat[2] = 0;
	printf("cat[1]: %s\n", cat[1]);
	printf("argv[1]: %s\n", argv[1]);
	printf("---\n");
	if (ft_strlen(argv[1]) == 1)
		ft_rewrite(cat, argv, envp);
	if (ft_strlen(argv[1]) == 2)
		ft_add(cat, argv, envp);
}

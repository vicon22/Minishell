/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:46:20 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/18 17:46:52 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add(char *file_name)
{
	int		fd;

	//write(2, "+++\n", 4);
	//pipe(pip);
	fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd == -1)
	{
		write(2, "Error with open\n", 16);
		return ;
	}
	//	pid = fork();
	//	if (!pid)
	//	{
	//		dup2(fd, 1);
	//	}
	dup2(fd, 1);
	//close(fd);
	//	else
	//		//waitpid(pid, NULL, 0);
}

void	ft_rewrite(char *file_name)
{
	//int		pip[2];
	int		fd;
	//int		pid;

	//write(2, "---\n", 4);
	fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
	{
		write(2, "Error with open\n", 16);
		return ;
	}
	//	pid = fork();
	//	if (!pid)
	//	{
	//		dup2(fd, 1);
	//	}
	dup2(fd, 1);
	//close(fd);
	//	else
	//		//waitpid(pid, NULL, 0);
	//	else
	//		//waitpid(pid, NULL, 0);
}

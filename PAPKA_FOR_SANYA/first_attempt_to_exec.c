/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_attempt_to_exec.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:45:26 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/01 18:57:53 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_2.h"

void	ft_exec(t_arg *lst, char **envp)
{
	int	pid;
	int	fd[2];
	int	check_command;

	pid = fork();
	//ft_check_build_functions();
	if (pid < 0)
	{
		printf("fork error in ft_exec\n");
		exit (1);
	}
	if (pid == 0)
	{
		execve(lst->path, lst->args, envp);
	}
	waitpid(pid, NULL, 0);
}

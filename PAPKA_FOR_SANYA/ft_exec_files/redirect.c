/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:42:00 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/19 13:38:32 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_arg	*ft_find_redirect(t_arg *lst)
{
	t_arg	*redirect;

	redirect = lst;
	while (redirect && ft_strncmp(redirect->content, "<<", 3)
		&& ft_strncmp(redirect->content, "<", 2))
	{
		//write(2, redirect->content, ft_strlen(redirect->content));
		//write(2, "\n", 1);
		if (!ft_strncmp(redirect->content, "|", 2))
		{
			redirect = NULL;
			break ;
		}
		redirect = redirect->next;
	}
	return (redirect);
}

void	ft_redirect(t_arg *redirect, char *file, char **envp)
{
	int	fd;

	(void)envp;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return ;
	else
		if (!ft_find_redirect(redirect->next))
			dup2(fd, 0);
}

char	**ft_redirect_in_command(t_arg *lst, char ***envp)
{
	t_arg	*needful;
	char	**args;

	args = NULL;
	needful = ft_find_redirect(lst);
	while (needful)
	{
//		write(2, "needful", 7);
//		write(2, needful->content, ft_strlen(needful->content));
//		write(2, "\n", 1);
		if (!ft_strncmp(needful->content, "<<", 3))
			ft_heredoc(needful, needful->next->content, *envp);
		else
			ft_redirect(needful, needful->next->content, *envp);
		args = ft_binding_args(args, needful->next->args, 0);
//		if (args)
//		{
//			write(2, "+++\n", 4);
//			show_args(args);
//		}
		needful = ft_find_redirect(needful->next);
	}
	return (args);
}

char	**ft_redirect_in_file(t_arg *lst, char ***envp)
{
	t_arg	*needful;
	char	**args;

	(void)envp;
	args = NULL;
	needful = ft_find_output(lst);
	while (needful)
	{
		if (ft_strlen(needful->content) == 1)
			ft_rewrite(needful->next->content);
		if (ft_strlen(needful->content) == 2)
			ft_add(needful->next->content);
		args = ft_binding_args(args, needful->next->args, 0);
//		if (args)
//		{
//			write(2, "+++\n", 4);
//			show_args(args);
//		}
		needful = ft_find_output(needful->next);
	}
	return (args);
}

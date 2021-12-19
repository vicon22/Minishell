/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 12:55:33 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/19 13:41:24 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_2.h"

void	signal_handler_in_exec(int status, char **argv, char ***envp)
{
	WIFEXITED(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_call_export(argv, envp, 130);
		if (WTERMSIG(status) == SIGQUIT)
			ft_call_export(argv, envp, 131);
	}
	else
	{
		if (status != 0)
			ft_call_export(argv, envp, 1);
		else
			ft_call_export(argv, envp, 0);
	}
}

int	ft_wait_all_child_processes(t_arg *lst)
{
	int		number_of_pipes;
	int		i;
	t_arg	*lst_saver;
	int		status;

	lst_saver = lst;
	number_of_pipes = 0;
	i = 0;
	status = 0;
	while (lst_saver)
	{
		if (!ft_strncmp(lst_saver->content, "|", 2))
			number_of_pipes++;
		lst_saver = lst_saver->next;
	}
	while (i < number_of_pipes)
	{
		waitpid(0, &status, 0);
		i++;
	}
	return (status);
}

void	ft_add_command_after_pipe(t_arg	*needful, char ***envp)
{
	t_arg	*arg_l;
	char	*args_str;

	args_str = readline("> ");
	if (!args_str)
		exit(0);
	arg_l = NULL;
	ft_parse_input_str(args_str, &arg_l);
	ft_handle_envps(arg_l, *envp);
	ft_set_funcs_structure(arg_l, &needful);
	ft_set_path(needful, ft_return_path(*envp), envp);
	ft_show_lst(needful);
	ft_free_lst(&arg_l);
	free(args_str);
}

void	ft_exec(t_arg *lst, char ***envp)
{
	int		in_out[2];
	int		in_out_2[2];
	t_arg	*needful;
	t_arg	*command;
	int		status;
	char	**args;
	char	**args2;

	in_out[0] = dup(0);
	in_out[1] = dup(1);
	if (lst->next == NULL)
		ft_return_one_command(lst->path, lst->args, envp);
	else
	{
		needful = lst;
		while (needful)
		{
			if (!ft_strncmp(needful->content, "|", 2) && !needful->next)
			{
				in_out_2[0] = dup(0);
				in_out_2[1] = dup(1);
				dup2(in_out[0], 0);
				dup2(in_out[1], 1);
				write(2, "second:needful: ", 15);
				write(2, needful->content, ft_strlen(needful->content));
				write(2, "\n", 1);
				ft_add_command_after_pipe(needful, envp);
				dup2(in_out_2[0], 0);
				dup2(in_out_2[1], 1);
			}
			args = ft_redirect_in_command(needful, envp);
			args2 = ft_redirect_in_file(needful, envp);
			command = ft_find_command(needful, envp);
			ft_putstr_fd("find command: ", 2);
			write(2, command->content, ft_strlen(command->content));
			write(2, "\n", 1);
			args = ft_binding_args(args, args2, 0);
			if (!ft_is_a_command(command))
			{
				args = ft_binding_args(command->args, args, 1);
				show_args(args);
				write(2, "needful: ", 9);
				write(2, needful->content, ft_strlen(needful->content));
				write(2, "\n", 1);
				if (!ft_find_output_int(needful) || ft_find_pipe_int(needful->next))
				{
					write(2, "return: ", 8);
					write(2, command->path, ft_strlen(command->path));
					write(2, "\n", 1);
					ft_return(command->path, args, envp);
					dup2(in_out[1], 1);
				}
				else if (!ft_find_pipe_int(needful->next) && ft_find_output_int(needful))
				{
					write(2, "pipe: ", 6);
					write(2, command->path, ft_strlen(command->path));
					write(2, "\n", 1);
					ft_pipe(command->path, args, envp);
				}
				if (ft_array_cpm(args, command->args))
					ft_free(args);
			}
			needful = ft_find_pipe(needful->next);
		}
		status = ft_wait_all_child_processes(lst);
		signal_handler_in_exec(status, lst->args, envp);
	}
	dup2(in_out[0], 0);
	dup2(in_out[1], 1);
}


#include "minishell_2.h"

void ft_heredoc(t_arg *heredoc, char *stop, char **envp)
{
	int		pip[2];
	int		pid;
	char	*args_str;

	pipe(pip);
	pid = fork();
	if (!pid)
	{
		ft_sig_child_heredoc();
		args_str = readline("> ");
		while (ft_strncmp(args_str, stop, ft_strlen(stop)))
		{
			while (ft_strchr(args_str, '\"') && ft_closed_quote(ft_strchr(args_str, '\"')) && ft_strchr(args_str, '$'))
				ft_replace_by_envp(&args_str, envp);
			while (!(ft_strchr(args_str, '\'') && ft_closed_quote(ft_strchr(args_str, '\''))) && ft_strchr(args_str, '$'))
				ft_replace_by_envp(&args_str, envp);
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
		ft_sig_ignore();
		if (!ft_find_redirect(heredoc->next)) {
			close(pip[1]);
			dup2(pip[0], 0);
			close(pip[0]);
		}
		waitpid(0, NULL, 0);
	}
}

//void	ft_return(char *path, char **argc, char **envp)
//{
//	int		pid;
//	int		pip[2];
//
//	pipe(pip);
//	pid = fork();
//	if (pid == 0)
//		execve(path, argc, envp);
//	else
//		waitpid(pid, NULL, 0);
//}

t_arg	*ft_find_output(t_arg *lst)
{
	t_arg	*output;
	int 	i;

	output = lst;
	i = 0;
	while (output && ft_strncmp(output->content, ">>", 3) && ft_strncmp(output->content, ">", 2))
	{
		if (!ft_strncmp(output->content, "|", 2) && i != 0)
		{
			output = NULL;
			break;
		}
		i++;
		output = output->next;
	}
	return (output);
}

int	ft_find_output_int(t_arg *lst)
{
	t_arg	*output;
	int 	i;

	output = lst;
	i = 0;
	while (output && ft_strncmp(output->content, ">>", 3) && ft_strncmp(output->content, ">", 2))
	{
		if (!ft_strncmp(output->content, "|", 2)  && i != 0)
		{
			output = NULL;
			break;
		}
		i++;
		output = output->next;
	}
	if (output)
		return (0);
	else
		return (1);
}

t_arg	*ft_find_pipe(t_arg *lst)
{
	t_arg	*pipe;

	pipe = lst;
	while (pipe && ft_strncmp(pipe->content, "|", 2))
	{
		pipe = pipe->next;
	}
	return (pipe);
}

int	ft_find_pipe_int(t_arg *lst)
{
	t_arg	*pipe;

	pipe = lst;
	while (pipe && ft_strncmp(pipe->content, "|", 2))
	{
		pipe = pipe->next;
	}
	if (pipe)
		return (0);
	else
		return (1);
}

int	ft_lstcmp(t_arg *lst)
{
	int		n_pipe;
	int		n_output;
	t_arg	*pipe;
	t_arg	*output;

	n_pipe = -1;
	n_output = -1;
//	printf("ft_lstcmp: %s\n", lst->content);
//	if (lst->next)
//		printf("ft_lstcmp->next: %s\n", lst->next->content);
	pipe = lst;
	output = lst;
	if (output && (!ft_strncmp(output->content, ">>", 3) || !ft_strncmp(output->content, ">", 2)))
	{
		//output = output->next;
		n_output++;
		//printf("out1\n");
	}
	while (output && ft_strncmp(output->content, ">>", 3) && ft_strncmp(output->content, ">", 2))
	{
		output = output->next;
		n_output++;
		//printf("out2\n");
	}
	if (pipe && !ft_strncmp(pipe->content, "|", 2))
	{
		//pipe = pipe->next;
		n_pipe++;
		//printf("1\n");
	}
	while (pipe && ft_strncmp(pipe->content, "|", 2))
	{
		pipe = pipe->next;
		n_pipe++;
		//printf("2\n");
	}
	//printf("n_pipe:%d\n", n_pipe);
	//printf("n_output:%d\n", n_output);
	if (n_pipe == n_output)
		return (-1);
	if (n_pipe >= 0 && n_output >= 0)
	{
		if (n_pipe > n_output)
			return (0);
		else
			return (1);
	}
	else
	{
		if (n_pipe < 0)
			return (0);
		else
			return (1);
	}
}

void	ft_pipe(char *path, char **argc, char ***envp)
{
	int		pid;
	int		pip[2];
	void	(*buildin)(char **argc, char ***envp);

	errno = 0;
	// write(2, path, ft_strlen(path));
	buildin = ft_find_buildin(argc, *envp);
	pipe(pip);
	pid = fork();
	if (!pid)
	{
		ft_sig_child();
		close(pip[0]);
		dup2(pip[1], 1);
		close(pip[1]);
		if (buildin)
			buildin(argc, envp);
		else if (path)
			execve(path, argc, *envp);
		else
			ft_call_export(argc, envp, 127);
		exit(0);
	}
	else
	{
		ft_sig_par_ignore();
		//waitpid(0, NULL, 0);
		close(pip[1]);
		dup2(pip[0], 0);
		close(pip[0]);
	}
}

void ft_return(char *path, char **argc, char ***envp)
{
	int		pid;
	int		pip[2];
	void	(*buildin)(char **argc, char ***envp);

	buildin = ft_find_buildin(argc, *envp);
	pipe(pip);
	pid = fork();
	if (!pid)
	{
		ft_sig_child();
		if (buildin)
			buildin(argc, envp);
		else
			execve(path, argc, *envp);
		exit(0);
	}
	else
	{
		ft_sig_par_ignore();
		close(pip[1]);
		dup2(pip[0], 0);
		close(pip[0]);
		waitpid(pid, NULL, 0);
	}
}

void	ft_full_return(char **envp)
{
	int		pid;
	char	*cat[2];

	cat[0] = "/bin/cat";
	cat[1] = 0;
	pid = fork();
	if (pid == 0)
	{
		ft_sig_child();
		//		dup2(pip[0], 0);
		//		close(pip[0]);
		//		close(pip[1]);
		execve(cat[0], cat, envp);
		exit(0);
	}
	else
	{
		ft_sig_par_ignore();
		waitpid(pid, NULL, 0);
	}
}

void	ft_full_return_2(char **envp)
{
	int		pid;
	char	*cat[2];
	int i;
	char ch;

	cat[0] = "/bin/cat";
	cat[1] = 0;
	pid = fork();
	if (pid == 0)
	{
		ft_sig_child();
		i = read(0, &ch, 1);
		while (i)
		{
			write (1, &ch, 1);
			i = read(0, &ch, 1);
		}
		exit(0);
	}
	else
	{
		ft_sig_par_ignore();
		waitpid(pid, NULL, 0);
	}
}

void	ft_return_one_command(char *path, char **argv, char ***envp)
{
	int		pid;
	void	(*buildin)(char **argc, char ***envp);
	int status;

	errno = 0;
	buildin = ft_find_buildin(argv, *envp);
	if (buildin)
		buildin(argv, envp);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			ft_sig_child();
			execve(path, argv, *envp);
			exit (1);
		}
		else
		{
			ft_sig_par_ignore();
			waitpid(0, &status, 0);
			WIFEXITED(status);
			if (WIFSIGNALED(status))
			{
					if (WTERMSIG(status) == SIGINT)
						ft_call_export(argv, envp, 130);;
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
	}
}

int ft_wait_all_child_processes(t_arg *lst)
{
	int number_of_pipes;
	int i;
	t_arg *lst_saver;
	int status;

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
	t_arg *arg_l;
	t_arg *func_l;
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
	int 	status;
	char 	**args;
	char 	**args2;

	in_out[0] = dup(0);
	in_out[1] = dup(1);
	if (lst->next == NULL)
	{
		ft_return_one_command(lst->path, lst->args, envp);
	}
	else
	{
		needful = lst;
		while (needful)
		{
//			write(2, "first:needful: ", 15);
//			write(2, needful->content, ft_strlen(needful->content));
//			write(2, "\n", 1);
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
	}
	status = ft_wait_all_child_processes(lst);
	WIFEXITED(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_call_export(lst->args, envp, 130);
		if (WTERMSIG(status) == SIGQUIT)
			ft_call_export(lst->args, envp, 131);
	}
	else
	{
		if (status != 0)
			ft_call_export(lst->args, envp, 1);
		else
			ft_call_export(lst->args, envp, 0);
	}
	dup2(in_out[0], 0);
	dup2(in_out[1], 1);
}

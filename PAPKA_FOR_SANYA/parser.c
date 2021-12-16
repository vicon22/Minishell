/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:07:08 by kmercy            #+#    #+#             */
/*   Updated: 2021/12/16 15:02:08 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_2.h"

int g_flag;
void	ft_set_funcs_structure(t_arg *arg_l, t_arg **func_l)
{
	char	*line;

	while (arg_l)
	{
		if (!ft_strncmp(arg_l->content, ">", 2) && arg_l->next)
		{
			ft_lst2add_back(func_l, ft_lst2_new(ft_strdup(arg_l->content)));
			ft_lst2add_back(func_l, ft_lst2_new(ft_strdup(arg_l->next->content)));
			arg_l = arg_l->next->next;
			continue;
		}
		if (arg_l->content)
			ft_lst2add_back(func_l, ft_lst2_new(ft_strdup(arg_l->content)));
		if (!ft_is_pipe_or_redir(arg_l->content))
		{
			line = ft_strjoin(" ", arg_l->content);
			arg_l = arg_l->next;
			while (arg_l && !ft_is_pipe_or_redir(arg_l->content))
			{
				if (*arg_l->content == '\"' && ft_closed_quote(ft_strchr(arg_l->content, '\"')))
					ft_remove_quotes(ft_strchr(arg_l->content, '\"'));
				else if (*arg_l->content == '\'' && ft_closed_quote(ft_strchr(arg_l->content, '\'')))
					ft_remove_quotes(ft_strchr(arg_l->content, '\''));
				line = ft_strjoin2(&line, " ");
				line = ft_strjoin2(&line, arg_l->content);
				arg_l = arg_l->next;
			}
			ft_lst2add_args(func_l, ft_split(line, ' '));
			free(line);
		}
		else
			arg_l = arg_l->next;
//		if (arg_l && ft_is_pipe_or_redir(arg_l->content))
//		{
//			ft_lst2add_back(func_l, ft_lst2_new(ft_strdup(arg_l->content)));
//			arg_l = arg_l->next;
//		}
	}
}

char	*ft_find_path(void *content, char *path)
{
	char	**paths;
	char	*path_result;
	int		i;

	i = 0;
	paths = ft_split(path, ':');
	while (paths[i])
	{
		paths[i] = ft_strjoin2(&paths[i], "/");
		path_result = ft_strjoin(paths[i], (char *) content);
		if (access(path_result, F_OK) == 0)
		{
			free_all(paths);
			return (path_result);
		}
		else
			free(path_result);
		i++;
	}
	free_all(paths);
	return (NULL);
}

int ft_is_built_int(char *func_name)
{
	if (!ft_strncmp(func_name, "pwd", 4))
		return (1);
	if (!ft_strncmp(func_name, "cd", 3))
		return (1);
	if (!ft_strncmp(func_name, "echo", 5))
		return (1);
	if (!ft_strncmp(func_name, "unset", 6))
		return (1);
	if (!ft_strncmp(func_name, "export", 7))
		return (1);
	if (!ft_strncmp(func_name, "env", 4))
		return (1);
	if (!ft_strncmp(func_name, "exit", 5))
		return (1);
	return (0);
}

int    ft_set_path(t_arg *func_l, char *path, char ***envp)
{
	int flag;

	flag = 0;
	while (func_l)
	{
		func_l->path = ft_find_path(func_l->content, path);
		if (!func_l->path && !ft_is_pipe_or_redir(func_l->content) && !ft_is_built_int(func_l->content) &&
				!ft_is_pipe_or_redir(func_l->content) && !func_l->prev)
		{
			ft_call_export(func_l->args, envp, 127);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(func_l->content, 2);
			ft_putstr_fd(" : command not found\n", 2);
			flag = 1;
		}
		func_l = func_l->next;
	}
	return (flag);
}

void	ft_parse_input_str(char *args_str, t_arg **arg_l)
{
	char	*arg;

	while (*args_str)
	{
		while (ft_is_space(*args_str))
			args_str++;
		arg = NULL;
		if ((*args_str == '\''
				|| *args_str == '\"') && ft_closed_quote(args_str))
			args_str += ft_pull_str(args_str, &arg, ft_closed_quote(args_str));
		else if (*args_str == '>' || *args_str == '<')
		{
			if (*(args_str + 1) == *args_str)
				args_str += ft_pull_str(args_str, &arg, 2);
			else
				args_str += ft_pull_str(args_str, &arg, 1);
		}
		else if ((*args_str == '\'' || *args_str == '\"'))
			args_str += ft_pull_str(args_str, &arg, ft_next_space_or_pipe(args_str));
		else if (*args_str == '|')
			args_str += ft_pull_str(args_str, &arg, 1);
		else
			args_str += ft_pull_str(args_str, &arg, ft_next_space_or_quote_or_other(args_str));
		ft_lst2add_back(arg_l, ft_lst2_new(arg));
	}
}

int ft_array_len(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void ft_set_heredoc(t_arg *func_l)
{
	t_arg *next;
	int i;
	int j;
	char **new_args;

	while (func_l)
	{
		next = func_l->next;
		if (next)
			if (!ft_strncmp(next->content, "<<", 2))
			{
				if (next->next)
				{
					new_args = (char **)ft_calloc((ft_array_len(func_l->args) + ft_array_len(next->next->args) + 1), sizeof(char *));
					i = -1;
					while (++i < ft_array_len(func_l->args))
						new_args[i] = ft_strdup(func_l->args[i]);
					j = 0;
					while (++j < ft_array_len(next->next->args))
						new_args[i + j - 1] = ft_strdup(next->next->args[j]);
					free_all(func_l->args);
//					free(func_l->args);
					func_l->args = new_args;
					func_l = next->next;
				}
			}
		func_l = func_l->next;
	}
}

void sig_quit_par(int signal)
{
	ft_putstr_fd("Quit: 3\n", 2);
}

void ft_sig_parent()
{
	signal(SIGINT, sig_int_par);
	signal(SIGQUIT,	SIG_IGN);
}

void	sig_quit_ch(int signal)
{
	write(0, "\n", 2);
	ft_putstr_fd("Quit: 3\n", 2);
	exit(131);
}

void ft_sig_ignore()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void ft_sig_child_heredoc()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void ft_sig_child()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sig_quit_ch);
}

void ft_sig_par_ignore()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, sig_quit_par);
}

void	sig_int_par(int signal)
{
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void ft_read_history(int history_fd)
{
	char *history_line;

	history_line = 	get_next_line(history_fd);
	while (history_line != NULL)
	{
		history_line[ft_strlen(history_line) - 1] = '\0';
		add_history(history_line);
		free(history_line);
		history_line = get_next_line(history_fd);
	}
}

void ft_write_history(int history_fd, char *line)
{
	write(history_fd, line, ft_strlen(line));
	write(history_fd, "\n", 1);
}

int	ft_arr_len(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char **ft_char_array_cpy(char **array)
{
	char **new_array;
	int i;

	new_array = ft_calloc(ft_arr_len(array) + 2, sizeof (char *));
	i = 0;
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = ft_strdup("?=0");
	i++;
	new_array[i] = NULL;

	return (new_array);
}

int ft_check_syntax_errors(t_arg *func_l)
{
	while (func_l)
	{
		if (ft_is_pipe_or_redir(func_l->content) && ((!func_l->prev && (!ft_strncmp(func_l->content, "<", 2)  || !ft_strncmp(func_l->content, "|", 2))) || (!func_l->next || ft_is_pipe_or_redir(func_l->next->content))))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("syntax error near unexpected token '", 2);
			ft_putstr_fd(func_l->content, 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
		func_l = func_l->next;
	}
	return (0);
}

//void ft_remove_newline(t_arg *func_l)
//{
//	t_arg *tmp;
//
//	while (func_l)
//	{
//		if (!ft_strncmp(func_l->content,  "<", 2))
//		{
//			tmp = func_l;
//			if (func_l->next && func_l->prev)
//				func_l->prev->next = func_l->next;
//			else if (func_l->next)
//				func_l = func_l->next;
//			else if (func_l->prev)
//				func_l->prev->next = NULL;
//			free(tmp->content);
//			free(tmp);
//		}
//
//		func_l=func_l->next;
//	}
//}

void ft_handle_quotes(t_arg *func_l)
{
	int i;

	while(func_l)
	{
		i = 0;
		if (func_l->args && ft_strncmp(func_l->content, "export", 7))
		{
			while (func_l->args[i]) {
				if (*func_l->args[i] == '\"' && ft_closed_quote(ft_strchr(func_l->args[i], '\"')))
					ft_remove_quotes(ft_strchr(func_l->args[i], '\"'));
				else if (*func_l->args[i] == '\'' && ft_closed_quote(ft_strchr(func_l->args[i], '\'')))
					ft_remove_quotes(ft_strchr(func_l->args[i], '\''));
				i++;
			}
		}
		func_l=func_l->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	static char			*args_str;
	char				**env_array;
	t_arg				*arg_l;
	t_arg				*func_l;
	int 				input_fd[2];
	int 				history_fd;

	history_fd = open(".history", O_RDWR | O_APPEND | O_CREAT);
	ft_read_history(history_fd);

	(void) argc;
	(void) argv;
	input_fd[0] = 0;
	env_array = ft_char_array_cpy(envp);

	while (1)
	{
		ft_sig_parent();
		dup2(input_fd[0], 0);
		args_str = readline("minishell$ ");
		if (!args_str)
			exit(0);
		ft_write_history(history_fd, args_str);
		add_history(args_str);
		arg_l = NULL;
		ft_parse_input_str(args_str, &arg_l);
		ft_handle_envps(arg_l, env_array);
		ft_set_funcs_structure(arg_l, &func_l);
//		ft_handle_quotes(func_l);
		ft_set_heredoc(func_l);
//		ft_show_lst(func_l);
		if (!ft_check_syntax_errors(func_l))
			if (func_l && !ft_set_path(func_l, PATH, &env_array))
				ft_exec(func_l, &env_array);
		ft_free_lst(&arg_l);
		ft_free_lst(&func_l);
		free(args_str);
	}
	return 0;
}

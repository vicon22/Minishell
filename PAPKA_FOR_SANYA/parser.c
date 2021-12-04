/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:07:08 by kmercy            #+#    #+#             */
/*   Updated: 2021/12/04 14:45:11 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_2.h"

void	ft_set_funcs_structure(t_arg *arg_l, t_arg **func_l)
{
	char	*line;

	while (arg_l)
	{
		if (arg_l->content)
			ft_lst2add_back(func_l, ft_lst2_new(ft_strdup(arg_l->content)));
		if (!ft_is_pipe_or_redir(arg_l->content))
		{
			line = ft_strjoin(" ", arg_l->content);
			arg_l = arg_l->next;
			while (arg_l && !ft_is_pipe_or_redir(arg_l->content))
			{
				line = ft_strjoin2(&line, " ");
				line = ft_strjoin2(&line, arg_l->content);
				arg_l = arg_l->next;
			}
			ft_lst2add_args(func_l, ft_split(line, ' '));
			free(line);
		}
		if (arg_l && ft_is_pipe_or_redir(arg_l->content))
		{
			ft_lst2add_back(func_l, ft_lst2_new(ft_strdup(arg_l->content)));
			arg_l = arg_l->next;
		}
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

void	ft_set_path(t_arg *func_l, char *path)
{
	while (func_l)
	{
		func_l->path = ft_find_path(func_l->content, path);
		func_l = func_l->next;
	}
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
			args_str += ft_pull_str(args_str, &arg, ft_next_space(args_str));
		else
			args_str += ft_pull_str(args_str, &arg, ft_next_space_or_quote(args_str));
		ft_lst2add_back(arg_l, ft_lst2_new(arg));
	}
}

void	nothing(int signal)
{
	(void) signal;
	//printf("here will be nothing\n");
}

void	new_prompt(int signal)
{
	(void) signal;
	printf("\nminishell$ ");
}

void	ft_exit(int signal)
{
	(void) signal;
	printf("VEOF\n");
	exit (0);
}

int	main(int argc, char **argv, char **envp)
{
	char				*args_str;
	t_arg				*arg_l;
	t_arg				*func_l;
	int 				input_fd[2];

	(void) argc;
	(void) argv;
	input_fd[0] = 0;
	//signal(SIGQUIT, nothing);
	//signal(SIGINT, new_prompt);
	//signal(EOF, ft_exit);
	while (1)
	{
		dup2(input_fd[0], 0);
//		args_str = "echo \"dasdada\" \'vasya\' 228 \'$PATH\' \"$LOGNAME\" | grep $PWD \"$PATH\"  \'\"31231\"\' \' \" \'";
		args_str = readline("minishell$ ");
		arg_l = NULL;
		ft_parse_input_str(args_str, &arg_l);
		printf("22\n");
		ft_handle_quotes(arg_l, envp);
		ft_set_funcs_structure(arg_l, &func_l);
		ft_set_path(func_l, PATH);
		ft_show_lst(func_l);
		ft_exec(func_l, envp);
		ft_free_lst(&arg_l);
		ft_free_lst(&func_l);
		//break ;
	}
	return 0;
}

//Добавить проверку на пустоту команд
//Дописать замену переменных окружения

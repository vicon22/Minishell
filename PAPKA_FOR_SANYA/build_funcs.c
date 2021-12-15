/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:38:03 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/15 15:43:03 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_2.h"

int	count_argv(char **argv)
{
	int	size;
	char	**save;

	save = argv;
	size = 0;
	while (save[size])
		size++;
	return (size);
}

void ft_set_oldpwd(char *old_pwd, char ***envp)
{
	int i;
	char *tmp;

	i = -1;
	while ((*envp)[++i])
	{
		if (!ft_strncmp((*envp)[i], "OLDPWD", 6) && (ft_strlen((*envp)[i]) - ft_strlen(ft_strchr((*envp)[i], '=')) == 6))
		{
			tmp = (*envp)[i];
			(*envp)[i] = ft_strjoin("OLDPWD=", old_pwd);
			free(old_pwd);
			free(tmp);
		}
	}
}

void ft_set_pwd(char ***envp)
{
	int i;
	char dir[200];
	char *tmp;

	i = -1;
	while ((*envp)[++i])
	{
		if (!ft_strncmp((*envp)[i], "PWD", 3) && (ft_strlen((*envp)[i]) - ft_strlen(ft_strchr((*envp)[i], '=')) == 3))
		{
			tmp = (*envp)[i];
			getcwd(dir, 200);
			(*envp)[i] = ft_strjoin("PWD=", dir);
			free(tmp);
		}
	}
}

void	ft_pwd(char **argc, char ***envp)
{
	char	dir[200];

	(void)argc;
	(void)envp;
	if (getcwd(dir, 200) != NULL)
	{
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
	}
	ft_call_export(argc, envp, 0);
}

void ft_call_export(char **argc, char ***envp, int status)
{
	char *export[3];
	char *error;

	error = ft_itoa(status);
	export[0] = "export";
	export[1] = ft_strjoin("?=", error);
	export[2] = NULL;
	ft_export(export, envp);
	free(error);
	free(export[1]);
}

void	ft_cd(char **argc, char ***envp)
{
	char *old_pwd;
	int i;

	i = -1;
	while ((*envp)[++i])
	{
		if (!ft_strncmp((*envp)[i], "PWD", 3) && (ft_strlen((*envp)[i]) - ft_strlen(ft_strchr((*envp)[i], '=')) == 3))
			old_pwd = ft_strdup(ft_strchr((*envp)[i] , '=') + 1);
	}

	(void)envp;
	if (chdir(argc[1]) == -1)
	{
		ft_putstr_fd("minishell$: ", 2);
		perror(argc[1]);
		ft_call_export(argc, envp, 1);
	}
	else
	{
		ft_set_oldpwd(old_pwd, envp);
		ft_set_pwd(envp);
		ft_call_export(argc, envp, 0);
	}
}

void	ft_echo(char **argv, char ***envp)
{
	int	flag;
	int	i;
	int	argc;

	i = 1;
	flag = 0;
	(void)envp;
	argc = count_argv(argv);
	if (ft_arr_len(argv) > 1)
	{
		while (!ft_strncmp(argv[i], "-n", 3))
		{
			i++;
			flag++;
		}
		while (i != argc) {
			write(1, argv[i], ft_strlen(argv[i]));
			i++;
			if (i != argc)
				write(1, " ", 1);
		}
		if (flag == 0)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
	ft_call_export(argv, envp, 0);
}

void	ft_exit(char **argv, char ***envp)
{
	(void)argv;
	(void)envp;

	ft_putstr_fd("exit\n", 1);
	if (argv[1] != NULL)
	{
		if (ft_correct_number(argv[1]) ==  0)
			exit(ft_atoi(argv[1]) % 256);
		else
		{
			ft_putstr_fd("minishell$: ", 2);
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("numeric argument required\n", 2);
			exit (255);
		}
	}
	else
		exit(0);
}

void	(*ft_find_buildin(char **argc, char **envp))(char **argc, char ***envp)
{
	char	*func_name;
	void	(*buildin)(char **argc, char ***envp);

	func_name = argc[0];
	buildin = NULL;
	if (!ft_strncmp(func_name, "pwd", 4))
		buildin = ft_pwd;
	if (!ft_strncmp(func_name, "cd", 3))
		buildin = ft_cd;
	if (!ft_strncmp(func_name, "echo", 5))
		buildin = ft_echo;
	if (!ft_strncmp(func_name, "unset", 6))
		buildin = ft_unset;
	if (!ft_strncmp(func_name, "export", 7))
		buildin = ft_export;
	if (!ft_strncmp(func_name, "env", 4))
		buildin = ft_env;
	if (!ft_strncmp(func_name, "exit", 5))
		buildin = ft_exit;
	return (buildin);
}

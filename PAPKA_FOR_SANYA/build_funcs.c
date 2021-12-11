/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:38:03 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/09 16:32:09 by eveiled          ###   ########.fr       */
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

void	ft_pwd(char **argc, char **envp)
{
	char	dir[200];

	(void)argc;
	(void)envp;
	printf("in ft_pwd\n");
	if (getcwd(dir, 200) != NULL)
	{
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
	}
	else
	{
		//perror("getcwd() error");
		write(1, "getcwd error\n", 13);
	}
}

void	ft_cd(char **argc, char **envp)
{
	(void)envp;
	printf("(in ft_cd)argc[1]:%s\n", argc[1]);
	chdir(argc[1]);
}

void	ft_echo(char **argv, char **envp)
{
	int	flag;
	int	i;
	int	argc;

	i = 1;
	flag = 0;
	(void)envp;
	argc = count_argv(argv);
	if (!ft_strncmp(argv[1], "-n", 3))
	{
		i = 2;
		flag = 1;
	}
	while (i != argc)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		i++;
		if (i != argc)
			write(1, " ", 1);
	}
	if (flag != 1)
		write(1, "\n", 1);
}

void	ft_exit(char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	exit(0);
}

void	(*ft_find_buildin(char **argc, char **envp))(char **argc, char **envp)
{
	char	*func_name;
	void	(*buildin)(char **argc, char **envp);

	func_name = argc[0];
	printf("func_name:%s\n", func_name);
	buildin = NULL;
	if (!ft_strncmp(func_name, "pwd", 4))
		buildin = &ft_pwd;
	if (!ft_strncmp(func_name, "cd", 3))
		buildin = &ft_cd;
	if (!ft_strncmp(func_name, "echo", 5))
		buildin = &ft_echo;
//	if (ft_strncmp(func_name, "unset", 6))
//		buildin = ft_unset;
//	if (ft_strncmp(func_name, "export", 7))
//		buildin = ft_export;
//	if (ft_strncmp(func_name, "env", 4))
//		buildin = ft_env;
//	if (ft_strncmp(func_name, "exit", 5))
//		buildin = ft_exit;
	return (buildin);
}

//int	main(int argc, char **argv, char **envp)
//{
//	void	(*buildin)(char **argv, char **envp);
//
//	buildin = ft_find_buildin(argv, envp);
//	if (buildin)
//		buildin(argv, envp);
//	else
//		printf("can't find buildin\n");
//	return (0);
//}

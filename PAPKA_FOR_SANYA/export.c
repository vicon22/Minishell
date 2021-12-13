/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:10:30 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/13 15:26:07 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell_2.h"
static void ft_exp(char **env_array)
{
	int i;
	int j;
	char *tmp;
	i = -1;
	while (env_array[++i])
	{
		j = i - 1;
		while (env_array[++j])
		{
			if (ft_strncmp(env_array[i], env_array[j], ft_strlen(env_array[i])) > 0)
			{
				tmp = env_array[i];
				env_array[i] = env_array[j];
				env_array[j] = tmp;
			}
		}
	}
	i = -1;
	while (env_array[++i])
	{
		if (env_array[i][0] != '?')
		{
			ft_putstr_fd(env_array[i], 1);
			ft_putchar_fd('\n', 1);
		}
	}
	free_all(env_array);
}
static int ft_arg_contains_only_valid_c(char *arg)
{
	int i;
	i = -1;
	if (ft_strchr(arg, '=') && ft_strlen(arg) >= 2)
	{
		while (arg[++i] && arg[i] != '=') {
			if (!ft_isdigit(arg[i]) && !ft_isalpha(arg[i]) && arg[i] != '_' && arg[i] != '?')
				return (0);
		}
	}
	else
		return (0);
	return (1);
}
void    ft_export(char **args, char ***env_array)
{
	int     i;
	int     j;
	char    **tmp;
	int     is_added;
	int     arg_len;
	int     envp_len;
	j = 0;
	if (ft_arr_len(args) == 1)
		ft_exp(ft_char_array_cpy(*env_array));
	else if (ft_arr_len(args) > 1)
	{
		while (args[++j])
		{
			if (ft_arg_contains_only_valid_c(args[j]))
			{
				tmp = *env_array;
				*env_array = ft_calloc(ft_arr_len(tmp) + 2, sizeof(char *));
				is_added = 0;
				i = -1;
				while ((tmp)[++i]) {
					envp_len = ft_strlen(tmp[i]) - ft_strlen(ft_strchr(tmp[i], '='));
					arg_len = ft_strlen(args[j]) - ft_strlen(ft_strchr(args[j], '='));
					if (ft_strncmp(tmp[i], args[j], arg_len) || arg_len != envp_len)
						(*env_array)[i] = ft_strdup(tmp[i]);
					else {
						(*env_array)[i] = ft_strdup(args[j]);
						is_added = 1;
					}
				}
				if (!is_added)
					(*env_array)[i++] = ft_strdup(args[j]);
				(*env_array)[i] = NULL;
				free_all(tmp);
			}
			else
			{
				ft_putstr_fd("minishell: export: '", 2);
				ft_putstr_fd(args[j], 2);
				ft_putstr_fd("' : not a valid identifier\n", 2);
			}
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:10:30 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/20 14:04:46 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_call_export(char **argc, char ***envp, int status)
{
	char	*export[3];
	char	*error;

	(void)argc;
	error = ft_itoa(status);
	export[0] = "export";
	export[1] = ft_strjoin("?=", error);
	export[2] = NULL;
	ft_export(export, envp);
	free(error);
	free(export[1]);
}

static int	ft_arg_contains_only_valid_c(char *arg)
{
	int	i;

	i = -1;
	if (ft_strchr(arg, '=') && ft_strlen(arg) >= 2)
	{
		if (ft_isdigit(arg[0]))
			return (0);
		while (arg[++i] && arg[i] != '=')
		{
			if (!ft_isdigit(arg[i]) && !ft_isalpha(arg[i]) && arg[i] != '_'
				&& arg[i] != '?')
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

void	ft_join_args(char ***env_array, char **args, int *i, int *j)
{
	(*env_array)[*i] = ft_strdup(args[(*j)++]);
	while (args[*j] && !ft_strchr(args[*j], '='))
	{
		if (*args[*j] == '\"' && ft_closed_quote(
				ft_strchr(args[*j], '\"')))
			ft_remove_quotes(ft_strchr(args[*j], '\"'));
		else if (*args[*j] == '\'' && ft_closed_quote(
				ft_strchr(args[*j], '\'')))
			ft_remove_quotes(ft_strchr(args[*j], '\''));
		(*env_array)[*i] = ft_strjoin2(&(*env_array)[*i], args[(*j)++]);
		(*env_array)[*i] = ft_strjoin2(&(*env_array)[*i], " ");
	}
	(*j)--;
}

static void	ft_copy_args(char ***env_array, char **args, int *j)
{
	char	**tmp;
	int		i;
	int		is_added;
	int		arg_len;

	tmp = *env_array;
	*env_array = ft_calloc(ft_arr_len(tmp) + 2, sizeof(char *));
	is_added = 0;
	i = -1;
	while ((tmp)[++i])
	{
		arg_len = ft_strlen(args[*j]) - ft_strlen(ft_strchr(args[*j], '='));
		if (ft_strncmp(tmp[i], args[*j], arg_len + 1))
			(*env_array)[i] = ft_strdup(tmp[i]);
		else
		{
			ft_join_args(env_array, args, &i, j);
			is_added = 1;
		}
	}
	if (!is_added)
		ft_join_args(env_array, args, &i, j);
	(*env_array)[++i] = NULL;
	free_all(tmp);
}

void	ft_export(char **args, char ***env_array)
{
	int		j;

	j = 0;
	if (ft_arr_len(args) == 1)
		ft_env(args, env_array);
	else if (ft_arr_len(args) > 1)
	{
		while (args[++j])
		{
			if (ft_arg_contains_only_valid_c(args[j]))
				ft_copy_args(env_array, args, &j);
			else
			{
				ft_putstr_fd("minishell: export: '", 2);
				ft_putstr_fd(args[j], 2);
				ft_putstr_fd("' : not a valid identifier\n", 2);
				j++;
				while (args[j] && !ft_strchr(args[j], '='))
					j++;
				j--;
			}
		}
	}
}

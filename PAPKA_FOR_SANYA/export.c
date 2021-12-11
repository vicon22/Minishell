/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:10:30 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/11 19:38:44 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_2.h"

static void	ft_exp(char	**env_array)
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
		ft_putstr_fd(env_array[i], 1);
		ft_putchar_fd('\n', 1);
	}
	free_all(env_array);
}

void	ft_export(char **args, char ***env_array)
{
	int		i;
	char	**tmp;
	int 	is_added;
	int 	arg_len;
	int 	envp_len;

	if (ft_arr_len(args) == 1)
		ft_exp(ft_char_array_cpy(*env_array));
	else
		{
			tmp = *env_array;
			*env_array = ft_calloc(ft_arr_len(tmp) + 2, sizeof (char *));
			is_added = 0;
			i = -1;
			while ((tmp)[++i])
			{
				envp_len = ft_strlen(tmp[i]) - ft_strlen(ft_strchr(tmp[i], '='));
				arg_len = ft_strlen(args[1]) - ft_strlen(ft_strchr(args[1], '='));

				if (ft_strncmp(tmp[i], args[1], arg_len) || arg_len != envp_len)
					(*env_array)[i] = ft_strdup(tmp[i]);
				else
				{
					(*env_array)[i] = ft_strdup(args[1]);
					is_added = 1;
				}
			}
			if (!is_added)
				(*env_array)[i++] = ft_strdup(args[1]);
			(*env_array)[i] = NULL;
			free_all(tmp);
		}
}

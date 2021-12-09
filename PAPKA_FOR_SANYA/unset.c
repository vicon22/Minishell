/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:36:25 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/09 17:33:33 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../evgenii.h"
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

void	ft_unset(char **args, char ***env_array)
{
	int		i;
	int		argc;
	char	**tmp;
	int 	arg_len;
	int 	envp_len;

	if (ft_arr_len(args) <= 1)
	{
		write(1, "unset: not enough arguments\n", 28);
		//переделать в errno
		return ;
	}
	else
	{
		tmp = *env_array;
		*env_array = ft_calloc(ft_arr_len(tmp) + 1, sizeof (char *));
		i = -1;
		while ((tmp)[++i])
		{
			envp_len = ft_strlen(tmp[i]) - ft_strlen(ft_strchr(tmp[i], '='));
			arg_len = ft_strlen(args[1]);
			printf("%d   %d  %d \n", envp_len, arg_len, ft_strncmp(tmp[i], args[1], envp_len));
			if (!((!ft_strncmp(tmp[i], args[1], envp_len)) && envp_len == arg_len))
				(*env_array)[i] = ft_strdup(tmp[i]);
		}
		(*env_array)[i] = NULL;
		free_all(tmp);
	}
}

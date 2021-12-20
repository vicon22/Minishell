/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_funcs_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:48:49 by kmercy            #+#    #+#             */
/*   Updated: 2021/12/19 17:51:15 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_return_env(char **envp, char *var)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], var, ft_strlen(var)))
			return (ft_strchr(envp[i], '=') + 1);
	}
	return (NULL);
}

void	ft_free_argl_func_l_argstr(t_arg **arg_l, t_arg **func_l,
	char *args_str)
{
	ft_free_lst(arg_l);
	ft_free_lst(func_l);
	free(args_str);
}

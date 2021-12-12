/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:06:59 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/12 15:41:20 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_2.h"

void	ft_env(char **argc, char ***env_array)
{
	int i;

	i = -1;
	(void)argc;
	while ((*env_array)[++i])
	{
		ft_putstr_fd((*env_array)[i], 1);
		ft_putchar_fd('\n', 1);
	}
}

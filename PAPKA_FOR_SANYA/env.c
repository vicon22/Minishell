/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:06:59 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/30 15:25:28 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../evgenii.h"
#include "minishell_2.h"

void	ft_env(char	**env_array)
{
	int i;

	i = -1;
	while (env_array[++i])
	{
		ft_putstr_fd(env_array[i], 0);
		ft_putchar_fd('\n', 1);
	}
}

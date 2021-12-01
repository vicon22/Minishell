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

#include "evgenii.h"

void	ft_env(t_envp	*all_envp)
{
	while (all_envp)
	{
		if (all_envp->value[0] != '\'' && all_envp->value[1] != '\'')
		{
			write(1, all_envp->name, ft_strlen(all_envp->name));
			write(1, "=", 1);
			write(1, all_envp->value, ft_strlen(all_envp->value));
			write(1, "\n", 1);
			all_envp = all_envp->next;
		}
//		write(1, all_envp->name, ft_strlen(all_envp->name));
//		write(1, "=", 1);
//		write(1, all_envp->value, ft_strlen(all_envp->value));
//		write(1, "\n", 1);
		all_envp = all_envp->next;
	}
}

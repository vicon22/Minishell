/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:06:59 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/29 18:12:33 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "evgenii.h"

void	ft_env(t_envp	*all_envp)
{
	while (all_envp)
	{
		write(1, all_envp->allstr, ft_strlen(all_envp->allstr));
		write(1, "\n", 1);
		all_envp = all_envp->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:10:30 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/29 18:23:16 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "evgenii.h"

void	ft_export(int argc, char **argv, t_envp *all_envp)
{
	int		i;

	if (argc == 1)
	{
		ft_env(all_envp); //нужно отсортировать
		return ;
	}
	i = 1;
	while (i != argc)
	{
		ft_lstadd_back(&all_envp, ft_lstnew_envp(argv[i]));
		i++;
	}
}

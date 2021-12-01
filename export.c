/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:10:30 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/30 15:26:31 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "evgenii.h"

static void	ft_exp(t_envp	*all_envp)
{
	while (all_envp)
	{
		write(1, all_envp->name, ft_strlen(all_envp->name));
		write(1, "=", 1);
		write(1, all_envp->value, ft_strlen(all_envp->value));
		write(1, "\n", 1);
		all_envp = all_envp->next;
	}
}

void	ft_export(int argc, char **argv, t_envp *all_envp)
{
	int		i;

	if (argc == 1)
	{
		ft_exp(all_envp); //нужно отсортировать
		return ;
	}
	i = 1;
	while (i != argc)
	{
		printf("+++\n");
		ft_lstadd_back(&all_envp, ft_lstnew_envp(argv[i]));
		printf("---\n");
		i++;
	}
}

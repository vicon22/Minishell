/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:36:25 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/30 14:15:39 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "evgenii.h"

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

void	ft_unset(char **argv, t_envp *all_envp)
{
	int		i;
	t_envp	*saver;
	int		argc;

	argc = count_argv(argv);
	if (argc == 1)
	{
		write(1, "unset: not enough arguments\n", 28);
		//переделать в errno
		return ;
	}
	i = 1;
	while (i != argc)
	{
		saver = all_envp;
		while (saver)
		{
			if (!ft_strncmp(saver->name, argv[i], ft_strlen(saver->name)))
			{
				ft_delete_current(saver);
			}
			saver = saver->next;
		}
		i++;
	}
}

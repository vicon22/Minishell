/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:10:30 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/28 21:50:00 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "evgenii.h"

void	ft_export(int argc, char **argv, char **envp)
{
	int		i;
	char	*name;

	if (argc == 1)
	{
		ft_env(envp);
		return ;
	}
	i = 1;
	while (i != argc)
	{
		name = ft_take_name(argv[i]);
		if (NULL == name)
		{
			write(1, "malloc error in ft_export\n", 26);
			exit (1); /*plz delete me*/
		}
		printf("name: %s\n", name);
		free(name);
		printf("value: %s\n", ft_strchr(argv[i], '=') + 1);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:23:14 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/28 18:26:04 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "evgenii.h"

void	ft_echo(int argc, char **argv)
{
	int	flag;
	int	i;

	i = 1;
	flag = 0;
	if (argv[1][0] == '-' && argv[1][1] == 'n')
	{
		i = 2;
		flag = 1;
	}
	while (i != argc)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		i++;
		if (i != argc)
			write(1, " ", 1);
	}
	if (flag != 1)
		write(1, "\n", 1);
}

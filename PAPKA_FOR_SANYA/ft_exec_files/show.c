/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:41:16 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/17 14:43:16 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	show_args(char **args)
{
	int	i;

	i = 0;
	write(2, "-------\n", 8);
	while (args[i])
	{
		write(2, args[i], ft_strlen(args[i]));
		write(2, "\n", 1);
		i++;
	}
	write(2, "-------\n", 8);
}
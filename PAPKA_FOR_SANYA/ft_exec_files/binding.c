/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:00:09 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/17 15:28:28 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_binding_args(char **args_first, char **args_second, int flag)
{
	int		count_first;
	int		count_second;
	int		i;
	int		j;
	char	**bind_args;

	count_first = 0;
	count_second = 0;
	if (args_first)
		while (args_first[count_first])
			count_first++;
	if (args_second)
		while (args_second[count_second])
			count_second++;
	if (count_second < 2)
		return (args_first);
	bind_args = (char **)malloc(sizeof(char *)
			* (count_first + count_second + 1));
	if (NULL == bind_args)
	{
		write(2, "malloc error in ft_binding_args\n", 32);
		exit(1);
	}
	i = 0;
	while (i < count_first)
	{
		bind_args[i] = ft_strdup(args_first[i]);
		i++;
	}
	j = 1;
	if (!args_first)
		j = 0;
	while (j < count_second)
	{
		bind_args[i] = ft_strdup(args_second[j]);
		j++;
		i++;
	}
	bind_args[i] = NULL;
	if (args_first && flag == 0)
		ft_free(args_first);
	if (args_second && flag == 1)
		ft_free(args_second);
	return (bind_args);
}

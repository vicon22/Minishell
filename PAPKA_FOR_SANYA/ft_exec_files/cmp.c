/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 13:20:42 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/19 13:22:01 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstcmp(t_arg *lst)
{
	int		n_pipe;
	int		n_output;
	t_arg	*pipe;
	t_arg	*output;

	n_pipe = -1;
	n_output = -1;
//	printf("ft_lstcmp: %s\n", lst->content);
//	if (lst->next)
//		printf("ft_lstcmp->next: %s\n", lst->next->content);
	pipe = lst;
	output = lst;
	if (output && (!ft_strncmp(output->content, ">>", 3)
			|| !ft_strncmp(output->content, ">", 2)))
		n_output++;
	while (output && ft_strncmp(output->content, ">>", 3)
		&& ft_strncmp(output->content, ">", 2))
	{
		output = output->next;
		n_output++;
	}
	if (pipe && !ft_strncmp(pipe->content, "|", 2))
		n_pipe++;
	while (pipe && ft_strncmp(pipe->content, "|", 2))
	{
		pipe = pipe->next;
		n_pipe++;
	}
	if (n_pipe == n_output)
		return (-1);
	if (n_pipe >= 0 && n_output >= 0)
	{
		if (n_pipe > n_output)
			return (0);
		else
			return (1);
	}
	else
	{
		if (n_pipe < 0)
			return (0);
		else
			return (1);
	}
}

int	ft_array_cpm(char **args_first, char **args_second)
{
	int	count_first;
	int	count_second;
	int	i;

	count_first = 0;
	count_second = 0;
	if (args_first)
		while (args_first[count_first])
			count_first++;
	if (args_second)
		while (args_second[count_second])
			count_second++;
	if (count_first != count_second)
		return (1);
	i = 0;
	while (args_first[i] && args_second[i])
	{
		if (ft_strlen(args_first[i]) != ft_strlen(args_second[i]))
			return (1);
		if (ft_strncmp(args_first[i], args_second[i], ft_strlen(args_first[i])))
			return (1);
		i++;
	}
	return (0);
}

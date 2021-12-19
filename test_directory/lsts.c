/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 21:23:32 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/30 15:13:34 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "evgenii.h"

char	*ft_take_name(char *str)
{
	int		name_size;
	int		i;
	char	*name;

	i = 0;
	name_size = 0;
	while (str[name_size] != '=')
		name_size++;
	name = (char *)malloc(sizeof(char) * (name_size + 1));
	if (NULL == name)
		return (NULL);
	while (str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*ft_take_value(char *envp)
{
	int		size;
	char	*value;
	char	*current;
	int		i;

	if (ft_strchr(envp, '='))
		size = ft_strlen(ft_strchr(envp, '=') + 1);
	else
		size = 0;
	if (size == 0)
	{
		value = (char *)malloc(sizeof(char) * (2));
		value = "''";
		if (NULL == value)
			return (NULL);
		return (value);
	}
	value = (char *)malloc(sizeof(char) * (size + 1));
	if (NULL == value)
		return (NULL);
	i = 0;
	current = ft_strchr(envp, '=') + 1;
	while (current[i])
	{
		value[i] = current[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

t_envp	*ft_lstnew_envp(char *envp)
{
	t_envp	*new;

	new = (t_envp *)malloc(sizeof(t_envp));
	if (NULL == new)
		return (NULL);
	new->name = ft_take_name(envp);
	new->value = ft_take_value(envp);
	new->allstr = ft_strdup(envp);
	if (new->name == NULL || new->value == NULL || new->allstr == NULL)
	{
		if (new->name)
			free(new->name);
		if (new->value)
			free(new->value);
		if (new->allstr)
			free(new->allstr);
		return (NULL);
	}
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

void	ft_lstadd_back(t_envp **lst, t_envp *new)
{
	t_envp	*saver;

	saver = *lst;
	if (saver)
	{
		while ((saver)->next)
		{
			saver = (saver)->next;
		}
		(saver)->next = new;
		new->previous = saver;
	}
	else
	{
		*lst = new;
	}
}

void	ft_delete_current(t_envp *current)
{
	t_envp	*next;
	t_envp	*previous;

	next = current->next;
	previous = current->previous;
	previous->next = next;
	next->previous = previous;
}
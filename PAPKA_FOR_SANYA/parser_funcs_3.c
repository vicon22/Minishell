/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_funcs_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:05:32 by kmercy            #+#    #+#             */
/*   Updated: 2021/12/01 16:47:38 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_2.h"

int	ft_is_pipe_or_redir(void *cont)
{
	char	*content;

	content = (char *) cont;
	if (content)
	{
		if (!ft_strncmp(content, "|", 1) && ft_strlen(content) == 1)
			return (1);
		else if (!ft_strncmp(content, ">", 1) && ft_strlen(content) == 1)
			return (2);
		else if (!ft_strncmp(content, "<", 1) && ft_strlen(content) == 1)
			return (3);
		else if (!ft_strncmp(content, ">>", 1) && ft_strlen(content) == 2)
			return (4);
		else if (!ft_strncmp(content, "<<", 1) && ft_strlen(content) == 2)
			return (5);
		else
			return (0);
	}
	return (0);
}

char	*ft_strjoin2(char **s1, char *s2)
{
	char	*s_start;
	char	*s1_start;
	char	*s;

	s = malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1));
	if (!s)
		return (NULL);
	s_start = s;
	s1_start = *s1;
	while (**s1)
		*(s++) = *((*s1)++);
	while (*s2 && *s2 != '\n')
		*s++ = *s2++;
	if (*s2 == '\n')
		*(s++) = '\n';
	*s = '\0';
	free((void *) s1_start);
	return (s_start);
}

int	ft_is_space(char c)
{
	if (c == ' ')
		return (1);
	else
		return (0);
}

int	ft_next_space_or_quote(char *arg_str)
{
	int	i;

	i = -1;
	while (arg_str[++i])
	{
		if ((arg_str[i] == ' ' || arg_str[i] == '\''
				|| arg_str[i] == '\"' ) && i != 0)
		{
			return (i);
		}
	}
	return (i);
}

int	ft_next_space(char *arg_str)
{
	int	i;

	i = -1;
	while (arg_str[++i])
	{
		if ((arg_str[i] == ' ') && i != 0)
		{
			return (i);
		}
	}
	return (i);
}

void	free_all(char **result)
{
	int	j;

	j = 0;
	while (result[j])
	{
		free(result[j]);
		j++;
	}
	free(result);
}

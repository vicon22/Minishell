/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_funcs_2_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:04:36 by kmercy            #+#    #+#             */
/*   Updated: 2021/12/19 16:14:23 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_is_valid_dollar(char *content)
{
	while (*content)
	{
		if (*content == '$' && (ft_isalpha(*(content + 1)) || ft_isdigit(*(content + 1)) ||  *(content + 1) == '_' || *(content + 1) == '?'))
			return (1);
		content++;
	}
	return (0);
}

int	is_double_quote_main(char *content)
{
	int i;

	i = -1;
	if (ft_strchr(content, '\"') && ft_closed_quote(ft_strchr(content, '\"')) && (ft_strchr(content, '\'') && ft_closed_quote(ft_strchr(content, '\''))))
	{
		while (content[++i])
		{
			if (*content == '\'')
				return (0);
			if (*content == '\"')
				return (1);
		}
	}
	else if (ft_strchr(content, '\"') && ft_closed_quote(ft_strchr(content, '\"')))
		return (1);
	return (0);
}

void   ft_handle_envps(t_arg *arg_l, char**envp)
{
	char   **content;


	while (arg_l != NULL)
	{
		content = &(arg_l->content);
		while (ft_strchr(*content, '\"') && ft_closed_quote(ft_strchr(*content, '\"')) && ft_is_valid_dollar(*content) &&
			   is_double_quote_main(*content))
			ft_replace_by_envp(content, envp);
		while (!(ft_strchr(*content, '\'') && ft_closed_quote(ft_strchr(*content, '\''))) && ft_is_valid_dollar(*content))
			ft_replace_by_envp(content, envp);
//    if (**content == '\"' && ft_closed_quote(ft_strchr(*content, '\"')))
//       ft_remove_quotes(ft_strchr(*content, '\"'));
//    else if (**content == '\'' && ft_closed_quote(ft_strchr(*content, '\'')))
//       ft_remove_quotes(ft_strchr(*content, '\''));
		arg_l = arg_l->next;
	}
}

int	ft_closed_quote(char *arg_str)
{
	int	i;

	i = 0;

	while (arg_str[++i])
	{
		if ((arg_str[i] == '\'' && arg_str[0] == '\'')
			|| (arg_str[i] == '\"' && arg_str[0] == '\"'))
		{
			i++;
			return (i);
		}
	}
	return (0);
}

int	ft_pull_str(char *args_str, char **cur_arg, int n)
{
	*cur_arg = ft_calloc(n + 1, sizeof (char));
	if (!*cur_arg)
		return (0);
	ft_memcpy(*cur_arg, args_str, n);
	return (n);
}

void	ft_remove_quotes(void *content)
{
	char	*str;
	int		i;

	str = (char *)content;
	i = -1;
	while (str[++i + 1])
		str[i] = str[i + 1];
	str[i - 1] = '\0';
}

char	*ft_end_of_var(char *content)
{
	content++;
	if (ft_isdigit(*content))
	{
		content++;
		return (content);
	}
	while (*content && !ft_is_space(*content) && *content != '\'' && *content != '\"' && (ft_isalpha(*content) || ft_isdigit(*content) || *content == '_'))
	{
		content++;
	}
	if (*content == '?')
		content++;
	return (content);
}

//int ft_is_any_of_envp(char **envp, char *content)
//{
//	int i;
//	int		pre_len;
//	int		post_len;
//	int		var_len;
//
//
//	i = -1;
//	while (envp[++i] && ft_strchr(content, '$'))
//	{
//		pre_len = ft_strlen(content) - ft_strlen(ft_strchr(content, '$'));
//		post_len = ft_strlen(ft_end_of_var(ft_strchr(content, '$')));
//		var_len = ft_strlen(content) - pre_len - post_len - 1;
//
//		if (ft_strchr(content, '$') && !ft_strncmp(envp[i], ft_strchr(content, '$') + 1, var_len))
//			return (1);
//	}
//	return (0);
//}


void ft_replace_by_envp(char **content, char**envp)
{
	int		i;
	int		pre_len;
	int		var_len;
	char	*new_content;
	int		post_len;

	i = -1;
	pre_len = ft_strlen(*content) - ft_strlen(ft_strchr(*content, '$'));
	post_len = ft_strlen(ft_end_of_var(ft_strchr(*content, '$')));
	var_len = ft_strlen(*content) - pre_len - post_len - 1;
	while (envp[++i] && ft_strchr(*content, '$'))
	{
		if (ft_strchr(*content, '$') && !ft_strncmp(envp[i], ft_strchr(*content, '$') + 1, var_len) && var_len == (int)(ft_strlen(envp[i]) -
				ft_strlen(ft_strchr(envp[i], '='))))
		{
			pre_len = ft_strlen(*content) - ft_strlen(ft_strchr(*content, '$'));
			post_len = ft_strlen(ft_end_of_var(ft_strchr(*content, '$')));
			var_len = ft_strlen(*content) - pre_len - post_len - 1;
			new_content = ft_calloc(pre_len + 1, sizeof (char));
			new_content = ft_memcpy(new_content, *content, pre_len);
			new_content = ft_strjoin2(&new_content, ft_strchr(envp[i], '=') + 1);
			new_content = ft_strjoin2(&new_content, *content + pre_len + var_len + 1);

			ft_bzero(*content, ft_strlen(*content) + 1);
			*content = ft_strjoin2(content, new_content);
			free(new_content);
			return ;
		}
	}
	if (ft_is_valid_dollar(*content))
	{
		new_content = ft_calloc(pre_len + 1, sizeof(char));
		new_content = ft_memcpy(new_content, *content, pre_len);
		new_content = ft_strjoin2(&new_content, *content + pre_len + var_len + 1);

		ft_bzero(*content, ft_strlen(*content) + 1);
		*content = ft_strjoin2(content, new_content);
		free(new_content);
	}
}

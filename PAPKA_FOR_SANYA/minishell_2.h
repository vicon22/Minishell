/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_2.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:03:02 by kmercy            #+#    #+#             */
/*   Updated: 2021/12/01 13:02:58 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_2_H
# define MINISHELL_2_H

# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# define PATH "/Users/kmercy/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki"

typedef struct d_arg
{
	struct d_arg	*next;
	struct d_arg	*prev;
	char			*path;
	char			**args;
	char			*content;
}	t_arg;

t_arg	*ft_lst2_new(char *content);
void	ft_lst2add_back(t_arg **lst, t_arg *new);
int		ft_is_space(char c);
void	ft_show_lst(t_arg *lst);
void	ft_free_lst(t_arg **lst);
int		ft_closed_quote(char *arg_str);
int		ft_next_space_or_quote(char *arg_str);
int		ft_next_space(char *arg_str);
int		ft_pull_str(char *args_str, char **cur_arg, int n);
void	ft_remove_quotes(void *content);
void    ft_replace_by_envp(char **content, char**envp);
void	ft_handle_quotes(t_arg *arg_l, char**envp);
int		ft_is_pipe_or_redir(void *cont);
char	*ft_strjoin2(char **s1, char *s2);
void	ft_lst2add_args(t_arg **lst, char **line);
void	free_all(char **result);
#endif

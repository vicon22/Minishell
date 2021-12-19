/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_attempt_to_exec.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:45:26 by eveiled           #+#    #+#             */
/*   Updated: 2021/12/02 16:23:50 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell_2.h"
//
//int	ft_strncmp2(const char *s1, const char *s2, size_t n)
//{
//	size_t	count;
//
//	count = 0;
//	//printf("s1: %s\n", s1);
//	//printf("s2: %s\n", s2);
//	if (s1 == NULL)
//		return (1);
//	while (count < n && *(s1 + count) && *(s2 + count))
//	{
//		if (*(s1 + count) != *(s2 + count))
//			return ((unsigned char)*(s1 + count)
//					- (unsigned char)*(s2 + count));
//		count++;
//	}
//	if (count < n)
//	{
//		if (*(s1 + count) != *(s2 + count))
//			return ((unsigned char)*(s1 + count)
//					- (unsigned char)*(s2 + count));
//	}
//	return ((unsigned char)0);
//}
//
//void	ft_exec(t_arg *lst, char **envp)
//{
//	int		pid;
//	int		pip[2];
//	char	*args_str;
//	int		status;
//
//	pipe(pip);
//	if (pid < 0)
//	{
//		printf("fork error in ft_exec\n");
//		exit(1);
//	}
//	if (!fork())
//	{
//		args_str = readline("> ");
//		while (ft_strncmp2(args_str, lst->next->next->content, ft_strlen(lst->next->next->content))) {
//			write(pip[1], args_str, ft_strlen(args_str));
//			write(pip[1], "\n", 1);
//			args_str = readline("> ");
//		}
//		close(pip[1]);
////		close(pip[0]);
//	}
//	close(pip[1]);
//
//	waitpid(0, &status, 0);
//	pid = fork();
//	if (pid == 0)
//	{
//		dup2(pip[0], 0);
//		close(pip[0]);
//		close(pip[1]);
//		write(2, "doch2\n", 6);
//		execve(lst->path, lst->args, envp);
//	}
//	close(pip[0]);
//	waitpid(0, &status, 0);
//}

//
//#include "minishell_2.h"
//
//int	ft_strncmp2(const char *s1, const char *s2, size_t n)
//{
//	size_t	count;
//
//	count = 0;
//	//printf("s1: %s\n", s1);
//	//printf("s2: %s\n", s2);
//	if (s1 == NULL)
//		return (1);
//	while (count < n && *(s1 + count) && *(s2 + count))
//	{
//		if (*(s1 + count) != *(s2 + count))
//			return ((unsigned char)*(s1 + count)
//					- (unsigned char)*(s2 + count));
//		count++;
//	}
//	if (count < n)
//	{
//		if (*(s1 + count) != *(s2 + count))
//			return ((unsigned char)*(s1 + count)
//					- (unsigned char)*(s2 + count));
//	}
//	return ((unsigned char)0);
//}

//void	ft_exec(t_arg *lst, char **envp) {
//	int pid;
//	int check_command;
//	int pip[2];
//	int pip_2[2];
//	char *args_str;
//	int 	p;
//	int 	status;
//
//	pipe(pip);
//	if (pid < 0)
//	{
//		printf("fork error in ft_exec\n");
//		exit(1);
//	}
//	args_str = readline("> ");
//	while (ft_strncmp2(args_str, lst->next->next->content, ft_strlen(lst->next->next->content))) {
//		write(pip[1], args_str, ft_strlen(args_str));
//		args_str = readline("> ");
//	}
//	close(pip[1]);
//
//	pid = fork();
//	if (pid == 0)
//	{
//		dup2(pip[0], 0);
//		write(2, "doch\n", 6);
//		execve(lst->path, lst->args, envp);
//	}
//	waitpid(0, &status, 0);
//	printf("\nstatus %d \n", status);
//}
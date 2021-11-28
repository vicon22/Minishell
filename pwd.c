/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:42:46 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/28 16:43:08 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "evgenii.h"

//void	ft_pwd(char **envp)
//{
//	int	i;
//
//	i = 0;
//	while (envp[i])
//	{
//		if (envp[i][0] == 'P' && envp[i][1] == 'W' && envp[i][2] == 'D')
//		{
//			write(1, envp[i] + 4, ft_strlen(envp[i] + 4));
//			write(1, "\n", 1);
//		}
//		i++;
//	}
//}

void	ft_pwd(void)
{
	char	dir[200];

	if (getcwd(dir, 200) != NULL)
	{
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
	}
	else
	{
		//perror("getcwd() error");
		write(1, "getcwd error\n", 13);
	}
}

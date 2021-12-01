/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_additional_functions.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:23:55 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/30 14:14:47 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "evgenii.h"

t_envp	*ft_cr_list_envp(char **envp)
{
	t_envp	*all_envp;
	t_envp	*current_envp;

	all_envp = NULL;
	while (*envp)
	{
		current_envp = ft_lstnew_envp(*envp);
		if (NULL == current_envp)
		{
			//ft_clear_all(all_envp);
			write(1, "malloc error in ft_cr_list_envp\n", 32);
			exit (1); /*plz delete me*/
		}
		ft_lstadd_back(&all_envp, current_envp);
		envp++;
	}
	return (all_envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_envp	*all_envp;

	//ft_echo(argc, argv);
	//ft_pwd(envp);
//	ft_env(envp);
	all_envp = ft_cr_list_envp(envp);
	ft_export(argc, argv, all_envp);
	//ft_env(all_envp);
	//ft_unset(argv, all_envp);
	ft_env(all_envp);

	return (0);
}

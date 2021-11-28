/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_additional_functions.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:23:55 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/28 21:56:53 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "evgenii.h"

t_envp	*ft_cr_list_envp(char **envp)
{
	t_envp	*all_envp;
	t_envp	*current_envp;

	while (*envp)
	{
		current_envp = ft_lstnew_envp(*envp);
		if (NULL == current_envp)
		{
			//ft_clear_all(all_envp);
			write(1, "malloc error in ft_cr_list_envp\n", 32);
			exit (1); /*plz delete me*/
		}
		printf("--\n");
		printf("current_envp->name: %s", current_envp->name);
		printf("current_envp->value: %s", current_envp->value);
		printf("current_envp->allstr: %s", current_envp->allstr);
		ft_lstadd_back(&all_envp, current_envp);
		printf("++\n");
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
	while (all_envp)
	{
		printf("all_envp->name: %s", all_envp->name);
		printf("all_envp->value: %s", all_envp->value);
		printf("all_envp->allstr: %s", all_envp->allstr);
		all_envp = all_envp->next;
	}
	//ft_export(argc, argv, envp);

	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:13:47 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/06 13:42:38 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
char *env_list_find_var(t_env **head, char *to_look)
{
	t_env	*tmp;

	if (!(*head)) 
	{
		printf("Invalid data or data->env is NULL\n");
		return (0);
	}
	tmp = *head;
	while(tmp)
		{
			if(ft_strcmp(tmp->name, to_look) == 0)
				return(tmp->var);

			tmp = tmp->next;
		}
		return("\0");
}
int ft_cd(char *dir, t_env *env, t_pipe *needs)
{
	char	cwd[1024];
	char	*home;
	char	*oldpwd;
	oldpwd = env_list_find_var(&env, "PWD");
	if (!dir || !ft_strcmp(dir, "~"))
	{
		home = env_list_find_var(&env, "HOME");
		if(!home)
		{
			ft_putstr_fd("HOME is not set\n", 2);
			*(needs->ex_stat) = 1;
			ft_set_status(*(needs->ex_stat), 1);
			return(1);
		}
		if (chdir(home) < 0)
		{
			*(needs->ex_stat) = 1;
			ft_set_status(*(needs->ex_stat), 1);
			perror("chdir");
			return (1);
		}
	}
	else if (chdir(dir) != 0)
	{
		*(needs->ex_stat) = 1;
		ft_set_status(*(needs->ex_stat), 1);
		perror("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		*(needs->ex_stat) = 1;
		ft_set_status(*(needs->ex_stat), 1);
		perror("getcwd");
		return (1);
	}
	env_search_replace(env, cwd, "PWD");
	if (!env_list_serch(&env, "OLDPWD"))
		ft_export("OLDPWD", oldpwd, env, needs);
	else
		env_search_replace(env, oldpwd, "OLDPWD");
	if (!env_list_serch(&env, "PWD"))
	{
		ft_unset(&env, "OLDPWD");
	}
	*(needs->ex_stat) = 0;
	ft_set_status(*(needs->ex_stat), 1);
	return (1);
}

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	ft_cd(av[1]);
// }

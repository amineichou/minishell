/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:13:47 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/10 12:06:36 by moichou          ###   ########.fr       */
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

void cd_home(t_pipe *needs, t_env *env)
{
	char *home;
		home = env_list_find_var(&env, "HOME");
		if(!home)
		{
			ft_putstr_fd("HOME is not set\n", 2);
			*(needs->ex_stat) = 1;
			ft_set_status(*(needs->ex_stat), 1);
			return ;
		}
		if (chdir(home) < 0)
		{
			*(needs->ex_stat) = 1;
			ft_set_status(*(needs->ex_stat), 1);
			perror("chdir");
			return ;
		}
		*(needs->ex_stat) = 0;
	ft_set_status(*(needs->ex_stat), 1);
}

void cd_dir(t_pipe *needs, char *dir)
{

	if (chdir(dir) != 0)
	{
		*(needs->ex_stat) = 1;
		ft_set_status(*(needs->ex_stat), 1);
		perror("cd");
		return ;
	}
	*(needs->ex_stat) = 0;
	ft_set_status(*(needs->ex_stat), 1);
	
}

int ft_cd(char *dir, t_env *env, t_pipe *needs)
{

	char	cwd[1024];
	char	*oldpwd;

	oldpwd = env_list_find_var(&env, "PWD");
	if (!dir || !ft_strcmp(dir, "~"))
		cd_home(needs, env);
	else
		cd_dir(needs, dir);
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
	
	return (1);
}

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	ft_cd(av[1]);
// }

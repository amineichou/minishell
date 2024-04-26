/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:13:47 by zyamli            #+#    #+#             */
/*   Updated: 2024/04/25 15:30:48 by zyamli           ###   ########.fr       */
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
	char cwd[1024];
	// if (getcwd(cwd, sizeof(cwd)) == NULL)
	// {
	//     // Error handling
	//     perror("cd ");
	//     return (0);
	// }
	char *home;
	char *oldpwd = env_list_find_var(&env, "PWD");
	if (dir == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			*(needs->ex_stat) = 1;
			perror("cd");
			return (0);
		}
	}
	if (!dir || !ft_strcmp(dir, "~"))
	{
		home = ft_strjoin("/Users/",env_list_find_var(&env, "USER"));
		if (chdir(home) < 0)
		{
			*(needs->ex_stat) = 1;
			perror("chdir");
			return (0);
		}
		free(home);
	}
	else if (chdir(dir) != 0)
	{
		*(needs->ex_stat) = 1;
		perror("cd");
		return (0);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		*(needs->ex_stat) = 1;
		perror("getcwd");
		return (0);
	}
	env_search_replace(env, cwd, "PWD");
	env_search_replace(needs->env_dup, cwd, "PWD");
	if (!env_list_serch(&env, "OLDPWD"))
		ft_export("OLDPWD", oldpwd, env, needs);
	else
		env_search_replace(env, oldpwd, "OLDPWD");
	if (!env_list_serch(&env, "PWD"))
	{
		ft_unset(&env, "OLDPWD");
		ft_unset(&needs->env_dup, "OLDPWD");
	}
	*(needs->ex_stat) = 0;
	return (1);
}

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	ft_cd(av[1]);
// }

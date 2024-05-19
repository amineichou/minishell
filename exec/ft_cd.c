/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:13:47 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/16 16:52:24 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_list_find_var(t_env **head, char *to_look)
{
	t_env	*tmp;

	if (!(*head))
		return (0);
	tmp = *head;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, to_look) == 0)
			return (tmp->var);
		tmp = tmp->next;
	}
	return ("\0");
}

void	cd_home(t_pipe *needs, t_env *env)
{
	char	*home;

	home = env_list_find_var(&env, "HOME");
	if (!home || !*home)
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

void	cd_dir(t_pipe *needs, char *dir, t_env *env)
{
	if (chdir(dir) != 0)
	{
		*(needs->ex_stat) = 1;
		ft_set_status(*(needs->ex_stat), 1);
		if (ft_strcmp(dir, "..") == 0)
			env_search_and_add(env, "/..", "PWD");
		perror("cd");
		return ;
	}
	*(needs->ex_stat) = 0;
	ft_set_status(*(needs->ex_stat), 1);
}

int	ft_cd(char *dir, t_env *env, t_pipe *needs)
{
	char	cwd[1024];
	char	*oldpwd;

	oldpwd = env_list_find_var(&env, "PWD");
	if (!dir || !ft_strcmp(dir, "~"))
		cd_home(needs, env);
	else
		cd_dir(needs, dir, env);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		*(needs->ex_stat) = 1;
		ft_set_status(*(needs->ex_stat), 1);
		perror("getcwd");
		return (1);
	}
	env_search_replace(env, cwd, "PWD");
	if (!env_list_serch(&env, "OLDPWD"))
	{
		if (oldpwd && *oldpwd)
			ft_export("OLDPWD", oldpwd, &env, needs);
	}
	else
		if (oldpwd && *oldpwd)
			env_search_replace(env, oldpwd, "OLDPWD");
	return (1);
}

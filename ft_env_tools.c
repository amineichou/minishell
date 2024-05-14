/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:16:50 by moichou           #+#    #+#             */
/*   Updated: 2024/05/14 22:05:39 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_envinlist(t_toexec **head, t_env **env_list)
{
	t_toexec	*current;

	current = *head;
	while (current != NULL)
	{
		current->env = (*env_list);
		current = current->next;
	}
}

void	update_env(t_env *envl)
{
	char	*to_replace;

	to_replace = ft_env_list_serch_res(envl, "SHLVL");
	env_search_replace(envl, ft_itoa(ft_atoi(to_replace) + 1, false), "SHLVL");
}

static void	ft_add_last_env(t_env *new_env, t_env *envl)
{
	t_env	*tmp;

	tmp = NULL;
	tmp = envl;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_env;
}

t_env	*set_env(char **env)
{
	t_env	*envl;
	t_env	*new_env;
	char	**argument;
	int		i;

	i = 0;
	envl = NULL;
	argument = NULL;
	while (env[i] != NULL)
	{
		new_env = zyalloc(sizeof(t_env), 'a', false);
		if (!new_env)
			return (ft_printerror(MALLOC_ERORR), NULL);
		argument = split_env(env[i], '=');
		new_env->var = ft_strdup(argument[1], false);
		new_env->name = ft_strdup(argument[0], false);
		new_env->next = NULL;
		if (envl == NULL)
			envl = new_env;
		else
			ft_add_last_env(new_env, envl);
		i++;
	}
	return (envl);
}

t_env	*set_spare_env(void)
{
	t_env	*head;
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd");
	head = zyalloc(sizeof(t_env), 'a', false);
	head->name = ft_strdup("SHLVL", false);
	head->var = ft_strdup("0", false);
	head->next = zyalloc(sizeof(t_env), 'a', false);
	head->next->name = ft_strdup("PATH", false);
	head->next->var = \
	ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", false);
	head->next->next = zyalloc(sizeof(t_env), 'a', false);
	head->next->next->name = ft_strdup("PWD", false);
	head->next->next->var = ft_strdup(cwd, false);
	head->next->next->next = zyalloc(sizeof(t_env), 'a', false);
	head->next->next->next->name = ft_strdup("_", false);
	head->next->next->next->var = ft_strdup("./minishell", false);
	head->next->next->next->next = NULL;
	return (head);
}

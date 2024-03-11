/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:39:33 by zyamli            #+#    #+#             */
/*   Updated: 2024/03/10 21:35:13 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

void freeList(t_env *head)
{
	t_env *current = head;
	t_env *next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}
void env_print(t_toexec *data)
{
	t_env *tmp;

	tmp = data->env;
	while(tmp)
	{
		printf("%s=", tmp->name);
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
}
void ft_unset(t_env **env, char *to_del)
{
	t_env *tmp;
	t_env *prev;

	tmp = *env;
	prev = NULL;
	if (tmp != NULL && strcmp(tmp->name, to_del) == 0)
	{
		prev = *env;
		*env = (*env)->next;
		free(tmp->var);	
		free(tmp->name);
		free(prev);
		// free(tmp);
	}
	else
		while(tmp && tmp->next)
		{
			if(strcmp(tmp->next->name, to_del) == 0)
			{
				prev = tmp->next;
				tmp->next = tmp->next->next;
				free(prev->var);
				free(prev->name);
				free(prev);
			}
			tmp = tmp->next;
		}
	if(tmp == NULL)
		return ;
}



int main(int ac, char **av, char **env)
{
	t_env	*envi = NULL;
	t_env	*tmp = NULL;
	char	**arg = NULL;
	t_toexec data;

	(void)ac;
	// (void)av;
	int i;

	i = 0;
	while (env[i])
	{
		t_env *new_env = malloc(sizeof(t_env));
		if (!new_env)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
        }
		arg = ft_split(env[i], '=');
        new_env->var = arg[1];
		new_env->name = arg[0];
        new_env->next = NULL;
        if (envi == NULL)
            envi = new_env;
		else
		{
			tmp = envi;
            while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_env;
		}
		i++;
	}
	data.env = envi;

	// env_print(&data);
	// exit(1);
	// char *to_unset = ft_strjoin(av[1], "=");
	ft_unset(&data.env, av[1]);
	env_print(&data);
	// while(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:39:33 by zyamli            #+#    #+#             */
/*   Updated: 2024/03/06 22:32:52 by zyamli           ###   ########.fr       */
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
void env_print(t_token *data)
{
	t_env *tmp;

	tmp = data->env;
	while(tmp)
	{
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
	if (tmp != NULL && strncmp(tmp->var, to_del, strlen(to_del)) == 0)
	{
		prev = *env;
		*env = (*env)->next;
		// printf("%p llj\n", tmp->var);
		free(prev);
		// free(tmp);
	}
	else
		while(tmp->next)
		{
			if(strncmp(tmp->next->var, to_del, strlen(to_del)) == 0)
			{
				prev = tmp->next;
				tmp->next = tmp->next->next;
				free(prev->var);
				free(prev);
			}
			tmp = tmp->next;
		}
	if(tmp == NULL)
		return ;
}
int main(int ac, char **av, char **env)
{
	t_env *envi = NULL;
	t_env *tmp = NULL;
	t_token data;

	(void)ac;
	(void)av;
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
        new_env->var = strdup(env[i]);
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
	ft_unset(&data.env, "TERM");
	env_print(&data);
}
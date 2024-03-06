/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:54:51 by zyamli            #+#    #+#             */
/*   Updated: 2024/03/06 20:38:36 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

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

	env_print(&data);
}
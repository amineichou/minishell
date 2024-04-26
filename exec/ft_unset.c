/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:39:33 by zyamli            #+#    #+#             */
/*   Updated: 2024/04/25 15:32:15 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

void freeList(t_env **head)
{
	t_env *current;
	t_env *next;

	current = *head;
	while (current != NULL)
	{

		next = current->next;
		free(current->name);
		free(current->var);
		free(current);
		current = next;
	}
}
// void env_print(t_toexec *data)
// {
// 	t_env *tmp;

// 	tmp = data->env;
// 	while(tmp)
// 	{
// 		printf("%s=", tmp->name);
// 		printf("%s\n", tmp->var);
// 		tmp = tmp->next;
// 	}
// }
void ft_unset(t_env **env, char *to_del)
{
	t_env *tmp;
	t_env *prev;

	tmp = *env;
	prev = NULL;

	// if (tmp != NULL && strcmp(tmp->name, to_del) == 0)
	// {
	// 	prev = *env;
	// 	*env = (*env)->next;
	// 	free(tmp->var);	
	// 	free(tmp->name);
	// 	free(prev);
	// 	// free(tmp);
	// }
	// else
	// {
	// 	while(tmp && tmp->next)
	// 	{
	// 		if(strcmp(tmp->next->name, to_del) == 0)
	// 		{
	// 			printf("{{%s}}\n", tmp->next->name);
	// 			prev = tmp->next;
	// 			if (tmp && tmp->next && tmp->next->next)
	// 				tmp = tmp->next->next;
	// 			else
	// 				tmp = NULL;
	// 			free(prev->var);
	// 			free(prev->name);
	// 			free(prev);
	// 		}
	// 		tmp = tmp->next;
	// 	}
	// }
	if (tmp != NULL && ft_strcmp(tmp->name, to_del) == 0)
	{

		prev = *env;
		*env = (*env)->next;
		free(tmp->var);
		free(tmp->name);
		free(prev);
		// free(tmp);
	}
	else
	{
		while(tmp)
		{
			if(tmp->next && (ft_strcmp(tmp->next->name, to_del) == 0))
			{
				prev = tmp->next;
				if (tmp->next->next)
				{
					tmp->next = tmp->next->next;
					free(prev->var);
					prev->var = NULL;
					free(prev->name);
					prev->name = NULL;
					free(prev);
					prev = NULL;
				}
				else
					tmp->next = NULL;
				break;
			}
			tmp = tmp->next;
		}
	}
}



int unseter(t_toexec *cmd, t_pipe *needs)
{
	// t_env	*envi = NULL;
	// t_env	*tmp = NULL;
	// char	**arg = NULL;
	// t_toexec data;

	// (void)ac;
	// // (void)av;
	// int i;

	// i = 0;
	// while (env[i])
	// {
	// 	t_env *new_env = malloc(sizeof(t_env));
	// 	if (!new_env)
	// 	{
	// 		perror("malloc");
	// 		exit(EXIT_FAILURE);
    //     }
	// 	arg = ft_split(env[i], '=');
    //     new_env->var = arg[1];
	// 	new_env->name = arg[0];
    //     new_env->next = NULL;
    //     if (envi == NULL)
    //         envi = new_env;
	// 	else
	// 	{
	// 		tmp = envi;
    //         while (tmp->next)
	// 			tmp = tmp->next;
	// 		tmp->next = new_env;
	// 	}
	// 	i++;
	// }
	// data.env = envi;

	// // env_print(&data);
	// // exit(1);
	// // char *to_unset = ft_strjoin(av[1], "=");
	(void)needs;
	int i = 1;
	while(cmd->args[i])
	{
		ft_unset(&cmd->env, cmd->args[i]);
		i++;
	}
	*(needs->ex_stat) = 0;
	return(1);
	// env_print(&data);
	// while(1);
}

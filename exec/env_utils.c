/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:19:15 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/11 15:20:16 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lst_add(t_env **lst, t_env *new)
{
	t_env	*lastone;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	lastone = *lst;
	while (lastone->next)
		lastone = lastone->next;
	lastone->next = new;
	new->next = NULL;
}

t_env	*env_new(char *var, char *name, bool to_free)
{
	t_env	*newnode;

	newnode = (t_env *)zyalloc(sizeof(t_env), 'a', to_free);
	if (newnode == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	newnode->var = ft_strdup(var, to_free);
	newnode->name = ft_strdup(name, to_free);
	newnode->next = NULL;
	return (newnode);
}

void	env_search_replace(t_env *head, char *to_replace, char *to_look)
{
	t_env	*tmp;

	if (!head)
		return ;
	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, to_look) == 0)
		{
			tmp->var = ft_strdup(to_replace, false);
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

int	env_list_serch(t_env **head, char *to_look)
{
	t_env	*tmp;

	if (!(*head))
		return (0);
	tmp = *head;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, to_look) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	env_search_and_add(t_env *head, char *to_add, char *to_look)
{
	t_env	*tmp;

	if (!head)
		return ;
	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, to_look) == 0)
		{
			tmp->var = ft_strjoin(tmp->var, to_add, false);
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

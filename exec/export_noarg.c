/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_noarg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:09:41 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/12 21:41:28 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*duplicate_list(t_env **head)
{
	t_env	*tmp;
	t_env	*newlist;
	t_env	*tmpnew;
	t_env	*newnode;

	if (head == NULL)
		return (NULL);
	tmp = *head;
	newlist = NULL;
	tmpnew = NULL;
	while (tmp != NULL)
	{
		newnode = env_new(tmp->var, tmp->name, true);
		if (newlist == NULL)
			newlist = newnode;
		else
			tmpnew->next = newnode;
		tmpnew = newnode;
		tmp = tmp->next;
	}
	return (newlist);
}

void	export_env_print(t_toexec *data)
{
	t_env	*tmp;

	if (!data || !data->env)
		return ;
	tmp = data->env;
	while (tmp)
	{
		printf("declare -x %s", tmp->name);
		if (tmp->var)
			printf("=\"%s\"", tmp->var);
		printf("\n");
		tmp = tmp->next;
	}
}

void	swap(t_env *a, t_env *b)
{
	char	*temp_var;
	char	*temp_name;

	temp_var = a->var;
	temp_name = a->name;
	a->var = b->var;
	a->name = b->name;
	b->var = temp_var;
	b->name = temp_name;
}

void	env_sort(t_env **start)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;

	lptr = NULL;
	if (start == NULL)
		return ;
	while (1)
	{
		swapped = 0;
		ptr1 = *start;
		while (ptr1->next != lptr)
		{
			if (ft_strncmp(ptr1->name, ptr1->next->name,
					ft_strlen(ptr1->name) + ft_strlen(ptr1->next->name)) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		if (!swapped)
			break ;
		lptr = ptr1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:54:51 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/14 20:34:22 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lst_size(t_toexec *head)
{
	int			i;
	t_toexec	*lst;

	i = 0;
	lst = head;
	if (!head)
		return (-1);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	env_size(t_env *head)
{
	int		i;
	t_env	*lst;

	i = 0;
	lst = head;
	if (!head)
		return (-1);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**env_tolist(t_env **env_list)
{
	int		size;
	int		i;
	char	*tmp;
	t_env	*current;
	char	**result;

	if (!env_list || !*env_list)
		return (NULL);
	size = env_size(*env_list);
	current = (*env_list);
	result = (char **)zyalloc(sizeof(char *) * (size + 1), 'a', true);
	if (!result)
		return (perror("malloc"), NULL);
	i = 0;
	while (current != NULL)
	{
		tmp = ft_strjoin(current->name, "=", true);
		result[i] = ft_strjoin(tmp, current->var, true);
		current = current->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	env_print(t_env **data)
{
	t_env	*tmp;

	tmp = *(data);
	while (tmp)
	{
		if (tmp->name && tmp->var)
			printf("%s=%s\n", tmp->name, tmp->var);
		tmp = tmp->next;
	}
	return (1);
}

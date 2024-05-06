/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_expand_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:13:13 by moichou           #+#    #+#             */
/*   Updated: 2024/05/04 15:57:06 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_expand	*ft_create_expand_node(char *str)
{
	t_expand	*node;

	node = zyalloc(sizeof(t_expand), 'a', true);
	if (!node)
		return (ft_printerror(MALLOC_ERORR), NULL);
	node->value = str;
	node->next = NULL;
	return (node);
}

void	ft_append_node_expand(t_expand **head, t_expand *node)
{
	t_expand	*last;

	if ((*head) == NULL)
	{
		(*head) = node;
		// (*head)->next = NULL;
		return ;
	}

	last = (*head);
	while (last->next)
		last = last->next;
	last->next = node;
	node->next = NULL;
}

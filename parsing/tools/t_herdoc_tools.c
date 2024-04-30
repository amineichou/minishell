/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_herdoc_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 11:34:29 by moichou           #+#    #+#             */
/*   Updated: 2024/04/30 12:00:57 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_herdoc	*ft_create_herdoc_node(char *del)
{
	t_herdoc	*node;

	node = malloc(sizeof(t_herdoc));
	if (!node)
		return (ft_printerror(MALLOC_ERORR), NULL);
	node->del = del;
	node->next = NULL;
	return (node);
}

void	ft_append_node_herdoc(t_herdoc **head, t_herdoc *node)
{
	t_herdoc	*last;

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
	// node->next = NULL;
}
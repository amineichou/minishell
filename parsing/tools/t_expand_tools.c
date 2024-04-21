/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_expand_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:13:13 by moichou           #+#    #+#             */
/*   Updated: 2024/04/21 11:35:32 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_expand	*ft_create_expand_node(char *str)
{
	t_expand	*node;

	node = malloc(sizeof(t_expand));
	if (!node)
		return (ft_print_error(MALLOC_ERORR), NULL);
	node->value = str;
	node->is_expand = true;
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

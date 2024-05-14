/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 03:30:26 by moichou           #+#    #+#             */
/*   Updated: 2024/05/14 10:28:48 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_append_node_t_token(t_token **head, t_token *node)
{
	t_token	*last;

	if ((*head) == NULL)
	{
		(*head) = node;
		(*head)->next = NULL;
		return ;
	}
	last = (*head);
	while (last->next)
		last = last->next;
	last->next = node;
	node->next = NULL;
}

void	ft_pop_node_t_token(t_token **head, t_token *to_pop)
{
	t_token	*prev;

	if ((*head) == NULL)
		return ;
	prev = (*head);
	if ((*head) == to_pop)
	{
		(*head) = to_pop->next;
		return ;
	}
	while (prev)
	{
		if (prev->next == to_pop)
		{
			prev->next = to_pop->next;
			break ;
		}
		prev = prev->next;
	}
}

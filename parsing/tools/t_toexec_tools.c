/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_toexec_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 03:30:22 by moichou           #+#    #+#             */
/*   Updated: 2024/05/19 15:04:27 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_append_node_t_toexec(t_toexec **head, t_toexec *node)
{
	t_toexec	*last;

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

void	ft_check_valid_fd(t_toexec **head)
{
	t_toexec	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->output == -1 || tmp->input == -1)
			tmp->args = NULL;
		tmp = tmp->next;
	}
}

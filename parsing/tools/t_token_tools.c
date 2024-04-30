/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 03:30:26 by moichou           #+#    #+#             */
/*   Updated: 2024/04/30 15:11:55 by moichou          ###   ########.fr       */
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
		free(to_pop->value);
		free(to_pop);
		return ;
	}
	while (prev)
	{
		if (prev->next == to_pop)
		{
			prev->next = to_pop->next;
			free(to_pop->value);
			free(to_pop);
			break;
		}
		prev = prev->next;
	}
}

// int main(void)
// {
// 	t_token *head = malloc(sizeof(t_token));
// 	t_token *node1 = malloc(sizeof(t_token));
// 	t_token *node2 = malloc(sizeof(t_token));
// 	t_token *node3 = malloc(sizeof(t_token));
// 	t_token *node4 = malloc(sizeof(t_token));
// 	t_token *node5 = malloc(sizeof(t_token));
// 	head->next = node1;
// 	node1->next = node2;
// 	node2->next = node3;
// 	node3->next = node4;
// 	node4->next = node5;
// 	node5->next = NULL;
	
// 	t_token *test = head;
// 	int i = 0;
// 	while (test)
// 	{
// 		test->order = i;
// 		test->value = NULL;
// 		i++;
// 		test = test->next;
// 	}

// 	ft_pop_node_t_token(&head, head);
// 	ft_pop_node_t_token(&head, node1);
// 	ft_pop_node_t_token(&head, node2);
// 	ft_pop_node_t_token(&head, node3);
// 	ft_pop_node_t_token(&head, node4);
// 	ft_pop_node_t_token(&head, node5);
// 	t_token *last = head;
// 	while (last)
// 	{
// 		printf("%d\n", last->order);
// 		last = last->next;
// 	}
// }
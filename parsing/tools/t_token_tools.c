/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 03:30:26 by moichou           #+#    #+#             */
/*   Updated: 2024/03/22 03:16:23 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../includes/macros.h"

t_toexec	*ft_create_node(char *cmd, char **args)
{
	t_toexec	*node;

	node = malloc(sizeof(t_toexec));
	if (!node)
		return (ft_printerror(MALLOC_ERORR) ,NULL);
	node->args = args;
	return (node);
}

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

// int main(void)
// {
// 	t_toexec *head = malloc(sizeof(t_toexec));
// 	t_toexec *node1 = malloc(sizeof(t_toexec));
// 	t_toexec *node2 = malloc(sizeof(t_toexec));
// 	t_toexec *node3 = malloc(sizeof(t_toexec));
// 	t_toexec *node4 = malloc(sizeof(t_toexec));
// 	t_toexec *node5 = malloc(sizeof(t_toexec));
// 	head->next = node1;
// 	node1->next = node2;
// 	node2->next = node3;
// 	node3->next = node4;
// 	node4->next = node5;
// 	node5->next = NULL;
	
// 	t_toexec *test = head;
// 	int i = 0;
// 	while (test)
// 	{
// 		test->input = i;
// 		i++;
// 		test = test->next;
// 	}

// 	t_toexec *last = head;
// 	while (last->next)
// 		last = last->next;
// 	printf("%d\n", last->input);
// }
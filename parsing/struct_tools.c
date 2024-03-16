/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:16:12 by moichou           #+#    #+#             */
/*   Updated: 2024/03/16 01:18:23 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "includes/macros.h"

t_toexec	*ft_create_node(char *cmd, char **args)
{
	t_toexec	*node;

	node = malloc(sizeof(t_toexec));
	if (!node)
		return (ft_printerror(MALLOC_ERORR) ,NULL);
	node->cmd = cmd;
	node->args = args;
	return (node);
}

t_toexec	*ft_append_node(t_toexec *head, t_toexec *node)
{
	t_toexec	*last;

	if (head == NULL)
	{
		head = node;
		node->next = NULL;
		return (head);
	}

	last = head;
	while (last->next)
		last = last->next;
	last->next = node;
	node->next = NULL;
	return (head);
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
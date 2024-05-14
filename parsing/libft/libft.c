/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:59:34 by moichou           #+#    #+#             */
/*   Updated: 2024/05/14 14:43:41 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	garb_add(t_garbage **lst, t_garbage *new)
{
	t_garbage	*lastone;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	lastone = *lst;
	while (lastone->next)
		lastone = lastone->next;
	lastone->next = new;
	new->next = NULL;
}

static t_garbage	*garb_new(void *addrress, bool is_free)
{
	t_garbage	*newnode;

	newnode = malloc(sizeof(t_garbage));
	if (newnode == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	newnode->adr = addrress;
	newnode->is_free = is_free;
	newnode->next = NULL;
	return (newnode);
}

static void	free_garb_list(t_garbage **head)
{
	t_garbage	*current;
	t_garbage	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		if (current->is_free)
		{
			free(current->adr);
			current->adr = NULL;
		}
		current = next;
	}
}

void	*zyalloc(size_t size, int flag, bool is_free)
{
	static t_garbage	*gooper;
	t_garbage			*node;
	void				*address;

	address = NULL;
	if (flag == 'a')
	{
		address = malloc(size);
		if (!address)
			(perror("malloc"), exit(1));
		if (gooper == NULL)
			gooper = garb_new(address, is_free);
		else
		{
			node = garb_new(address, is_free);
			garb_add(&gooper, node);
		}
	}
	else if (flag == 'f')
		free_garb_list(&gooper);
	return (address);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*p1;
	const char	*p2;
	const char	*p1_advance;

	if (*needle == '\0')
		return ((char *)haystack);
	p1_advance = haystack;
	while (*p1_advance)
	{
		p1 = p1_advance;
		p2 = needle;
		while (*p1 && *p2 && *p1 == *p2)
		{
			p1++;
			p2++;
		}
		if (*p2 == '\0')
			return ((char *)p1_advance);
		p1_advance++;
	}
	return (NULL);
}

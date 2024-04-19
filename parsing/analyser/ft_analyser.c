/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:02:34 by moichou           #+#    #+#             */
/*   Updated: 2024/04/05 00:39:03 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char		**ft_reallocate_copy(char **old_res, char *new)
{
	char	**res;
	int		i;

	i = 0;
	if (!old_res)
	{
		res = malloc(sizeof(char *) * 2);
		res[0] = ft_strdup(new); // leaks if new is mallocated
		res[1] = NULL;
	}
	else
	{
		while (old_res[i])
			i++;
		res = malloc(sizeof(char *) * (i + 2));
		i = 0;
		while (old_res[i])
		{
			res[i] = ft_strdup(old_res[i]);
			i++;
		}
		res[i] = ft_strdup(new);
		res[i + 1] = NULL;
	}
	return (res);
}

static void	ft_handle_args(t_toexec **node, t_token **lst_token)
{
	char	**joined;

	joined = NULL;
	while ((*lst_token) && (*lst_token)->token == WORD)
	{
		joined = ft_reallocate_copy(joined, (*lst_token)->value); // TODO : leaks
		(*lst_token) = (*lst_token)->next;
	}
	(*node)->args = joined;
}

static void	ft_set_default_vals(t_toexec *node)
{
	node->input = 0;
	node->output = 1;
	node->args = NULL;
}

// analyser will analyze tokens and create the t_toexec list
t_toexec	*ft_analyser(char *sanitize_result)
{
	t_token		*lst_token;
	t_toexec	*lst_toexec;
	t_toexec	*node;

	lst_token = ft_make_tokens(sanitize_result);
	// expanding
	lst_toexec = NULL;
	while (lst_token)
	{
		node = malloc(sizeof(t_toexec));
		if (!node)
			return (ft_printerror(MALLOC_ERORR), NULL);
		ft_set_default_vals(node);
		if (lst_token->token == WORD)
		{
			ft_handle_args(&node, &lst_token);
			if (lst_token == NULL)
			{
				ft_append_node_t_toexec(&lst_toexec, node);
				break;
			}
		}
		if (lst_token->token == RD_AP || lst_token->token == RD_RP || lst_token->token == RD_IN)
		{
			ft_handle_redirections(&lst_token, node);
			if (lst_token == NULL)
			{
				ft_append_node_t_toexec(&lst_toexec, node);
				break;
			}
			else if (lst_token->token == WORD)
			{
				ft_handle_args(&node, &lst_token);
				if (lst_token == NULL)
				{
					ft_append_node_t_toexec(&lst_toexec, node);
					break;
				}
			}
		}
		if (lst_token->token == PIPE)
		{
			lst_token = lst_token->next;
			ft_append_node_t_toexec(&lst_toexec, node);
			continue;
		}
	}
	return (lst_toexec);
}

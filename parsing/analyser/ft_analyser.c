/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:02:34 by moichou           #+#    #+#             */
/*   Updated: 2024/05/13 17:16:30 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// return -1 == exit loop aka don't send to exec
static int	ft_analyse_herdoc(t_token **lst_token, t_toexec *node)
{
	if ((*lst_token) && (*lst_token)->token == HEREDOC)
	{
		if (ft_hnadle_herdoc(lst_token, node) == -1)
		{
			ft_set_status(1, 1);
			signal(SIGINT, ft_sigkill_handler);
			return (-1);
		}
	}
	signal(SIGINT, ft_sigkill_handler);
	return (0);
}

// return 1 == break
static int	ft_analyse_args(t_token **lst_token,
		t_toexec **lst_toexec, t_toexec *node)
{
	if ((*lst_token) && (*lst_token)->token == WORD)
	{
		ft_handle_args(&node, lst_token);
		if (lst_token == NULL)
		{
			ft_append_node_t_toexec(lst_toexec, node);
			return (1);
		}
	}
	return (0);
}

// return 1 == break
static int	ft_analyse_redd(t_token **lst_token, t_toexec *node)
{
	if ((*lst_token) && ((*lst_token)->token == RD_AP
			|| (*lst_token)->token == RD_RP || (*lst_token)->token == RD_IN))
	{
		ft_handle_redirections(lst_token, node);
		if (lst_token == NULL)
			return (1);
	}
	return (0);
}

static void	ft_analyser_init(t_token **lst_token, t_toexec **lst_toexec,
			char *sanitize_result, t_env *envl)
{
	*lst_token = ft_make_tokens(sanitize_result);
	*lst_token = ft_make_tokens(ft_expand(*lst_token, envl));
	*lst_token = ft_lst_remvove_qoutes(*lst_token);
	*lst_toexec = NULL;
}

// analyser will analyze tokens and create the t_toexec list
t_toexec	*ft_analyser(char *sanitize_result, t_env *envl)
{
	t_token		*lst_token;
	t_toexec	*lst_toexec;
	t_toexec	*node;

	ft_analyser_init(&lst_token, &lst_toexec, sanitize_result, envl);
	while (lst_token)
	{
		node = zyalloc(sizeof(t_toexec), 'a', true);
		if (!node)
			return (ft_printerror(MALLOC_ERORR), NULL);
		ft_set_default_vals(node, envl);
		while (lst_token && lst_token->token != PIPE)
		{
			if (ft_analyse_args(&lst_token, &lst_toexec, node))
				break ;
			if (ft_analyse_herdoc(&lst_token, node) == -1)
				return (NULL);
			if (ft_analyse_redd(&lst_token, node))
				break ;
		}
		ft_append_node_t_toexec(&lst_toexec, node);
		if (lst_token)
			lst_token = lst_token->next;
	}
	return (lst_toexec);
}

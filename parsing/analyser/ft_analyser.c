/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:02:34 by moichou           #+#    #+#             */
/*   Updated: 2024/05/13 10:28:43 by moichou          ###   ########.fr       */
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
		res = zyalloc(sizeof(char *) * 2, 'a', true);
		res[0] = ft_strdup(new, true);
		res[1] = NULL;
	}
	else
	{
		while (old_res[i])
			i++;
		res = zyalloc(sizeof(char *) * (i + 2), 'a', true);
		i = 0;
		while (old_res[i])
		{
			res[i] = ft_strdup(old_res[i], true);
			i++;
		}
		res[i] = ft_strdup(new, true);
		res[i + 1] = NULL;
	}
	return (res);
}

void	ft_handle_args(t_toexec **node, t_token **lst_token)
{
	char	**joined;
	int		i;

	i = 0;
	joined = (*node)->args;
	if ((*lst_token) && (*lst_token)->value == NULL)
	{
		(*node)->args = NULL;
		(*lst_token) = (*lst_token)->next;
		return ;
	}
	while ((*lst_token) && (*lst_token)->token == WORD)
	{
		joined = ft_reallocate_copy(joined, (*lst_token)->value);
		(*lst_token) = (*lst_token)->next;
	}

	(*node)->args = joined;
}

char	*ft_get_herdoc_del(char *line, int *i)
{
	int	start;
	int	length;

	*i += 2;
	length = 0;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (line[*i] && ft_isquote(line[*i]))
		return (ft_get_inside_quotes(line, i, line[*i]));
	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && !ft_isspecialchars(line[*i]))
	{
		(*i)++;
		length++;
	}
	if (length)
		return (ft_strldup(&line[start], length));
	return (NULL);
}

static void	ft_set_default_vals(t_toexec *node, t_env *envl)
{
	node->input = 0;
	node->output = 1;
	node->args = NULL;
	node->env = envl;
}

// static char *ft_ckeck_herdoc_del(char *del, t_herdoc *node)
// {
// 	char	*res;

// 	if (ft_isquote(del[0]))
// 	{
// 		node->is_expand = false;
// 		return (ft_strldup(&del[1], ft_strlen(del) - 2));
// 	}
// 	node->is_expand = true;
// 	res = ft_strdup(del, true);
// 	return (res);
// }

// static void	ft_skip_till_end(t_token **lst_token)
// {
// 	while ((*lst_token))
// 		(*lst_token) = (*lst_token)->next;
// 	// if ((*lst_token))
// 	// 	(*lst_token) = (*lst_token)->next;
// }

// checks for quotes and return false i any
static bool	ft_isexpand_herdoc(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (ft_isquote(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	ft_hnadle_herdoc(t_token **lst_token, t_toexec *node)
{
	char	*del;
	bool	is_expand;

	while ((*lst_token) && (*lst_token)->token == HEREDOC)
	{
		if ((*lst_token)->next)
			del = (*lst_token)->next->value;
		else
			del = NULL;
		is_expand = ft_isexpand_herdoc(del);
		del = ft_remove_qoutes(del);
		if (del && ft_heredoc_handler_exec(node, del, is_expand) == -1)
		{
			close_all();
			return (-1);
		}
		if ((*lst_token)->next)
			(*lst_token) = (*lst_token)->next->next;
		else
			(*lst_token) = (*lst_token)->next;
	}
	return (1);
}

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
static int	ft_analyse_args(t_token **lst_token, t_toexec **lst_toexec, t_toexec *node)
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
static int	ft_analyse_redd(t_token **lst_token, t_toexec **lst_toexec, t_toexec *node)
{
	if ((*lst_token) && ((*lst_token)->token == RD_AP
		|| (*lst_token)->token == RD_RP || (*lst_token)->token == RD_IN))
	{
		ft_handle_redirections(lst_token, node);
		(void)lst_toexec;
		// ft_append_node_t_toexec(lst_toexec, node);
		if (lst_token == NULL)
			return (1);
	}
	return (0);
}

// analyser will analyze tokens and create the t_toexec list
t_toexec	*ft_analyser(char *sanitize_result, t_env *envl)
{
	t_token		*lst_token;
	t_toexec	*lst_toexec;
	t_toexec	*node;

	lst_token = ft_make_tokens(sanitize_result);
	lst_token = ft_make_tokens(ft_expand(lst_token, envl));
	lst_token = ft_lst_remvove_qoutes(lst_token);
	// test_tokens(lst_token);
	lst_toexec = NULL;
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
			if (ft_analyse_redd(&lst_token, &lst_toexec, node))
				break ;
		}
		// if there's NULL after pipe
		if (lst_token && lst_token->token == PIPE
			&& lst_token->next == NULL)
		{
			// node = zyalloc(sizeof(t_toexec), 'a', true);
			// if (!node)
			// 	return (ft_printerror(MALLOC_ERORR), NULL);
			node->args = NULL;
			ft_append_node_t_toexec(&lst_toexec, node);
			lst_token = lst_token->next;
			break;
		}
		else
			ft_append_node_t_toexec(&lst_toexec, node);
		if (lst_token)
			lst_token = lst_token->next;
	}
	return (lst_toexec);
}

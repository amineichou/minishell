/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:02:34 by moichou           #+#    #+#             */
/*   Updated: 2024/03/20 02:58:50 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// free after using
static char	*ft_get_cmd(char *str)
{
	char	*res;
	int		i;
	int		in_quotes;

	i = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
			in_quotes = 1;
		if (str[i] == ' ' && !in_quotes)
			break;
		i++;
	}
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		perror("MALLOC_ERORR");
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			break;
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static char **ft_get_args(char *str)
{
	char	**res;
	int		i;
	while (str[i])
	{
		if (str[i] == ' ')
			break ;
		i++;
	}
	res = ft_split(str + i, ' ');
	return (res);
}

t_toexec	*ft_analyser(char *sanitize_result)
{
	t_token		*lst_token;
	t_toexec	*lst_toexec;
	t_toexec	*node;

	lst_token = ft_analyse_tokens(sanitize_result);
	lst_toexec = NULL;
	while (lst_token)
	{
		node = malloc(sizeof(t_toexec));
		if (lst_token->token == PIPE)
		{
			lst_token = lst_token->next;
			continue;
		}
		if (lst_token->token != PIPE && lst_token->token != WORD)
		{
			ft_handle_redirections(lst_token->token, &lst_toexec, node);
			lst_token = lst_token->next;
			continue;
		}
		if (lst_token->token == WORD)
		{
			node->cmd = ft_get_cmd(lst_token->value);
			node->args = ft_get_args(lst_token->value);
			node->input = 0;
			node->output = 2;
		}
		ft_append_node_t_toexec(&lst_toexec, node);
		lst_token = lst_token->next;
	}
	return (lst_toexec);
}

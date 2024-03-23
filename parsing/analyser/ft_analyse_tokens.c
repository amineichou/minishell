/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:29:49 by moichou           #+#    #+#             */
/*   Updated: 2024/03/22 00:11:12 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../includes/macros.h"


static token	ft_check_token(char *args)
{
	if (args[0] == '|')
		return (PIPE);
	if (args[0] == '<')
	{
		if (args[1] == '<')
			return (HEREDOC);
		return (RD_IN);
	}
	if (args[0] == '>')
	{
		if (args[1] == '>')
			return (RD_AP);
		return (RD_RP);
	}
	return (0);
}

static void ft_increase_helper(int *i, int *j)
{
	(*i)++;
	(*j)++;
}

static void  ft_count_with_quotes(char *sanitize_result, int *i, int *j)
{
	while (sanitize_result[*i] && !ft_isspecialchars(sanitize_result[*i]))
	{
		if (ft_isquote(sanitize_result[*i]) == 1)
		{
			(*j)++;
			(*i)++;
			while (sanitize_result[*i] && ft_isquote(sanitize_result[*i]) != 1)
			{
				(*j)++;
				(*i)++;
			}
		}
		else if (ft_isquote(sanitize_result[*i]) == 2)
		{
			(*j)++;
			(*i)++;
			while (sanitize_result[*i] && ft_isquote(sanitize_result[*i]) != 2)
			{
				(*j)++;
				(*i)++;
			}
		}
		ft_increase_helper(i, j);
	}
}

static void	ft_count_without_quotes(char *sanitize_result, int *i, int *j)
{
	while (sanitize_result[*i] && ft_isspecialchars(sanitize_result[*i]))
		ft_increase_helper(i, j);
}

static void	ft_edit_node(t_token **node, char *sanitize_result, int start, int j)
{
	(*node)->value = ft_strlrdup(&sanitize_result[start], j);
	(*node)->value = ft_trim_spaces((*node)->value);
	(*node)->token = ft_check_token((*node)->value);
}

t_token	*ft_analyse_tokens(char *sanitize_result)
{
	t_token		*lst_token;
	t_token		*node;
	int			i;
	int			j;
	int			start;

	i = 0;
	lst_token = NULL;
	while (sanitize_result[i])
	{
		node = malloc(sizeof(t_token));
		j = 0;
		start = i;
		ft_count_with_quotes(sanitize_result, &i, &j);
		if (j > 0)
		{
			ft_edit_node(&node, sanitize_result, start, j);
			ft_append_node_t_token(&lst_token, node);
			continue ;
		}
		ft_count_without_quotes(sanitize_result, &i, &j);
		ft_edit_node(&node, sanitize_result, start, j);
		ft_append_node_t_token(&lst_token, node);
	}
	return (lst_token);
}

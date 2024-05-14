/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:29:49 by moichou           #+#    #+#             */
/*   Updated: 2024/05/14 17:45:39 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_tokenenm	ft_check_token_type(char *args)
{
	if (!args)
		return (WORD);
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
	return (WORD);
}

static void	ft_check_token_val(char *str, int *i)
{
	while (str[*i])
	{
		if (ft_isquote(str[*i]))
			ft_skip_quotes(str, i);
		if ((str[*i] && ft_isspecialchars(str[*i]))
			|| (str[*i] && ft_isspace(str[*i]))
			|| str[*i] == '\0')
			break ;
		(*i)++;
	}
}

static void	ft_handle_spcecial_tokens(char *str, int *i)
{
	if (str[*i] == '|')
		(*i)++;
	else
	{
		while (str[*i] && ft_isspecialchars(str[*i]))
			(*i)++;
	}
}

static char	*ft_get_toknen_val(char *str, int start, int i)
{
	char	*res;

	res = ft_strldup(&str[start], i - start);
	if (!res)
		return (NULL);
	return (ft_trim_spaces(res));
}

t_token	*ft_make_tokens(char *sanitize_result)
{
	t_token	*lst_token;
	t_token	*node;
	int		i;
	int		start;

	i = 0;
	lst_token = NULL;
	if (!sanitize_result)
		return (NULL);
	while (sanitize_result[i])
	{
		node = zyalloc(sizeof(t_token), 'a', true);
		if (!node)
			return (ft_printerror(MALLOC_ERORR), NULL);
		start = i;
		ft_check_token_val(sanitize_result, &i);
		if (start == i)
			ft_handle_spcecial_tokens(sanitize_result, &i);
		while (sanitize_result[i] && ft_isspace(sanitize_result[i]))
			i++;
		node->value = ft_get_toknen_val(sanitize_result, start, i);
		node->token = ft_check_token_type(node->value);
		ft_append_node_t_token(&lst_token, node);
	}
	return (lst_token);
}

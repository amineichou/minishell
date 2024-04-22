/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:29:49 by moichou           #+#    #+#             */
/*   Updated: 2024/04/22 23:29:43 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static token	ft_check_token_type(char *args)
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
			break;
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
		return (NULL); // TODO : leaks
	return (res);
}


t_token	*ft_make_tokens(char *sanitize_result)
{
	t_token	*lst_token;
	t_token	*node;
	int		i;
	int		start;

	i = 0;
	lst_token = NULL;
	while (sanitize_result[i])
	{
		node = malloc(sizeof(t_token));// TODO : malloc protection
		start = i;
		ft_check_token_val(sanitize_result, &i);
		if (start == i)
			ft_handle_spcecial_tokens(sanitize_result, &i);
		while (sanitize_result[i] && ft_isspace(sanitize_result[i]))
			i++;
		// doing this just temporary to fix some bugs in execution
		node->value = ft_trim_spaces(ft_get_toknen_val(sanitize_result, start, i));// TODO : malloc protection
		node->token = ft_check_token_type(node->value);
		ft_append_node_t_token(&lst_token, node);
		if (sanitize_result[i] == '\0')
			break ;
	}
	return (lst_token);
}

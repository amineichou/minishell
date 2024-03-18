/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:29:49 by moichou           #+#    #+#             */
/*   Updated: 2024/03/18 04:11:46 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../includes/macros.h"

// free after using
static char	*ft_get_word(char *str, int *i)
{
	char	*res;
	int		tmp;

	tmp = *i;
	while (str[*i])
	{
		if (str[*i] == ' ')
			break;
		(*i)++;
	}
	res = malloc(sizeof(char) * (*i + 1));
	if (!res)
		perror("MALLOC_ERORR");
	*i = tmp;
	while (str[*i])
	{
		if (str[*i] == ' ')
			break;
		res[*i] = str[*i];
		(*i)++;
	}
	res[*i] = '\0';
	return (res);
}

static int	ft_count_args(char *rest_args, int index)
{
	int		size;

	size = 0;
	while (rest_args[index++])
	{
		if (rest_args[index] == '"')
		{
			size++;
			while (rest_args[++index] != '"')
				size++;
		}
		if (rest_args[index] == '\'')
		{
			size++;
			while (rest_args[++index] != '\'')
				size++;
		}
		if (rest_args[index] == '|')
		{
			size++;
			break ;
		}
		size++;
	}
	return (size);
}

static char *ft_get_args(char *rest_args, int *i)
{
	char	*res;
	int		size;

	size = ft_count_args(rest_args, *i);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		ft_printerror(MALLOC_ERORR);
	ft_strcpy(res, rest_args, size);
	*i += size;
	return (res);
}

static token	ft_check_token(char *args)
{
	if (args[0] == '|')
		return (PIPE);
	if (args[0] == '<')
		return (RD_IN);
	if (args[0] == '>')
		return (RD_OUT);
	return (0);
}

static void  ft_count_with_quotes(char *sanitize_result, int *i, int *j)
{
	while (sanitize_result[*i] && !ft_isspecialchars(sanitize_result[*i]))
	{
		if (ft_isquote(sanitize_result[*i]) == 1)
		{
			(*j)++;
			(*i)++;
			while (sanitize_result[*i] && ft_isquote(sanitize_result[(*i)++]) != 1)
				(*j)++;
		}
		else if (ft_isquote(sanitize_result[*i]) == 2)
		{
			(*j)++;
			(*i)++;
			while (sanitize_result[*i] && ft_isquote(sanitize_result[(*i)++]) != 2)
				(*j)++;
		}
		else
		{
			(*i)++;
			(*j)++;
		}
	}
}

t_token	*ft_analyser(char *sanitize_result)
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
			node->value = ft_strlrdup(&sanitize_result[start], j);
			node->token = ft_check_token(node->value);
			ft_append_node(&lst_token, node);
			continue ;
		}
		while (sanitize_result[i] && ft_isspecialchars(sanitize_result[i]))
		{
			i++;
			j++;
		}
		node->value = ft_strlrdup(&sanitize_result[start], j);
		node->token = ft_check_token(node->value);
		ft_append_node(&lst_token, node);
	}
	while (lst_token)
	{
		printf("value : %s\n", lst_token->value);
		printf("type %d\n", lst_token->token);
		lst_token = lst_token->next;
	}
	return (lst_token);
}

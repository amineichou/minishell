/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:05:57 by moichou           #+#    #+#             */
/*   Updated: 2024/04/21 21:37:55 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_get_between_quotes(char *str, int *i, int type)
{
	char	*res;
	int		start;

	start = *i;
	(*i)++;
	while (str[*i] && ft_isquote(str[*i]) != type)
		(*i)++;
	// (*i)++;
	res = ft_strldup(&str[start], (*i) - start);
	return (res);
}
static bool	ft_is_expand(char *str)
{
	int	i;
	int	is_dollar;

	is_dollar = 0;
	i = 0;
	if (ft_isquote(str[0]) == 1)
		return (false);
	while (str[i])
	{
		if (str[i] == '$')
		{
			is_dollar = 1;
			break ;
		}
		i++;
	}
	if (is_dollar == 1)
		return (true);
	return (false);
}

static t_expand	*ft_create_expand_list(char *str)
{
	t_expand	*lst_expand;
	t_expand	*node;
	char		*res;
	int			i;
	int			start;

	i = 0;
	lst_expand = NULL;
	while (str[i])
	{
		if (str[i] && ft_isquote(str[i]) == 1)
			res = ft_get_between_quotes(str, &i, 1);
		else if (str[i] && ft_isquote(str[i]) == 2)
			res = ft_get_between_quotes(str, &i, 2);
		else
		{
			start = i;
			while (str[i] && !ft_isquote(str[i]))
				i++;
			if (start != i)
				res = ft_strldup(str, i - start);
		}
		node = ft_create_expand_node(res);
		node->is_expand = ft_is_expand(res);
		ft_append_node_expand(&lst_expand, node);
	}
	return (lst_expand);
}

static char	*ft_expand_dollar(char *str, t_env *env)
{
	t_expand	*lst_expand;
	t_expand	*tmp;
	char		*res;

	lst_expand = ft_create_expand_list(str);
	tmp = lst_expand;
	res = NULL;
	while (tmp)
	{
		if (tmp->is_expand)
			tmp->value = ft_replace_dollar(tmp->value, env);
		tmp = tmp->next;
	}
	tmp = lst_expand;
	while (tmp)
	{
		res = ft_strjoin(res, tmp->value);
		tmp = tmp->next;
	}
	return (res);
}

void	ft_expand(t_token *lst_token, t_env *envl)
{
	t_token	*tmp;

	tmp = lst_token;
	while (tmp)
	{
		if (tmp->token == WORD)
		{
			// tmp->value = ft_replace_dollar(tmp->value, envl);
			tmp->value = ft_expand_dollar(tmp->value, envl);
			tmp->value = ft_remove_qoutes(tmp->value);
			// printf("%s\n", tmp->value);
		}
		tmp = tmp->next;
	}
}

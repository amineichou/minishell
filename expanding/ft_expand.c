/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:05:57 by moichou           #+#    #+#             */
/*   Updated: 2024/04/25 10:49:29 by moichou          ###   ########.fr       */
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
	if (str[*i])
		(*i)++;
	res = ft_strldup(&str[start], (*i) - start);
	return (res);
}

static t_expand	*ft_create_expand_list(char *str)
{
	t_expand	*lst_expand;
	t_expand	*node;
	char		*res;
	int			i;
	int			start;
	bool		is_expand;

	i = 0;
	lst_expand = NULL;
	while (str[i])
	{
		is_expand = true;
		res = NULL;
		if (str[i] && ft_isquote(str[i]) == 1)
		{
			res = ft_get_between_quotes(str, &i, 1);
			is_expand = false;
		}
		else if (str[i] && ft_isquote(str[i]) == 2)
			res = ft_get_between_quotes(str, &i, 2);
		else
		{
			start = i;
			while (str[i] && !ft_isquote(str[i]))
				i++;
			if (start != i)
				res = ft_strldup(&str[start], i - start);
		}
		node = ft_create_expand_node(res);
		node->is_expand = is_expand;
		ft_append_node_expand(&lst_expand, node);
	}
	return (lst_expand);
}

static char	*ft_expand_dollar(char *str, t_env *env, int ex_sta)
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
			tmp->value = ft_replace_dollar(tmp->value, env, ex_sta);
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

void	ft_expand(t_token *lst_token, t_env *envl, int ex_sta)
{
	t_token	*tmp;

	tmp = lst_token;
	while (tmp)
	{
		if (tmp->token == WORD)
		{
			tmp->value = ft_expand_dollar(tmp->value, envl, ex_sta);
			tmp->value = ft_remove_qoutes(tmp->value);
		}
		tmp = tmp->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 01:40:17 by moichou           #+#    #+#             */
/*   Updated: 2024/05/14 15:51:29 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_get_inside_qoutes(char *str, int *i, int type)
{
	char	*res;
	int		start;
	int		length;

	(*i)++;
	start = *i;
	length = 0;
	while (str[*i] && ft_isquote(str[*i]) != type)
	{
		(*i)++;
		length++;
	}
	if (str[*i])
		(*i)++;
	res = ft_strldup(&str[start], length);
	return (res);
}

static void	ft_remove_qoutes_handler(char *str, char *res, int *x, int *i)
{
	res[*x] = str[*i];
	(*x)++;
	(*i)++;
}

static void	ft_cat_inside_qoutes(char *res, char *str, int *i, int *x)
{
	char	*inside_quotes;
	int		j;

	inside_quotes = ft_get_inside_qoutes(str, i, ft_isquote(str[*i]));
	j = 0;
	while (inside_quotes[j])
		res[(*x)++] = inside_quotes[j++];
}

char	*ft_remove_qoutes(char *str)
{
	char	*res;
	int		i;
	int		x;

	i = 0;
	x = 0;
	if (!str)
		return (NULL);
	res = (char *)zyalloc(sizeof(char) * (ft_strlen(str) + 1), 'a', true);
	if (!res)
		return (ft_printerror(MALLOC_ERORR), NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (ft_isquote(str[i + 1]))
				i++;
		}
		if (str[i] && ft_isquote(str[i]))
			ft_cat_inside_qoutes(res, str, &i, &x);
		else
			ft_remove_qoutes_handler(str, res, &x, &i);
	}
	res[x] = '\0';
	return (res);
}

t_token	*ft_lst_remvove_qoutes(t_token *lst_token)
{
	t_token	*tmp;

	tmp = lst_token;
	while (tmp)
	{
		if (tmp->token == HEREDOC)
			tmp = tmp->next;
		else if (tmp->token == WORD)
			tmp->value = ft_remove_qoutes(tmp->value);
		tmp = tmp->next;
	}
	return (lst_token);
}

// int main(void)
// {
// 	char *test = NULL;
// 	char *res = ft_remove_qoutes(test);
// 	printf("%s\n", res);
// }
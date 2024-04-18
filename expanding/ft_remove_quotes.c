/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 01:40:17 by moichou           #+#    #+#             */
/*   Updated: 2024/04/18 21:37:31 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_get_inside_qoutes(char *str, int *i, int type)
{
	char	*res;
	int		start;
	int		length;

	start = *i;
	length = 0;
	while (str[*i] && ft_isquote(str[*i]) != type)
	{
		(*i)++;
		length++;
	}
	res = ft_strldup(&str[start], length);
	return (res);
}

char	*ft_remove_qoutes(char *str)
{
	char	*res;
	char	*inside_quotes;
	int		i;
	int		start;
	int		length;

	i = 0;
	while (str[i])
	{
		start = i;
		if (str[i] && ft_isquote(str[i]))
			inside_quotes = ft_get_inside_qoutes(str, &i, ft_isquote(str[i]));
		printf("%s\n", inside_quotes);
		i++;
	}
	return (res);
}

int main(void)
{
	char *test = ft_strdup("amine 'ichou' hello world");
	char *res = ft_remove_qoutes(test);
}
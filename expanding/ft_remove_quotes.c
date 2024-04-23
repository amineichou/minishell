/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 01:40:17 by moichou           #+#    #+#             */
/*   Updated: 2024/04/23 12:04:00 by moichou          ###   ########.fr       */
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

char	*ft_remove_qoutes(char *str)
{
	char	*res;
	char	*inside_quotes;
	int		i;
	int		j;
	int		x;

	i = 0;
	x = 0;
	if (!str)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
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
		{
			inside_quotes = ft_get_inside_qoutes(str, &i, ft_isquote(str[i]));
			j = 0;
			while (inside_quotes[j])
				res[x++] = inside_quotes[j++];
		}
		else
		{
				res[x] = str[i];
				x++;
				i++;
		}
	}
	res[x] = '\0';
	return (res);
}

// int main(void)
// {
// 	char *test = NULL;
// 	char *res = ft_remove_qoutes(test);
// 	printf("%s\n", res);
// }
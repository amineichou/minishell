/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:19:06 by moichou           #+#    #+#             */
/*   Updated: 2024/05/14 10:29:34 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_count_delimiters(char const *s, char c)
{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	**fill_the_splited(char **splited, char *str, char c)
{
	int	splited_i;
	int	index;
	int	str_len;

	splited_i = 0;
	index = 0;
	while (str[index])
	{
		str_len = 0;
		while (str[index] == c)
			index++;
		while (str[index] != c && str[index])
		{
			str_len++;
			index++;
		}
		if (str_len == 0)
			break ;
		splited[splited_i] = zyalloc(sizeof(char) * (str_len + 1), 'a', true);
		if (!splited[splited_i])
			return (NULL);
		ft_strlcpy(splited[splited_i], &str[index] - str_len, str_len + 1);
		splited_i += 1;
	}
	return (splited);
}

char	**ft_split(char *s, char c)
{
	char	**splited;
	int		count_del;

	if (!s)
		return (NULL);
	count_del = ft_count_delimiters(s, c);
	splited = zyalloc(sizeof(char *) * (count_del + 1), 'a', true);
	if (!splited)
		return (NULL);
	if (!fill_the_splited(splited, s, c))
		return (NULL);
	splited[count_del] = 0;
	return (splited);
}

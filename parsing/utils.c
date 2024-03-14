/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:35:18 by moichou           #+#    #+#             */
/*   Updated: 2024/03/14 17:35:15 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "includes/macros.h"

// free after using
char	*ft_get_word(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			break;
		i++;
	}
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		ft_printerror(MALLOC_ERORR);
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			break;
		res[i] = str[i];
		i++;
	}
	return (res);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*result;
	int		i;
	int		beginning;
	int		end;

	if (!s1 || !set)
		return (NULL);
	beginning = 0;
	end = ft_strlen(s1) - 1;
	i = 0;
	while (ft_strchr(set, s1[beginning]) && beginning <= end)
		beginning++;
	if (beginning > end)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[end]) && end >= 0)
		end--;
	result = malloc(sizeof(char) * (end - beginning + 2));
	if (!result)
		return (MALLOC_ERORR, NULL);
	ft_strlcpy(result, &s1[beginning], end - beginning + 2);
	return (result);
}

void	ft_trim_spaces(char *str)
{
    int i;
	int	j;

	i = 0;
    while (ft_isspace(str[i]))
        i++;
    j = 0;
    while (str[i] != '\0') {
        str[j] = str[i];
        i++;
        j++;
    }
    str[j] = '\0';
    j = ft_strlen(str) - 1;
    while (j >= 0 && ft_isspace(str[j]))
	{
        str[j] = '\0';
        j--;
    }
}

void	ft_printerror(char *msg)
{
	int	i;

	i = 0;
	write(2, "minishell: ", 12);
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
}
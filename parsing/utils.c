/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:35:18 by moichou           #+#    #+#             */
/*   Updated: 2024/03/15 15:21:17 by moichou          ###   ########.fr       */
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

int	ft_count_legal_char(char *line, char c)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i++] != '"');
			i++;
		}
		if (line[i] == '\'')
		{
			i++;
			while (line[i++] != '\'');
			i++;
		}
		if (line[i] == c)
			size++;
		i++;
	}
	return (size);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:11:11 by zyamli            #+#    #+#             */
/*   Updated: 2024/03/10 15:15:23 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include<string.h>

char *ft_strjoin(char *s1, char *s2)
{
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    char *result = malloc(len1 + len2 + 1);
    if (result == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    strcpy(result, s1);
    strcat(result, s2);

    return result;
}
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	if (dstsize)
	{
		while (i < dstsize - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

static char	**free_leaks(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static int	count(const char *str, char c)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
			words++;
		while (str[i] != '\0' && str[i] != c)
			i++;
	}
	return (words);
}
static char	**count_allocate_char(char **strs, const char *s, char c)
{
	int		len;
	int		ptr_index;

	ptr_index = 0;
	while (*s)
	{
		len = 0;
		while ((*s) == c)
			s++;
		while (*s && *s != c)
		{
			s++;
			len++;
		}
		if (!len)
			break ;
		strs[ptr_index] = malloc((sizeof(char) * len + 1));
		if (strs[ptr_index] == NULL)
			return (free_leaks(strs));
		ft_strlcpy(strs[ptr_index], s - len, len + 1);
		ptr_index++;
	}
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**splitedf;

	size = 0;
	if (s == NULL)
		return (NULL);
	size = count(s, c);
	splitedf = malloc(sizeof(char *) * (size + 1));
	if (!splitedf)
		return (NULL);
	if (count_allocate_char(splitedf, s, c) == NULL)
		return (NULL);
	splitedf[size] = NULL;
	return (splitedf);
}
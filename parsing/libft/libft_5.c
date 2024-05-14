/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:26:56 by moichou           #+#    #+#             */
/*   Updated: 2024/05/14 12:28:07 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	result = ft_substr(s1, start, end - start, true);
	return (result);
}

char	*ft_strjoin(char *s1, char *s2, bool to_free)
{
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2, to_free));
	else if (!s2)
		return (ft_strdup(s1, to_free));
	str = (char *)zyalloc(ft_strlen(s1) + ft_strlen(s2) + 1, 'a', to_free);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (str);
}

char	*ft_strjoin_addspace(char *s1, char *s2, bool to_free)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2, to_free));
	else if (!s2)
		return (ft_strdup(s1, to_free));
	str = (char *)zyalloc(ft_strlen(s1) + ft_strlen(s2) + 2, 'a', to_free);
	if (!str)
		return (NULL);
	j = 0;
	while (i < ft_strlen(s1))
		str[i++] = s1[j++];
	str[i] = ' ';
	i++;
	j = 0;
	while (i <= (ft_strlen(s1) + ft_strlen(s2)))
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_lenth;
	size_t	src_lenth;

	src_lenth = ft_strlen(src);
	if (!dst && dstsize == 0 && src)
		return (src_lenth);
	dst_lenth = ft_strlen(dst);
	i = 0;
	if (dst_lenth >= dstsize)
		return (dstsize + src_lenth);
	while (src[i] && i + dst_lenth < dstsize - 1)
	{
		dst[dst_lenth + i] = src[i];
		i++;
	}
	dst[i + dst_lenth] = '\0';
	return (dst_lenth + src_lenth);
}

void	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:11:11 by zyamli            #+#    #+#             */
/*   Updated: 2024/04/25 11:26:07 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include<string.h>

char* ft_strstr(const char* haystack, const char* needle)
{

    const char* p1;
    const char* p2;
    const char* p1_advance;

	if (*needle == '\0')
        return (char*)haystack;
	p1_advance = haystack;
    while (*p1_advance)
	{
        p1 = p1_advance;
        p2 = needle;
        
        while (*p1 && *p2 && *p1 == *p2)
		{
            p1++;
            p2++;
        }
        if (*p2 == '\0')
            return (char*)p1_advance;
        
        p1_advance++;
    }
    
    return NULL;
}

void	ft_print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit (127);
}
void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (fd < 0)
		return ;
	if (!s)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

// size_t	ft_strlen(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// int ft_strcmp(const char *str1, const char *str2)
// {
// 	while (*str1 && *str2 && *str1 == *str2)
// 	{
// 		str1++;
// 		str2++;
// 	}

// 	return *(unsigned char *)str1 - *(unsigned char *)str2;
// // }

// char	*ft_strdup(const char *s1)
// {
// 	int		i;
// 	char	*rs;

// 	i = 0;
// 	rs = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
// 	if (!rs)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		rs[i] = s1[i];
// 		i++;
// 	}
// 	rs[i] = '\0';
// 	return (rs);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	int				i;
// 	unsigned char	*str;
// 	unsigned char	a;

// 	i = 0;
// 	str = (unsigned char *)s;
// 	a = (unsigned char)c;
// 	while (str[i])
// 	{
// 		if (str[i] == a)
// 			return ((char *)&str[i]);
// 		i++;
// 	}
// 	if (a == '\0')
// 		return ((char *)str + ft_strlen((char *)str));
// 	return (0);
// }



// static void	*ft_memmove(void *dest, const void *src, size_t n)
// {
// 	unsigned char		*d;
// 	const unsigned char	*s;

// 	d = dest;
// 	s = src;
// 	while (n--)
// 		*d++ = *s++;
// 	return (dest);
// }

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n && (str1[i] || str2[i]))
	{
		if (str1[i] > str2[i])
			return (1);
		else if (str1[i] < str2[i])
			return (-1);
		i++;
	}
	return (0);
}

char	**free_leaks(char **strs)
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

// static int	count(const char *str, char c)
// {
// 	int		i;
// 	int		words;

// 	words = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		while (str[i] == c)
// 			i++;
// 		if (str[i])
// 			words++;
// 		while (str[i] != '\0' && str[i] != c)
// 			i++;
// 	}
// 	return (words);
// }
// static char	**count_allocate_char(char **strs, char *s, char c)
// {
// 	int		len;
// 	int		ptr_index;

// 	ptr_index = 0;
// 	while (*s)
// 	{
// 		len = 0;
// 		while ((*s) == c)
// 			s++;
// 		while (*s && *s != c)
// 		{
// 			s++;
// 			len++;
// 		}
// 		if (!len)
// 			break ;
// 		strs[ptr_index] = malloc((sizeof(char) * len + 1));
// 		if (strs[ptr_index] == NULL)
// 			return (free_leaks(strs));
// 		ft_strlcpy(strs[ptr_index], s - len, len + 1);
// 		ptr_index++;
// 	}
// 	return (strs);
// }

// char	**ft_split(char const *s, char c)
// {
// 	int		size;
// 	char	**splitedf;

// 	size = 0;
// 	if (s == NULL)
// 		return (NULL);
// 	size = count(s, c);
// 	splitedf = malloc(sizeof(char *) * (size + 1));
// 	if (!splitedf)
// 		return (NULL);
// 	if (count_allocate_char(splitedf,(char *)s, c) == NULL)
// 		return (NULL);
// 	splitedf[size] = NULL;
// 	return (splitedf);
// }
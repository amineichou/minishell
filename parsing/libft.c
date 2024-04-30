/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:59:34 by moichou           #+#    #+#             */
/*   Updated: 2024/04/27 15:13:40 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\f' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

int	ft_is_alphanumeric(char c)
{
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*ft_strdup(char *s1)
{
	int		str_length;
	int		i;
	char	*s2;

	i = 0;
	if(!s1)
		return (NULL);
	str_length = ft_strlen(s1) + 1;
	s2 = malloc(sizeof(char) * str_length);
	if (!s2)
		return (0);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strchr(char *s, int c)
{
	int				i;
	char			*searched;
	unsigned char	d;

	i = 0;
	searched = (char *)s;
	d = (unsigned char)c;
	while (searched[i])
	{
		if (searched[i] == d)
			return (&searched[i]);
		i++;
	}
	if (d == '\0')
		return (searched + ft_strlen(searched));
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_strcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
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

static int	ft_handler(const char *str, int sign)
{
	int			i;
	long long	handler;
	long long	tmp;

	i = 0;
	handler = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = handler * 10 + (str[i] - 48); 
		if (tmp < handler && sign == 1)
			return (-1);
		if (tmp < handler && sign == -1)
			return (0);
		handler = tmp;
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (ft_handler(&str[i], sign) == -1)
		return (-1);
	if (ft_handler(&str[i], sign) == 0)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
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

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int		i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (s[start] && i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
void	*talloc(size_t __size)
{
	void	*__ptr;

	__ptr = malloc(__size);
	if (__ptr == NULL)
		return (NULL);
	printf("pointer \033[32m%p\033[0m was allocated, size : \033[32m%ld\033[0m\n", __ptr, __size);
	return (__ptr);
}



// itoi

static int	ft_count_dig(long int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char		*converted_number;
	int			digit_count;
	long int	number;

	number = n;
	digit_count = ft_count_dig(number);
	if (number < 0)
	{
		number *= -1;
		digit_count++;
	}
	converted_number = malloc(sizeof(char) * (digit_count + 1));
	if (!converted_number)
		return (0);
	converted_number[digit_count] = '\0';
	while (digit_count--)
	{
		converted_number[digit_count] = (number % 10) + '0';
		number /= 10;
	}
	if (n < 0)
		converted_number[0] = '-';
	return (converted_number);
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

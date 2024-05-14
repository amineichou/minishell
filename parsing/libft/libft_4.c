/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:24:50 by moichou           #+#    #+#             */
/*   Updated: 2024/05/14 12:26:44 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// atoi
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

// itoa
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

char	*ft_itoa(int n, bool to_free)
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
	converted_number = zyalloc(sizeof(char) * (digit_count + 1), 'a', to_free);
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

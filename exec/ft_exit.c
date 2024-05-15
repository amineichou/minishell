/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 03:04:31 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/14 23:24:28 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	overflow_handler(const char *str)
{
	int			i;
	int			sign;
	long long	tmp;

	i = 0;
	sign = 1;
	tmp = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = tmp * 10 + (str[i] - 48);
		if (tmp > 2147483647 && sign == 1)
			return (1);
		if (tmp > 2147483648 && sign == -1)
			return (1);
		i++;
	}
	return (0);
}

int	str_isnum(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	char	*res;

	if (!args[1])
		exit(0);
	res = ft_strtrim(args[1], " ");
	if ((res && !str_isnum(res)) || overflow_handler(res))
	{
		ft_printerror(" exit: ");
		ft_putstr_fd(res, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit (255);
	}
	if (args[2])
	{
		ft_printerror("exit: too many arguments\n");
		return (1);
	}
	else
		exit(ft_atoi(res) % 256);
}

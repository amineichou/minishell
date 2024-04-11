/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 03:04:31 by zyamli            #+#    #+#             */
/*   Updated: 2024/04/05 00:50:17 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int ft_exit(char **args)
{
	if (!args[1])
		exit(0);
	if(args[2])
		ft_printerror("exit: too many arguments");
	if (args[1] && !str_isnum(args[1]))
	{
		ft_print_error("numeric argument required");
		exit (255);
	}
	else
		exit(ft_atoi(args[1]) % 256);
}
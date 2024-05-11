/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 20:18:36 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/11 14:48:59 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	flag_check(char *str)
{
	if (!*str)
		return (0);
	if (*str == '-' && *(str + 1) != '\0')
	{
		str++;
		while (*str && *str == 'n')
			str++;
	}
	if (*str)
		return (0);
	return (1);
}

int	ft_echo(t_toexec *cmd, t_pipe *needs)
{
	int	step;
	int	i;

	i = 0;
	step = 0;
	if (cmd->args)
	{
		while (cmd->args[++i] && flag_check(cmd->args[i]))
			step = 1;
		while (cmd->args[i])
		{
			ft_putstr(cmd->args[i]);
			i++;
			if (cmd->args[i])
				ft_putstr(" ");
		}
		if (!step)
			ft_putstr("\n");
	}
	*(needs->ex_stat) = 0;
	ft_set_status(0, 1);
	return (1);
}

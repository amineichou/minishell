/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:24:33 by moichou           #+#    #+#             */
/*   Updated: 2024/04/01 02:08:06 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_first_last_pipe(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
		return (1);
	i = ft_strlen(str) - 1;
	if (str[i] == '|')
		return (1);
	return (0);
}

static int	ft_sequential_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			while (str[i] && ft_isspace(str[i]))
				i++;
			if (str[i] && str[i] == '|')
				return (1);
		}
		if (ft_isquote(str[i]))
			ft_skip_quotes(str, &i);
		else if (str[i] == '\0')
			break ;
		else
			i++;
	}
	return (0);
}

static int	ft_red_before_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isredirection(str[i]))
		{
			i++;
			if (str[i] && ft_isredirection(str[i]))
				i++;
			while (str[i] && ft_isspace(str[i]))
				i++;
			if (str[i] && str[i] == '|')
				return (1);
		}
		if (str[i] == '\0')
			break ;
		else
			i++;
	}
	return (0);
}

int	ft_sanitize_pipes(char *line)
{
	if (ft_first_last_pipe(line)
		|| ft_sequential_pipes(line)
		|| ft_red_before_pipe(line))
	{
		ft_printerror(SYNTAX_ERROR_PIPE);
		return (-1);
	}
	return (0);
}

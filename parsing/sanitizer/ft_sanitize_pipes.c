/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:24:33 by moichou           #+#    #+#             */
/*   Updated: 2024/03/14 16:51:23 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../includes/macros.h"

static int	pipe_is_last_prop(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i--;
		if (line[i] == '|')
			return (1);
		else
			break;
	}
	return (0);
}

// handle emptiness between pipes
static int	check_between_pipes(char *line)
{
	int	i;

	i = 1;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '|')
		return (1);
	return (0);
}

int	ft_sanitize_pipes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && i == 0
			|| line[i] == '|' && line[i + 1] == '\0'
			|| line[i] == '|' && line[i + 1] == '|'
			|| line[i] == '|' && check_between_pipes(&line[i]))
		{
			ft_printerror(SYNTAX_ERROR_PIPE);
			return (-1);
		}
		i++;
	}
	return (0);
}

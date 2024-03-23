/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:36:51 by moichou           #+#    #+#             */
/*   Updated: 2024/03/22 23:35:38 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../includes/macros.h"

static int	ft_check_closure(char *line, char c, int *index)
{
	(*index)++;
	while (line[*index])
	{
		if (line[*index] == c)
			return (1);
		(*index)++;
	}
	return (0);
}

int	ft_sanitize_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			if (ft_check_closure(line, '"', &i) == 0)
				return (ft_printerror(SYNTAX_ERROR_QUOTE), -1);
		}
		else if (line[i] == '\'')
		{
			if (ft_check_closure(line,'\'', &i) == 0)
				return (ft_printerror(SYNTAX_ERROR_QUOTE), -1);
		}
		i++;
	}
	return (0);
}

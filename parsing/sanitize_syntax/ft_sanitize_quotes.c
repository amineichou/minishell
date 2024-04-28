/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:36:51 by moichou           #+#    #+#             */
/*   Updated: 2024/04/27 16:24:00 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	ft_sanitize_quotes(char *line, int *where)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			if (ft_check_closure(line, '"', &i) == 0)
			{
				if (i < *where || *where == -1)
					*where = i;
				return (ft_printerror("syntax error missing quote `\"'\n"), -1);
			}
		}
		else if (line[i] == '\'')
		{
			if (ft_check_closure(line,'\'', &i) == 0)
			{
				if (i < *where || *where == -1)
					*where = i;
				return (ft_printerror("syntax error missing quote `''\n"), -1);
			}
		}
		i++;
	}
	return (0);
}

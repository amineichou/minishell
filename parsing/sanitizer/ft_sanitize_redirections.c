/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:53:48 by moichou           #+#    #+#             */
/*   Updated: 2024/03/19 00:08:20 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../includes/macros.h"

static int	ft_count_bigest_series_char(char *line, char c)
{
	int	i;
	int count_char;
	int res;

	i = 0;
	res = 0;
	while (line[i])
	{
		count_char = 0;
		while (line[i] == c)
		{
			count_char++;
			i++;
		}
		if (count_char > res)
			res = count_char;
		i++;
	}
	return (res);
}

static int	ft_is_red_is_last(char *line)
{
	int	last_index;

	last_index = ft_strlen(line) - 1;
	if (line[last_index] == '<' || line[last_index] == '>')
		return (1);
	return (0);
}

int	ft_sanitize_redirections(char *line)
{
	if (ft_count_bigest_series_char(line, '>') > 2
		|| ft_count_bigest_series_char(line, '<') > 2
		|| ft_is_red_is_last(line))
	{
		ft_printerror(SYNTAX_ERROR_REDIRECTION);
		return (-1);
	}
	return (0);
}

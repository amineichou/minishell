/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:53:48 by moichou           #+#    #+#             */
/*   Updated: 2024/03/12 15:05:55 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_bigest_series_char(char *line, char c)
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

int	ft_sanitize_redirections(char *line)
{
	if (count_bigest_series_char(line, '>') > 2
		|| count_bigest_series_char(line, '<') > 2)
	{
		ft_printerror("syntax error near unexpected token `>'\n");
		return (-1);
	}
	return (0);
}

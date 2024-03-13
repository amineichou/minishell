/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:36:51 by moichou           #+#    #+#             */
/*   Updated: 2024/03/13 02:41:46 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../includes/macros.h"

static int	ft_count_char(char *line, char c)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == c)
			count++;
		line++;
	}
	return (count);
}

int	ft_sanitize_quotes(char *line)
{
	int	double_quotes_size;
	int	single_quotes_size;

	double_quotes_size = ft_count_char(line, '"');
	single_quotes_size = ft_count_char(line, '\'');
	if (double_quotes_size % 2 != 0
		|| single_quotes_size % 2 != 0)
	{
		ft_printerror(SYNTAX_ERROR_QUOTE);
		return (-1);
	}
	return (0);
}

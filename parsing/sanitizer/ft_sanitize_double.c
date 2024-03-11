/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_double.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:24:25 by moichou           #+#    #+#             */
/*   Updated: 2024/03/11 17:19:17 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_count_double_quotes(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == '"')
			count++;
		line++;
	}
	return (count);
}

int	ft_sanitize_double_quotes(char *line)
{
	int	double_quotes_size;

	double_quotes_size = ft_count_double_quotes(line);
	if (double_quotes_size % 2 != 0)
	{
		ft_printerror("syntax error missing quote\n");
		return (-1);
	}
	return (0);
}

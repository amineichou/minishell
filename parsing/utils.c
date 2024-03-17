/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:35:18 by moichou           #+#    #+#             */
/*   Updated: 2024/03/17 02:11:19 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "includes/macros.h"

int	ft_count_legal_char(char *line, char c)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i++] != '"');
			i++;
		}
		if (line[i] == '\'')
		{
			i++;
			while (line[i++] != '\'');
			i++;
		}
		if (line[i] == c)
			size++;
		i++;
	}
	return (size);
}

void	ft_printerror(char *msg)
{
	int	i;

	i = 0;
	write(2, "minishell: ", 12);
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:35:18 by moichou           #+#    #+#             */
/*   Updated: 2024/03/18 03:28:24 by moichou          ###   ########.fr       */
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

// returns 1 if it is
int	ft_isspecialchars(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

// returns 1 if it is single and 2 if double 0 if not quote
int	ft_isquote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
	return (0);
}

char	*ft_strlrdup(char *s1, int lenght)
{
	int		i;
	char	*s2;

	i = 0;
	if (ft_strlen(s1) < lenght)
		return (NULL);
	s2 = malloc(sizeof(char) * (lenght + 1));
	if (!s2)
		return (NULL);
	while (i < lenght)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[lenght] = '\0';
	return (s2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:45:42 by moichou           #+#    #+#             */
/*   Updated: 2024/05/13 22:45:59 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

// returns 1 if it is > < |
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

// > == 1 | < == -1
int	ft_isredirection(char c)
{
	if (c == '>')
		return (1);
	else if (c == '<')
		return (-1);
	return (0);
}

char	*ft_strldup(char *s1, int lenght)
{
	int		i;
	char	*s2;

	i = 0;
	if (ft_strlen(s1) < lenght)
		return (NULL);
	s2 = zyalloc(sizeof(char) * (lenght + 1), 'a', true);
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

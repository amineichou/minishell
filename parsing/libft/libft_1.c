/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:43:20 by moichou           #+#    #+#             */
/*   Updated: 2024/05/13 22:44:22 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// remove the spaces/tabs form the bigg-end if str 
char	*ft_trim_spaces(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	if (!str)
		return (NULL);
	j = ft_strlen(str) - 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (i == ft_strlen(str))
		return (NULL);
	while (ft_isspace(str[j]))
		j--;
	j = ft_strlen(str) - j - 1;
	res = ft_strldup(str + i, (ft_strlen(str) - i - j));
	if (!res)
		return (ft_printerror(MALLOC_ERORR), NULL);
	return (res);
}

void	ft_skip_quotes(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] && ft_isquote(str[*i]) == 1)
		{
			(*i)++;
			while (str[*i] && ft_isquote(str[*i]) != 1)
				(*i)++;
		}
		else if (str[*i] && ft_isquote(str[*i]) == 2)
		{
			(*i)++;
			while (str[*i] && ft_isquote(str[*i]) != 2)
				(*i)++;
		}
		if (str[*i] == '\0')
			break ;
		break ;
	}
}

void	ft_put_syntaxerror(char *msg, char c)
{
	int	i;

	i = 0;
	write (2, "minishell: ", 11);
	while (msg[i])
	{
		write (2, &msg[i], 1);
		i++;
	}
	write (2, "`", 1);
	write (2, &c, 1);
	write (2, "`\n", 2);
}

// get the value in quotes (quotes r not included)
char	*ft_get_inside_quotes(char *in_quotes, int *i, char q_type)
{
	char	*res;
	int		start;
	int		length;

	(*i)++;
	start = *i;
	length = 0;
	while (in_quotes[*i] && in_quotes[*i] != q_type)
	{
		length++;
		(*i)++;
	}
	(*i)++;
	res = ft_strldup(&in_quotes[start], length);
	if (!res)
		return (NULL);
	return (res);
}

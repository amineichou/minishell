/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:16:32 by moichou           #+#    #+#             */
/*   Updated: 2024/03/17 22:40:50 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// make it allocat in the heap bc this is bullshit
static void	ft_trim_spaces(char *str)
{
    int i;
	int	j;

	i = 0;
    while (ft_isspace(str[i]))
        i++;
    j = 0;
    while (str[i] != '\0') {
        str[j] = str[i];
        i++;
        j++;
    }
    str[j] = '\0';
    j = ft_strlen(str) - 1;
    while (j >= 0 && ft_isspace(str[j]))
	{
        str[j] = '\0';
        j--;
    }
}

static void	ft_replace_illegal_tab(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] != '"')
				i++;
		}
		if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				i++;
		}
		if (ft_isspace(line[i]))
			line[i] = ' ';
		i++;
	}
}

char	*ft_sanitizer(char *line)
{
	ft_trim_spaces(line);
    ft_replace_illegal_tab(line);
	if (ft_sanitize_pipes(line) == -1
		|| ft_sanitize_quotes(line) == -1
		|| ft_sanitize_redirections(line) == -1)
		return (NULL);
	return (line);
}

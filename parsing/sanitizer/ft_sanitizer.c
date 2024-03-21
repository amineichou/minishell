/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:16:32 by moichou           #+#    #+#             */
/*   Updated: 2024/03/21 03:46:09 by moichou          ###   ########.fr       */
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
	j = ft_strlen(str) - 1;
	while (ft_isspace(str[i]))
		i++;
	while (ft_isspace(str[j]))
		j--;
	res = ft_strlrdup(str + i, ft_strlen(str) - (i + j));
	// TODO : protect this
	return (res);
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
			while (line[i] && line[i] != '"')
				i++;
		}
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
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
	if (ft_sanitize_quotes(line) == -1
		|| ft_sanitize_pipes(line) == -1
		|| ft_sanitize_redirections(line) == -1)
		return (NULL);
	return (line);
}

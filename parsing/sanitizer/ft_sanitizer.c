/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:16:32 by moichou           #+#    #+#             */
/*   Updated: 2024/03/23 01:19:57 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../includes/macros.h"

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
	res = ft_strlrdup(str + i, (ft_strlen(str) - i - j));
	if (!res)
		ft_printerror(MALLOC_ERORR);
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
			continue ;
		}
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			continue ;
		}
		if (ft_isspace(line[i]))
			line[i] = ' ';
		i++;
	}
}

char	*ft_sanitizer(char *line)
{
	ft_replace_illegal_tab(line);
	if (ft_sanitize_quotes(line) == -1
		|| ft_sanitize_pipes(line) == -1
		|| ft_sanitize_redirections(line) == -1)
		return (NULL);
	return (line);
}

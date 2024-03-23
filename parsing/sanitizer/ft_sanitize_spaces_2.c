/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_spaces_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:58:02 by moichou           #+#    #+#             */
/*   Updated: 2024/03/17 00:51:00 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../includes/macros.h"


static void	ft_add_spaces_to_pipes(char *line, char *res)
{
	int	i;
	int	j;
	int	in_quotes;

	i = 0;
	j = 0;
	in_quotes = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			in_quotes = !in_quotes;
			res[j++] = line[i++];
		}
		else if (line[i] == '|' && !in_quotes)
		{
			res[j++] = ' ';
			res[j++] = line[i++];
			res[j++] = ' ';
		} 
		else
			res[j++] = line[i++];
	}
	res[j] = '\0';
}

// free after using
char	*ft_addspace_illegal_pipe(char *line)
{
	char	*res;
	int		to_add_spaces;
	int		i;
	int		new_size;

	to_add_spaces = ft_count_legal_char(line, '|') * 3;
	i = 0;
	new_size = ft_strlen(line) + to_add_spaces;
	res = malloc (sizeof(char) * (new_size + 2));
	if (!res)
		return (ft_printerror(MALLOC_ERORR), NULL);
	ft_add_spaces_to_pipes(line, res);
	return (res);
}

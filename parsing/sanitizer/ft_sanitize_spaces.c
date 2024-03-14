/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_spaces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:41:47 by moichou           #+#    #+#             */
/*   Updated: 2024/03/14 18:25:54 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../includes/macros.h"

// encrypt the spaces that we want to save aka space between quotes
static void	encypt_wanted_spaces(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '"')
		{
			while ((*str)[i++] && (*str)[i] != '"')
			{
				if ((*str)[i] == ' ')
					(*str)[i] *= -1;
			}
		}
		if ((*str)[i] == '\'')
		{
			while ((*str)[i++] && (*str)[i] != '\'')
			{
				if ((*str)[i] == ' ')
					(*str)[i] *= -1;
			}
		}
		i++;
	}
}

// decrypt the spaces that we saved aka space between quotes
static void	decypt_wanted_spaces(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '"')
		{
			while ((*str)[i++] && (*str)[i] != '"')
			{
				if ((*str)[i] == -32)
					(*str)[i] = 32;
			}
		}
		if ((*str)[i] == '\'')
		{
			while ((*str)[i++] && (*str)[i] != '\'')
			{
				if ((*str)[i] == -32)
					(*str)[i] = 32;
			}
		}
		i++;
	}
}

static int	count_legal_pipes(char *line)
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
		if (line[i] == '|')
			size++;
		i++;
	}
	return (size);
}

static void	add_spaces_to_pipes(char **line)
{
	int	i;
	int	legal_pipes;

	i = 0;
	legal_pipes = count_legal_pipes(*line);
	printf("%d\n", legal_pipes);
	// while ((*line)[i])
	// {
		
	// }
}

// remove unnecessary spaces
// free the old one if you allocate
char	**ft_remove_split_spaces(char *line)
{
	char **splited_line;
	int	i;

	encypt_wanted_spaces(&line);
	add_spaces_to_pipes(&line);
	splited_line = ft_split(line, ' ');
	if (!splited_line)
		return (ft_printerror(MALLOC_ERORR), NULL);
	i = 0;
	while (splited_line[i])
	{
		decypt_wanted_spaces(&splited_line[i]);
		i++;
	}
	return (splited_line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_spaces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:41:47 by moichou           #+#    #+#             */
/*   Updated: 2024/03/11 18:40:43 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// encrypt the spaces that we want to save aka space between quotes
static void	encypt_wanted_spaces(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] && (*str)[i] == '"')
		{
			i++;
			while ((*str)[i++] && (*str)[i] != '"')
			{
				if ((*str)[i] == ' ')
					(*str)[i] *= -1;
			}
		}
		if ((*str)[i] && (*str)[i] == '\'')
		{
			i++; 
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
		if ((*str)[i] && (*str)[i] == '"')
		{
			i++;
			while ((*str)[i++] && (*str)[i] != '"')
			{
				if ((*str)[i] == ' ')
					(*str)[i] *= -1;
			}
		}
		if ((*str)[i] && (*str)[i] == '\'')
		{
			i++; 
			while ((*str)[i++] && (*str)[i] != '\'')
			{
				if ((*str)[i] == ' ')
					(*str)[i] *= -1;
			}
		}
		i++;
	}
}

// remove unnecessary spaces
// free the old one if you allocate
char	*ft_remove_un_spaces(char *str)
{
	encypt_wanted_spaces(&str);
	printf("%s\n", str);
	decypt_wanted_spaces(&str);
	printf("%s\n", str);
	return (str);
}
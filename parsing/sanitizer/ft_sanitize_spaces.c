/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_spaces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:41:47 by moichou           #+#    #+#             */
/*   Updated: 2024/03/17 23:57:11 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../includes/macros.h"

// // encrypt the spaces that we want to save aka space between quotes
// static void	encypt_wanted_spaces(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '"')
// 		{
// 			while (str[i++] && str[i] != '"')
// 			{
// 				if (str[i] == ' ')
// 					str[i] *= -1;
// 			}
// 		}
// 		if (str[i] == '\'')
// 		{
// 			while (str[i++] && str[i] != '\'')
// 			{
// 				if (str[i] == ' ')
// 					str[i] *= -1;
// 			}
// 		}
// 		i++;
// 	}
// }

// // decrypt the spaces that we saved aka space between quotes
// static void	decypt_wanted_spaces(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '"')
// 		{
// 			while (str[i++] && str[i] != '"')
// 			{
// 				if (str[i] == -32)
// 					str[i] = 32;
// 			}
// 		}
// 		if (str[i] == '\'')
// 		{
// 			while (str[i++] && str[i] != '\'')
// 			{
// 				if (str[i] == -32)
// 					str[i] = 32;
// 			}
// 		}
// 		i++;
// 	}
// }



// remove unnecessary spaces
// free the old one if you allocate
// protect these functions ???????????????????
void	ft_sanitize_spaces(char *line)
{
	//ft_replace_illegal_tab(line);
}

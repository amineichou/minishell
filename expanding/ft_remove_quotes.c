/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 01:40:17 by moichou           #+#    #+#             */
/*   Updated: 2024/04/18 19:18:08 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



char	*ft_remove_qoutes(char *str)
{
	char	*res;
	char	*inside_quotes;
	int		i;
	int		start;
	int		length;

	i = 0;
	while (str[i])
	{
		start = i;
		if (ft_isquote(str[i + 1]))
			inside_quotes = ft_get_inside_qoutes(str, &i);
		
		i++;
	}	
}

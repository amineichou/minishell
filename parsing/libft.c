/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:59:34 by moichou           #+#    #+#             */
/*   Updated: 2024/03/13 16:47:26 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	int		str_length;
	int		i;
	char	*s2;

	i = 0;
	str_length = ft_strlen(s1) + 1;
	s2 = malloc(sizeof(char) * str_length);
	if (!s2)
		return (0);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strchr(char *s, int c)
{
	int				i;
	char			*searched;
	unsigned char	d;

	i = 0;
	searched = (char *)s;
	d = (unsigned char)c;
	while (searched[i])
	{
		if (searched[i] == d)
			return (&searched[i]);
		i++;
	}
	if (d == '\0')
		return (searched + ft_strlen(searched));
	return (NULL);
}
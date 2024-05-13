/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyser_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:01:01 by moichou           #+#    #+#             */
/*   Updated: 2024/05/13 17:01:58 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_reallocate_copy(char **old_res, char *new)
{
	char	**res;
	int		i;

	i = 0;
	if (!old_res)
	{
		res = zyalloc(sizeof(char *) * 2, 'a', true);
		res[0] = ft_strdup(new, true);
		res[1] = NULL;
	}
	else
	{
		while (old_res[i])
			i++;
		res = zyalloc(sizeof(char *) * (i + 2), 'a', true);
		i = 0;
		while (old_res[i])
		{
			res[i] = ft_strdup(old_res[i], true);
			i++;
		}
		res[i] = ft_strdup(new, true);
		res[i + 1] = NULL;
	}
	return (res);
}


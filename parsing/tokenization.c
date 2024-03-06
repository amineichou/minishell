/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:34:15 by moichou           #+#    #+#             */
/*   Updated: 2024/03/06 22:32:48 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_token(char *line, int *index)
{
	while (line[*index])
	{
		if (line[*index] == '|')
			return (PIPE);
		(*index)++;
	}
	return (0);
}

t_toexec	*ft_tokenization(char *line)
{
	int			check;
	t_toexec	*test = NULL;
	int			index;
	index = 0;
	while (line[index])
	{
		check = ft_check_token(line, &index);
		if (check == PIPE)
		{
			if (ft_handle_pipe(line, index) == -1)
				return NULL;
		}
		index++;
	}
	return (test);
}

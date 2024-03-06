/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:29:45 by moichou           #+#    #+#             */
/*   Updated: 2024/03/06 22:28:37 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handle_pipe(char *line, int index)
{
	if (!line[index + 1] || line[index + 1] == '\0' || index == 0
		|| line[index + 1] == '|')
	{
		ft_printerror("syntax error near `|'\n");
		return (-1);
	}
	return (0);
}

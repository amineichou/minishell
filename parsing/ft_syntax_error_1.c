/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:48:59 by moichou           #+#    #+#             */
/*   Updated: 2024/05/14 15:01:16 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_init_syntax_error_vals(int *i, char *line, int *where)
{
	*i = 0;
	*where = 0;
	if (!line || line[*i] == '|')
		return (ft_printerror("syntax error near unexpected token `|'\n"), -1);
	return (1);
}

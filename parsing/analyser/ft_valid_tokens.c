/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 23:53:35 by moichou           #+#    #+#             */
/*   Updated: 2024/03/25 03:20:19 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// static int	ft_check_rd_in()

int	ft_check_valid_tokens(t_token *lst_token)
{
	t_token	*node_token;

	node_token = lst_token;
	while (node_token)
	{
		if ((node_token->token == RD_AP
			|| node_token->token == RD_IN
			|| node_token->token == RD_OUT
			|| node_token->token == RD_RP)
			&& (node_token->next->token != WORD))
			return (ft_printerror(SYNTAX_ERROR_REDIRECTION_2), -1);
		node_token = node_token->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:52:13 by moichou           #+#    #+#             */
/*   Updated: 2024/03/21 03:37:59 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_handle_file_open(t_token *lst_token, t_toexec **node)
{
	int fd;
	if (lst_token->token == RD_AP)
	{
		fd = open(lst_token->next->value, O_RDWR | O_APPEND | O_CREAT, 777);
		// if (fd == -1) TODO : handle error
	}
	else if (lst_token->token == RD_RP)
	{
		fd = open(lst_token->next->value, O_RDWR | O_TRUNC | O_CREAT, 777);
		// if (fd == -1) TODO : handle error
	}
	(*node)->output = 9;
}

void	ft_handle_redirections(t_token *lst_token, t_toexec **node)
{
	if (lst_token->token == RD_AP
		|| lst_token->token == RD_RP)
		ft_handle_file_open(lst_token, node);
}

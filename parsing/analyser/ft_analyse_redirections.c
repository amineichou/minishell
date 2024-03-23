/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:52:13 by moichou           #+#    #+#             */
/*   Updated: 2024/03/23 01:22:25 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../includes/macros.h"

static void	ft_handle_file_open(t_token *lst_token, t_toexec **node)
{
	int fd;
	if (lst_token->token == RD_AP)
	{
		fd = open(lst_token->next->value, O_RDWR | O_APPEND | O_CREAT, 777);
		if (fd == -1)
			ft_printerror(FILE_D_ERROR_FAIL);
	}
	else if (lst_token->token == RD_RP)
	{
		fd = open(lst_token->next->value, O_RDWR | O_TRUNC | O_CREAT, 777);
		if (fd == -1)
			ft_printerror(FILE_D_ERROR_FAIL);
	}
	(*node)->output = fd;
}

void	ft_handle_redirections(t_token *lst_token, t_toexec **node)
{
	if (lst_token->token == RD_AP
		|| lst_token->token == RD_RP)
		ft_handle_file_open(lst_token, node);
}

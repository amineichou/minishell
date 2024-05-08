/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:52:13 by moichou           #+#    #+#             */
/*   Updated: 2024/05/08 16:36:03 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_hanlde_red_ap(t_token *lst_token, t_toexec *node)
{
	node->output = open(lst_token->next->value, O_RDWR | O_APPEND | O_CREAT, 0777);
	if (node->output == -1)
		ft_printerror(FILE_D_ERROR_FAIL);
}

static void	ft_hanlde_red_rp(t_token *lst_token, t_toexec *node)
{
	node->output = open(lst_token->next->value, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (node->output == -1)
		ft_printerror(FILE_D_ERROR_FAIL);
}

static void	ft_hanlde_red_in(t_token *lst_token, t_toexec *node)
{
	node->input = open(lst_token->next->value, O_RDWR, 0777);
	if (node->input == -1)
		ft_printerror("no such file or directory\n");
}

void	ft_handle_redirections(t_token **lst_token, t_toexec *node)
{
	while ((*lst_token) && ((*lst_token)->token == RD_AP || (*lst_token)->token == RD_RP || (*lst_token)->token == RD_IN))
	{
		if ((*lst_token)->token == RD_AP)
			ft_hanlde_red_ap(*lst_token, node);
		else if ((*lst_token)->token == RD_RP)
			ft_hanlde_red_rp(*lst_token, node);
		else if ((*lst_token)->token == RD_IN)
			ft_hanlde_red_in(*lst_token, node);
		(*lst_token) = (*lst_token)->next->next;
		ft_handle_args(&node, lst_token);
	}
}

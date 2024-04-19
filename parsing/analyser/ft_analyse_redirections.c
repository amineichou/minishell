/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:52:13 by moichou           #+#    #+#             */
/*   Updated: 2024/04/19 14:42:44 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_hanlde_ed_ap(t_token *lst_token, t_toexec *node)
{
	node->output = open(lst_token->next->value, O_RDWR | O_APPEND | O_CREAT, 0777);
	if (node->output == -1)
		ft_printerror(FILE_D_ERROR_FAIL);
}

static void	ft_hanlde_ed_rp(t_token *lst_token, t_toexec *node)
{
	node->output = open(lst_token->next->value, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (node->output == -1)
		ft_printerror(FILE_D_ERROR_FAIL);
}

static void	ft_hanlde_ed_in(t_token *lst_token, t_toexec *node)
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
			ft_hanlde_ed_ap(*lst_token, node);
		else if ((*lst_token)->token == RD_RP)
			ft_hanlde_ed_rp(*lst_token, node);
		else if ((*lst_token)->token == RD_IN)
			ft_hanlde_ed_in(*lst_token, node);
		(*lst_token) = (*lst_token)->next->next;
		if ((*lst_token) && ((*lst_token)->token == RD_AP || (*lst_token)->token == RD_RP))
			close(node->output);
		else if ((*lst_token) && (*lst_token)->token == RD_IN)
			close(node->input);
	}
}

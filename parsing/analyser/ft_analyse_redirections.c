/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:52:13 by moichou           #+#    #+#             */
/*   Updated: 2024/05/12 12:33:51 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_hanlde_red_ap(t_token **lst_token, t_toexec *node)
{
	node->output = open((*lst_token)->next->value, O_RDWR | O_APPEND | O_CREAT, 0777);
	if (node->input == -1)
		perror("open");
	(*lst_token) = (*lst_token)->next;
}

static void	ft_hanlde_red_rp(t_token **lst_token, t_toexec *node)
{
	node->output = open((*lst_token)->next->value, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (node->input == -1)
		perror("open");
	(*lst_token) = (*lst_token)->next;
}

static void	ft_hanlde_red_in(t_token **lst_token, t_toexec *node)
{
	node->input = open((*lst_token)->next->value, O_RDWR, 0777);
	if (node->input == -1)
		perror("open");
	(*lst_token) = (*lst_token)->next;
}

void	ft_handle_redirections(t_token **lst_token, t_toexec *node)
{
	while ((*lst_token) && ((*lst_token)->token == RD_AP || (*lst_token)->token == RD_RP || (*lst_token)->token == RD_IN))
	{
		if ((*lst_token)->next == NULL || (*lst_token)->next->token != WORD)
		{
			ft_printerror("ambiguous redirect\n");
			(*lst_token) = (*lst_token)->next;
			return ;
		}
		if ((*lst_token)->token == RD_AP)
			ft_hanlde_red_ap(lst_token, node);
		else if ((*lst_token)->token == RD_RP)
			ft_hanlde_red_rp(lst_token, node);
		else if ((*lst_token)->token == RD_IN)
			ft_hanlde_red_in(lst_token, node);
		if ((*lst_token))
			(*lst_token) = (*lst_token)->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:47:36 by moichou           #+#    #+#             */
/*   Updated: 2024/05/04 18:03:39 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	ft_open_herdoc(t_toexec *node, t_token **lst_token, t_env *env)
// {
// 	while ((*lst_token)->token && (*lst_token)->token == HEREDOC)
// 	{
// 		heredoc_handler(node, env);
// 		if ((*lst_token  ))
// 		(*lst_token) = (*lst_token)->next;
// 	}
// }

void	ft_heredoc_handler_exec(t_toexec *node, t_herdoc *herdoc_node, int ex_sta)
{
	char	*line;
	char	*tmp;
	int		fl;

	node->input = open("tempfile", O_CREAT | O_RDWR, 0777);
	fl = open("tempfile", O_CREAT | O_RDWR, 0777);
	if (node->input == -1 || fl == -1)
		ft_printerror("here_doc");
	if (-1 == unlink("tempfile"))
		(perror("unlink"));
	if (node->input == -1)
		ft_printerror("here_doc");
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, herdoc_node->del))
			break ;
		if (herdoc_node->is_expand)
		{
			tmp = ft_replace_dollar(line, node->env, ex_sta);
			ft_putstr_fd(tmp, fl);
			ft_putstr_fd("\n", fl);
			free(line);
		}
		else
		{
			ft_putstr_fd(line, fl);
			ft_putstr_fd("\n", fl);
			free(line);
		}
		// free(line);
		// line = NULL;
	}
	(free(line), close(fl));
}

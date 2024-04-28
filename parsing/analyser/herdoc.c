/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:47:36 by moichou           #+#    #+#             */
/*   Updated: 2024/04/28 13:13:06 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_open_herdoc(t_toexec *node, t_token **lst_token, t_env *env)
{
	while ((*lst_token)->token && (*lst_token)->token == HEREDOC)
	{
		heredoc_handler(node, env);
		if ((*lst_token  ))
		(*lst_token) = (*lst_token)->next;
	}
}

void	ft_heredoc_handler(t_toexec *node, t_env *env, char *delemiter)
{
	char	*line;
	int		fl;

	node->output = open("tempfile", O_CREAT | O_RDWR, 0777);
	fl = open("tempfile", O_CREAT | O_RDWR, 0777);
	if (node->output == -1 || fl == -1)
		ft_printerror("here_doc");
	if (-1 == unlink("tempfile"))
		(perror("unlink"));
	if (node->output == -1)
		ft_printerror("here_doc");
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, delemiter, ft_strlen(delemiter)))
			break ;
		ft_putstr_fd(line, fl);
		free(line);
	}
	(free(delemiter), free(line), close(fl));
}

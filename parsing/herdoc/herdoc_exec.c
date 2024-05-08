/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:47:36 by moichou           #+#    #+#             */
/*   Updated: 2024/05/08 18:08:13 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_heredoc_handler_exec(t_toexec *node, t_herdoc *herdoc_node, int ex_sta)
{
	char	*line;
	char	*tmp;
	int		fl;

	line = NULL;
	int fd = dup(STDIN_FILENO);
	node->input = open("tempfile", O_CREAT | O_RDWR, 0777);
	fl = open("tempfile", O_CREAT | O_RDWR, 0777);
	if (node->input == -1 || fl == -1)
		ft_printerror("here_doc");
	if (-1 == unlink("tempfile"))
		(perror("unlink"));
	if (node->input == -1)
		ft_printerror("here_doc");
	signal(SIGINT, ft_sigkill_herdoc);
	while (1)
	{
		line = readline("> ");
		if (!ttyname(0))
		{
			open(ttyname(fd), O_RDWR);
            close(fl);
            return (-1);
        }
		if (!line)
			break ;
		if (line[0] && !ft_strcmp(line, herdoc_node->del))
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
	}
	return (free(line), close(fl), 1);
}

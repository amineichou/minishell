/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_syn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:20:27 by moichou           #+#    #+#             */
/*   Updated: 2024/05/08 18:06:21 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_heredoc_handler_syn(t_env *env, char *delemiter)
{
	char	*line;
	int		fl;

	int fd = dup(STDIN_FILENO);
	fl = open("tempfile", O_CREAT | O_RDWR, 0777);
	if (fl == -1)
		ft_printerror("error opning heredoc file\n");
	if (-1 == unlink("tempfile"))
		perror("unlink");
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
		if (!ft_strcmp(line, delemiter))
			break ;
		ft_putstr_fd(line, fl);
		free(line);
		line = NULL;
	}
	return (free(line), close(fl), 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_syn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:20:27 by moichou           #+#    #+#             */
/*   Updated: 2024/05/10 12:00:19 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_heredoc_handler_syn(char *delemiter)
{
	char	*line;
	int		fl;
	char	*name;

	line = NULL;
	name = ft_itoa((int)delemiter, true);
	int fd = dup(STDIN_FILENO);
	fl = open(name, O_CREAT | O_RDWR, 0777);
	if (fl == -1)
		ft_printerror("HERDOC error ! couldn't open tmp file\n");
	if (-1 == unlink(name))
		(perror("unlink"));
	signal(SIGINT, ft_sigkill_herdoc);
	while (1)
	{
		line = readline("> ");
		if (g_inexec == -1)
		{
			free(line);
			dup2(fd, 0);
			close(fd);
			close(fl);
			return (g_inexec = 0, -1);
		}
		if (!line)
			break ;
		if (!ft_strcmp(line, delemiter))
			break ;
		ft_putstr_fd(line, fl);
		free(line);
		line = NULL;
	}
	return (free(line),close(fd), close(fl), 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_syn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:20:27 by moichou           #+#    #+#             */
/*   Updated: 2024/05/14 11:12:05 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_check_for_open(int fl, int fd, char *name)
{
	if (fl == -1 || fd == -1)
		ft_printerror("HERDOC error ! couldn't open tmp file\n");
	if (-1 == unlink(name))
		(perror("unlink"));
}

static void	ft_write_in_file_d(int fl, char *line)
{
	ft_putstr_fd(line, fl);
	free(line);
}

int	ft_heredoc_handler_syn(char *delemiter)
{
	char	*line;
	int		fl;
	char	*name;
	int		fd;

	line = NULL;
	name = ft_itoa((int)delemiter, true);
	fd = dup(STDIN_FILENO);
	fl = open(name, O_CREAT | O_RDWR, 0777);
	ft_check_for_open(fl, fd, name);
	signal(SIGINT, ft_sigkill_herdoc);
	while (1)
	{
		line = readline("> ");
		if (g_inexec == -1)
			return (free(line), dup2(fd, 0), close(fd),
				close(fl), g_inexec = 0, -1);
		if (!line)
			break ;
		if (!ft_strcmp(line, delemiter))
			break ;
		ft_write_in_file_d(fl, line);
	}
	return (free(line), close(fd), close(fl), 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_syn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:20:27 by moichou           #+#    #+#             */
/*   Updated: 2024/05/07 20:59:19 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_heredoc_handler_syn(t_env *env, char *delemiter)
{
	char	*line;
	int		fl;

	fl = open("tempfile", O_CREAT | O_RDWR, 0777);
	if (fl == -1)
		ft_printerror("error opning heredoc file\n");
	if (-1 == unlink("tempfile"))
		perror("unlink");
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, delemiter))
			break ;
		ft_putstr_fd(line, fl);
		free(line);
		line = NULL;
	}
	(free(line), close(fl));
}
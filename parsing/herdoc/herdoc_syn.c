/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_syn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:20:27 by moichou           #+#    #+#             */
/*   Updated: 2024/04/28 16:22:53 by moichou          ###   ########.fr       */
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
		if (!ft_strncmp(line, delemiter, ft_strlen(delemiter)))
			break ;
		ft_putstr_fd(line, fl);
		free(line);
	}
	(free(delemiter), free(line), close(fl));
}
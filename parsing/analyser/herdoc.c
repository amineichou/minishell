/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:47:36 by moichou           #+#    #+#             */
/*   Updated: 2024/04/24 15:07:36 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredoc_handler(t_pipe *needs, t_env *env)
{
	char	*line;
	int		fl;

	needs->infile = open("tempfile", O_CREAT | O_RDWR, 0777);
	fl = open("tempfile", O_CREAT | O_RDWR, 0777);
	if (needs->infile == -1 || fl == -1)
		error_handler("here_doc");
	if (-1 == unlink("tempfile"))
		(perror("unlink"));
	if (needs->infile == -1)
		error_handler("here_doc");
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if(ft_check_quotes(needs->limiter))
			ft_replace_dollar(line, env);
		if (!ft_strncmp(line, needs->limiter, ft_strlen(needs->limiter)))
			break ;
		ft_putstr_fd(line, fl);
		free(line);
	}
	(free(needs->limiter), free(line), close(fl));
}

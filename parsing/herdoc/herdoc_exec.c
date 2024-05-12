/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:47:36 by moichou           #+#    #+#             */
/*   Updated: 2024/05/12 21:57:45 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_heredoc_handler_exec(t_toexec *node, char *del, bool is_expand)
{
	char	*line;
	char	*tmp;
	char	*name;
	int		tmp_file;

	line = NULL;
	name = ft_itoa((int)del, true);
	int fd = dup(STDIN_FILENO);
	node->input = open(name, O_CREAT | O_RDWR, 0777);
	tmp_file = open(name, O_CREAT | O_RDWR, 0777);
	if (node->input == -1 || tmp_file == -1)
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
			close(tmp_file);
			g_inexec = 0;
			return (-1);
		}
		if (!line)
			break ;
		if (!ft_strcmp(line, del))
			break ;
		if (is_expand)
		{
			tmp = ft_replace_dollar(line, node->env);
			ft_putstr_fd(tmp, tmp_file);
			ft_putstr_fd("\n", tmp_file);
			free(line);
		}
		else
		{
			ft_putstr_fd(line, tmp_file);
			ft_putstr_fd("\n", tmp_file);
			free(line);
		}
	}
	return (free(line), close(fd), 1);
}

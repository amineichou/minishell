/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:47:36 by moichou           #+#    #+#             */
/*   Updated: 2024/05/14 11:03:21 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_write_in_file(bool is_expand, char *line,
				int tmp_file, t_env *envl)
{
	char	*tmp;

	if (is_expand)
	{
		tmp = ft_replace_dollar(line, envl);
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

static void	ft_check_for_open(int inp, int tmpf, char *name)
{
	if (inp == -1 || tmpf == -1)
		ft_printerror("HERDOC error ! couldn't open tmp file\n");
	if (-1 == unlink(name))
		(perror("unlink"));
}

int	ft_heredoc_handler_exec(t_toexec *node, char *del, bool is_expand)
{
	char	*line;
	char	*name;
	int		tmp_file;
	int		fd;

	line = NULL;
	name = ft_itoa((int)del, true);
	fd = dup(STDIN_FILENO);
	node->input = open(name, O_CREAT | O_RDWR, 0777);
	tmp_file = open(name, O_CREAT | O_RDWR, 0777);
	ft_check_for_open(node->input, tmp_file, name);
	signal(SIGINT, ft_sigkill_herdoc);
	while (1)
	{
		line = readline("> ");
		if (g_inexec == -1)
			return (free(line), dup2(fd, 0), close(fd),
				close(tmp_file), g_inexec = 0, -1);
		if (!line)
			break ;
		if (!ft_strcmp(line, del))
			break ;
		ft_write_in_file(is_expand, line, tmp_file, node->env);
	}
	return (free(line), close(fd), 1);
}

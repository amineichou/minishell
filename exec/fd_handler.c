/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:13:43 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/11 14:43:36 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	in_out_handler(t_toexec *cmds, t_pipe *needs)
{
	(void)needs;
	if (cmds->input == -1 || cmds->output == -1)
		return ;
	if (cmds->input != STDIN_FILENO)
	{
		if (dup2(cmds->input, STDIN_FILENO) == -1)
			perror("STDIN");
		close(cmds->input);
	}
	if (cmds->output != STDOUT_FILENO)
	{
		dup2(cmds->output, STDOUT_FILENO);
		close(cmds->output);
	}
}

void	in_out_handler_multiple(t_toexec *cmds, t_pipe *needs)
{
	if (cmds->input == -1 || cmds->output == -1)
		exit (1);
	if (cmds->input != STDIN_FILENO)
	{
		if (dup2(cmds->input, STDIN_FILENO) == -1)
			perror("STDIN");
		(close(cmds->input), close(needs->fd[0]));
	}
	if (cmds->output != STDOUT_FILENO)
	{
		if (dup2(cmds->output, STDOUT_FILENO) == -1)
			perror("dup2");
		(close(cmds->output), close(needs->fd[1]), close(needs->fd[0]));
	}
	else
	{
		if (dup2(needs->fd[1], STDOUT_FILENO) == -1)
			perror("dup2");
		(close(needs->fd[1]), close(needs->fd[0]));
	}
}

void	in_out_handler_last(t_toexec *cmds, t_pipe *needs)
{
	if (cmds->input == -1 || cmds->output == -1)
		exit (1);
	if (cmds->input != STDIN_FILENO)
	{
		if (dup2(cmds->input, STDIN_FILENO) == -1)
			perror("STDIN");
		(close(cmds->input), close(needs->fd[0]), close(needs->fd[1]));
	}
	if (cmds->output != STDOUT_FILENO)
	{
		if (dup2(cmds->output, STDOUT_FILENO) == -1)
			perror("dup2");
		(close(cmds->output), close(needs->fd[1]));
	}
}

void	in_out_fixer(t_pipe *needs)
{
	if (dup2(needs->save_fd_in, STDIN_FILENO) == -1)
		perror("dup2");
	if (dup2(needs->save_fd_out, STDOUT_FILENO) == -1)
		perror("dup2");
	close(needs->save_fd_in);
	close(needs->save_fd_out);
}

void	close_all(void)
{
	int	fds;

	fds = 3;
	while (fds < OPEN_MAX)
		close(fds++);
}

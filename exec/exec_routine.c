/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:23:05 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/17 18:45:09 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_routines(t_toexec *cmds, t_pipe *needs)
{
	if (needs->pids[needs->p] == 0)
	{
		in_out_handler_multiple(cmds, needs);
		(close(needs->save_fd_in), close(needs->save_fd_out));
		if (cmds->args)
		{
			if (check_builtin(cmds, needs))
				exit(*(needs->ex_stat));
			ft_execution(cmds, needs);
		}
		else
			exit (0);
	}
	else
	{
		if (-1 == dup2(needs->fd[0], STDIN_FILENO))
			return (perror("dup2"));
		(close(needs->fd[0]), close(needs->fd[1]));
		if (cmds->input != STDIN_FILENO)
			close(cmds->input);
		if (cmds->output != STDOUT_FILENO)
			close(cmds->output);
	}
}

void	cmds_executer(t_toexec *cmds, t_pipe *needs)
{
	if (pipe(needs->fd) == -1)
		return (perror("pipe"));
	needs->pids[needs->p] = fork();
	if (needs->pids[needs->p] == -1)
		return ;
	exec_routines(cmds, needs);
}

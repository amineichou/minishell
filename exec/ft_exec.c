/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:04:57 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/18 16:22:30 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_handler(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	last_child(t_toexec **cmds, t_pipe *needs)
{
	needs->pids[needs->p] = fork();
	if (needs->pids[needs->p] == -1)
		return (perror("fork"));
	if (needs->pids[needs->p] == 0)
	{
		(close(needs->save_fd_in), close(needs->save_fd_out));
		in_out_handler_last(*cmds, needs);
		if ((*cmds)->args)
		{
			if (check_builtin((*cmds), needs))
				exit (*(needs->ex_stat));
			ft_execution((*cmds), needs);
		}
		else
			exit (0);
	}
}

void	first_cmd(t_toexec **cmds, t_pipe *needs)
{
	needs->i = lst_size((*cmds));
	needs->env = env_tolist(&(*cmds)->env);
	env_search_replace((*cmds)->env, ft_strdup(" ", false), "_");
	needs->pids = zyalloc(sizeof(int) * needs->i, 'a', true);
	if (!needs->pids)
		return ;
	while (needs->i > 1)
	{
		cmds_executer((*cmds), needs);
		(*cmds) = (*cmds)->next;
		needs->p++;
		needs->i--;
	}
}

void	single_cmd(t_toexec *cmds, t_pipe *needs)
{
	if (cmds->args)
	{
		needs->pids[needs->p] = fork();
		if (needs->pids[needs->p] == -1)
			perror("fork");
		if (needs->pids[needs->p] == 0)
			ft_execution(cmds, needs);
	}
}

void	executer(t_toexec *cmds, t_pipe *needs)
{
	set_values(needs, cmds);
	if (needs->size == 1)
	{
		needs->pids = zyalloc(sizeof(int), 'a', true);
		if (cmds->args)
		{
			env_search_replace(cmds->env, ft_strdup(cmds->args[0], false), "_");
			in_out_handler(cmds, needs);
			if (check_builtin(cmds, needs))
			{
				in_out_fixer(needs);
				return ;
			}
			single_cmd(cmds, needs);
		}
	}
	else if (needs->size > 1)
	{
		first_cmd(&cmds, needs);
		last_child(&cmds, needs);
	}
	in_out_fixer(needs);
	close_all();
	ft_wait(needs);
}

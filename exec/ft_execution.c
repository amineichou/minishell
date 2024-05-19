/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:09:30 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/16 16:57:18 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_if_found(t_pipe *needs, t_toexec *cmd)
{
	if (ft_strchr(cmd->args[0], '/') != NULL)
	{
		if (access(cmd->args[0], F_OK | X_OK) == 0)
			needs->path = cmd->args[0];
		else if (access(cmd->args[0], F_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(127);
		}
		else if (access(cmd->args[0], X_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(126);
		}
	}
	else
	{
		ft_printerror(cmd->args[0]);
		ft_print_error(": command not found\n");
	}
}

static void	check_if_executable(t_pipe *needs, t_toexec *cmd)
{
	if (access(needs->path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	if (!cmd->args[0][0])
		ft_print_error("minishell: : command not found\n");
}

void	ft_execution(t_toexec *cmd, t_pipe *needs)
{
	needs->path = find_path(cmd->args[0], needs->env);
	if (!needs->path)
		check_if_found(needs, cmd);
	check_if_executable(needs, cmd);
	if (-1 == execve(needs->path, cmd->args, needs->env))
		(close(0), close(needs->infile), error_handler("execve"));
}

int	check_builtin(t_toexec *cmd, t_pipe *needs)
{
	int	res;

	res = 0;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		res = ft_echo(cmd, needs);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		res = ft_pwd(needs, cmd->env);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		res = ft_cd(cmd->args[1], cmd->env, needs);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		res = env_print(&cmd->env);
	if (ft_strcmp(cmd->args[0], "export") == 0)
		res = ft_exporter(cmd, needs);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		res = unseter(&cmd, needs);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		res = ft_exit(cmd->args);
		*(needs->ex_stat) = 1;
		ft_set_status(1, 1);
	}
	return (res);
}

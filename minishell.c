/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:35:15 by moichou           #+#    #+#             */
/*   Updated: 2024/05/14 15:33:47 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_inexec = 0;

static void	ft_init(char **env, t_env **envl, int *exit_status)
{
	if (*env == NULL)
		*envl = set_spare_env();
	else
		*envl = set_env(env);
	if (!isatty(STDIN_FILENO))
	{
		write (2, "tty required!\n", 14);
		exit(1);
	}
	*exit_status = 0;
	rl_catch_signals = 0;
	signal(SIGINT, ft_sigkill_handler);
	signal(SIGQUIT, ft_sigquit_handler);
}

int	main(int ac, char **av, char **env)
{
	t_toexec	*lst;
	char		*line;
	t_env		*envl;
	int			exit_status;
	t_pipe		needs;

	((void)ac, (void)av);
	ft_init(env, &envl, &exit_status);
	update_env(envl);
	while (1)
	{
		line = readline("\033[0;32mminishell$ \033[0;0m");
		if (!line)
		{
			write(1, "exit\n", 6);
			exit (0);
		}
		if (line && line[0])
		{
			add_history(line);
			lst = ft_parser(line, envl);
			if (lst)
			{
				// test_lst(lst);
				g_inexec = 1;
				fill_envinlist(&lst, envl);
				executer(lst, &needs);
				envl = lst->env;
				exit_status = *(needs.ex_stat);
				g_inexec = 0;
				continue ;
			}
		}
		else
			free(line);
	}
}

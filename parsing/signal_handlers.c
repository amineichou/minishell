/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:33:14 by moichou           #+#    #+#             */
/*   Updated: 2024/05/14 10:30:22 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_update_status(int status, struct termios *term)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			ft_putstr_fd("\n", 2);
		else if (WTERMSIG(status) == 3)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, term);
			ft_putstr_fd("Quit: 3\n", 2);
		}
		ft_set_status(WTERMSIG(status) + 128, 1);
		return (WTERMSIG(status) + 128);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

void	ft_sigkill_handler(int signum)
{
	if (signum == 2 && !g_inexec)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		ft_set_status(1, 1);
	}
}

void	ft_sigkill_herdoc(int signum)
{
	(void)signum;
	g_inexec = -1;
	close(0);
}

void	ft_sigquit_handler(int signum)
{
	(void)signum;
}

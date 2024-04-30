/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:33:14 by moichou           #+#    #+#             */
/*   Updated: 2024/04/30 18:44:38 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_update_status(int status, struct termios *term)
{
    if (WIFSIGNALED(status))
    {
        if (WTERMSIG(status) == 2)
            ft_putstr_fd("\n", 2);
        else if (WTERMSIG(status) == 3)		{
			tcsetattr(STDIN_FILENO, TCSANOW, term);
            ft_putstr_fd("Quit: 3\n", 2);
		}
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
	}
}

void	ft_sigquit_handler(int signum)
{
	
	
	// s.c_lflag = ~ECHOCTL;
	// executs signal
	// if (signum == 3 && !g_inexec)
	// {
		
	// }
	// tcsetattr(STDIN_FILENO, TCSANOW, &s);
}

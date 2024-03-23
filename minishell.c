/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:00 by moichou           #+#    #+#             */
/*   Updated: 2024/03/23 02:43:32 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <termios.h>
#include <unistd.h>

void disableEcho() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void enableEcho() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void lex(void)
{
	system("leaks minishell");
}

int main(int ac, char **av, char **env)
{
	t_toexec	*lst;
	char		*line;
	char		*sanitize_result;

	// atexit(lex);
	// signal(SIGINT, ft_sigkill_handler);
	disableEcho();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		line = ft_trim_spaces(line); //TODO : protect
		if (line && line[0])
		{
			add_history(line);
			sanitize_result = ft_sanitizer(line);
			if (sanitize_result)
			{
				lst = ft_analyser(sanitize_result);
				test_lst(lst);
			}
			free(line);
		}
	}
	(void)av;
	enableEcho();
}

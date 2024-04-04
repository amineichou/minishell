/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:00 by moichou           #+#    #+#             */
/*   Updated: 2024/03/31 02:27:40 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #include <termios.h>
// #include <unistd.h>

// void disableEcho() {
//     struct termios term;
//     tcgetattr(STDIN_FILENO, &term);
//     term.c_lflag &= ~(ECHO);
//     tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

// void enableEcho() {
//     struct termios term;
//     tcgetattr(STDIN_FILENO, &term);
//     term.c_lflag |= ECHO;
//     tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

void lex(void)
{
	system("leaks minishell");
}

int main(int ac, char **av, char **env)
{
	t_toexec	*lst;
	char		*line;

	// atexit(lex);
	// disableEcho();
	(void)av;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		line = ft_trim_spaces(line); //TODO : protect
		if (line && line[0])
		{
			add_history(line);
			lst = ft_parser(line);
			// if (lst)
				// sent t execution
			// else
				// free it and continue;
		}
	}
}

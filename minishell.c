/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:00 by moichou           #+#    #+#             */
/*   Updated: 2024/03/20 03:14:04 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void lex(void)
{
	system("leaks minishell");
}

int main(int ac, char **av, char **env)
{
	t_toexec	*lst;
	char		*line;
	char		*sanitize_result;

	atexit(lex);
	// signal(SIGINT, ft_sigkill_handler);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		else if (line && line[0])
		{
			add_history(line);
			sanitize_result = ft_sanitizer(line);
			if (sanitize_result)
			{
				lst = ft_analyser(sanitize_result);
				test_lst(lst);
			}
			
			
			free(line);
			exit(1);
		}
	}
	(void)av;
}

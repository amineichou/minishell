/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:00 by moichou           #+#    #+#             */
/*   Updated: 2024/04/08 22:37:36 by zyamli           ###   ########.fr       */
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
	system("lsof -c minishell");
}
void fill_envinlist(t_toexec **head, t_env *env_list)
{
    t_toexec *current = *head;
    while (current != NULL) 
	{
        current->env = env_list;
        current = current->next;
    }
}
int main(int ac, char **av, char **env)
{
	t_toexec	*lst;
	char		*line;
	char		*sanitize_result;
	t_env	*envl = NULL;
	t_env	*tmp = NULL;
	char	**argument = NULL;

	(void)ac;
	(void)av;
	int i;
	i = 0;
	while (env[i] != NULL)
	{
		t_env *new_env = malloc(sizeof(t_env));
		if (!new_env)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
        }
		argument = ft_split(env[i], '=');
        new_env->var = ft_strdup(argument[1]);
		new_env->name = ft_strdup(argument[0]);
        new_env->next = NULL;
        if (envl == NULL)
            envl = new_env;
		else
		{
			tmp = envl;
            while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_env;
		}
		i++;
	}
	
	t_pipe needs;
	needs.env_dup = NULL;
	// atexit(lex);
	// signal(SIGINT, ft_sigkill_handler);
	// disableEcho();
	while (1)
	{
		// line = "\0"
		// needs.save_fd_out = dup(STDOUT_FILENO);
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			exit (0);
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

				fill_envinlist(&lst, envl);
				executer(lst, &needs);
				envl = lst->env;
	
				// continue ;
			}
			free(line);
		}
	}
	(void)av;
	// enableEcho();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:00 by moichou           #+#    #+#             */
/*   Updated: 2024/04/05 00:31:06 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void lex(void)
{
	system("leaks minishell");
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
	while (env[i])
	{
		t_env *new_env = malloc(sizeof(t_env));
		if (!new_env)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
        }
		argument = ft_split(env[i], '=');
        new_env->var = argument[1];
		new_env->name = argument[0];
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
	

	while (1)
	{
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

				continue ;
			}
			free(line);
		}
	}
	(void)av;
}

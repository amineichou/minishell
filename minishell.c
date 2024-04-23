/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:00 by moichou           #+#    #+#             */
/*   Updated: 2024/04/23 18:36:14 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_env	*envl = NULL;
	t_env	*tmp = NULL;
	char	**argument = NULL;

	(void)ac;
	(void)av;
	int i;
	i = 0;
	rl_catch_signals = 0;
	while (env[i] != NULL)
	{
		t_env *new_env = malloc(sizeof(t_env));
		if (!new_env)
			return (ft_printerror(MALLOC_ERORR), 0);
		argument = ft_split(env[i], '=');
        new_env->var = ft_strdup(argument[1]);
		new_env->name = ft_strdup(argument[0]);
		free_leaks(argument);
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
	signal(SIGINT, ft_sigkill_handler);
	while (1)
	{
		line = readline("\033[0;32mminishell$ \033[0;0m");
		if (!line)
		{
			write(1, "exit\n", 6);
			exit (0);
		}
		line = ft_trim_spaces(line); //TODO : protect
		if (line && line[0])
		{
			add_history(line);
			lst = ft_parser(line, envl);
			if (lst)
			{
				// test_lst(lst);
				// test_lst(lst);
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

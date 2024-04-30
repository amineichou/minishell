/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:00 by moichou           #+#    #+#             */
/*   Updated: 2024/04/30 18:34:30 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_inexec = 0;

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

void update_env(t_env *envl)
{
	char *to_replace;

	to_replace = ft_env_list_serch_res(envl, "SHLVL");
	env_search_replace(envl, ft_itoa(ft_atoi(to_replace) + 1), "SHLVL");
	env_search_replace(envl, ft_strdup("/bin/minishell"), "SHELL");
}

int main(int ac, char **av, char **env)
{
	t_toexec	*lst;
	char		*line;
	t_env	*envl = NULL;
	t_env	*tmp = NULL;
	char	**argument = NULL;
	int		exit_status;

	(void)ac;
	(void)av;
	int i;
	i = 0;
	rl_catch_signals = 0;
	exit_status = 0;
	signal(SIGINT, ft_sigkill_handler);
	signal(SIGQUIT, ft_sigquit_handler);
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
	update_env(envl);
	// atexit(lex);
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
			lst = ft_parser(line, envl, exit_status);
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
			free(line);
		}
	}
	(void)av;
}

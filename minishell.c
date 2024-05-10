/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:53:33 by moichou           #+#    #+#             */
/*   Updated: 2024/05/10 16:32:05 by zyamli           ###   ########.fr       */
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
	char *tmp;
	to_replace = ft_env_list_serch_res(envl, "SHLVL");
	tmp = to_replace;
	env_search_replace(envl, ft_itoa(ft_atoi(to_replace) + 1, false), "SHLVL");
	env_search_replace(envl, ft_strdup("/bin/minishell", false), "SHELL");
	env_search_replace(envl, NULL, "OLDPWD");
}

static void	ft_init(void)
{
	if (!isatty(STDIN_FILENO))
	{
		// close(0);
		write (2, "tty required!\n", 14);
		exit(1);
	}

	signal(SIGINT, ft_sigkill_handler);
	signal(SIGQUIT, ft_sigquit_handler);
}

static void	ft_add_last_env(t_env *new_env, t_env *envl)
{
	t_env	*tmp;

	tmp = NULL;
	tmp = envl;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_env;
}

t_env *set_env(char **env)
{
	t_env	*envl;
	char	**argument;
	int i;

	i = 0;
	envl = NULL;
	argument = NULL;
	while (env[i] != NULL)
	{
		t_env *new_env = zyalloc(sizeof(t_env), 'a', false);
		if (!new_env)
			return (ft_printerror(MALLOC_ERORR), NULL);
		argument = split_env(env[i], '=');
		new_env->var = ft_strdup(argument[1], false);
		new_env->name = ft_strdup(argument[0], false);
		new_env->next = NULL;
		if (envl == NULL)
			envl = new_env;
		else
			ft_add_last_env(new_env, envl);
		i++;
	}
	return(envl);
}
t_env *set_spare_env(void)
{
	t_env	*head;
	char	cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd");
	head = zyalloc(sizeof(t_env), 'a', false);
	head->name = ft_strdup("SHLVL", false);
	head->var = ft_strdup("0", false);
	head->next = zyalloc(sizeof(t_env), 'a', false);
	head->next->name = ft_strdup("PATH", false);
	head->next->var = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", false);
	head->next->next = zyalloc(sizeof(t_env), 'a', false);
	head->next->next->name = ft_strdup("PWD", false);
	head->next->next->var = ft_strdup(cwd, false);
	head->next->next->next = zyalloc(sizeof(t_env), 'a', false);
	head->next->next->next->name = ft_strdup("_", false);
	head->next->next->next->var = ft_strdup("./minishell", false);
	return(head);
	
}
int	ft_set_status(int	new_status, int type)
{
	static int	old_status;

	if (type)
		old_status = new_status;
	return (old_status);
}

void leak(){system("lsof -p minishell");}

int	main(int ac, char **av, char **env)
{
	atexit(leak);
	t_toexec	*lst;
	char		*line;
	t_env		*envl;
	int			exit_status;
	t_pipe		needs;

	(void)ac;
	(void)av;
	ft_init();
	// rl_catch_signals = 0;
	exit_status = 0;
	if(*env == NULL)
		envl = set_spare_env();
	else
		envl = set_env(env);
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
				test_lst(lst);
				g_inexec = 1;
				fill_envinlist(&lst, envl);
				executer(lst, &needs);
				envl = lst->env;
				exit_status = *(needs.ex_stat);
				g_inexec = 0;
				// zyalloc(0, 'f', true);
				continue ;
			}
		}
		else
			free(line);
	}
}


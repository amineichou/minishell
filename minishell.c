/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:00 by moichou           #+#    #+#             */
/*   Updated: 2024/03/18 00:10:46 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_list(t_toexec *lst)
{
	t_toexec *test = lst;
	if (!test)
	{
		printf("list is empty\n");
		return ;
	}
	printf("  \033[0;31mCMD\033[0m          \033[0;32mARGS\033[0m            \033[0;33mOUTPUT\033[0m      \033[0;34mINPUT\033[0m \n");
	while (test)
	{
		printf("--------------------------------------------------------------------------------------------\n");
		printf("\033[0;31m[%s ,]\033[0m\033[0;32m[", test->cmd);
		for (int i = 0; test->args[i]; i++)
			printf("%s ,", test->args[i]);
		printf("]\033[0m[");
		printf("\033[0;33m%d]\033[0m[", test->output);
		printf("\033[0;34m%d]\033[0m", test->input);
		printf("\n--------------------------------------------------------------------------------------------\n");
		test = test->next;
	}
}


int main(int ac, char **av, char **env)
{
	t_token	*lst;
	char		*line;
	char		*sanitize_result;

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
				lst = ft_analyser(sanitize_result);

			// while (lst)
			// {
			// 	printf("value : %s\n", lst->value);
			// 	printf("type %d\n", lst->token);
			// 	lst = lst->next;
			// }

			// print_list(lst);
			
			free(line);
		}
	}
	(void)av;
}

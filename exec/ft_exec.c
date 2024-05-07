/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:04:57 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/07 15:30:41 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "head.h"
#include "../minishell.h"
#include <fcntl.h> 
void print_open_file_descriptors()
{
   int fd;
    char path[256];
    
    for(fd = 0; fd < 2500; fd++) {
        if (fcntl(fd, F_GETFD) != -1) {
            if (fcntl(fd, F_GETPATH, path) != -1) {
                printf("File descriptor %d is referencing: %s\n", fd, path);
            } else {
                printf("File descriptor %d is not associated with an open file.\n", fd);
            }
        }
    }
}
void ff(void)
{
	system("lsof -c minishell");
}
void	error_handler(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

// void	free_leaks_arr(char **strs)
// {
// 	size_t	i;

// 	i = 0;
// 	while (strs[i])
// 	{
// 		free(strs[i]);
// 		i++;
// 	}
// 	free(strs);
// }

void	last_child(t_toexec **cmds, t_pipe *needs)
{
	needs->pids[needs->p] = fork();
	if (needs->pids[needs->p] == -1)
		return(perror("fork"));
	if (needs->pids[needs->p] == 0)
	{
		(close(needs->save_fd_in), close(needs->save_fd_out));
		in_out_handler_last(*cmds, needs);
		if((*cmds)->args)
		{
			if(check_builtin((*cmds), needs))
				exit(*(needs->ex_stat)) ;		
			ft_execution((*cmds), needs);
		}
		else
			exit (0);
	}
}

void	first_cmd(t_toexec **cmds, t_pipe *needs)
{
	needs->i = lst_size((*cmds));
	needs->env = env_tolist(&(*cmds)->env);
	env_search_replace((*cmds)->env, ft_strdup(" ", false), "_");
	needs->pids = zyalloc(sizeof(int) * needs->i, 'a', true);
	if(!needs->pids)
		return ; 
	while (needs->i > 1)
	{
		cmds_executer((*cmds), needs);
		(*cmds) = (*cmds)->next;	
		needs->p++;
		needs->i--;
	}
}



void single_cmd(t_toexec *cmds, t_pipe *needs)
{
	needs->pids = zyalloc(sizeof(int), 'a', true);
	if(cmds->args)
	{
		needs->pids[needs->p] = fork();
		if(needs->pids[needs->p] == -1)
			perror("fork");
		
		if(needs->pids[needs->p] == 0)
			ft_execution(cmds, needs);
	}
}

void executer(t_toexec *cmds, t_pipe *needs)
{
	set_values(needs, cmds);
	if(needs->size == 1)
	{
		if(cmds->args)
		{
			env_search_replace(cmds->env, ft_strdup(cmds->args[0], false), "_");
			in_out_handler(cmds, needs);
			if (check_builtin(cmds, needs))
			{
				in_out_fixer(needs);
				return ;
			}
			single_cmd(cmds, needs);
			ft_wait(needs);
		}
	}
	else if (needs->size > 1)
	{
		first_cmd(&cmds, needs);
		last_child(&cmds, needs);
	}
	in_out_fixer(needs);
	close_all();
	ft_wait(needs);
}

	//_________________________________________________________________________________________________________________________________
	// char **arg = malloc(sizeof(char *) * 4);
	// arg[0] = ft_strdup("cat");
	// arg[1] = ft_strdup("ft_env.c");
	// arg[2] = NULL;
	// char **arg2 = malloc(sizeof(char *) * 4);
	// arg2[0] = ft_strdup("grep");
	// arg2[1] = ft_strdup("N");
	// arg2[2] = NULL;
	// t_toexec *node = malloc(sizeof(t_toexec));
	// node->args = arg;
	// node->input = 0;
	// node->output = 1;
	// char **arg3 = malloc(sizeof(char *) * 4);
	// arg3[0] = ft_strdup("grep");
	// arg3[1] = ft_strdup("z");
	// arg3[2] = NULL;
	// char **arg4 = malloc(sizeof(char *) * 4);
	// arg4[0] = ft_strdup("wc");
	// arg4[1] = ft_strdup("-c");
	// arg4[2] = NULL;
	// t_toexec *node2 = malloc(sizeof(t_toexec));
	// node->next = node2;
	// node->next->args = arg2;
	// node->next->input = 0;
	// node->next->output = 1;
	// t_toexec *node3 = malloc(sizeof(t_toexec));
	// node2->next = node3;
	// node2->next->args = arg3;
	// node2->next->input = 0;
	// node2->next->output = 1;
	// t_toexec *node4 = malloc(sizeof(t_toexec));
	// node3->next = node4;
	// node3->next->args = arg4;
	// node3->next->input = 0;
	// node3->next->output = 1;
	// node3->next->next = NULL;
	// node->env = envi;



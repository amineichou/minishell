/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:04:57 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/06 13:48:39 by zyamli           ###   ########.fr       */
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

char	*find_commands(char *av, char **pathes)
{
	char	*result;
	char	*path;
	int		i;
	if (ft_strchr(av , '/') != 0)
	{
		result = ft_strdup(av, true);
		return (result);
	}
	path = ft_strjoin("/", av, true);
	i = 0;
	while (pathes[i])
	{
		result = ft_strjoin(pathes[i], path, true);
		if (access(result, F_OK | X_OK) == 0)
		{
			return (result);
		}
		i++;
		result = NULL;
	}
	return (NULL);
}

char	**extract_paths(char **env)
{
	int	i;
	i = 0;
	
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 4) == 0)
			return (ft_split(env[i] + 5, ':', true));
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char *env[])
{
	char	**to_look;
	char	*path;

	to_look = extract_paths(env);
	if (!to_look || !*to_look)
		return (NULL);
	path = find_commands(cmd, to_look);
	if (!path)
		return (NULL);
	return (path);
}

int	lst_size(t_toexec *head)
{
	int	i;
	t_toexec	*lst;

	i = 0;
	lst = head;

	if (!head)
		return (-1);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
int	env_size(t_env *head)
{
	int	i;
	t_env	*lst;

	i = 0;
	lst = head;

	if (!head)
		return (-1);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
char **env_tolist(t_env **env_list)
{
    int		size;
	int 	i;
	char	*tmp;
    t_env	*current;
	char	**result;

	size = env_size(*env_list);
	current = (*env_list);
    result = (char **)zyalloc(sizeof(char *) * (size + 1), 'a', true);
	if (!result)
		return (perror("malloc"), NULL);
    i = 0;
    while (current != NULL)
	{
		tmp = ft_strjoin(current->name, "=", true);
		result[i] = ft_strjoin(tmp, current->var, true);
        current = current->next;
        i++;
    }
    result[i] = NULL;
    return (result);
}
void in_out_handler(t_toexec *cmds, t_pipe *needs)
{
	(void)needs;
	if(cmds->input == - 1 || cmds->output == -1)
		return ;
	if(cmds->input != STDIN_FILENO)
	{
		if (dup2(cmds->input, STDIN_FILENO) == -1)
			perror("STDIN");
		close(cmds->input);
	}
	if(cmds->output != STDOUT_FILENO)
	{
		dup2(cmds->output, STDOUT_FILENO);
		close(cmds->output);
	}
}
void in_out_handler_multiple(t_toexec *cmds, t_pipe *needs)
{
	if (cmds->input == -1 || cmds->output == -1)
		exit (1);
	if (cmds->input != STDIN_FILENO)
	{
		if (dup2(cmds->input, STDIN_FILENO) == -1)
			perror("STDIN");
		(close(cmds->input), close(needs->fd[0]));
	}

	if (cmds->output != STDOUT_FILENO)
	{
		if (dup2(cmds->output, STDOUT_FILENO) == -1)
			perror("dup2");
		(close(cmds->output), close(needs->fd[1]), close(needs->fd[0]));
	}
	else 
	{

		if (dup2(needs->fd[1], STDOUT_FILENO) == -1)
			perror("dup2");
		(close(needs->fd[1]), close(needs->fd[0]));
	}
}
void in_out_handler_last(t_toexec *cmds, t_pipe *needs)
{
	if (cmds->input == -1 || cmds->output == -1)
		exit (1);
	if (cmds->input != STDIN_FILENO)
	{
		
		if (dup2(cmds->input, STDIN_FILENO) == -1)
			perror("STDIN");
		(close(cmds->input), close(needs->fd[0]), close(needs->fd[1]));
	}
	if (cmds->output != STDOUT_FILENO)
	{
		if (dup2(cmds->output, STDOUT_FILENO) == -1)
			perror("dup2");
		(close(cmds->output), close(needs->fd[1]));
	}
}
int check_builtin(t_toexec *cmd, t_pipe *needs)
{
	int res = 0;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		res = ft_echo(cmd, needs);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		res = ft_pwd(needs);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		res = ft_cd(cmd->args[1], cmd->env, needs);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		res = env_print(cmd, needs);
	if (ft_strcmp(cmd->args[0], "export") == 0)
		res = ft_exporter(cmd, needs);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		res = unseter(cmd, needs);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		res = ft_exit(cmd->args);
		*(needs->ex_stat) = 1;
		ft_set_status(*(needs->ex_stat), 1);
	}
	return (res);
}

void	ft_execution(t_toexec *cmd, t_pipe *needs)
{
	
	needs->path = find_path(cmd->args[0], needs->env);
	if (!needs->path)
	{
		if(ft_strchr(cmd->args[0], '/') != NULL)
		{
			if (access(cmd->args[0], F_OK | X_OK) == 0)
				needs->path = cmd->args[0];
			else if(access(cmd->args[0], F_OK) != 0)
			{
				ft_putstr_fd( "minishell: ",2);
				ft_putstr_fd(cmd->args[0], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				exit(127);
			}
			else if (access(cmd->args[0], X_OK) != 0)
			{
				ft_putstr_fd( "minishell: ",2);
				ft_putstr_fd(cmd->args[0], 2);
				ft_putstr_fd(": Permission denied\n", 2);
				exit(126);
			}
		}
		else
		{
			ft_printerror(cmd->args[0]);
			ft_print_error(": command not found\n");
		}
	}	
	if(access(needs->path, X_OK) != 0)
	{
		ft_putstr_fd( "minishell: ",2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	if (!cmd->args[0][0])
		ft_print_error("minishell: : command not found\n");
	if (-1 == execve(needs->path, cmd->args, needs->env))
		(close(0), close(needs->infile), error_handler("execve"));
}

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
				exit(0) ;		
			ft_execution((*cmds), needs);
		}
		else
			exit (0);
	}


}

void exec_routines(t_toexec *cmds, t_pipe *needs)
{
	if (needs->pids[needs->p] == 0)
	{
		in_out_handler_multiple(cmds, needs);
		(close(needs->save_fd_in), close(needs->save_fd_out));
		if(cmds->args)
		{
			if(check_builtin(cmds, needs))
				exit(*(needs->ex_stat));
			ft_execution(cmds, needs);
		}
		else
			exit (0);
	}
	else
	{
		if (-1 == dup2(needs->fd[0], STDIN_FILENO))
			return(perror("dup2"));
		(close(needs->fd[0]), close(needs->fd[1]));
		if(cmds->input != STDIN_FILENO)
			close(cmds->input);
		if(cmds->output != STDOUT_FILENO)
			close(cmds->output);
	}
}

void cmds_executer(t_toexec *cmds, t_pipe *needs)
{
	if (pipe(needs->fd) == -1)
		return(perror("pipe"));
	needs->pids[needs->p] = fork();
	if (needs->pids[needs->p] == -1)
		return (perror("fork"));
	exec_routines(cmds, needs);
	
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

void executer(t_toexec *cmds, t_pipe *needs)
{
	needs->p = 0;
	needs->env = env_tolist(&cmds->env);
	needs->save_fd_in = dup(STDIN_FILENO);
	needs->save_fd_out = dup(STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &needs->term);
	needs->size = lst_size(cmds);
	needs->step = 0;
		if(needs->size == 1)
		{
			
			needs->pids = zyalloc(sizeof(int), 'a', true);
			if(cmds->args)
			{
				env_search_replace(cmds->env, ft_strdup(cmds->args[0], false), "_");
				in_out_handler(cmds, needs);
				if (check_builtin(cmds, needs))
				{
					(dup2(needs->save_fd_in, STDIN_FILENO) ,close(needs->save_fd_in));
					(dup2(needs->save_fd_out, STDOUT_FILENO) ,close(needs->save_fd_out));
					return ;
				}
				needs->pids[needs->p] = fork();
				if(needs->pids[needs->p] == -1)
					perror("fork");
				
				if(needs->pids[needs->p] == 0)
					ft_execution(cmds, needs);
					
				
			}
		}
		else if (needs->size > 1)
		{
			first_cmd(&cmds, needs);
			last_child(&cmds, needs);
		}
			(dup2(needs->save_fd_in, STDIN_FILENO) ,close(needs->save_fd_in));
			(dup2(needs->save_fd_out, STDOUT_FILENO) ,close(needs->save_fd_out));
		int fds = 3;
		while (fds < 2400)
		{
			close(fds++);
		}
	needs->j = 0;
	int x;
	while(needs->j <= needs->p)
	{
		waitpid(needs->pids[needs->j], &x, 0);
		needs->j++;
	}
	ft_set_status(WEXITSTATUS(x), 1);
	*(needs->ex_stat)= ft_update_status(x, &needs->term);
	
	

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



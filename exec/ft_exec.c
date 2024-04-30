/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:04:57 by zyamli            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/30 18:44:12 by moichou          ###   ########.fr       */
=======
/*   Updated: 2024/04/30 16:12:36 by zyamli           ###   ########.fr       */
>>>>>>> 52851129b44902c75ba1d15e6cc16ed2ef33490f
/*                                                                            */
/* ************************************************************************** */

// #include "head.h"
#include "../minishell.h"
#include <fcntl.h> 
void print_open_file_descriptors() {
    int fd;
    
    // Iterate through possible file descriptors
    for (fd = 0; fd < 256; fd++) { // Adjust the range as per your requirements
        // int flags = fcntl(fd, F_GETFD);
        // if (flags != -1) {
        //     dprintf(2,"File descriptor %d is open\n", fd);
        // }
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

void	free_leaks_arr(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	*find_commands(char *av, char **pathes)
{
	char	*result;
	// char	**command;
	char	*path;
	int		i;
	// command = ft_split(av, ' ');
	// pause();
	if (ft_strchr(av , '/') != 0)
	{
		result = ft_strdup(av);
		return (result);
	}
	path = ft_strjoin("/", av);
	// free_leaks_arr(command);
	i = 0;
	while (pathes[i])
	{
		result = ft_strjoin(pathes[i], path);
		// dprintf(2,"%s\n", result);
		if (access(result, F_OK | X_OK) == 0)
		{
			return (free(path), result);
		}
		i++;
		free(result);
		result = NULL;
	}
	// ft_putstr_fd("command not found\n", 2);
	return (NULL);
}

char	**extract_paths(char **env)
{
	int	i;
	i = 0;
	
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			// printf("%s", env[i]);
			return (ft_split(env[i] + 5, ':'));}
		i++;
	}
	// ft_print_error("PATH not found\n");
	return (NULL);
}

char	*find_path(char *cmd, char *env[])
{
	char	**to_look;
	char	*path;

	to_look = extract_paths(env);
	if (!to_look || !*to_look)
		return (NULL);
		// ft_print_error("PATH not found\n");
	path = find_commands(cmd, to_look);
	if (!path)
		return (NULL);
		// ft_print_error("command error\n");
	free_leaks_arr(to_look);
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

char **env_tolist(t_env **env_list)
{
    int		size;
	int		length;
	int 	i;
	char	*tmp;
    t_env	*current;
	char	**result;
	size = 0;
	current = (*env_list);
    while (current != NULL) 
	{
	// for(int k = 0; result[k]; k++)
        size++;
        current = current->next;
    }
    result = (char **)malloc(sizeof(char *) * (size + 1));
	if(!result)
		return(perror("malloc"), NULL);
    current = (*env_list);
	
    i = 0;
    while (current != NULL)
	{
        length = ft_strlen(current->name) + ft_strlen(current->var) + 2;
        // result[i] = (char *)malloc(length);
		// if(!result[i])
		// 	return(perror("malloc"), NULL);
		tmp = ft_strjoin(current->name, "=");
		result[i] = ft_strjoin(tmp, current->var);
		free(tmp);
        current = current->next;
        i++;
    }
	// for(result; result != NULL; result++)
	// 	printf(":%s::\n", *result);
    result[i] = NULL;
    return (result);
}
void in_out_handler(t_toexec *cmds, t_pipe *needs)
{
	(void)needs;
		// dprintf(2, "%d\n\n\n", cmds->input);
	if(cmds->input == - 1 || cmds->output == -1)
		return ;
	if(cmds->input != STDIN_FILENO)
	{
		if (dup2(cmds->input, STDIN_FILENO) == -1)
			perror("STDIN");
		close(cmds->input);
		// close(needs->fd[0]);
		// dprintf(2, "|%d|\n\n", needs->fd[0]);
		// ff();
	}
	if(cmds->output != STDOUT_FILENO)
	{
		// dprintf(2, "|%d|\n\n", cmds->output);
		dup2(cmds->output, STDOUT_FILENO);
		close(cmds->output);
		// close(needs->fd[1]);
	}
}
void in_out_handler_multiple(t_toexec *cmds, t_pipe *needs)
{
		// dprintf(2, "%d\n\n\n", cmds->input);
	if(cmds->input == -1 || cmds->output == -1)
		exit (1);
	if(cmds->input != STDIN_FILENO)
	{
		// dprintf(2, "to change fdin = %s\n", cmds->args[0]);
		if (dup2(cmds->input, STDIN_FILENO) == -1)
			perror("STDIN");
		close(cmds->input);
		close(needs->fd[0]);
		// dprintf(2, "|%d|\n\n", needs->fd[0]);
	}
	// else 
	// {
	// 	dprintf(2, "just to pipe == %s\n", cmds->args[0]);
	// 	dup2(needs->fd[0], STDIN_FILENO);
	// 	close(needs->fd[0]);
	// 	close(needs->fd[1]);
	// }
	if(cmds->output != STDOUT_FILENO)
	{
		// dprintf(2, "|%d|\n\n", cmds->output);
		// dprintf(2, "to change fd out == %s \n", cmds->args[0]);
		
		if(dup2(cmds->output, STDOUT_FILENO) == -1)
			perror("dup2");
		close(cmds->output);
		close(needs->fd[1]);
		close(needs->fd[0]);
	}
	else 
	{
		// dprintf(2, "just to pipe == %s\n", cmds->args[0]);
		
		if(dup2(needs->fd[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close(needs->fd[1]);
		close(needs->fd[0]);
	}
		// ff();
}
void in_out_handler_last(t_toexec *cmds, t_pipe *needs)
{
		// dprintf(2, "%d\n\n\n", cmds->input);
	if(cmds->input == -1 || cmds->output == -1)
		exit (1);
	if(cmds->input != STDIN_FILENO)
	{
	// dprintf(2, "to change fd in == %s\n", cmds->args[0]);
		
		if (dup2(cmds->input, STDIN_FILENO) == -1)
			perror("STDIN");
		close(cmds->input);
		close(needs->fd[0]);
		close(needs->fd[1]);
		// dprintf(2, "|%d|\n\n", needs->fd[0]);
	}
		// dprintf(2, "this me %d\n", getpid());
		// ff();
		
		// print_open_file_descriptors();
	// else
	// {
	// 	if(dup2(needs->fd[0], STDIN_FILENO) == -1)
	// 		perror("STDIN");
	// 	close(needs->fd[0]);
	// 	close(needs->fd[1]);
	// }
	if(cmds->output != STDOUT_FILENO)
	{
		// dprintf(2, "|%d|\n\n", cmds->output);
		// dprintf(2, "to change fd out == %s\n", cmds->args[0]);
		
		if(dup2(cmds->output, STDOUT_FILENO) == -1)
			perror("dup2");
		close(cmds->output);
		close(needs->fd[1]);
		// ff();
	}
}
int check_builtin(t_toexec *cmd, t_pipe *needs)
{

	int res = 0;
	if(ft_strcmp(cmd->args[0], "echo") == 0)
		res = ft_echo(cmd, needs);
	if(ft_strcmp(cmd->args[0], "pwd") == 0)
		res = ft_pwd(needs);
	if(ft_strcmp(cmd->args[0], "cd") == 0)
		res = ft_cd(cmd->args[1], cmd->env, needs);
	if(ft_strcmp(cmd->args[0], "env") == 0)
		res = env_print(cmd, needs);
	if(ft_strcmp(cmd->args[0], "export") == 0)
		res = ft_exporter(cmd, needs);
	if(ft_strcmp(cmd->args[0], "unset") == 0)
		res = unseter(cmd, needs);
	if(ft_strcmp(cmd->args[0], "exit") == 0)
		res = ft_exit(cmd->args);
	// (dup2(needs->save_fd_in, STDIN_FILENO) ,close(needs->save_fd_in));
	// (dup2(needs->save_fd_out, STDOUT_FILENO) ,close(needs->save_fd_out));
	return(res);
}

void	ft_execution(t_toexec *cmd, t_pipe *needs)
{
	// dprintf(2, "%s=  %s", cmd->env->name, cmd->env->var);
	// needs->env = env_tolist(&cmd->env);
	
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
			ft_print_error("command not found\n");
	}
	// if (access(cmd->args[0], F_OK) == 0)
	// 	needs->path = cmd->args[0];
		
	if(access(needs->path, X_OK) != 0)
	{
		ft_putstr_fd( "minishell: ",2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
			// else
			// {
			// 	ft_putstr_fd( "minishell: ",2);
			// 	ft_putstr_fd(cmd->args[0], 2);
			// 	ft_putstr_fd(": No such file or directory\n", 2);
			// 	exit(127);
			// }
	// dprintf(needs->path);
		// system("lsof -c minishell");


	// dprintf(2,"%s===== %s ======= %s\n", needs->path, cmd->args[0], cmd->args[1]);
	// printf("hna  %s   %s\n", needs->path, cmd->args[0]);
	// for(int i = 0;needs->env[i]; i++)
		// dprintf(2,"%s   %s    %s\n", needs->env[4], needs->path, cmd->args[0]);
	if (-1 == execve(needs->path, cmd->args, needs->env))
		(close(0), close(needs->infile), error_handler("execve"));
}

void	last_child(t_toexec **cmds, t_pipe *needs)
{
	// needs->p++;
	needs->pids[needs->p] = fork();
	if (needs->pids[needs->p] == -1)
		return(perror("fork"));
	if (needs->pids[needs->p] == 0)
	{
		// dprintf(2, "hana last == %d\n", getpid());
		close(needs->save_fd_in);
		close(needs->save_fd_out);
		// if (-1 == dup2(cmds->output, 1))
		// 	error_handler("dup2");
		// dprintf(2, "{{{%s\n", (*cmds)->args[0]);
		in_out_handler_last(*cmds, needs);
		// close(needs->save_fd_in);
		// close(needs->save_fd_out);
		if((*cmds)->args)
		{
			if(check_builtin((*cmds), needs))
				exit(0) ;
			
			// print_open_file_descriptors();			
			ft_execution((*cmds), needs);
		}
		else
			exit (0);
	}
	
	// close(0);

}

void cmds_executer(t_toexec *cmds, t_pipe *needs)
{
	if (pipe(needs->fd) == -1)
		return(perror("pipe"));
	needs->pids[needs->p] = fork();
	if (needs->pids[needs->p] == -1)
		return (perror("fork"));
	
	if (needs->pids[needs->p] == 0)
	{
		in_out_handler_multiple(cmds, needs);
		close(needs->save_fd_in);
		close(needs->save_fd_out);
		// open_handler(needs);
		// if (-1 == dup2(needs->fd[1], STDOUT_FILENO))
		// 	error_handler("dup2");

		// (close(needs->fd[1]), close(needs->fd[0]));
		if(cmds->args)
		{
			if(check_builtin(cmds, needs))
				exit(0);
		// print_open_file_descriptors();
			ft_execution(cmds, needs);
		}
		else
			exit (0);
	}
	else
	{
		// dprintf(2, "%d === 0;;;%d .   1;;;%d\n", needs->p, needs->fd[0], needs->fd[1]);
		if (-1 == dup2(needs->fd[0], STDIN_FILENO))
			return(perror("dup2"));
		(close(needs->fd[0]), close(needs->fd[1]));
		if(cmds->input != STDIN_FILENO)
			close(cmds->input);
		if(cmds->output != STDOUT_FILENO)
			close(cmds->output);
		// (dup2(needs->save_fd_in, STDIN_FILENO) ,close(needs->save_fd_in));
		// (dup2(needs->save_fd_out, STDOUT_FILENO) ,close(needs->save_fd_out));
		
	}
}

void	first_cmd(t_toexec **cmds, t_pipe *needs)
{
	needs->i = lst_size((*cmds));
	// dprintf(2, "%d\n", needs->i);
	needs->env = env_tolist(&(*cmds)->env);
	// dup2(cmds->input, 0);
	// dprintf(2, "%d\n", needs->i);
	env_search_replace((*cmds)->env, ft_strdup(" "), "_");
	needs->pids = malloc(sizeof(int) * needs->i);
	if(!needs->pids)
		return ; 
	while (needs->i > 1)
	{
		// dprintf(2, "%s\n",(*cmds)->args[0]);
		cmds_executer((*cmds), needs);
		(*cmds) = (*cmds)->next;	
		needs->p++;
		needs->i--;
	}
}

void executer(t_toexec *cmds, t_pipe *needs)
{
	// t_pipe needs;
	needs->p = 0;
	needs->env = env_tolist(&cmds->env);
	
	// for(cmds->env; cmds->env != NULL; cmds->env = cmds->env->next)
	// 	dprintf(2, "%s  == %s\n", cmds->env->name, cmds->env->var);
	// dprintf(2, "hna\n");
	// needs.save_fd_in = cmds->save_fd_in;
	needs->save_fd_in = dup(STDIN_FILENO);
	needs->save_fd_out = dup(STDOUT_FILENO);
		if(lst_size(cmds) == 1)
		{
			needs->pids = malloc(sizeof(int));
			if(cmds->args)
			{
				env_search_replace(cmds->env, ft_strdup(cmds->args[0]), "_");
				in_out_handler(cmds, needs);
				if(check_builtin(cmds, needs))
				{
					
					(dup2(needs->save_fd_in, STDIN_FILENO) ,close(needs->save_fd_in));
					(dup2(needs->save_fd_out, STDOUT_FILENO) ,close(needs->save_fd_out));
					return ;
				}
				needs->pids[needs->p] = fork();
				if(needs->pids[needs->p] == -1)
					perror("fork");
				
				tcgetattr(STDIN_FILENO, &needs->term);
				if(needs->pids[needs->p] == 0)
					ft_execution(cmds, needs);
					
				
			}
		}
		else if(lst_size(cmds) > 1)
		{
			first_cmd(&cmds, needs);
			last_child(&cmds, needs);
			// close(STDIN_FILENO);
		}
			(dup2(needs->save_fd_in, STDIN_FILENO) ,close(needs->save_fd_in));
			(dup2(needs->save_fd_out, STDOUT_FILENO) ,close(needs->save_fd_out));

	// dprintf(2, "{{{%d p == %d}}}\n", getpid(), getppid());
		// ff();

	// dprintf(2, "{{%d}}\n", needs.p);
		int fds = 3;
		while(fds < 2400)
		{
			close(fds++);
		}
	needs->j = 0;
	int x;
	while(needs->j <= needs->p)
	{
		// dprintf(2, "this the child %d\n", needs->pids[needs->j]);
		waitpid(needs->pids[needs->j], &x, 0);
		// *(needs->ex_stat) = WEXITSTATUS(x);
		// dprintf(2, "{{{pids==%d}}}\n", needs.pids[needs.p]);
		needs->j++;
	}
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



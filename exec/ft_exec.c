/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:04:57 by zyamli            #+#    #+#             */
/*   Updated: 2024/03/23 03:23:26 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h> 
void print_open_file_descriptors() {
    int fd;
    
    // Iterate through possible file descriptors
    for (fd = 0; fd < 256; fd++) { // Adjust the range as per your requirements
        int flags = fcntl(fd, F_GETFD);
        if (flags != -1) {
            dprintf(2,"File descriptor %d is open\n", fd);
        }
    }
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
	char	**command;
	char	*path;
	int		i;
	command = ft_split(av, ' ');
	if (ft_strchr(command[0] , '/') != 0)
	{
		result = ft_strdup(command[0]);
		return (free_leaks_arr(command), result);
	}
	path = ft_strjoin("/", command[0]);
	free_leaks_arr(command);
	i = 0;
	while (pathes[i])
	{
		result = ft_strjoin(pathes[i], path);
		if (access(result, F_OK) == 0 || access(result, X_OK) == 0)
		{
			return (free(path), result);
		}
		i++;
		free(result);
		result = NULL;
	}
	ft_putstr_fd("command not found\n", 2);
	return (NULL);
}

char	**extract_paths(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], "PATH"))
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	ft_print_error("PATH not found\n");
	return (NULL);
}

char	*find_path(char *cmd, char *env[])
{
	char	**to_look;
	char	*path;

	to_look = extract_paths(env);

	if (!*to_look)
		ft_print_error("PATH not found\n");
	path = find_commands(cmd, to_look);
	if (!path)
		ft_print_error("command error\n");
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

char **env_tolist(t_env *env_list)
{
    int		size;
	int		length;
	int 	i;
	char	*tmp;
    t_env	*current;
	char	**result;

	size = 0;
	current = env_list;
    while (current != NULL) 
	{
        size++;
        current = current->next;
    }
    result = (char **)malloc(sizeof(char *) * (size + 1));
    current = env_list;
    i = 0;
    while (current != NULL)
	{
        length = ft_strlen(current->name) + ft_strlen(current->var) + 2;
        result[i] = (char *)malloc(length);
		tmp = ft_strjoin(current->name, "=");
		result[i] = ft_strjoin(tmp, current->var);
        current = current->next;
        i++;
    }
    result[size] = NULL;
    return (result);
}

void	ft_execution(t_toexec *cmd, t_pipe *needs)
{
	// needs->env = env_tolist(cmd->env);
	needs->path = find_path(cmd->args[0], needs->env);

	print_open_file_descriptors();
	// dprintf(2,"%s===== %s ======= %s\n", needs->path, cmd->args[0], cmd->args[1]);
	if (!needs->path)
		ft_print_error("error PATH\n");
	if (-1 == execve(needs->path, cmd->args, needs->env))
		(close(0), close(needs->infile), error_handler("execve"));
}

void	last_child(t_toexec **cmds, t_pipe *needs)
{
	// needs->p++;
	needs->pids[needs->p] = fork();
	if (needs->pids[needs->p] == -1)
		error_handler("fork");
	if (needs->pids[needs->p] == 0)
	{
		// if (-1 == dup2(cmds->output, 1))
		// 	error_handler("dup2");
		ft_execution((*cmds), needs);
	}
	// close(0);

}
void cmds_executer(t_toexec *cmds, t_pipe *needs)
{
	if (pipe(needs->fd) == -1)
		error_handler("pipe");
	needs->pids[needs->p] = fork();
	if (needs->pids[needs->p] == -1)
		error_handler("fork");
	
	if (needs->pids[needs->p] == 0)
	{
		// open_handler(needs);
		if (-1 == dup2(needs->fd[1], STDOUT_FILENO))
			error_handler("dup2");

		(close(needs->fd[1]), close(needs->fd[0]));
		ft_execution(cmds, needs);
	}
	else
	{
		// dprintf(2, "%d === 0;;;%d .   1;;;%d\n", needs->p, needs->fd[0], needs->fd[1]);
		if (-1 == dup2(needs->fd[0], STDIN_FILENO))
			error_handler("dup2");
		(close(needs->fd[0]), close(needs->fd[1]));
		
	}
}

void	first_cmd(t_toexec **cmds, t_pipe *needs)
{
	needs->i = lst_size((*cmds));
	needs->env = env_tolist((*cmds)->env);
	// dup2(cmds->input, 0);
	// dprintf(2, "%d\n", needs->i);
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
void executer(t_toexec *cmds)
{
	t_pipe needs;
	needs.p = 0;
	if(lst_size(cmds) == 1)
	{
		needs.pids[needs.p] = fork();
		if(!needs.pids[needs.p])
			perror("fork");
		if(needs.pids[needs.p] == 0)
			ft_execution(cmds, &needs);
		needs.p++;
	}
	else
	{
		first_cmd(&cmds, &needs);
		last_child(&cmds, &needs);
	}
	int i = 0;
	// dprintf(2, "{{%d}}\n", needs.p);
	while(needs.p >= 0)
	{
		waitpid(needs.pids[needs.p], NULL, 0);
		// dprintf(2, "{{{pids==%d}}}\n", needs.pids[needs.p]);
		needs.p--;
	}
}
int main(int ac, char **av, char **env)
{

t_env	*envi = NULL;
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
        if (envi == NULL)
            envi = new_env;
		else
		{
			tmp = envi;
            while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_env;
		}
		i++;
	}
	
	//_________________________________________________________________________________________________________________________________
	char **arg = malloc(sizeof(char *) * 4);
	arg[0] = ft_strdup("cat");
	arg[1] = ft_strdup("ft_env.c");
	arg[2] = NULL;
	char **arg2 = malloc(sizeof(char *) * 4);
	arg2[0] = ft_strdup("grep");
	arg2[1] = ft_strdup("N");
	arg2[2] = NULL;
	t_toexec *node = malloc(sizeof(t_toexec));
	node->args = arg;
	node->input = 0;
	node->output = 1;
	char **arg3 = malloc(sizeof(char *) * 4);
	arg3[0] = ft_strdup("grep");
	arg3[1] = ft_strdup("z");
	arg3[2] = NULL;
	char **arg4 = malloc(sizeof(char *) * 4);
	arg4[0] = ft_strdup("wc");
	arg4[1] = ft_strdup("-c");
	arg4[2] = NULL;
	t_toexec *node2 = malloc(sizeof(t_toexec));
	node->next = node2;
	node->next->args = arg2;
	node->next->input = 0;
	node->next->output = 1;
	t_toexec *node3 = malloc(sizeof(t_toexec));
	node2->next = node3;
	node2->next->args = arg3;
	node2->next->input = 0;
	node2->next->output = 1;
	t_toexec *node4 = malloc(sizeof(t_toexec));
	node3->next = node4;
	node3->next->args = arg4;
	node3->next->input = 0;
	node3->next->output = 1;
	node3->next->next = NULL;
	node->env = envi;
	executer(node);
	
}


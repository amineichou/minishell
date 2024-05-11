/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:11:11 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/11 15:05:50 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit (127);
}

void	ft_wait(t_pipe *needs)
{
	int	j;
	int	x;

	j = 0;
	while (j <= needs->p)
	{
		waitpid(needs->pids[j], &x, 0);
		j++;
	}
	ft_set_status(WEXITSTATUS(x), 1);
	*(needs->ex_stat) = ft_update_status(x, &needs->term);
}

void	set_values(t_pipe *needs, t_toexec *cmds)
{
	needs->p = 0;
	needs->env = env_tolist(&cmds->env);
	needs->save_fd_in = dup(STDIN_FILENO);
	needs->save_fd_out = dup(STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &needs->term);
	needs->size = lst_size(cmds);
	needs->step = 0;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n && (str1[i] || str2[i]))
	{
		if (str1[i] > str2[i])
			return (1);
		else if (str1[i] < str2[i])
			return (-1);
		i++;
	}
	return (0);
}

char	**free_leaks(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:29:49 by moichou           #+#    #+#             */
/*   Updated: 2024/03/17 03:40:08 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../includes/macros.h"

// free after using
static char	*ft_get_word(char *str, int *i)
{
	char	*res;
	int		tmp;

	tmp = *i;
	while (str[*i])
	{
		if (str[*i] == ' ')
			break;
		(*i)++;
	}
	res = malloc(sizeof(char) * (*i + 1));
	if (!res)
		perror("MALLOC_ERORR");
	*i = tmp;
	while (str[*i])
	{
		if (str[*i] == ' ')
			break;
		res[*i] = str[*i];
		(*i)++;
	}
	res[*i] = '\0';
	return (res);
}

static int	ft_count_args(char *rest_args, int index)
{
	int		size;

	size = 0;
	while (rest_args[index++])
	{
		if (rest_args[index] == '"')
		{
			size++;
			while (rest_args[++index] != '"')
				size++;
		}
		if (rest_args[index] == '\'')
		{
			size++;
			while (rest_args[++index] != '\'')
				size++;
		}
		if (rest_args[index] == '|')
		{
			size++;
			break ;
		}
		size++;
	}
	return (size);
}

static char *ft_get_args(char *rest_args, int *i)
{
	char	*res;
	int		size;

	size = ft_count_args(rest_args, *i);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		ft_printerror(MALLOC_ERORR);
	ft_strcpy(res, rest_args, size);
	*i += size;
	return (res);
}

t_toexec	*ft_analyser(char *sanitize_result)
{
	t_toexec	*lst;
	t_toexec	*node;
	char		*cmd;
	char		*args;
	int			i;

	i = 0;
	while (sanitize_result[i])
	{
		//cmd = ft_get_word(&sanitize_result[i], &i);
		//printf("%d\n", i);
		//args = ft_get_args(&sanitize_result[i], &i);
		// node = ft_create_node(cmd, ft_split(args, ' '));
		//ft_append_node(lst, node);
		i++;
	}
	return (lst);
}

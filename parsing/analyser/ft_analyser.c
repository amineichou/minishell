/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:29:49 by moichou           #+#    #+#             */
/*   Updated: 2024/03/14 18:08:35 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../includes/macros.h"

static char	*ft_get_args(char *args)
{
	char	*res;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (args[i++] != '|')
		size++;
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (ft_printerror(MALLOC_ERORR), NULL);
	i = 0;
	while (args[i++] != '|')
		res[i] = args[i];
	res[i] = '\0';
	return (res);
}

t_toexec	*ft_analyser(char **args)
{
	t_toexec	*lst;
	t_toexec	*node;
	int			i;

	// i = 2;
	// args = ft_get_args((*args)[1]);
	// node = ft_create_node((*args)[0], args);
	// while ((*args)[i])
	// {
	// 	args = ft_create_node((*args)[i])
	// 	i++;
	// }
	i = 0;
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
	return (lst);
}
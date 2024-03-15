/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:29:49 by moichou           #+#    #+#             */
/*   Updated: 2024/03/15 18:39:37 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../includes/macros.h"


t_toexec	*ft_analyser(char **args)
{
	t_toexec	*lst;
	t_toexec	*node;
	char		*cmd;
	int			i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
		{
			cmd = ft_get_word((*args)[i]);
			node = ft_create_node(cmd, args);
		}
		else
			ft_append_node(lst, node);
		i++;
	}
	// i = 0;
	// while (args[i])
	// {
	// 	printf("%s\n", args[i]);
	// 	i++;
	// }
	return (lst);
}
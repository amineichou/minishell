/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:29:49 by moichou           #+#    #+#             */
/*   Updated: 2024/03/16 01:23:00 by moichou          ###   ########.fr       */
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
	lst = NULL;
	cmd = NULL;
	lst = NULL;
	while (args[i])
	{
		// cmd = ft_get_word(args[i]);
		node = ft_create_node(args[i], args);
		lst = ft_append_node(lst, node);
		i++;
	}
	return (lst);
}

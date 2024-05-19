/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:32:10 by moichou           #+#    #+#             */
/*   Updated: 2024/05/19 15:00:47 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_set_status(int new_status, int type)
{
	static int	old_status;

	if (type)
		old_status = new_status;
	return (old_status);
}

// this func will set t_toexec node to it's default values
void	ft_set_default_vals(t_toexec *node, t_env *envl)
{
	node->input = 0;
	node->output = 1;
	node->args = NULL;
	node->env = envl;
}

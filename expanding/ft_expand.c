/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:05:57 by moichou           #+#    #+#             */
/*   Updated: 2024/04/19 10:40:37 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expand(t_token *lst_token, t_env *envl)
{
	t_token	*tmp;

	tmp = lst_token;
	while (tmp)
	{
		if (tmp->token == WORD)
		{
			tmp->value = ft_replace_dollar(tmp->value, envl);
			tmp->value = ft_remove_qoutes(tmp->value);
		}
		tmp = tmp->next;
	}
}

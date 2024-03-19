/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:02:34 by moichou           #+#    #+#             */
/*   Updated: 2024/03/19 04:08:27 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// free after using
static char	*ft_get_word(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			break;
		i++;
	}
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		perror("MALLOC_ERORR");
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			break;
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_toexec	*ft_analyser(char *sanitize_result)
{
	t_token		*lst_token;
	t_toexec	*lst_toexec;
	t_toexec	*node;

	lst_token = ft_analyse_tokens(sanitize_result);
	//test_tokens(lst_token);
	lst_toexec = NULL;
	while (lst_token)
	{
		node = malloc(sizeof(t_toexec));
		if (lst_token->token == WORD)
		{
			node->cmd = ft_get_word(lst_token->value);
			node->args = ft_split(lst_token->value, ' ');
			lst_token = lst_token->next;
			// if (lst_token && lst_token->token == RD_AP)
			// {
				
			// }
		}
		ft_append_node_t_toexec(&lst_toexec, node);
		lst_token = lst_token->next;
	}
	return (lst_toexec);
}

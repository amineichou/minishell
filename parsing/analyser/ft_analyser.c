/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:02:34 by moichou           #+#    #+#             */
/*   Updated: 2024/03/23 02:56:39 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// free after using
// static char	*ft_get_cmd(char *str)
// {
// 	char	*res;
// 	int		i;
// 	int		in_quotes;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (ft_isquote(str[i]))
// 			in_quotes = 1;
// 		if (str[i] == ' ' && !in_quotes)
// 			break;
// 		i++;
// 	}
// 	res = malloc(sizeof(char) * (i + 1));
// 	if (!res)
// 		perror("MALLOC_ERORR");
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == ' ')
// 			break;
// 		res[i] = str[i];
// 		i++;
// 	}
// 	res[i] = '\0';
// 	return (res);
// }

static char **ft_get_args(char *str)
{
	char	**res;
	int		i;
	while (str[i])
	{
		if (str[i] == ' ')
			break ;
		i++;
	}
	res = ft_split(str + i, ' ');
	return (res);
}

t_toexec	*ft_analyser(char *sanitize_result)
{
	t_token		*lst_token;
	t_toexec	*lst_toexec;
	t_toexec	*node;

	lst_token = ft_analyse_tokens(sanitize_result);
	// test_tokens(lst_token);
	lst_toexec = NULL;
	while (lst_token)
	{
		node = malloc(sizeof(t_toexec));
		if (lst_token->token == PIPE)
		{
			if (lst_token->next && lst_token->next->token != WORD)
			{
				ft_handle_redirections(lst_token->next, &node);
				lst_token = lst_token->next;
			}
			else
			{
				lst_token = lst_token->next;
				continue ;
			}
		}
		else if (lst_token->token == WORD)
		{
			node->args = ft_split(lst_token->value, ' ');
			if (lst_token->next && lst_token->next->token != PIPE && lst_token->next->token != WORD)
			{
				ft_handle_redirections(lst_token->next, &node);
				lst_token = lst_token->next;
			}
			else
			{
				node->input = 0;
				node->output = 1;
			}
		}
		ft_append_node_t_toexec(&lst_toexec, node);
		lst_token = lst_token->next;
	}
	return (lst_toexec);
}

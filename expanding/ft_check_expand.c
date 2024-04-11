/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 06:43:50 by moichou           #+#    #+#             */
/*   Updated: 2024/04/04 22:20:06 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_search_for_dollar(char *str, int *i)
{
	while (str[*i] && ft_isquote(str[*i] != 1))
	{
		if (str[*i] == '$')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_check_expand_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]) == 1)
		{
			ft_skip_quotes(str, &i);
			if (str[i] == '\0')
				return (0);
		}
		if (ft_search_for_dollar(str, &i))
			return (1);
		if (str[i] == '\0')
			break;
		i++;
	}
	return (0);
}

// int main(void)
// {
// 	char test[] = "amine ichou 'amine ichou $' ami$ne";
// 	printf("%d\n", ft_check_expand_value(test));
// }

//check if the string will be expanded & expand if it is; returns NULL if malloc failed
// void ft_check_expand(t_token **lst_token, char **env)
// {
// 	t_token	*node_token;

// 	node_token = *lst_token;
// 	while (node_token)
// 	{
// 		if (node_token->value == WORD && ft_check_expand_value(node_token->value))
// 			node_token->value = ft_expand(node_token->value, env);
// 		node_token = node_token->next;
// 	}
// }
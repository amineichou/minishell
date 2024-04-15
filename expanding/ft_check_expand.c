/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 06:43:50 by moichou           #+#    #+#             */
/*   Updated: 2024/04/12 15:26:58 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_expand_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		
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
// 			node_token->value = ft_expand(node_token->value);
// 		node_token = node_token->next;
// 	}
// }
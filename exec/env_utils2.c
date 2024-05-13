/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:21:48 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/13 14:59:33 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_env(char *arg, char c)
{
	int		i;
	char	**res;

	i = 0;
	res = zyalloc(sizeof(char *) * 3, 'a', false);
	if (!res)
		return (NULL);
	while (arg[i] != c && arg[i])
		i++;
	if (arg[i] == c)
	{
		res[0] = ft_substr(arg, 0, i, false);
		res[1] = ft_substr(arg, i + 1, ft_strlen(arg), false);
		res[2] = NULL;
		return (res);
	}
	else
	{
		res[0] = arg;
		res[1] = NULL;
		return (res);
	}
	return (NULL);
}

int	look_for(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	add_orjoin(char *av)
{
	int	i;

	i = 0;
	while (av[i] && av[i] != '=')
		i++;
	if (av[i] == '=' && av[i - 1] == '+')
		return (1);
	return (0);
}

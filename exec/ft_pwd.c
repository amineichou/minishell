/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:14:31 by zyamli            #+#    #+#             */
/*   Updated: 2024/04/25 15:29:55 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd(t_pipe *needs)
{
	char	buff[1024];
	if(getcwd(buff, 1024) == NULL)
	{
		*(needs->ex_stat) = 1;
		perror("pwd");
	}
	else
	{
		printf("%s\n", buff);
		*(needs->ex_stat) = 0;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:00 by moichou           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/06 14:58:51 by zyamli           ###   ########.fr       */
=======
/*   Updated: 2024/03/06 22:30:03 by moichou          ###   ########.fr       */
>>>>>>> 64342c4d2c6e4e1b244394994bc38bf9afec8abd
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av)
{
	char		*line;
	t_toexec	*lst;
	(void)av;
	while (1)
	{
		line = readline("minishell$ ");
		lst = ft_tokenization(line);
		//if (lst != NULL)
			//send it to exec
	}
}

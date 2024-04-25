/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 03:41:06 by moichou           #+#    #+#             */
/*   Updated: 2024/04/25 10:47:08 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_valid_fd(t_toexec *head)
{
	t_toexec	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->output == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (1);
}

t_toexec	*ft_parser(char *line, t_env *envl, int ex_sta)
{
	char		*sanitize_result;
	t_toexec	*lst_toexec;

	sanitize_result = ft_sanitizer(line);
	if (!sanitize_result)
		return (NULL); // TODO : free
	
	lst_toexec = ft_analyser(sanitize_result, envl, ex_sta);
	if (!lst_toexec)
		return (NULL);
	if (ft_check_valid_fd(lst_toexec) == -1)
		return (NULL);
	// test_lst(lst_toexec);
	return (lst_toexec);
}

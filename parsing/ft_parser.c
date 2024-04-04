/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 03:41:06 by moichou           #+#    #+#             */
/*   Updated: 2024/04/04 23:09:39 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_toexec	*ft_parser(char *line)
{
	char		*sanitize_result;
	t_toexec	*lst_toexec;

	sanitize_result = ft_sanitizer(line);
	if (!sanitize_result)
		return (NULL); // TODO : free
	lst_toexec = ft_analyser(sanitize_result);
	if (!lst_toexec)
		return (NULL);
	// test_lst(lst_toexec);
	return (lst_toexec);
}

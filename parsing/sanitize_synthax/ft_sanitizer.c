/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:16:32 by moichou           #+#    #+#             */
/*   Updated: 2024/03/30 01:39:17 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// synthax health check and fix it's structure
char	*ft_sanitizer(char *line)
{
	line = ft_trim_spaces(line); // TODO : leaks + protection
	if (ft_sanitize_quotes(line) == -1
		|| ft_sanitize_pipes(line) == -1
		|| ft_sanitize_redirections(line) == -1)
		return (NULL);
	return (line);
}

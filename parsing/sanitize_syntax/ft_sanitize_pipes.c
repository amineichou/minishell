/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:24:33 by moichou           #+#    #+#             */
/*   Updated: 2024/04/27 16:45:41 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_first_last_pipe(char *str, int *where)
{
	int	i;

	i = 0;
	if (str[i] == '|')
	{
		if (i < *where || *where == -1)
			*where = i;
		return (1);
	}
	i = ft_strlen(str) - 1;
	if (str[i] == '|')
	{
		if (i < *where || *where == -1)
		{
			printf("test %d\n", *where);
		}
			*where = i;
		return (1);
	}
	return (0);
}

static int	ft_sequential_pipes(char *str, int *where)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			while (str[i] && ft_isspace(str[i]))
				i++;
			if (str[i] && str[i] == '|')
			{
				if (i < *where || *where == -1)
					*where = i;
				return (1);
			}
		}
		if (ft_isquote(str[i]))
			ft_skip_quotes(str, &i);
		else if (str[i] == '\0')
			break ;
		else
			i++;
	}
	return (0);
}

static int	ft_red_before_pipe(char *str, int *where)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && ft_isquote(str[i]))
			ft_skip_quotes(str, &i);
		if (ft_isredirection(str[i]))
		{
			i++;
			if (str[i] && ft_isredirection(str[i]))
				i++;
			while (str[i] && ft_isspace(str[i]))
				i++;
			if (str[i] && str[i] == '|')
			{
				if (i < *where || *where == -1)
					*where = i;
				return (1);
			}
		}
		if (str[i] == '\0')
			break ;
		else
			i++;
	}
	return (0);
}

int	ft_sanitize_pipes(char *line, int *where)
{
	if (ft_first_last_pipe(line, where)
		|| ft_red_before_pipe(line, where)
		|| ft_sequential_pipes(line, where))
	{
		ft_printerror(SYNTAX_ERROR_PIPE);
		return (-1);
	}
	return (0);
}

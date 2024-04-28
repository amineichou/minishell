/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:53:48 by moichou           #+#    #+#             */
/*   Updated: 2024/04/27 16:25:14 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_is_red_is_last(char *line, int *where)
{
	int	last_index;

	last_index = ft_strlen(line) - 1;
	if (line[last_index] == '<' || line[last_index] == '>')
	{
		if (last_index < *where || *where == -1)
			*where = last_index;
		return (ft_printerror("syntax error near unexpected token `newline'\n"), 1);
	}
	return (0);
}

static int	ft_sequential_red_same(char *line, int *where)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] && ft_isredirection(line[i]))
		{
			i++;
			if (line[i] && ft_isredirection(line[i]))
				i++;
			while (line[i] && ft_isspace(line[i]))
				i++;
			if (line[i] && ft_isredirection(line[i]))
			{
				if (i < *where || *where == -1)
					*where = i;
				return (ft_printerror("syntax error near unexpected token `>'\n") ,1);
			}
		}
		if (line[i] == '\0')
			break ;
		if (ft_isquote(line[i]))
			ft_skip_quotes(line, &i);
		else
			i++;
	}
	return (0);
}

static int	ft_sequential_red_oposite(char *line, int *where)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isredirection(line[i]) == 1)
		{
			i++;
			if (line[i] && ft_isredirection(line[i]) == -1)
			{
				if (i < *where || *where == -1)
					*where = i;
				return (ft_printerror("syntax error near unexpected token `<'\n") , 1);
			}
		}
		else if (ft_isredirection(line[i]) == -1)
		{
			i++;
			if (line[i] && ft_isredirection(line[i]) == 1)
			{
				if (i < *where || *where == -1)
					*where = i;
				return (ft_printerror("syntax error near unexpected token `>'\n") , 1);
			}
		}
		if (ft_isquote(line[i]))
			ft_skip_quotes(line, &i);
		else if (line[i] == '\0')
			break ;
		else
			i++;
	}
	return (0);
}

static int	ft_sequential_redirections(char *line, int *where)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (line[i])
	{
		if (line[i] && ft_isredirection(line[i]))
		{
			i++;
			if (line[i] && ft_isredirection(line[i]))
				i++;
			while (line[i] && ft_isspace(line[i]))
				i++;
			if (line[i] && ft_isredirection(line[i]))
			{
				if (i < *where || *where == -1)
					*where = i;
				return (ft_printerror("syntax error near unexpected token `>'\n") , 1);
			}
		}
		if (line[i] == '\0')
			break ;
		if (ft_isquote(line[i]))
			ft_skip_quotes(line, &i);
		else
			i++;
	}
	return (0);
}

int	ft_sanitize_redirections(char *line, int *where)
{
	if (ft_sequential_red_same(line, where)
		|| ft_sequential_red_oposite(line, where)
		|| ft_sequential_redirections(line, where)
		|| ft_is_red_is_last(line, where))
	{
		return (-1); 
	}
	return (0);
}

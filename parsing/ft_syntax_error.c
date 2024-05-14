/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:04:48 by moichou           #+#    #+#             */
/*   Updated: 2024/05/14 14:48:21 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_quote_closure(char *line, char c, int *i, int *where)
{
	(*i)++;
	*where = *i;
	while (line[*i])
	{
		if (line[*i] && line[*i] == c)
		{
			(*i)++;
			*where = *i;
			return (1);
		}
		(*i)++;
	}
	ft_put_syntaxerror("syntax error, missing quote ", c);
	return (-1);
}

static int	ft_check_pipe_syntax(char *line, int *i, int *where)
{
	(*i)++;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (line[*i] == '\0' || line[*i] == '|')
	{
		*where = *i;
		return (ft_put_syntaxerror("syntax error near unexpected \
token ", '|'), -1);
	}
	return (1);
}

static int	ft_handle_red_syntax(char *line, int *i, int *where)
{
	if (line[*i] == '\0')
	{
		*where = *i;
		ft_printerror("syntax error near unexpected token `newline`\n");
		return (-1);
	}
	if (ft_isredirection(line[*i]))
	{
		*where = *i;
		ft_put_syntaxerror("syntax error near unexpected token ", line[*i]);
		return (-1);
	}
	if (line[*i] == '|')
	{
		*where = *i;
		ft_printerror("syntax error near unexpected token `|`\n");
		return (-1);
	}
	return (1);
}

static int	ft_check_red_syntax(char *line, char red, int *i, int *where)
{
	int	last_index;

	last_index = ft_strlen(line) - 1;
	if (ft_isredirection(line[last_index]))
	{
		*where = last_index;
		return (ft_put_syntaxerror("syntax error near unexpected \
token `newline", 0), -1);
	}
	(*i)++;
	if (line[*i] == red)
		(*i)++;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (ft_isquote(line[*i]) || line[*i] == '\0')
		return (1);
	return (ft_handle_red_syntax(line, i, where));
}

int	ft_check_syntax_error(char *line, int *where)
{
	int	i;

	if (ft_init_syntax_error_vals(&i, line, where) == -1)
		return (-1);
	while (line[i])
	{
		if (ft_isquote(line[i]))
		{
			if (ft_check_quote_closure(line, line[i], &i, where) == -1)
				return (-1);
		}
		else if (line[i] == '|')
		{
			if (ft_check_pipe_syntax(line, &i, where) == -1)
				return (-1);
		}
		else if (line[i] && ft_isredirection(line[i]))
		{
			if (ft_check_red_syntax(line, line[i], &i, where) == -1)
				return (-1);
		}
		else
			i++;
	}
	return (1);
}

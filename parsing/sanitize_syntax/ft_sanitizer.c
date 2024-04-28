/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:16:32 by moichou           #+#    #+#             */
/*   Updated: 2024/04/28 13:10:34 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// syntax health check and fix it's structure

static int	ft_check_quote_closure(char *line, char c, int *i, int *where)
{
	(*i)++;
	while (line[*i])
	{
		if (line[*i] && line[*i] == c)
		{
			(*i)++;
			return (1);
		}
		(*i)++;
	}
	*where = *i;
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
		return (ft_put_syntaxerror("syntax error near unexpected token ", '|'), -1);
	}
	return (1);
}

static int	ft_check_red_syntax(char *line, char red, int *i, int *where)
{
	int	last_index;

	last_index = ft_strlen(line) - 1;
	if (ft_isredirection(line[last_index]))
		return (ft_put_syntaxerror("syntax error near unexpected token `newline", 0), -1);
	(*i)++;
	if (line[*i] == red)
		(*i)++;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (ft_isquote(line[*i]) || line[*i] == '\0')
		return (1);
	if (line[*i] == '\0' || line[*i] == '|' || ft_isredirection(line[*i]))
	{
		*where = *i;
		ft_put_syntaxerror("syntax error near unexpected token ", red);
		return (-1);
	}
	return (1);
}

static int	new_syntax_error(char *line, int *where)
{
	int	i;

	i = 0;
	*where = 0;
	if (!line || line[i] == '|')
		return (ft_printerror("syntax error near unexpected token `|'\n"), -1);
	while (line[i])
	{
		if (ft_isquote(line[i]))
		{
			if (ft_check_quote_closure(line, line[i], &i, where) == -1)
				return (-1);
		}
		else if (line[i] == '|')
		{
			if (ft_check_pipe_syntax(line , &i, where) == -1)
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

static char	*ft_get_herdoc_del(char *line, int *i)
{
	int	start;
	int	length;

	*i = *i + 2;
	start = *i;
	length = 0;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	while (line[*i] && !ft_isspace(line[*i]))
	{
		(*i)++;
		length++;
	}
	if (length)
		return (ft_strldup(&line[start], length));
	return (NULL);
}

static t_herdoc	*ft_create_herdocft_runpast_herdoc(char *line, int stop)
{
	t_herdoc	*herdoc_lst;
	t_herdoc	*node;
	char	*del;
	int		i;

	i = 0;
	herdoc_lst = NULL;
	while (line[i] && i < stop)
	{
		if (line[i] && line[i + 1] && line[i] == '<' && line[i + 1] == '<')
		{
			del = ft_get_herdoc_del(line, &i);
			node = ft_create_herdoc_node(del);
			ft_append_node_herdoc(&herdoc_lst, node);
		}
		i++;
	}
	return (herdoc_lst);
}

char	*ft_sanitizer(char *line)
{
	t_herdoc	*herdoc_lst;
	t_toexec	*lst_toexec;
	t_toexec	*node;
	int			syntax_error_where;

	syntax_error_where = -1;
	line = ft_trim_spaces(line);
	if (!line)
		return (NULL);
	if (new_syntax_error(line, &syntax_error_where) == -1)
	{
		if (syntax_error_where > 1)
		{
			herdoc_lst = ft_create_herdocft_runpast_herdoc(line, syntax_error_where);
			// ft_run_herdoclst(herdoc_lst);
			printf("fucking herdoc\n");
		}
		return (NULL);
	}
	return (line);
}


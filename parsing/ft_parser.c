/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 03:41:06 by moichou           #+#    #+#             */
/*   Updated: 2024/05/19 15:04:15 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_get_herdoc_del(char *line, int *i)
{
	int	start;
	int	length;

	*i += 2;
	length = 0;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (line[*i] && ft_isquote(line[*i]))
		return (ft_get_inside_quotes(line, i, line[*i]));
	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && !ft_isspecialchars(line[*i]))
	{
		(*i)++;
		length++;
	}
	if (length)
		return (ft_strldup(&line[start], length));
	return (NULL);
}

static t_herdoc	*ft_createpast_herdoc(char *line, int stop)
{
	t_herdoc	*herdoc_lst;
	t_herdoc	*node;
	char		*del;
	int			i;

	i = 0;
	herdoc_lst = NULL;
	while (i < stop)
	{
		if (line[i] && line[i + 1] && line[i] == '<' && line[i + 1] == '<')
		{
			del = ft_get_herdoc_del(line, &i);
			if (del)
			{
				node = ft_create_herdoc_node(del);
				ft_append_node_herdoc(&herdoc_lst, node);
			}
		}
		i++;
	}
	return (herdoc_lst);
}

static void	ft_runpast_herdoclst(t_herdoc *head)
{
	t_herdoc	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_heredoc_handler_syn(tmp->del) == -1)
		{
			signal(SIGINT, ft_sigkill_handler);
			close_all();
			break ;
		}
		tmp = tmp->next;
	}
}

static t_toexec	*ft_sanitizer(char *line, t_env *env)
{
	t_herdoc	*herdoc_lst;
	int			syntax_error_where;

	syntax_error_where = -1;
	line = ft_trim_spaces(line);
	if (!line)
		return (free(line), NULL);
	if (ft_check_syntax_error(line, &syntax_error_where) == -1)
	{
		ft_set_status(258, 1);
		if (syntax_error_where > 1)
		{
			herdoc_lst = ft_createpast_herdoc(line, syntax_error_where);
			if (!herdoc_lst)
				return (free(line), NULL);
			ft_runpast_herdoclst(herdoc_lst);
		}
		return (free(line), NULL);
	}
	return (ft_analyser(line, env));
}

// syntax health check and fix it's structure
t_toexec	*ft_parser(char *line, t_env *envl)
{
	t_toexec	*lst_toexec;

	lst_toexec = ft_sanitizer(line, envl);
	ft_check_valid_fd(&lst_toexec);
	free(line);
	return (lst_toexec);
}

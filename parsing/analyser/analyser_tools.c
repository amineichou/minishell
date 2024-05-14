/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyser_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:01:01 by moichou           #+#    #+#             */
/*   Updated: 2024/05/13 17:11:55 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_reallocate_copy(char **old_res, char *new)
{
	char	**res;
	int		i;

	i = 0;
	if (!old_res)
	{
		res = zyalloc(sizeof(char *) * 2, 'a', true);
		res[0] = ft_strdup(new, true);
		res[1] = NULL;
	}
	else
	{
		while (old_res[i])
			i++;
		res = zyalloc(sizeof(char *) * (i + 2), 'a', true);
		i = 0;
		while (old_res[i])
		{
			res[i] = ft_strdup(old_res[i], true);
			i++;
		}
		res[i] = ft_strdup(new, true);
		res[i + 1] = NULL;
	}
	return (res);
}

void	ft_handle_args(t_toexec **node, t_token **lst_token)
{
	char	**joined;
	int		i;

	i = 0;
	joined = (*node)->args;
	if ((*lst_token) && (*lst_token)->value == NULL)
	{
		(*node)->args = NULL;
		(*lst_token) = (*lst_token)->next;
		return ;
	}
	while ((*lst_token) && (*lst_token)->token == WORD)
	{
		joined = ft_reallocate_copy(joined, (*lst_token)->value);
		(*lst_token) = (*lst_token)->next;
	}
	(*node)->args = joined;
}

char	*ft_get_herdoc_del(char *line, int *i)
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

bool	ft_isexpand_herdoc(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (ft_isquote(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_hnadle_herdoc(t_token **lst_token,
			t_toexec *node)
{
	char	*del;
	bool	is_expand;

	while ((*lst_token) && (*lst_token)->token == HEREDOC)
	{
		if ((*lst_token)->next)
			del = (*lst_token)->next->value;
		else
			del = NULL;
		is_expand = ft_isexpand_herdoc(del);
		del = ft_remove_qoutes(del);
		if (del && ft_heredoc_handler_exec(node, del, is_expand) == -1)
		{
			close_all();
			return (-1);
		}
		if ((*lst_token)->next)
			(*lst_token) = (*lst_token)->next->next;
		else
			(*lst_token) = (*lst_token)->next;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_structure.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 01:40:17 by moichou           #+#    #+#             */
/*   Updated: 2024/04/03 06:16:34 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_add_spaces_to_char(char *line, char *res, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (ft_isquote(line[i]) == 1)
		{
			res[j] = line[i];
			j++;
			i++;
			while (ft_isquote(line[i]) != 1)
				res[j++] = line[i++];
			res[j] = line[i];
			j++;
			i++;
		}
		else if (ft_isquote(line[i]) == 2)
		{
			res[j] = line[i];
			j++;
			i++;
			while (ft_isquote(line[i]) != 2)
				res[j++] = line[i++];
			res[j] = line[i];
			j++;
			i++;
		}
		else if (line[i] == c)
		{
			if (line[i + 1] && line[i] == c)
			{
				res[j++] = line[i++];
				res[j++] = line[i++];
			}
			else
			{
				res[j++] = ' ';
				res[j++] = line[i++];
				res[j++] = ' ';
			}
		} 
		else
			res[j++] = line[i++];
	}
	res[j] = '\0';
}

static void	ft_add_spaces_to_string(char *line, char *res, char *c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (ft_isquote(line[i]) == 1)
		{
			res[j] = line[i];
			j++;
			i++;
			while (ft_isquote(line[i]) != 1)
				res[j++] = line[i++];
			res[j] = line[i];
			j++;
			i++;
		}
		else if (ft_isquote(line[i]) == 2)
		{
			res[j] = line[i];
			j++;
			i++;
			while (ft_isquote(line[i]) != 2)
				res[j++] = line[i++];
			res[j] = line[i];
			j++;
			i++;
		}
		else if (line[i] == c[0])
		{
			res[j++] = ' ';
			res[j++] = line[i++];
			res[j++] = line[i++];
			res[j++] = ' ';
		} 
		else
			res[j++] = line[i++];
	}
	res[j] = '\0';
}

// free after using
char	*ft_addspace_illegal_chars(char *line, char *token)
{
	char	*res;
	int		to_add_spaces;
	int		i;
	int		new_size;

	to_add_spaces = ft_count_legal_char(line, token[0]) * 3;
	i = 0;
	new_size = ft_strlen(line) + to_add_spaces;
	res = malloc (sizeof(char) * (new_size + 2));
	if (!res)
		return (ft_printerror("malloc"), NULL);
	if (ft_strlen(token) == 1)
		ft_add_spaces_to_char(line, res, token[0]);
	else
		ft_add_spaces_to_string(line, res, token);
	return (res);
}


//////

// remove the spaces/tabs form the bigg-end if str 
char	*ft_trim_spaces(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	if (!str)
		return (NULL);
	j = ft_strlen(str) - 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (i == ft_strlen(str))
		return (NULL);
	while (ft_isspace(str[j]))
		j--;
	j = ft_strlen(str) - j - 1;
	res = ft_strldup(str + i, (ft_strlen(str) - i - j));
	if (!res)
		ft_printerror(MALLOC_ERORR);
	return (res);
}

static void	ft_replace_illegal_tab(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
			continue ;
		}
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			continue ;
		}
		if (ft_isspace(line[i]))
			line[i] = ' ';
		i++;
	}
}
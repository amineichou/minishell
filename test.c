#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline/history.h"
#include "readline/readline.h"

int	ft_isquote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
	return (0);
}

void	ft_skip_quotes(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] && ft_isquote(str[*i]) == 1)
		{
			(*i)++;
			while (str[*i] && ft_isquote(str[*i]) != 1)
				(*i)++;
		}
		else if (str[*i] && ft_isquote(str[*i]) == 2)
		{
			(*i)++;
			while (str[*i] && ft_isquote(str[*i]) != 2)
				(*i)++;
			
		}
		if (str[*i] == '\0')
				break ;
		(*i)++;
		break ;
	}
}

int	ft_isredirection(char c)
{
	if (c == '>')
		return (1);
	else if (c == '<')
		return (-1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\f' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

static int	ft_sequential_redirections(char *line)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '>')
		{
			i++;
			if (line[i] && line[i] == '>')
				i++;
			while (line[i] && ft_isspace(line[i]))
				i++;
			if (line[i] && line[i] == '>')
				return (1);
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

static int	ft_sequential_red_oposite(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isredirection(line[i]) == 1)
		{
			i++;
			if (line[i] && ft_isredirection(line[i]) == -1)
				return (1);
		}
		else if (ft_isredirection(line[i]) == -1)
		{
			i++;
			if (line[i] && ft_isredirection(line[i]) == 1)
				return (1);
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

static int	ft_sequential_red_same(char *line)
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
				return (printf("syntax error near unexpected token `%c'\n",line[i]) ,1);
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

static char		**ft_reallocate_copy(char **old_res, char *new)
{
	char	**res;
	int		i;

	i = 0;
	if (!old_res)
	{
		res = malloc(sizeof(char *) + 2);
		res[0] = ft_strdup(new); // leaks if new is mallocated
		res[1] = NULL;
	}
	else
	{
		while (old_res[i])
			i++;
		res = malloc(sizeof(char *) * (i + 2));
		i = 0;
		while (old_res[i])
		{
			res[i] = ft_strdup(old_res[i]);
			i++;
		}
		res[i] = strdup(new);
		res[i + 1] = NULL;
	}
	return (res);
}
int main(void)
{
	char *tests[] = {"hello world 1", "hello world 2", "hello world 3", NULL};
	char *test = strdup("hello world 4");
	char **res = ft_reallocate_copy(tests, test);

    for (int i = 0; res[i]; i++)
	{
		printf("%s\n", res[i]);
	}
	
}


// static void	ft_skip_quotess(char *str, int *i, int *size)
// {
// 	if (ft_isquote(str[*i]) == 1)
// 	{
// 		(*i)++;
// 		(*size)++;
// 		while (str[*i])
// 		{
// 			if (ft_isquote(str[*i]) == 1)
// 				break;
// 			(*i)++;
// 			(*size)++;
// 		}
// 		if (str[*i])
// 		{
// 			(*i)++;
// 			(*size)++;
// 		}
// 	}
// 	else if (ft_isquote(str[*i]) == 2)
// 	{
// 		(*i)++;
// 		(*size)++;
// 		while (str[*i])
// 		{
// 			if (ft_isquote(str[*i]) == 2)
// 				break;
// 			(*i)++;
// 			(*size)++;
// 		}
// 		if (str[*i])
// 		{
// 			(*i)++;
// 			(*size)++;
// 		}
// 	}
// }

// static int	ft_count_args(char *str)
// {
// 	int	i;
// 	int	count;
// 	int	in_quotes;
// 	int nevermind = 0;

// 	i = 0;
// 	count = 0;
// 	in_quotes = 0;
// 	while (str[i])
// 	{
// 		while (ft_isspace(str[i]))
// 			i++;
// 		if (str[i])
// 			count++;
// 		while (str[i] && !ft_isspace(str[i]) && !ft_isquote(str[i]))
// 			i++;
// 		if (str[i] && ft_isquote(str[i]))
// 			ft_skip_quotess(str, &i, &nevermind);
// 	}
// 	return (count);
// }

// // static char *ft_fill_arg(char *str, int *i)
// // {
// // 	char		*res;
// // 	int			size;
// // 	int			start;

// // 	size = 0;
// // 	start = *i;
// // 	while (str[*i])
// // 	{
// // 		while (ft_isspace(str[*i]))
// // 		{
// // 			size++;
// // 			(*i)++;
// // 		}
// // 		while (str[*i] && !ft_isspace(str[*i]) && !ft_isquote(str[*i]))
// // 		{
// // 			(*i)++;
// // 			size++;
// // 		}
// // 		if (str[*i] && ft_isquote(str[*i]))
// // 			ft_skip_quotes(str, i, &size);
// // 		break;
// // 	}
// // 	res = ft_strldup(&str[start], size);
// // 	// TODO : protection
// // 	return (res);
// // }

// static char	*ft_get_single_arg(char *str, int *i, int type)
// {
// 	char	*res;
// 	int		size;
// 	int		start;

// 	start = *i;
// 	size = 0;
// 	while (str[*i])
// 	{
// 		(*i)++;
// 		size++;
// 		if (ft_isquote(str[*i]) == type)
// 		{
// 			if (str[(*i) + 1] && !ft_isspace(str[(*i) + 1]))
// 			{
// 				(*i)++;
// 				size++;
// 				continue;
// 			}
// 			else
// 				break ;
// 		}
// 	}
// 	(*i)++;
// 	size++;
// 	res = ft_strldup(&str[start], size);
// 	// TODO : protect
// 	printf("mounted\n");
// 	return (res);
// }

// static char *ft_get_normal_arg(char *str, int *i)
// {
// 	char	*res;
// 	int		size;
// 	int		start;

// 	size = 0;
// 	while (ft_isspace(str[*i]))
// 		(*i)++;
// 	start = *i;
// 	while (str[*i])
// 	{
// 		if (ft_isspace(str[*i]) || ft_isquote(str[*i]))
// 			break ;
// 		(*i)++;
// 		size++;
// 	}
// 	while (ft_isspace(str[*i]))
// 		(*i)++;
// 	res = ft_strldup(&str[start], size);
// 	// TODO : protect
// 	return (res);
// }

// static char *ft_fill_arg(char *str, int *i)
// {
// 	char	*res;
// 	int		size;

// 	size = 0;
// 	if (str[*i] && ft_isquote(str[*i]) == 1)
// 		res = ft_get_single_arg(str, i, 1);
// 	else if (str[*i] && ft_isquote(str[*i]) == 2)
// 		res = ft_get_single_arg(str, i, 2);
// 	else if (str[*i])
// 		res = ft_get_normal_arg(str, i);
// 	else
// 		res = ft_strdup("nothing");
// 	// TODO : protect these
// 	return (res);
// }

char **ft_expand(char *str)
{
	char	**res;
	int		args_count;
	int		i;
	int		index;

	if (!str)
		return (NULL);
	args_count = ft_count_args(str);
	i = 0;
	index = 0;
	res = malloc(sizeof(char *) * (args_count + 1));
	while (i < args_count)
	{
		res[i] = ft_fill_arg(str, &index);// TODO : protect
		i++;
	}
	res[args_count] = NULL; 
	return (res);
}

// int main(void)
// {
// 	// 'ami'ne''       'amine'  amine    \"l\"
// 	char *test = "amine ic		'hou'amine''";
// 	char **res = ft_expand(test);
// 	// if (res)
// 	// {
// 		for (int i = 0; res[i]; i++)
// 		{
// 			printf("%s\n", res[i]);
// 		}
// 	// }
// }
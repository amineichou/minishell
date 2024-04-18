/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_old.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:37:39 by moichou           #+#    #+#             */
/*   Updated: 2024/04/18 18:31:12 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char *ft_env_list_serch_res(t_env *head, char *to_look)
// {
//     t_env    *tmp;

//     if (!head)
//     {
//         printf("Invalid data or data->env is NULL\n");
//         return (NULL);
//     }

//     tmp = head;
//     while(tmp)
// 	{
//        if(ft_strcmp(tmp->name, to_look) == 0)
//             return(ft_strdup(tmp->var));
//        tmp = tmp->next;
//     }
//     return(NULL);
// }

// static char *ft_get_env_arg(char *to_expand, int *i)
// {
// 	char	*res;
// 	int		size;
// 	int		start;

// 	size = 0;
// 	start = *i;
// 	if (to_expand[*i] == '$')
// 		return (NULL);
// 	else if (ft_isspace(to_expand[*i]) || ft_isdigit(to_expand[*i]))
// 		return (ft_strdup("$")); // TODO : leaks
// 	while (to_expand[*i] && ft_is_alphanumeric(to_expand[*i]))
// 	{
// 		size++;
// 		(*i)++;
// 	}
// 	res = ft_strldup(&to_expand[start], size); // TODO : leaks && protection
// 	return (res);
// }

// static void ft_add_size_env_arg(char *arg, int *size, t_env *env)
// {
// 	char	*arg_value;

// 	if (ft_strcmp(arg, "$") == 0)
// 	{
// 		*size += 1;
// 		return ;
// 	}
// 	arg_value = ft_env_list_serch_res(env, arg);
// 	if (arg_value)
// 	{
// 		*size += ft_strlen(arg_value);
// 		free(arg_value);
// 	}
// }

// static int	ft_get_size(char *to_expand, t_env *env)
// {
// 	char	*arg;
// 	int		i;
// 	int		size;

// 	size = 0;
// 	while (to_expand[i])
// 	{
// 		if (to_expand[i] == '$')
// 		{
// 			i++;
// 			if (to_expand[i] && to_expand[i] == '$')
// 				size++;
// 			arg = ft_get_env_arg(to_expand, &i);
// 			if (arg)
// 				ft_add_size_env_arg(arg, &size, env);
// 		}
// 		else
// 		{	
// 			size++;
// 			i++;
// 		}
// 		if (to_expand[i] == '\0')
// 			break ;
// 	}
// 	return (size);
// }

// char	*ft_expand(char *to_expand, t_env *env)
// {
// 	char	*res;
// 	char	*arg;
// 	int		i;
// 	int		j;
// 	int		tmp;
// 	int		size;

// 	j = 0;
// 	size = ft_get_size(to_expand, env);
// 	res = malloc(sizeof(char) * (size + 1));
// 	if (!res)
// 		return (NULL);// TODO : leaks protection
// 	while (to_expand[i])
// 	{
// 		// if (to_expand[i])
// 		if (to_expand[i] == '$')
// 		{
// 			i++;
// 			if (to_expand[i] == '\0')
// 			{
// 				res[j] = '$';
// 				j++;
// 				break;
// 			}
// 			arg = ft_get_env_arg(to_expand, &i);
// 			if (arg && ft_strcmp(arg, "$") == 0)
// 			{
// 				res[j] = '$';
// 				j++;
// 			}
// 			else if (arg)
// 			{
// 				arg = ft_env_list_serch_res(env, arg);
// 				tmp = 0;
// 				while (arg[tmp])
// 					res[j++] = arg[tmp++];
// 			}
// 		}
// 		if (to_expand[i] == '\0')
// 			break;
// 		res[j] = to_expand[i];
// 		j++;
// 		i++;
// 	}
// 	res[j] = '\0';
// 	return (res);
// 	// don't forget to trim spaces before expanding
// }

// int main(int ac, char **av, char **env)
// {
//     t_env    *envl = NULL;
//     t_env    *tmp = NULL;
//     char    **argument = NULL;

//     (void)ac;
//     (void)av;
//     int i;

//     i = 0;
//     while (env[i])
//     {
//         t_env *new_env = malloc(sizeof(t_env));
//         if (!new_env)
//         {
//             perror("malloc");
//             exit(EXIT_FAILURE);
//         }
//         argument = ft_split(env[i], '=');
//         new_env->var = argument[1];
//         new_env->name = argument[0];
//         new_env->next = NULL;
//         if (envl == NULL)
//             envl = new_env;
//         else
//         {
//             tmp = envl;
//             while (tmp->next)
//                 tmp = tmp->next;
//             tmp->next = new_env;
//         }
//         i++;
//     }

// 	char **test = malloc(sizeof(char *) * 8);
// 	test[0] = ft_strdup("hello world");
// 	test[1] = ft_strdup("hello $USER !");
// 	test[2] = ft_strdup("$$	$		$$");
// 	test[3] = ft_strdup("$USER is the best   ");
// 	test[4] = ft_strdup("$USER & $USER");
// 	test[5] = ft_strdup("$$$$$$$");
// 	test[6] = ft_strdup("$is the best	$");
// 	test[7] = NULL;

// 	// for (int i = 0; test[i]; i++)
// 	// {
// 	// 	printf("[%s] => [%s]\n", test[i], ft_expand(test[i], envl));
// 	// 	usleep(400);
// 	// }
// 	char *curr = test[4];
// 	printf("[%s] => [%s]\n", curr, ft_expand(curr, envl));
// }

































// static void	ft_add_spaces_to_char(char *line, char *res, char c)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (line[i])
// 	{
// 		if (ft_isquote(line[i]) == 1)
// 		{
// 			res[j] = line[i];
// 			j++;
// 			i++;
// 			while (ft_isquote(line[i]) != 1)
// 				res[j++] = line[i++];
// 			res[j] = line[i];
// 			j++;
// 			i++;
// 		}
// 		else if (ft_isquote(line[i]) == 2)
// 		{
// 			res[j] = line[i];
// 			j++;
// 			i++;
// 			while (ft_isquote(line[i]) != 2)
// 				res[j++] = line[i++];
// 			res[j] = line[i];
// 			j++;
// 			i++;
// 		}
// 		else if (line[i] == c)
// 		{
// 			if (line[i + 1] && line[i] == c)
// 			{
// 				res[j++] = line[i++];
// 				res[j++] = line[i++];
// 			}
// 			else
// 			{
// 				res[j++] = ' ';
// 				res[j++] = line[i++];
// 				res[j++] = ' ';
// 			}
// 		} 
// 		else
// 			res[j++] = line[i++];
// 	}
// 	res[j] = '\0';
// }

// static void	ft_add_spaces_to_string(char *line, char *res, char *c)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (line[i])
// 	{
// 		if (ft_isquote(line[i]) == 1)
// 		{
// 			res[j] = line[i];
// 			j++;
// 			i++;
// 			while (ft_isquote(line[i]) != 1)
// 				res[j++] = line[i++];
// 			res[j] = line[i];
// 			j++;
// 			i++;
// 		}
// 		else if (ft_isquote(line[i]) == 2)
// 		{
// 			res[j] = line[i];
// 			j++;
// 			i++;
// 			while (ft_isquote(line[i]) != 2)
// 				res[j++] = line[i++];
// 			res[j] = line[i];
// 			j++;
// 			i++;
// 		}
// 		else if (line[i] == c[0])
// 		{
// 			res[j++] = ' ';
// 			res[j++] = line[i++];
// 			res[j++] = line[i++];
// 			res[j++] = ' ';
// 		} 
// 		else
// 			res[j++] = line[i++];
// 	}
// 	res[j] = '\0';
// }

// // free after using
// char	*ft_addspace_illegal_chars(char *line, char *token)
// {
// 	char	*res;
// 	int		to_add_spaces;
// 	int		i;
// 	int		new_size;

// 	to_add_spaces = ft_count_legal_char(line, token[0]) * 3;
// 	i = 0;
// 	new_size = ft_strlen(line) + to_add_spaces;
// 	res = malloc (sizeof(char) * (new_size + 2));
// 	if (!res)
// 		return (ft_printerror("malloc"), NULL);
// 	if (ft_strlen(token) == 1)
// 		ft_add_spaces_to_char(line, res, token[0]);
// 	else
// 		ft_add_spaces_to_string(line, res, token);
// 	return (res);
// }


// //////

// // remove the spaces/tabs form the bigg-end if str 
// char	*ft_trim_spaces(char *str)
// {
// 	char	*res;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	if (!str)
// 		return (NULL);
// 	j = ft_strlen(str) - 1;
// 	while (str[i] && ft_isspace(str[i]))
// 		i++;
// 	if (i == ft_strlen(str))
// 		return (NULL);
// 	while (ft_isspace(str[j]))
// 		j--;
// 	j = ft_strlen(str) - j - 1;
// 	res = ft_strldup(str + i, (ft_strlen(str) - i - j));
// 	if (!res)
// 		ft_printerror(MALLOC_ERORR);
// 	return (res);
// }

// static void	ft_replace_illegal_tab(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '"')
// 		{
// 			i++;
// 			while (line[i] && line[i] != '"')
// 				i++;
// 			continue ;
// 		}
// 		if (line[i] == '\'')
// 		{
// 			i++;
// 			while (line[i] && line[i] != '\'')
// 				i++;
// 			continue ;
// 		}
// 		if (ft_isspace(line[i]))
// 			line[i] = ' ';
// 		i++;
// 	}
// }
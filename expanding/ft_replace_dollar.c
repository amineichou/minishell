/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:17:59 by moichou           #+#    #+#             */
/*   Updated: 2024/04/19 14:39:06 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_env_list_serch_res(t_env *head, char *to_look)
{
	t_env	*tmp;

	if (!head)
		return (NULL);
	tmp = head;
	if (to_look[0] == '$')
		return (to_look);
	while(tmp)
	{
		if(ft_strcmp(tmp->name, to_look) == 0)
			return(ft_strdup(tmp->var));
		tmp = tmp->next;
	}
	return(NULL);
}

static char	*ft_get_to_look(char *str, int *i)
{
	char	*res;
	int		length;
	int		start;
	int		j;

	length = 0;
	start = *i;
	if (str[*i] == '$')
	{
		while (str[*i] && str[(*i) + 1] && str[(*i) + 1] == '$')
		{
			length++;
			(*i)++;
		}
		res = ft_strldup(&str[start], (length / 2) + 1);
		j = 0;
		while (res[j])
			res[j++] = '$';
		return (res);
	}
	else if (ft_isspace(str[*i]) || str[*i] == '\0')
		return (ft_strdup("$"));
	while (str[*i] && ft_is_alphanumeric(str[*i]))
	{
		(*i)++;
		length++;
	}
	return (ft_strldup(&str[start], length)); // TODO : protection
}

char	*ft_replace_dollar(char *to_expand, t_env *env)
{
	char	*res;
	char	*to_look;
	char	*looked_arg;
	char	*new_arg;
	int		i;
	int		start;

	i = 0;
	res = NULL;
	while (to_expand[i])
	{
		start = i;
		while (to_expand[i] && to_expand[i] != '$')
		{
			if (to_expand[i] && ft_isquote(to_expand[i]) == 1)
			{
				i++;
				while (to_expand[i] && ft_isquote(to_expand[i]) != 1)
					i++;
				i++;
				if (to_expand[i] == '\0')
					break;
			}
			else
				i++;
		}
		new_arg = ft_strldup(&to_expand[start], i - start);
		res = ft_strjoin(res, new_arg);
		if (to_expand[i] && to_expand[i] == '$')
		{
			i++;
			to_look = ft_get_to_look(to_expand, &i);
			looked_arg = ft_env_list_serch_res(env, to_look);
			res = ft_strjoin(res, looked_arg);
		}
		if (to_expand[i] == '\0')
			break;
	}
	return (res);
	// don't forget to trim spaces before expanding
}


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
// 	test[2] = ft_strdup("$$	$		$");
// 	test[3] = ft_strdup("$USER$USER is the best  but $'$USER' is better  ");
// 	test[4] = ft_strdup("amine $USER");
// 	test[5] = ft_strdup("$$$$$$$$$$USER");
// 	test[6] = ft_strdup("");
// 	test[7] = NULL;

// 	for (int i = 0; test[i]; i++)
// 		printf("[%s] => [%s]\n", test[i], ft_expand(test[i], envl));
// 	// char *curr = test[4];
// 	// printf("[%s] => [%s]\n", curr, ft_expand(curr, envl));
// }
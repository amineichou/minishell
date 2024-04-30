/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2024/04/19 10:17:59 by moichou           #+#    #+#             */
/*   Updated: 2024/04/30 15:35:01 by zyamli           ###   ########.fr       */
=======
/*   Created: 2024/04/30 15:51:03 by moichou           #+#    #+#             */
/*   Updated: 2024/04/30 15:51:05 by moichou          ###   ########.fr       */
>>>>>>> 8ce7cc708d70a6cd7bffa1fa6716828af5b4a666
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_env_list_serch_res(t_env *head, char *to_look)
{
	t_env	*tmp;

	if (!head || !to_look)
		return (NULL);
	tmp = head;
	while(tmp)
	{
		if(ft_strcmp(tmp->name, to_look) == 0)
			return(ft_strdup(tmp->var));
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*ft_get_to_look(char *str, int *i)
{
	char	*res;
	int		length;
	int		start;

	length = 0;
	start = *i;
	while (str[*i] && ft_is_alphanumeric(str[*i]))
	{
		(*i)++;
		length++;
	}
	res = ft_strldup(&str[start], length); // TODO : protection
	return (res);
}

static char	*ft_fill_arg(char *str, int *i, t_env *env, int ex_sta)
{
	char	*res;
	char	*to_look;
	int		start;

	(*i)++;
	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(ex_sta));
	}
	if (str[*i] == '\0' || !ft_is_alphanumeric(str[*i]))
		return (ft_strdup("$"));
	to_look = ft_get_to_look(str, i);
	res = ft_env_list_serch_res(env, to_look);
	return (res);
}

char	*ft_replace_dollar(char *str, t_env *env, int ex_sta)
{
	char	*res;
	int		i;
	int		start;

	res = NULL;
	i = 0;
	while (str[i])
	{
		start = i;
		while (str[i])
		{
			if (str[i] == '$')
			{
				if (start != i)
					res = ft_strjoin(res, ft_strldup(&str[start], i - start));
				break ;
			}
			i++;
			if (str[i] == '\0')
				res = ft_strjoin(res, ft_strldup(&str[start], i - start));
		}
		if (str[i] && str[i] == '$')
			res = ft_strjoin(res, ft_fill_arg(str, &i, env, ex_sta));
	}
	return (res);
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
// 		printf("[%s] => [%s]\n", test[i], ft_replace_dollar(test[i], envl));
// 	// char *curr = test[1];
// 	// printf("[%s] => [%s]\n", curr, ft_replace_dollar_env(curr, envl));
// }

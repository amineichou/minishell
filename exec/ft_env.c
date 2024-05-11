/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:54:51 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/11 15:45:45 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lst_size(t_toexec *head)
{
	int	i;
	t_toexec	*lst;

	i = 0;
	lst = head;

	if (!head)
		return (-1);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
int	env_size(t_env *head)
{
	int	i;
	t_env	*lst;

	i = 0;
	lst = head;

	if (!head)
		return (-1);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
char **env_tolist(t_env **env_list)
{
    int		size;
	int 	i;
	char	*tmp;
    t_env	*current;
	char	**result;

	if(!env_list || !*env_list)
		return(NULL);
	size = env_size(*env_list);
	current = (*env_list);
    result = (char **)zyalloc(sizeof(char *) * (size + 1), 'a', true);
	if (!result)
		return (perror("malloc"), NULL);
    i = 0;
    while (current != NULL)
	{
		tmp = ft_strjoin(current->name, "=", true);
		result[i] = ft_strjoin(tmp, current->var, true);
        current = current->next;
        i++;
    }
    result[i] = NULL;
    return (result);
}

int env_print(t_toexec *data)
{
	t_env *tmp;

	tmp = data->env;
	while(tmp)
	{
		if (tmp->name && tmp->var)
			printf("%s=%s\n", tmp->name, tmp->var);
		tmp = tmp->next;
	}
	// *(needs->ex_stat) = 0;
	return(1);
}

// char **env_tolist(t_env *env_list)
// {
//     int size = 0;
// 	char *tmp;
//     t_env *current = env_list;

//     while (current != NULL) 
// 	{
//         size++;
//         current = current->next;
//     }

//     char **result = (char **)malloc(sizeof(char *) * (size + 1));
//     current = env_list;
//     int i = 0;
//     while (current != NULL)
// 	{
//         int length = ft_strlen(current->name) + ft_strlen(current->var) + 2;
//         result[i] = (char *)malloc(length);
// 		tmp = ft_strjoin(current->name, "=");
// 		result[i] = ft_strjoin(tmp, current->var);
//         current = current->next;
//         i++;
//     }
//     result[size] = NULL;
//     return (result);
// }
// int main(int ac, char **av, char **env)
// {
// 	// t_env	*envi = NULL;
// 	// t_env	*tmp = NULL;
// 	// char	**arg = NULL;
// 	// t_toexec data;

// 	// (void)ac;
// 	// (void)av;
// 	// int i;

// 	// i = 0;
// 	// while (env[i])
// 	// {
// 	// 	t_env *new_env = malloc(sizeof(t_env));
// 	// 	if (!new_env)
// 	// 	{
// 	// 		perror("malloc");
// 	// 		exit(EXIT_FAILURE);
//     //     }
// 	// 	arg = ft_split(env[i], '=');
//     //     new_env->var = arg[1];
// 	// 	new_env->name = arg[0];
//     //     new_env->next = NULL;
//     //     if (envi == NULL)
//     //         envi = new_env;
// 	// 	else
// 	// 	{
// 	// 		tmp = envi;
//     //         while (tmp->next)
// 	// 			tmp = tmp->next;
// 	// 		tmp->next = new_env;
// 	// 	}
// 	// 	i++;
// 	// }
// 	// data.env = envi;
// 	env_print(&data);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:05:13 by zyamli            #+#    #+#             */
/*   Updated: 2024/03/17 22:23:19 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"
#include <string.h>

char *env_list_serch_res(t_env **head, char *to_look)
{
	t_env	*tmp;

	if (!*head) 
	{
		printf("Invalid data or data->env is NULL\n");
		return (0);
	}

	tmp = *head;
	while(tmp)
		{
			if(strcmp(tmp->name, to_look) == 0)
				return(tmp->var);
			tmp = tmp->next;
		}
		return(NULL);
}

int is_alphanumeric(char c)
{
	if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9' || c == '_')
		return(1);
	return(0);
}

char *expander(char *arg, t_env *env)
{
	int i;
	int b;
	char *to_look;
	char *expanded;
	i = 0;
	
	while(arg[i] != '$' && arg[i])
		i++;
	if(!arg[i])
		return(NULL);
	i++;
	b = i;
	if(arg[i] > '0' && arg[i] < '9')
		return(NULL);
	while(is_alphanumeric(arg[i]) && arg[i])
		i++;
	to_look = ft_substr(arg, b, i - b);
	expanded = env_list_serch_res(&env, to_look);
	if(!expanded)
		expanded = "";
	return(expanded);
}

char *add_expanded(char *arg, t_env *env)
{
	int i = 0;
	int b = 0;
	char *expanded;
	char *rest;
	char *tmp;
	while(1)
	{
		i = 0;
		while(arg[i] != '$' && arg[i])
			i++;
		tmp = ft_substr(arg, 0, i);
		i++;
		while(is_alphanumeric(arg[i]) && arg[i] || arg[i] == '?')
			i++;
			// printf("%d", i);
			// while(is_alphanumeric(arg[i]))
			// 	i++;
			expanded = expander(arg, env);
			if(!expanded)
				break;
			rest  = ft_substr(arg, i, ft_strlen(arg));
			expanded = ft_strjoin(tmp, expanded);
			arg = ft_strjoin(expanded, rest);
			// printf("%s", arg);
	}
	return (arg);
}

int main(int ac, char **av, char **env)
{
	t_env	*envi = NULL;
	t_env	*tmp = NULL;
	char	**arg = NULL;
	char	*expanded;
	t_toexec data;
	// data.env = NULL;

	(void)ac;
	// (void)av;
	int i;
	i = 0;
	while (env[i] != NULL)
	{
		t_env *new_env = malloc(sizeof(t_env));
		if (!new_env)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
        }
		arg = ft_split(env[i], '=');
        new_env->var = arg[1];
		// printf("%s", arg[0]);
		new_env->name = arg[0];
        new_env->next = NULL;
        if (envi == NULL)
            envi = new_env;
		else
		{
			tmp = envi;
            while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_env;
		}
		i++;
	}
	data.env = envi;
	expanded = add_expanded("$PATH garbege $USER garbedge $? two $_ hello good  $jyf luxk $LESS moo bich $ZSH", data.env);
	printf("%s", expanded);
}

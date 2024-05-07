/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:20:27 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/06 18:43:47 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include<string.h>

void lst_add(t_env **lst, t_env *new)
{
	t_env *lastone;

	if (!lst || !new)
		return;
	if (!(*lst))
	{
		*lst = new;
		return;
	}
	lastone = *lst;
	while (lastone->next)
		lastone = lastone->next;
	lastone->next = new;
	new->next = NULL;
}

t_env *env_new(char *var, char *name, bool to_free)
{
    t_env *newnode = (t_env *)zyalloc(sizeof(t_env), 'a', to_free);
    if (newnode == NULL)
	{
        perror("malloc");
        return(NULL);
    }
    newnode->var = ft_strdup(var, to_free);
    newnode->name = ft_strdup(name, to_free);
    newnode->next = NULL;
    return (newnode);
}


t_env *duplicate_list(t_env **head)
{
	if (head == NULL)
		return NULL;

	t_env *tmp = *head; 
	t_env *newlist = NULL;
	t_env *tmpnew = NULL;
	t_env *newnode;

	while (tmp != NULL)
	{
		// printf("%s====%s\n",tmp->name , tmp->var);
		newnode = env_new(tmp->var, tmp->name, true);
		if (newlist == NULL)
			newlist = newnode;
		else
			tmpnew->next = newnode;
		tmpnew = newnode;
		tmp = tmp->next;
	}
	return (newlist); 
}

void env_search_replace(t_env *head, char *to_replace, char *to_look)
{
	t_env	*tmp;

	if (!head) 
	{
		// printf("Invalid data or env is NULL\n");
		return;
	}
	// printf("%s= = =%s\n", to_replace, to_look);
	tmp = head;
	while(tmp)
		{
			if(ft_strcmp(tmp->name, to_look) == 0)
			{
				// free(tmp->var);
				// tmp->var = NULL;
				tmp->var = ft_strdup(to_replace, false);
				// free(to_replace);
				// to_replace = NULL;
				return;
			}
				
			tmp = tmp->next;
		}
		return;
}
int env_list_serch(t_env **head, char *to_look)
{
	t_env	*tmp;

	if (!(*head)) 
		return (0);
	tmp = *head;
	while(tmp)
		{
			if(ft_strcmp(tmp->name, to_look) == 0)
				return(1);

			tmp = tmp->next;
		}
		return(0);
}
void env_search_and_add(t_env *head, char *to_add, char *to_look)
{
	t_env	*tmp;

	if (!head) 
		return;

	tmp = head;
	while(tmp)
		{
			if(ft_strcmp(tmp->name, to_look) == 0)
			{
				tmp->var = ft_strjoin(tmp->var ,to_add, false);
				return;
			}
				
			tmp = tmp->next;
		}
	return;
}
// void env_print(t_toexec *data)
// {
//     t_env *tmp;

//     if (!data || !data->env) {
//         printf("Invalid data or data->env is NULL\n");
//         return;
//     }
	
//     tmp = data->env; // Initialize tmp to point to the first node of the linked list
//     while (tmp)
// 	{
//         printf("%s", tmp->name);
// 		if(tmp->var[0] != '\0')
//         	printf("=\"%s\"\n", tmp->var);
//         tmp = tmp->next;
//     }
// }
void export_env_print(t_toexec *data)
{
    t_env *tmp;

    if (!data || !data->env)
        return;
	
    tmp = data->env; // Initialize tmp to point to the first node of the linked list
    while (tmp) {
        printf("declare -x %s=", tmp->name);
		if(tmp->var)
        	printf("\"%s\"\n", tmp->var);
		else
			printf("\"\"\n");
        tmp = tmp->next;
    }
}

void swap(t_env *a, t_env *b)
{
    char	*temp_var;
    char	*temp_name;

	temp_var = a->var;
	temp_name = a->name;
    a->var = b->var;
    a->name = b->name;
    b->var = temp_var;
    b->name = temp_name;
}

void env_sort(t_env **start)
{
	int swapped;
	t_env *ptr1;
	t_env *lptr;

	lptr = NULL;
	if (start == NULL)
		return;
	while (1)
	{
		swapped = 0;
		ptr1 = *start;
		while (ptr1->next != lptr)
		{
			if (ft_strncmp(ptr1->name, ptr1->next->name,
				ft_strlen(ptr1->name) + ft_strlen(ptr1->next->name)) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		if (!swapped)
			break;
		lptr = ptr1;
	}
}

void ft_export(char *name, char *var, t_env *head, t_pipe *needs)
{
	t_toexec data;
	t_env *newnode;

	if (name == NULL)
	{
		needs->env_dup = duplicate_list(&head);
		env_sort(&needs->env_dup);
		data.env = needs->env_dup;
		
		export_env_print(&data);
		needs->env_dup = NULL;
	}
	else if (name && var && *var)
	{
		newnode = env_new(var, name, false);
		lst_add(&head ,newnode);
	}
	else if(var == NULL || *var == '\0')
	{
		newnode = env_new(var, name, false);
		if(!env_list_serch(&head, name))
			lst_add(&head ,newnode);
	}
}
char **split_env(char *arg, char c)
{
	int i;
	char **res;
	
	i = 0;
	res = zyalloc(sizeof(char *) * 3, 'a', false);
	while(arg[i] != c && arg[i])
		i++;
	if(arg[i] == c)
	{
		res[0] = ft_substr(arg, 0, i, false);
		res[1] = ft_substr(arg ,i + 1 , ft_strlen(arg), false);
		res[2] = NULL;
		return(res);
	}
	else
	{
		res[0] = arg;
		res[1] = NULL;
		return(res);
	}
	return(NULL);
}
int look_for(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void add_to_env(char *av, t_toexec *data,t_pipe *needs, char **to_add)
{
	if (env_list_serch(&data->env, to_add[0]))
	{
		if (ft_strstr(av, "+=") != NULL)
			env_search_and_add(data->env, ft_strdup(&to_add[1][1], false), ft_strdup(to_add[0], false));
		else if (ft_strstr(av, "=") != NULL)
			env_search_replace(data->env, ft_strdup(to_add[1], false), ft_strdup(to_add[0], false));
		else
			ft_export(ft_strdup(av, false), NULL, data->env, needs);
	}
	else if (!env_list_serch(&data->env, to_add[0]))
	{
		if (ft_strstr(av, "+=") != NULL)
			ft_export(ft_strdup(to_add[0], false), ft_strdup(&to_add[1][1], false),data->env, needs);
		else
			ft_export(ft_strdup(to_add[0], false), ft_strdup(to_add[1], false),data->env, needs);
	}	
}

void exporter(char *av, t_toexec *data,t_pipe *needs)
{
	char **to_add;

	if (av == NULL || ft_strstr(av, "-p") != NULL)
	{
		ft_export(NULL, NULL, data->env, needs);
		return ;
	}
	if (ft_strstr(av, "+=") != NULL)
		to_add = split_env(av, '+');
	else
		to_add = split_env(av, '=');
	add_to_env(av, data, needs, to_add);
}

int check_ifvalid(char *cmd)
{
	int i;

	i = 0;
	if (cmd[0] == '=' || ft_isdigit(cmd[0]))
		return (0);
	while (cmd[i])
	{
		if (cmd[i] == '+' || cmd[i] == '=')
			break ;
		if (!ft_is_alphanumeric(cmd[i]))
			return (0);
		i++;
	}
	if (cmd[i] == '+' && cmd[i + 1] != '=')
		return (0);
	return (1);
}

int ft_exporter(t_toexec *cmd, t_pipe *needs)
{
	int k;
	
	k = 1;
	if(!cmd->args[k])
		exporter(cmd->args[k], cmd, needs);
	while(cmd->args[k])
	{
		if(!check_ifvalid(cmd->args[k]))
			{
				ft_putstr_fd("minishell: export: ",2);
				ft_putstr_fd(cmd->args[k],2);
				ft_putstr_fd(" : not a valid identifier\n",2);
				*(needs->ex_stat) = 1;
				ft_set_status(*(needs->ex_stat), 1);
				k++;
				continue;
			}
		exporter(cmd->args[k], cmd, needs);
		k++;
	}
	return (1);
}


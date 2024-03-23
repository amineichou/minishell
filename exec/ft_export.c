/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:20:27 by zyamli            #+#    #+#             */
/*   Updated: 2024/03/22 03:20:28 by zyamli           ###   ########.fr       */
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

t_env *env_new(char *var, char *name)
{
    t_env *newnode = (t_env *)malloc(sizeof(t_env));
    if (newnode == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    newnode->var = ft_strdup(var);
    newnode->name = ft_strdup(name);
    newnode->next = NULL;
    return newnode;
}


t_env *duplicate_list(t_env *head)
{
	if (head == NULL)
		return NULL;

	t_env *tmp = head; 
	t_env *newlist = NULL;
	t_env *tmpnew = NULL;
	t_env *newnode;

	while (tmp != NULL)
	{
		// printf("%s====%s\n",tmp->name , tmp->var);
		newnode = env_new(tmp->var, tmp->name);
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
		printf("Invalid data or data->env is NULL\n");
		return;
	}

	tmp = head;
	while(tmp)
		{
			if(ft_strcmp(tmp->name, to_look) == 0)
			{
				tmp->var = ft_strdup(to_replace);
				return;
			}
				
			tmp = tmp->next;
		}
		return;
}
int env_list_serch(t_env **head, char *to_look)
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
	{
		printf("Invalid data or data->env is NULL\n");
		return;
	}

	tmp = head;
	while(tmp)
		{
			if(ft_strcmp(tmp->name, to_look) == 0)
			{
				// printf("{%s}", tmp->next->name);
				
				tmp->var = ft_strjoin(tmp->var ,to_add);
				return;
			}
				
			tmp = tmp->next;
		}
		return;
}
void env_print(t_toexec *data)
{
    t_env *tmp;

    if (!data || !data->env) {
        printf("Invalid data or data->env is NULL\n");
        return;
    }
	
    tmp = data->env; // Initialize tmp to point to the first node of the linked list
    while (tmp)
	{
        printf("%s", tmp->name);
		if(tmp->var[0] != '\0')
        	printf("=\"%s\"\n", tmp->var);
        tmp = tmp->next;
    }
}
void export_env_print(t_toexec *data)
{
    t_env *tmp;

    if (!data || !data->env) {
        printf("Invalid data or data->env is NULL\n");
        return;
    }
	
    tmp = data->env; // Initialize tmp to point to the first node of the linked list
    while (tmp) {
        printf("declare -x %s=", tmp->name);
        printf("\"%s\"\n", tmp->var);
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

void env_sort(t_env *start)
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
		ptr1 = start;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->name, ptr1->next->name) > 0)
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

void ft_export(char *name, char *var, t_env *head)
{
	t_toexec data;
	t_env *exported_env = duplicate_list(head);
	t_env *newnode;
		// printf("{%s .   %s}\n",head->var, head->next->var);
	if (name == NULL)
	{
		// printf("{{{{{{hello}}}}}}\n");
		env_sort(exported_env);
		data.env = exported_env;
		export_env_print(&data);

	}
	else if (name && var)
	{
		// printf("{%s .   %s}\n",head->var, head->next->var);
		newnode = env_new(var, name);
		lst_add(&head ,newnode);
		lst_add(&exported_env ,newnode);
	}
	// else
	// {
	// 	newnode = env_new(var, name);
	// 	lst_add(&exported_env ,newnode);
		
	// }
	data.env = exported_env;	
	env_print(&data);
}
char **split_env(char *arg)
{
	int i;
	char **res = malloc(sizeof(char *) * 3);
	
	i = 0;
	while(arg[i] != '=' && arg[i])
		i++;
	if(arg[i] == '=')
	{
		res[0] = ft_substr(arg, 0, i);
		res[1] = ft_substr(arg ,i + 1 , ft_strlen(arg));
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

void exporter(char *av, t_toexec *data)
{

	// env_print(&data);
	// printf("FGhfgh\n");
	// printf("%s--------------------------------------\n", data.env->var);

	char **to_add;

	if(av == NULL || ft_strstr(av, "-p") != NULL)
	{
		ft_export(NULL, NULL, data->env);
		return ;
	}
	if(ft_strstr(av, "=") == NULL)
	{
		ft_export(av, "", data->env);
		return ;
	}
	if(ft_strstr(av, "+=") != NULL)
	{
		to_add = ft_split(av, '+');
	}
	else
	{
		to_add = split_env(av);
	}
	
	if(env_list_serch(&data->env, to_add[0]))
	{
		if(ft_strstr(av, "+=") != NULL)
		{
			env_search_and_add(data->env, &to_add[1][1], to_add[0]);
		}
		else if(ft_strstr(av, "=") != NULL)
		{
			env_search_replace(data->env, to_add[1], to_add[0]);
			// printf("{%s . %s}\n", to_replace[1], to_replace[0]);
		}
		else
			ft_export(av, "", data->env);
	}
	else if(!env_list_serch(&data->env, to_add[0]))
	{

		if(ft_strstr(av, "+=") != NULL)
		{
			ft_export(to_add[0], &to_add[1][1],data->env);
		}
		else if(ft_strstr(av, "=") != NULL)
		{
			ft_export(to_add[0], to_add[1],data->env);
		}
	}	
}
int main(int ac, char **av, char **env)
{
		t_env	*envi = NULL;
	t_env	*tmp = NULL;
	char	**arg = NULL;
	t_toexec data;
	// data.env = NULL;

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
	int k = 1;
	while(av[k])
	{
		exporter(av[k], &data);
		k++;
	}
	env_print(&data);
}


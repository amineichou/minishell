/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:20:27 by zyamli            #+#    #+#             */
/*   Updated: 2024/03/11 14:27:53 by zyamli           ###   ########.fr       */
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

t_env *env_new(char *var, char *name) {
    t_env *newnode = (t_env *)malloc(sizeof(t_env));
    if (newnode == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    newnode->var = strdup(var);
    newnode->name = strdup(name);
    newnode->next = NULL;
    return newnode;
}


t_env *duplicate_list(t_env *head)
{
	if (head == NULL)
	{
		return NULL;
	}

	t_env *tmp = head; 
	t_env *newlist = NULL;
	t_env *tmpnew = NULL;
	t_env *newnode;

	while (tmp != NULL)
	{
		printf("%s====%s\n",tmp->name , tmp->var);
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

void swap(t_env *a, t_env *b) 
{
    char *temp = a->var;
    a->var = b->var;
    b->var = temp;
	char *temp1 = a->name;
	a->name = b->name;
	b->name = temp1;
}
void env_print(t_toexec *data) {
    t_env *tmp;

    if (!data || !data->env) {
        printf("Invalid data or data->env is NULL\n");
        return;
    }
	
    tmp = data->env; // Initialize tmp to point to the first node of the linked list
    while (tmp) {
        printf("%s=", tmp->name);
        printf("\"%s\"\n", tmp->var);
        tmp = tmp->next;
    }
}

// void env_export(t_env *head)
// {
// 	int swapped;
//     t_env *tmp;
//     t_env *cur = NULL;

//     /* Checking for empty list */
//     if (head == NULL)
//         return;

//     while (1)
// 	{
//         swapped = 0;
//         tmp = head;

//         while (tmp->next != cur)
// 		{
//             if (strcmp(tmp->var, tmp->next->var) > 0)
// 			{
// 						// printf("hna\n");
//                 swap(tmp, tmp->next);
//                 swapped = 1;
//             }
//             tmp = tmp->next;
//         }

//         if (!swapped)
//             break;

//         cur = tmp;
//     }
	
// }
void ft_export(char *name, char *var, t_env *head)
{
	t_toexec data;
	t_env *exported_env = duplicate_list(head);
	t_env *newnode;
		// printf("{%s .   %s}\n",head->var, head->next->var);
	if (name == NULL)
	{
		// env_export(exported_env);
		data.env = exported_env;
		env_print(&data);

	}
	else
	{
		// printf("{%s .   %s}\n",head->var, head->next->var);
		newnode = env_new(var, name);
		lst_add(&head ,newnode);
		lst_add(&exported_env ,newnode);
	}


}

int main(int ac, char **av, char **env)
{
	t_env	*envi = NULL;
	t_env	*tmp = NULL;
	char	**arg =NULL;
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
	// env_print(&data);
	// printf("FGhfgh\n");
	// printf("%s--------------------------------------\n", data.env->var);
	ft_export("a", "zbizi",data.env);
	env_print(&data);
	env_print(&data);
	// printf("%s", data.env->var);
}
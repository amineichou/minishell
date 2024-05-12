/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:20:27 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/12 17:05:44 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(char *name, char *var, t_env **head, t_pipe *needs)
{
	t_toexec	data;
	t_env		*newnode;

	if (name == NULL)
	{
		if (!*head)
			return ;
		needs->env_dup = duplicate_list(head);
		env_sort(&needs->env_dup);
		data.env = needs->env_dup;
		export_env_print(&data);
		needs->env_dup = NULL;
	}
	else if (name && var && *var)
	{
		newnode = env_new(var, name, false);
		lst_add(head, newnode);
	}
	else if (var == NULL || *var == '\0')
	{
		newnode = env_new(var, name, false);
		if (!env_list_serch(head, name))
			lst_add(head, newnode);
	}
}

void	add_to_env(char *av, t_toexec *data, t_pipe *needs, char **to_add)
{
	if (env_list_serch(&data->env, to_add[0]))
	{
		if (ft_strstr(av, "+=") != NULL)
			env_search_and_add(data->env, ft_strdup(&to_add[1][1], false),
				ft_strdup(to_add[0], false));
		else if (ft_strstr(av, "=") != NULL)
			env_search_replace(data->env, ft_strdup(to_add[1], false),
				ft_strdup(to_add[0], false));
		else
			ft_export(ft_strdup(av, false), NULL, &data->env, needs);
	}
	else if (!env_list_serch(&data->env, to_add[0]))
	{
		if (ft_strstr(av, "+=") != NULL)
			ft_export(ft_strdup(to_add[0], false),
				ft_strdup(&to_add[1][1], false), &data->env, needs);
		else
			ft_export(ft_strdup(to_add[0], false),
				ft_strdup(to_add[1], false), &data->env, needs);
	}
}

void	exporter(char *av, t_toexec *data, t_pipe *needs)
{
	char	**to_add;
	int		i;

	i = 0;
	if (av == NULL || ft_strstr(av, "-p") != NULL)
	{
		ft_export(NULL, NULL, &data->env, needs);
		return ;
	}
	if (ft_strstr(av, "+=") != NULL)
	{
		while (av[i] != '+')
			i++;
		if (av[i - 1] == '=')
			to_add = split_env(av, '=');
		else
			to_add = split_env(av, '+');
	}
	else
		to_add = split_env(av, '=');
	add_to_env(av, data, needs, to_add);
}

int	check_ifvalid(char *cmd)
{
	int	i;

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

int	ft_exporter(t_toexec *cmd, t_pipe *needs)
{
	int	k;

	k = 1;
	if (!cmd->args[k])
		exporter(cmd->args[k], cmd, needs);
	while (cmd->args[k])
	{
		if (!check_ifvalid(cmd->args[k]))
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(cmd->args[k], 2);
			ft_putstr_fd(" : not a valid identifier\n", 2);
			*(needs->ex_stat) = 1;
			ft_set_status(*(needs->ex_stat), 1);
			k++;
			continue ;
		}
		exporter(cmd->args[k], cmd, needs);
		k++;
	}
	return (1);
}

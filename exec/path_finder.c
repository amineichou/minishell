/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:16:17 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/11 15:30:12 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_commands(char *av, char **pathes)
{
	char	*result;
	char	*path;
	int		i;

	if (ft_strchr(av, '/') != 0)
	{
		result = ft_strdup(av, true);
		return (result);
	}
	path = ft_strjoin("/", av, true);
	i = 0;
	while (pathes[i])
	{
		result = ft_strjoin(pathes[i], path, true);
		if (access(result, F_OK | X_OK) == 0)
		{
			return (result);
		}
		i++;
		result = NULL;
	}
	return (NULL);
}

static char	**extract_paths(char **env)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 4) == 0)
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char *env[])
{
	char	**to_look;
	char	*path;

	if (!env || !*env)
		return (NULL);
	to_look = extract_paths(env);
	if (!to_look || !*to_look)
		return (NULL);
	path = find_commands(cmd, to_look);
	if (!path)
		return (NULL);
	return (path);
}

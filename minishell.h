/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:11 by moichou           #+#    #+#             */
/*   Updated: 2024/03/06 14:58:40 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>


typedef struct s_env {
	char			*var;
	struct s_env	*next;
} t_env;

// parsing
typedef struct s_token {
	int				input;
	int				output;
	char			**args;
	t_env 			*env;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;




t_token	ft_parsing(char *line);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:11 by moichou           #+#    #+#             */
/*   Updated: 2024/03/11 17:35:05 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>


typedef struct s_env {
	char			*var;
	struct s_env	*next;
}	t_env;

typedef struct  s_toexec {
	int					input;
	int					output;
	char				**args;
	t_env 				*env;
	struct  s_toexec	*next;
	struct  s_toexec	*prev;
}	t_toexec;

enum token {
	WORD,
	PIPE,
	AP,
	RP,
	RD_IN,
	RD_OUT, 
	BRACET_LEFT,
	BRAKET_WRITE,
};

// parsing
// synthax sanitizer
int		ft_sanitizer(char *line);
int		ft_sanitize_pipes(char *line);
int		ft_sanitize_double_quotes(char *line);

// utils
void	ft_printerror(char *str);
char	*ft_remove_un_spaces(char *str);

#endif
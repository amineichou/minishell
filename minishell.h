/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:11 by moichou           #+#    #+#             */
/*   Updated: 2024/03/06 22:26:58 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>


typedef struct s_env {
	char			*var;
	struct s_env	*next;
} t_env;

// lexing
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

// lexing
t_toexec	*ft_tokenization(char *line);

// handlers
// token_1
int	ft_handle_pipe(char *line, int index);

// error hanling
void	ft_printerror(char *str);

#endif
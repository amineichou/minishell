/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:11 by moichou           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/06 20:55:51 by zyamli           ###   ########.fr       */
=======
/*   Updated: 2024/03/06 22:26:58 by moichou          ###   ########.fr       */
>>>>>>> 64342c4d2c6e4e1b244394994bc38bf9afec8abd
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
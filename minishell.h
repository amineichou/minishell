/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:11 by moichou           #+#    #+#             */
/*   Updated: 2024/03/17 02:39:30 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

typedef struct s_env {
	char			*var;
	struct s_env	*next;
}	t_env;

typedef struct  s_toexec {
	int					input;
	int					output;
	char				*cmd;
	char				**args;
	t_env 				*env;
	struct  s_toexec	*next;
	struct  s_toexec	*prev;
}	t_toexec;

typedef enum token {
	WORD,
	PIPE,
	AP,
	RP,
	RD_IN,
	RD_OUT, 
	BRACET_LEFT,
	BRAKET_WRITE,
}	token;

typedef struct s_token {
	token token;
	char	*value;
	struct s_token	*next;
}	t_token;

// synthax sanitizer
char		*ft_sanitizer(char *line);
int			ft_sanitize_pipes(char *line);
int			ft_sanitize_quotes(char *line);
int			ft_sanitize_redirections(char *line);
void		ft_sanitize_spaces(char *line);

// analyser
t_toexec	*ft_analyser(char *sanitize_result);

// utils
int			ft_strlen(char *str);
char		**ft_split(char const *s, char c);
void		ft_printerror(char *msg);
int			ft_count_legal_char(char *line, char c);

// struct tools
void		ft_append_node(t_toexec *head, t_toexec *node);
t_toexec	*ft_create_node(char *cmd, char **args);

// libft
char		*ft_strdup(char *s1);
char		*ft_strchr(char *s, int c);
int			ft_strlen(char *str);
int			ft_isspace(char c);
int			ft_strcmp(char *s1, char *s2);
void		ft_strcpy(char *dst, char *src, size_t dstsize);

// signal hanldler
void		ft_sigkill_handler(int signum);

#endif
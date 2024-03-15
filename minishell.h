/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:11 by moichou           #+#    #+#             */
/*   Updated: 2024/03/15 18:35:07 by moichou          ###   ########.fr       */
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

// synthax sanitizer
char		**ft_sanitizer(char *line);
int			ft_sanitize_pipes(char *line);
int			ft_sanitize_quotes(char *line);
int			ft_sanitize_redirections(char *line);
char		**ft_sanitize_spaces(char *line);
void		ft_replace_illegal_tab(char *line);
char		*ft_addspace_illegal_pipe(char *line);

// analyser
t_toexec	*ft_analyser(char **args);

// utils
int			ft_strlen(char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		**ft_split(char const *s, char c);
void		ft_trim_spaces(char *str);
void		ft_printerror(char *msg);
int			ft_count_legal_char(char *line, char c);
char		*ft_get_word(char *str);

// struct tools
t_toexec	*ft_create_node(char *cmd, char **args);
void		ft_append_node(t_toexec *head, t_toexec *node);

// libft
char		*ft_strdup(char *s1);
char		*ft_strchr(char *s, int c);
int			ft_strlen(char *str);
int			ft_isspace(char c);
int			ft_strcmp(char *s1, char *s2);

// signal hanldler
void		ft_sigkill_handler(int signum);

#endif
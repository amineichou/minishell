/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:11 by moichou           #+#    #+#             */
/*   Updated: 2024/03/23 01:20:31 by moichou          ###   ########.fr       */
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
#include <fcntl.h>

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

typedef enum token {
	WORD,
	PIPE,
	RD_AP,
	RD_RP,
	RD_IN,
	RD_OUT,
	HEREDOC,
}	token;

typedef struct s_token {
	token 	token;
	char	*value;
	int		order;
	struct s_token	*next;
}	t_token;

// #define malloc(x) NULL

// synthax sanitizer
char		*ft_sanitizer(char *line);
int			ft_sanitize_pipes(char *line);
int			ft_sanitize_quotes(char *line);
int			ft_sanitize_redirections(char *line);
void		ft_sanitize_spaces(char *line);
char		*ft_trim_spaces(char *str); // TODO : move it to tools
void		ft_handle_redirections(t_token *lst_token, t_toexec **node);

// analyser
t_toexec	*ft_analyser(char *sanitize_result);
t_token		*ft_analyse_tokens(char *sanitize_result);

// utils
int			ft_strlen(char *str);
char		**ft_split(char const *s, char c);
void		ft_printerror(char *msg);
int			ft_count_legal_char(char *line, char c);
char		*ft_strlrdup(char *s1, int lenght);
int			ft_isspecialchars(char c);
int			ft_isquote(char c);

// tools
t_toexec	*ft_create_node(char *cmd, char **args);
void		ft_append_node_t_token(t_token **head, t_token *node);
void		ft_append_node_t_toexec(t_toexec **head, t_toexec *node);

// libft
char		*ft_strdup(char *s1);
char		*ft_strchr(char *s, int c);
int			ft_strlen(char *str);
int			ft_isspace(char c);
int			ft_strcmp(char *s1, char *s2);
void		ft_strcpy(char *dst, char *src, size_t dstsize);

// signal hanldler
void		ft_sigkill_handler(int signum);

// tests start
void test_tokens(t_token *lst_token_input);
void	test_lst(t_toexec *lst);
// test end

#endif
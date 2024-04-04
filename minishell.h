/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:11 by moichou           #+#    #+#             */
/*   Updated: 2024/04/04 23:07:57 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "readline/history.h"
#include "readline/readline.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>


// errors handling
#define MALLOC_ERORR "allocation failed\n"
#define SYNTAX_ERROR_PIPE "syntax error near unexpected token `|'\n"
#define SYNTAX_ERROR_QUOTE "syntax error missing quote\n"
#define SYNTAX_ERROR_REDIRECTION "syntax error near unexpected token `>'\n"
#define SYNTAX_ERROR_REDIRECTION_2 "syntax error near unexpected token `>>'\n"
#define FILE_D_ERROR_FAIL "faild to open fd\n"

typedef struct s_env {
	char			*var;
	char			*name;
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

typedef struct t_pipe
{
	int		i;
	int		*ex_stat;
	int		fd[2];
	int		save_fd_in;
	int		save_fd_out;
	int		infile;
	int		outfile;
	int		j;
	char	*path;
	char	**cmd;
	char	*limiter;
	t_env	*env_dup;
	char	**env;
	int		*pids;
	int		p;
}	t_pipe;

typedef enum token {
	WORD,
	PIPE,
	RD_AP, // >>
	RD_RP, // >
	RD_IN, // <
	RD_OUT, 
	HEREDOC, // <<
	HEREDOC_E, // <<
	HEREDOC_O, // <<
}	token;

typedef struct s_token {
	token 	token;
	char	*value;
	int		order;
	struct s_token	*next;
}	t_token;

// #define malloc(x) NULL

// START FUNCTION
t_toexec	*ft_parser(char *line);

// synthax sanitizer
char		*ft_sanitizer(char *line);
int			ft_sanitize_pipes(char *line);
int			ft_sanitize_quotes(char *line);
int			ft_sanitize_redirections(char *line);
char		*ft_trim_spaces(char *str); // TODO : move it to tools
char		*ft_addspace_illegal_chars(char *line, char *token);
void		ft_handle_redirections(t_token **lst_token, t_toexec *node);

// analyser
t_toexec	*ft_analyser(char *sanitize_result);
t_token		*ft_make_tokens(char *sanitize_result);
int			ft_check_valid_tokens(t_token *lst_token);


// expanding
char		*ft_expand(char *to_expand, t_env *env);

// utils
int			ft_strlen(char *str);
char		**ft_split(char *s, char c);
void		ft_printerror(char *msg);
int			ft_count_legal_char(char *line, char c);
char		*ft_strldup(char *s1, int lenght);
int			ft_isspecialchars(char c);
int			ft_isquote(char c);

// tools
t_toexec	*ft_create_node(char *cmd, char **args);
void		ft_append_node_t_token(t_token **head, t_token *node);
void		ft_append_node_t_toexec(t_toexec **head, t_toexec *node);
// 1
char		*ft_remove_qoutes(char *str);
void		ft_skip_quotes(char *str, int *i);
int			ft_isredirection(char c);

// libft
char		*ft_strdup(char *s1);
char		*ft_strchr(char *s, int c);
int			ft_isspace(char c);
int			ft_isdigit(char c);
int			ft_strcmp(char *s1, char *s2);
void		ft_strcpy(char *dst, char *src, size_t dstsize);
int			ft_is_alphanumeric(char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_print_error(char *str);
char* ft_strstr(const char* haystack, const char* needle);
char	*ft_substr(char *s, unsigned int start, size_t len);
char *ft_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	**free_leaks(char **strs);
int	ft_atoi(const char *str);

// signal hanldler
void		ft_sigkill_handler(int signum);

// tests start
void test_tokens(t_token *lst_token_input);
void	test_lst(t_toexec *lst);
// test end
void executer(t_toexec *cmds, t_pipe *needs);
int ft_cd (char *dir, t_env *env, t_pipe *needs);
int ft_echo(t_toexec *cmd);
int env_print(t_toexec *data);
int ft_exporter(t_toexec *cmd, t_pipe *needs);
int ft_pwd(void);
int unseter(t_toexec *cmd, t_pipe *needs);
t_env *duplicate_list(t_env *head);
void ft_export(char *name, char *var, t_env *head, t_pipe *needs);
void env_search_replace(t_env *head, char *to_replace, char *to_look);
int env_list_serch(t_env **head, char *to_look);
void ft_unset(t_env **env, char *to_del);
int ft_exit(char **args);
#endif
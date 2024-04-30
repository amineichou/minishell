/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:11 by moichou           #+#    #+#             */
/*   Updated: 2024/04/30 18:43:50 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "readline/readline.h"
#include "readline/history.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/wait.h>

extern int g_inexec;

#define MALLOC_ERORR "allocation failed\n"
#define SYNTAX_ERROR_PIPE "syntax error near unexpected token `|'\n"
#define SYNTAX_ERROR_QUOTE "syntax error missing quote\n"
#define SYNTAX_ERROR_REDIRECTION "syntax error near unexpected token `>'\n"
#define SYNTAX_ERROR_REDIRECTION_2 "syntax error near unexpected token `>>'\n"
#define FILE_D_ERROR_FAIL "faild to open fd\n"

typedef struct s_expand {
	bool			is_expand;
	char			*value;
	struct s_expand	*next;
}	t_expand;

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
	struct s_toexec	*next;
	struct s_toexec	*prev;
}	t_toexec;

typedef struct t_pipe
{
	int		i;
	int		ex_stat[1];
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
	struct termios term;
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

typedef struct s_herdoc {
	char			*del;
	bool			is_expand;
	struct s_herdoc	*next;
}	t_herdoc;

// #define malloc(x) NULL

// START FUNCTION
t_toexec	*ft_parser(char *line, t_env *envl, int ex_sta);

// syntax sanitizer
t_toexec	*ft_sanitizer(char *line, t_env *env, int ex_sta);
int			ft_sanitize_pipes(char *line, int *where);
int			ft_sanitize_quotes(char *line, int *where);
int			ft_sanitize_redirections(char *line, int *where);
char		*ft_trim_spaces(char *str); // TODO : move it to tools
void		ft_handle_redirections(t_token **lst_token, t_toexec *node);

// analyser
t_toexec	*ft_analyser(char *sanitize_result, t_env *envl, int ex_sta);
t_token		*ft_make_tokens(char *sanitize_result);

// expanding
void		ft_expand(t_token *lst_token, t_env *envl, int ex_sta);
char		*ft_replace_dollar(char *to_expand, t_env *env, int ex_sta);
char		*ft_remove_qoutes(char *str);

// herdoc
// void	ft_open_herdoc(t_token **lst_token, t_pipe *needs, t_env *env);
void	ft_heredoc_handler_exec(t_toexec *node, t_herdoc *herdoc_node, int ex_sta);
void	ft_heredoc_handler_syn(t_env *env, char *delemiter);


// utils
int			ft_strlen(char *str);
char		**ft_split(char *s, char c);
void		ft_printerror(char *msg);
void		ft_put_syntaxerror(char *msg, char c);
int			ft_count_legal_char(char *line, char c);
char		*ft_strldup(char *s1, int lenght);
int			ft_isspecialchars(char c);
int			ft_isquote(char c);

// tools
t_toexec	*ft_create_node(char *cmd, char **args);
t_expand	*ft_create_expand_node(char *str);
t_herdoc	*ft_create_herdoc_node(char *del);
void		ft_append_node_herdoc(t_herdoc **head, t_herdoc *node);
void		ft_append_node_t_token(t_token **head, t_token *node);
void		ft_append_node_t_toexec(t_toexec **head, t_toexec *node);
void		ft_append_node_expand(t_expand **head, t_expand *node);
void		ft_pop_node_t_token(t_token **head, t_token *to_pop);
// 1
// char		*ft_remove_qoutes(char *str);
void		ft_skip_quotes(char *str, int *i);
int			ft_isredirection(char c);
char		*ft_get_inside_quotes(char *in_quotes, int *i, char q_type);

// libft
char		*ft_strdup(char *s1);
char		*ft_strchr(char *s, int c);
int			ft_isspace(char c);
int			ft_isdigit(char c);
int			ft_strcmp(char *s1, char *s2);
void		ft_strcpy(char *dst, char *src, size_t dstsize);
int			ft_is_alphanumeric(char c);
char		*ft_itoa(int n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr(char *s);
void	ft_print_error(char *str);
char* ft_strstr(const char* haystack, const char* needle);
char	*ft_substr(char *s, int start, int len);
char *ft_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	**free_leaks(char **strs);
int	ft_atoi(const char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void freeList(t_env **head);

// free leaks
void		ft_free_toexec(t_toexec *head);
void		ft_free_args(char **args);
void		ft_free_token(t_token *head);

// signal hanldler
void		ft_sigkill_handler(int signum);
void		ft_sigquit_handler(int signum);
int	ft_update_status(int status, struct termios *term);

// tests start
void test_tokens(t_token *lst_token_input);
void	test_lst(t_toexec *lst);
void	printf_test(char *str);
// test end
void executer(t_toexec *cmds, t_pipe *needs);
int ft_cd (char *dir, t_env *env, t_pipe *needs);
int ft_echo(t_toexec *cmd, t_pipe *needs);
int env_print(t_toexec *data, t_pipe *needs);
int ft_exporter(t_toexec *cmd, t_pipe *needs);
int ft_pwd(t_pipe *needs);
int unseter(t_toexec *cmd, t_pipe *needs);
t_env *duplicate_list(t_env **head);
void ft_export(char *name, char *var, t_env *head, t_pipe *needs);
void env_search_replace(t_env *head, char *to_replace, char *to_look);
int env_list_serch(t_env **head, char *to_look);
void ft_unset(t_env **env, char *to_del);
int ft_exit(char **args);
char	*ft_env_list_serch_res(t_env *head, char *to_look);
#endif

// 'something''something'
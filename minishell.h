/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:05:44 by moichou           #+#    #+#             */
/*   Updated: 2024/05/19 15:12:31 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/wait.h>
# include <limits.h>

int	g_inexec;

# define MALLOC_ERORR "allocation failed\n"
# define SYNTAX_ERROR_PIPE "syntax error near unexpected token `|'\n"
# define SYNTAX_ERROR_QUOTE "syntax error missing quote\n"
# define SYNTAX_ERROR_REDIRECTION "syntax error near unexpected token `>'\n"
# define SYNTAX_ERROR_REDIRECTION_2 "syntax error near unexpected token `>>'\n"
# define FILE_D_ERROR_FAIL "faild to open fd\n"

typedef struct s_expand
{
	bool			is_expand;
	char			*value;
	struct s_expand	*next;
}	t_expand;

typedef struct s_env
{
	char			*var;
	char			*name;
	struct s_env	*next;
}	t_env;

typedef struct s_toexec
{
	int					input;
	int					output;
	char				**args;
	t_env				*env;
	struct s_toexec		*next;
	struct s_toexec		*prev;
}	t_toexec;

typedef struct t_pipe
{
	int				i;
	int				p;
	int				size;
	int				step;
	int				ex_stat[1];
	int				fd[2];
	int				save_fd_in;
	int				save_fd_out;
	int				infile;
	int				outfile;
	char			*path;
	t_env			*env_dup;
	char			**env;
	int				*pids;
	struct termios	term;
}	t_pipe;

typedef enum tokenenm
{
	WORD,
	PIPE,
	RD_AP, // >>
	RD_RP, // >
	RD_IN, // <
	HEREDOC, // <<
}	t_tokenenm;

typedef struct s_token
{
	t_tokenenm			token;
	char				*value;
	int					order;
	struct s_token		*next;
}	t_token;

typedef struct s_herdoc
{
	char			*del;
	bool			is_expand;
	struct s_herdoc	*next;
}	t_herdoc;

typedef struct s_garbage
{
	void				*adr;
	bool				is_free;
	struct s_garbage	*next;
}	t_garbage;

// #define malloc(x) NULL

// START FUNCTION
t_toexec	*ft_parser(char *line, t_env *envl);

// syntax_error
int			ft_check_syntax_error(char *line, int *where);

// syntax sanitizer
char		*ft_trim_spaces(char *str); // TODO : move it to tools
void		ft_handle_redirections(t_token **lst_token, t_toexec *node);
void		ft_set_default_vals(t_toexec *node, t_env *envl);
int			ft_init_syntax_error_vals(int *i, char *line, int *where);
// analyser
t_toexec	*ft_analyser(char *sanitize_result, t_env *envl);
t_token		*ft_make_tokens(char *sanitize_result);
void		ft_handle_args(t_toexec **node, t_token **lst_token);
// analyser tools
char		**ft_reallocate_copy(char **old_res, char *new);
int			ft_hnadle_herdoc(t_token **lst_token, t_toexec *node);
bool		ft_isexpand_herdoc(char *str);

// expanding
char		*ft_expand(t_token *lst_token, t_env *envl);
char		*ft_replace_dollar(char *to_expand, t_env *env);
char		*ft_expand_dollar(char *str, t_env *env);
char		*ft_remove_qoutes(char *str);
t_token		*ft_lst_remvove_qoutes(t_token *lst_token);

// herdoc
int			ft_heredoc_handler_exec(t_toexec *node, char *del, bool is_expand);
int			ft_heredoc_handler_syn(char *delemiter);

// utils
int			ft_strlen(char *str);
char		**ft_split(char *s, char c);
void		ft_printerror(char *msg);
void		ft_put_syntaxerror(char *msg, char c);
char		*ft_strldup(char *s1, int lenght);
int			ft_isspecialchars(char c);
int			ft_isquote(char c);
char		*ft_strtrim(char *s1, char *set);

// tools
t_expand	*ft_create_expand_node(char *str);
t_herdoc	*ft_create_herdoc_node(char *del);
void		ft_append_node_herdoc(t_herdoc **head, t_herdoc *node);
void		ft_append_node_t_token(t_token **head, t_token *node);
void		ft_append_node_t_toexec(t_toexec **head, t_toexec *node);
void		ft_append_node_expand(t_expand **head, t_expand *node);
void		ft_pop_node_t_token(t_token **head, t_token *to_pop);
void		ft_check_valid_fd(t_toexec **head);
int			ft_set_status(int new_status, int type);
// 1
// char		*ft_remove_qoutes(char *str);
void		ft_skip_quotes(char *str, int *i);
int			ft_isredirection(char c);
char		*ft_get_inside_quotes(char *in_quotes, int *i, char q_type);

// libft
char		*ft_strdup(char *s1, bool to_free);
char		*ft_strchr(char *s, int c);
int			ft_isspace(char c);
int			ft_isdigit(char c);
int			ft_strcmp(char *s1, char *s2);
void		ft_strcpy(char *dst, char *src, size_t dstsize);
int			ft_is_alphanumeric(char c);
char		*ft_itoa(int n, bool to_free);
void		ft_putstr_fd(char *s, int fd);
void		ft_putstr(char *s);
void		ft_print_error(char *str);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_substr(char *s, int start, int len, bool to_free);
char		*ft_strjoin(char *s1, char *s2, bool to_free);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, char *src, size_t dstsize);
char		**free_leaks(char **strs);
int			ft_atoi(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		free_env_list(t_env **head);
char		*ft_strjoin_addspace(char *s1, char *s2, bool to_free);

// signal hanldler
void		ft_sigkill_handler(int signum);
void		ft_sigquit_handler(int signum);
void		ft_sigkill_herdoc(int signum);
int			ft_update_status(int status, struct termios *term);

// tests start
void		test_tokens(t_token *lst_token_input);
void		test_lst(t_toexec *lst);
void		printf_test(char *str);
// test end

// env_tools
t_env		*set_spare_env(void);
t_env		*set_env(char **env);
void		update_env(t_env *envl);
void		fill_envinlist(t_toexec **head, t_env **env_list);

// exec
void		executer(t_toexec *cmds, t_pipe *needs);
int			ft_cd(char *dir, t_env *env, t_pipe *needs);
int			ft_echo(t_toexec *cmd, t_pipe *needs);
int			env_print(t_env **data);
void		ft_export(char *name, char *var, t_env **head, t_pipe *needs);
int			ft_exporter(t_toexec *cmd, t_pipe *needs);
int			add_orjoin(char *av);
int			ft_pwd(t_pipe *needs, t_env *env);
int			unseter(t_toexec **cmd, t_pipe *needs);
t_env		*duplicate_list(t_env **head);
void		env_search_replace(t_env *head, char *to_replace, char *to_look);
int			env_list_serch(t_env **head, char *to_look);
void		env_search_and_add(t_env *head, char *to_add, char *to_look);
t_env		*env_new(char *var, char *name, bool to_free);
void		ft_unset(t_env **env, char *to_del);
int			check_ifvalid(char *cmd);
int			ft_exit(char **args);
void		in_out_fixer(t_pipe *needs);
void		ft_execution(t_toexec *cmd, t_pipe *needs);
void		ft_execution(t_toexec *cmd, t_pipe *needs);
int			check_builtin(t_toexec *cmd, t_pipe *needs);
void		in_out_handler_last(t_toexec *cmds, t_pipe *needs);
void		in_out_handler_multiple(t_toexec *cmds, t_pipe *needs);
void		in_out_handler(t_toexec *cmds, t_pipe *needs);
void		in_out_fixer(t_pipe *needs);
void		close_all(void);
int			lst_size(t_toexec *head);
int			env_size(t_env *head);
void		env_sort(t_env **start);
char		**env_tolist(t_env **env_list);
void		export_env_print(t_toexec *data);
t_env		*duplicate_list(t_env **head);
void		ft_wait(t_pipe *needs);
char		*ft_env_list_serch_res(t_env *head, char *to_look);
void		set_values(t_pipe *needs, t_toexec *cmds);
void		cmds_executer(t_toexec *cmds, t_pipe *needs);
char		*find_path(char *cmd, char *env[]);
void		error_handler(char *str);
int			look_for(char *str, char c);
char		**split_env(char *arg, char c);
int			ft_set_status(int new_status, int type);
void		lst_add(t_env **lst, t_env *new);
void		*zyalloc(size_t size, int flag, bool is_free);

#endif
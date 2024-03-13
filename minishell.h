/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:11 by moichou           #+#    #+#             */
/*   Updated: 2024/03/13 16:47:32 by moichou          ###   ########.fr       */
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
char	**ft_sanitizer(char *line);
int		ft_sanitize_pipes(char *line);
int		ft_sanitize_quotes(char *line);
int		ft_sanitize_redirections(char *line);
char	**ft_remove_split_spaces(char *line);

// analyser
int		ft_analyser(char **args);

// utils
int		ft_strlen(char *str);
void	ft_printerror(char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char *s1, char *set);
int		ft_strlen(char *str);

// struct tools
t_toexec	*ft_create_node(char *cmd, char **args);
void		ft_append_node(t_toexec *head, t_toexec *node);

// libft
char	*ft_strdup(char *s1);
char	*ft_strchr(char *s, int c);

#endif
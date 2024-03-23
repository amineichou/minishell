


#ifndef MINISHELL_H
#define MINISHELL_H
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

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
	int		link_var;
	int		fd[2];
	int		step;
	int		infile;
	int		outfile;
	char	*infile_name;
	char	*outfile_name;
	char	*path;
	char	**cmd;
	char	*limiter;
	char	**env;
	int		*pids;
	int		p;
}	t_pipe;

char	*ft_strdup(const char *s1);
int ft_strcmp(const char *str1, const char *str2);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_print_error(char *str);
char* ft_strstr(const char* haystack, const char* needle);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**free_leaks(char **strs);
char	**ft_split(char const *s, char c);
#endif
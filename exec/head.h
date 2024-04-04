


#ifndef HEAD_H
#define HEAD_H
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>



// char	*ft_strdup(const char *s1);
// int ft_strcmp(const char *str1, const char *str2);
// size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_print_error(char *str);
char* ft_strstr(const char* haystack, const char* needle);
// char	*ft_strchr(const char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char *ft_strjoin(char *s1, char *s2);
// size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**free_leaks(char **strs);
// char	**ft_split(char const *s, char c);
#endif
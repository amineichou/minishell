#include <libc.h>

// // free after using
// static char	*ft_get_word(char *str, int *i)
// {
// 	char	*res;
// 	int		tmp;

// 	tmp = *i;
// 	while (str[*i])
// 	{
// 		if (str[*i] == ' ')
// 			break;
// 		(*i)++;
// 	}
// 	res = malloc(sizeof(char) * (*i + 1));
// 	if (!res)
// 		perror("MALLOC_ERORR");
// 	*i = tmp;
// 	while (str[*i])
// 	{
// 		if (str[*i] == ' ')
// 			break;
// 		res[*i] = str[*i];
// 		(*i)++;
// 	}
// 	res[*i] = '\0';
// 	return (res);
// }

// static int	ft_count_args(char *rest_args, int index)
// {
// 	int		size;

// 	size = 0;
// 	while (rest_args[index++])
// 	{
// 		if (rest_args[index] == '"')
// 		{
// 			size++;
// 			while (rest_args[++index] != '"')
// 				size++;
// 		}
// 		if (rest_args[index] == '\'')
// 		{
// 			size++;
// 			while (rest_args[++index] != '\'')
// 				size++;
// 		}
// 		if (rest_args[index] == '|')
// 		{
// 			size++;
// 			break ;
// 		}
// 		size++;
// 	}
// 	return (size);
// }

// static char *ft_get_args(char *rest_args, int *i)
// {
// 	char	*res;
// 	int		size;

// 	size = ft_count_args(rest_args, *i);
// 	res = malloc(sizeof(char) * (size + 1));
// 	if (!res)
// 		ft_printerror(MALLOC_ERORR);
// 	ft_strcpy(res, rest_args, size);
// 	*i += size;
// 	return (res);
// }
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strlrdup(char *s1, int lenght)
{
	int		i;
	char	*s2;

	i = 0;

	s2 = malloc(sizeof(char) * (lenght + 1));
	if (!s2)
		return (NULL);
	while (i < lenght && s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	if (i < lenght)
	{
		s2[i] = '\0';
		i++;
	}
	s2[lenght] = '\0';
	return (s2);
}


int	ft_isquote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\f' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

// remove the spaces/tabs form the bigg-end if str 
char	*ft_trim_spaces(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	if (!str)
		return (NULL)
	j = ft_strlen(str) - 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (i == ft_strlen(str))
		return (NULL);
	while (ft_isspace(str[j]))
		j--;
	j = strlen(str) - j - 1;
	res = ft_strlrdup(str + i, (strlen(str) - i - j));
	if (!res)
		perror("malloc");
	return (res);
}

int main(void)
{
	char *test = NULL;
	char *res = ft_trim_spaces(test);
	printf("%s\n", res);
}
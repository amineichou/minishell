#include <libc.h>

// free after using
static char	*ft_get_word(char *str, int *i)
{
	char	*res;
	int		tmp;

	tmp = *i;
	while (str[*i])
	{
		if (str[*i] == ' ')
			break;
		(*i)++;
	}
	res = malloc(sizeof(char) * (*i + 1));
	if (!res)
		perror("MALLOC_ERORR");
	*i = tmp;
	while (str[*i])
	{
		if (str[*i] == ' ')
			break;
		res[*i] = str[*i];
		(*i)++;
	}
	res[*i] = '\0';
	return (res);
}

static int	ft_count_args(char *rest_args, int index)
{
	int		size;

	size = 0;
	while (rest_args[index++])
	{
		if (rest_args[index] == '"')
		{
			size++;
			while (rest_args[++index] != '"')
				size++;
		}
		if (rest_args[index] == '\'')
		{
			size++;
			while (rest_args[++index] != '\'')
				size++;
		}
		if (rest_args[index] == '|')
		{
			size++;
			break ;
		}
		size++;
	}
	return (size);
}

static char *ft_get_args(char *rest_args, int *i)
{
	char	*res;
	int		size;

	size = ft_count_args(rest_args, *i);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		ft_printerror(MALLOC_ERORR);
	ft_strcpy(res, rest_args, size);
	*i += size;
	return (res);
}

int main(void)
{
	char test[] = "amine ichou";
	char *res = ft_stlrdup(test, 18);
	printf("%s\n", res);
}
#include <libc.h>

void	ft_strcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
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
		printf("malloc\n");
	ft_strcpy(res, rest_args, size);
	*i += size;
	return (res);
}

int main(void)
{
	char test[] = "amine ichou";
	int i = 0;
	char *res = ft_get_args(test, &i);
	printf("%s\n%d\n", res, i);
}
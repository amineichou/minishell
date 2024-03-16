#include <libc.h>


char	*ft_get_word(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			break;
		i++;
	}
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		perror("MALLOC_ERORR");
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			break;
		res[i] = str[i];
		i++;
	}
	// add '\0'
	return (res);
}

int main(void)
{
	char test[] = "       hello my name i smaine ";
	char *res = ft_get_word(test);
	printf("%s\n", res);
}
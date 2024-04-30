// #include <libc.h>

// int ft_isquote(char c);
// int	ft_count_legal_char(char *line, char c);
// int ft_strlen(char *str);
// void ft_printerror(char *msg);

// static void	ft_add_spaces_to_char(char *line, char *res, char c)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (line[i])
// 	{
// 		if (ft_isquote(line[i]) == 1)
// 		{
// 			res[j] = line[i];
// 			j++;
// 			i++;
// 			while (ft_isquote(line[i]) != 1)
// 				res[j++] = line[i++];
// 			res[j] = line[i];
// 			j++;
// 			i++;
// 		}
// 		else if (ft_isquote(line[i]) == 2)
// 		{
// 			res[j] = line[i];
// 			j++;
// 			i++;
// 			while (ft_isquote(line[i]) != 2)
// 				res[j++] = line[i++];
// 			res[j] = line[i];
// 			j++;
// 			i++;
// 		}
// 		else if (line[i] == c)
// 		{
// 			if (line[i + 1] && line[i] == c)
// 			{
// 				res[j++] = line[i++];
// 				res[j++] = line[i++];
// 			}
// 			else
// 			{
// 				res[j++] = ' ';
// 				res[j++] = line[i++];
// 				res[j++] = ' ';
// 			}
// 		} 
// 		else
// 			res[j++] = line[i++];
// 	}
// 	res[j] = '\0';
// }

// static void	ft_add_spaces_to_string(char *line, char *res, char *c)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (line[i])
// 	{
// 		if (ft_isquote(line[i]) == 1)
// 		{
// 			res[j] = line[i];
// 			j++;
// 			i++;
// 			while (ft_isquote(line[i]) != 1)
// 				res[j++] = line[i++];
// 			res[j] = line[i];
// 			j++;
// 			i++;
// 		}
// 		else if (ft_isquote(line[i]) == 2)
// 		{
// 			res[j] = line[i];
// 			j++;
// 			i++;
// 			while (ft_isquote(line[i]) != 2)
// 				res[j++] = line[i++];
// 			res[j] = line[i];
// 			j++;
// 			i++;
// 		}
// 		else if (line[i] == c[0])
// 		{
// 			res[j++] = ' ';
// 			res[j++] = line[i++];
// 			res[j++] = line[i++];
// 			res[j++] = ' ';
// 		} 
// 		else
// 			res[j++] = line[i++];
// 	}
// 	res[j] = '\0';
// }

// // free after using
// char	*ft_addspace_illegal_chars(char *line, char *token)
// {
// 	char	*res;
// 	int		to_add_spaces;
// 	int		i;
// 	int		new_size;

// 	to_add_spaces = ft_count_legal_char(line, token[0]) * 3;
// 	i = 0;
// 	new_size = ft_strlen(line) + to_add_spaces;
// 	res = malloc (sizeof(char) * (new_size + 2));
// 	if (!res)
// 		return (ft_printerror("malloc"), NULL);
// 	if (ft_strlen(token) == 1)
// 		ft_add_spaces_to_char(line, res, token[0]);
// 	else
// 		ft_add_spaces_to_string(line, res, token);
// 	return (res);
// }

// int main(void)
// {
// 	char *test = "|amine>>ichou'|'""";
// 	char *res = ft_addspace_illegal_chars(test, "|");
// 	res = ft_addspace_illegal_chars(test, ">>");
// 	// res = ft_addspace_illegal_chars(test, '|');
// 	// res = ft_addspace_illegal_chars(test, '|');
// 	printf("%s\n", res);
// }









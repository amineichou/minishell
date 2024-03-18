#include <libc.h>



int main(void)
{
	char test[] = "amine ichou";
	char *res = ft_stlrdup(test, 18);
	printf("%s\n", res);
}
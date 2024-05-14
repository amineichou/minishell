#include "../../minishell.h"

void	test_lst(t_toexec *lst)
{
	if (!lst)
	{
		printf("\033[0;31mlist is empty\033[0m\n");
		return ;
	}
	t_toexec *test = lst;
	printf("\n+--------------------------------------------------------------------------------------------\n");
	printf("| \033[0;32mARGS\033[0m            \033[0;33mOUTPUT\033[0m      \033[0;34mINPUT\033[0m \n");
	while (test)
	{
		printf("+--------------------------------------------------------------------------------------------\n");
		printf("| [\033[0;32m");
		if (test->args)
		{
			for (int i = 0; test->args[i]; i++)
				printf("%s,", test->args[i]);
		}
		else
			printf("----");
		printf("]\033[0m	     [");
		printf("\033[0;33m%d\033[0m]	[", test->output);
		printf("\033[0;34m%d\033[0m]", test->input);
		printf("\n+--------------------------------------------------------------------------------------------\n");
		test = test->next;
	}
}

static char* token_to_string(t_tokenenm t) {
    switch (t) {
        case WORD:
            return "WORD";
        case PIPE:
            return "PIPE";
        case RD_AP:
            return "RD_AP";
        case RD_RP:
            return "RD_RP";
        case RD_IN:
            return "RD_IN";
        case HEREDOC:
            return "HEREDOC";
        default:
            return "UNKNOWN";
    }
}

void test_tokens(t_token *lst_token_input)
{
	t_token	*lst_token;
	lst_token = lst_token_input;
	while (lst_token)
	{
		printf("-----------------------------------------------------------\n");
		printf("\033[0;33morder : \033[0;30m%d\033[0m\n", lst_token->order);
		printf("\033[0;33mvalue : \033[0;31m%s\033[0m\n", lst_token->value);
		printf("\033[0;33mtype : \033[0;32m%s\033[0m\n", token_to_string(lst_token->token));
		printf("-----------------------------------------------------------\n");
		lst_token = lst_token->next;
	}
}

void	printf_test(char *str)
{
	printf("\033[0;31m%s\n\033[0;0m", str);
}
// int main(void)
// {
// 	char *arg[] = {"/bin/bash", "-c","ps -j $$ | awk 'NR==2 {print $3}'", NULL};
// 	execve("/bin/bash", arg, NULL);
// }
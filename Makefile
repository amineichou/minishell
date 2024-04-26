FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CC = cc
NAME = minishell
READLINE_LIB = -lreadline
READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include
SRC = minishell.c parsing/ft_parser.c parsing/ft_split.c parsing/libft.c parsing/signal_handlers.c \
	parsing/analyser/ft_analyse_redirections.c parsing/analyser/ft_analyser.c \
	parsing/analyser/ft_make_tokens.c parsing/analyser/ft_valid_tokens.c \
	parsing/sanitize_synthax/ft_sanitize_pipes.c parsing/sanitize_synthax/ft_sanitize_quotes.c \
	parsing/sanitize_synthax/ft_sanitize_redirections.c parsing/sanitize_synthax/ft_sanitizer.c \
	parsing/tools/t_expand_tools.c parsing/tools/t_toexec_tools.c parsing/tools/t_token_tools.c \
	free_leaks/ft_linked_lists.c \
	parsing/tools/tools_1.c parsing/test/test.c \
	expanding/ft_expand.c expanding/ft_remove_quotes.c expanding/ft_replace_dollar.c \
	exec/ft_cd.c exec/ft_echo.c exec/ft_env.c exec/ft_exec.c exec/ft_exit.c exec/ft_export.c exec/ft_pwd.c \
	exec/ft_unset.c exec/utilst.c
#remove test
OBJ = $(SRC:.c=.o)∆

all : $(NAME)

$(NAME) : $(OBJ)
	@ $(CC) $(FLAGS) $(OBJ) $(READLINE_LIB) -L $(READLINE_L) -o $(NAME)
	@ echo "DONE!"

%.o: %.c minishell.h
	@ $(CC) $(FLAGS) -I $(READLINE_I) -c $< -o $@
	@ clear
	@ echo "Making objects..."

clean:
	@ echo "Removing object files...Please Wait"
	@ rm -f $(OBJ)
	@ echo "Removing object files....DONE!"

fclean: clean
	@ echo "Removing minishell...Please Wait"
	@ rm -f $(NAME)
	@ echo "Removing minishell....DONE!"

re: fclean all

.PHONY: all clean fclean re
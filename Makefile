FLAGS = -Wall -Wextra -Werror
CC = cc
NAME = minishell
READLINE_LIB = -lreadline
SRC = minishell.c parsing/ft_parser.c parsing/ft_split.c parsing/libft.c parsing/signal_handlers.c \
	parsing/analyser/ft_analyse_redirections.c parsing/analyser/ft_analyser.c \
	parsing/analyser/ft_make_tokens.c parsing/analyser/ft_valid_tokens.c \
	parsing/sanitize_synthax/ft_sanitize_pipes.c parsing/sanitize_synthax/ft_sanitize_quotes.c \
	parsing/sanitize_synthax/ft_sanitize_redirections.c parsing/sanitize_synthax/ft_sanitizer.c \
	parsing/tools/t_expand_tools.c parsing/tools/t_toexec_tools.c parsing/tools/t_token_tools.c \
	parsing/tools/tools_1.c parsing/test/test.c \
	expanding/ft_expand.c expanding/ft_remove_quotes.c expanding/ft_replace_dollar.c \
	exec/ft_cd.c exec/ft_echo.c exec/ft_env.c exec/ft_exec.c exec/ft_exit.c exec/ft_export.c exec/ft_pwd.c \
	exec/ft_unset.c exec/utilst.c
#remove test
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(READLINE_LIB) -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
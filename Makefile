FLAGS = -g -fsanitize=address
CC = cc
NAME = minishell
READLINE_LIB = -lreadline
READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include
SRC = minishell.c parsing/ft_parser.c parsing/ft_split.c parsing/libft.c parsing/signal_handlers.c \
	parsing/analyser/ft_analyse_redirections.c parsing/analyser/ft_analyser.c \
	parsing/analyser/ft_make_tokens.c parsing/analyser/herdoc_exec.c parsing/analyser/herdoc_syn.c  \
	parsing/sanitize_syntax/ft_sanitizer.c \
	parsing/tools/t_expand_tools.c parsing/tools/t_toexec_tools.c parsing/tools/t_token_tools.c parsing/tools/t_herdoc_tools.c\
	free_leaks/ft_linked_lists.c \
	parsing/tools/tools_1.c parsing/test/test.c \
	expanding/ft_expand.c expanding/ft_remove_quotes.c expanding/ft_replace_dollar.c \
	exec/ft_cd.c exec/ft_echo.c exec/ft_env.c exec/ft_exec.c exec/ft_exit.c exec/ft_export.c exec/ft_pwd.c \
	exec/ft_unset.c exec/utilst.c
#remove test
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@ clear
	@ $(CC) $(FLAGS) $(OBJ) $(READLINE_LIB) -L $(READLINE_L) -o $(NAME)
	@ echo "DONE! minishell is successfully created."

%.o: %.c minishell.h
	@ $(CC) $(FLAGS) -I $(READLINE_I) -c $< -o $@
	@ clear
	@ echo "Making objects...\033[0;35m" $< "\033[0;0m"

clean:
	@ printf "Removing object files..."
	@ rm -f $(OBJ)
	@ echo "DONE!"

fclean: clean
	@ printf "Removing minishell..."
	@ rm -f $(NAME)
	@ echo "DONE!"

re: fclean all

.PHONY: all clean fclean re
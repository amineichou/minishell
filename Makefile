FLAGS = -Wall -Wextra -Werror
CC = cc
NAME = minishell
SRC = parsing/*.c parsing/sanitizer/*.c parsing/analyser/*.c 
OBJ = (SRC:.c=.o)
READLINE_LIB = -lreadline


all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(READLINE_LIB) -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
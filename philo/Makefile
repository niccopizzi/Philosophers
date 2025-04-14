CFLAGS = -Wall -Wextra -Werror -O3

NAME = philo

SRCS = ./main.c					\
		./errors.c				\
		./init.c				\
		./utils_one.c			\
		./utils_two.c			\
		./threads_one.c			\
		./threads_two.c			\

all: $(NAME)

$(NAME): $(SRCS)
	@cc $(CFLAGS) $(SRCS) -o $(NAME) -pthread
	@echo "... Amazing! I managed to compile philo"

clean:
	@$(RM) $(OBJ)
	@echo "Objects files removed."

fclean: clean
	@$(RM) $(NAME)
	@echo "$(NAME) removed."

re: fclean all

.PHONY: all clean fclean re

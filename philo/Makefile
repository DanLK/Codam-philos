NAME = philo
SRC = philo.c init.c init_utils.c clear.c routines.c routine_checks.c eat_routine.c utils.c atoi.c
SRC_DIR = ./src
OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

CFLAGS += -Werror -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -Iinclude -fsanitize=address -o $(NAME) $(CFLAGS) $(OBJ)
#-fsanitize=thread 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -c -Iinclude -fsanitize=address $(CFLAGS) -o $@ $<
#-fsanitize=thread

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
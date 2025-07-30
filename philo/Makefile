NAME = philo
SRC = philo.c init.c clear.c routines.c eat_routine.c routine_utils.c utils.c atoi.c debug.c
SRC_DIR = ./src
OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

CFLAGS += -Werror -Wall -Wextra 
#-fsanitize=thread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -Iinclude -o $(NAME) $(CFLAGS) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -c -Iinclude $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
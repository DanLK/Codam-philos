NAME = philo
SRC = philo.c init.c clear.c routines.c debug.c
SRC_DIR = ./src
OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

CFLAGS += -Werror -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -fsanitize=thread -Iinclude -o $(NAME) $(CFLAGS) $(OBJ) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -c -fsanitize=thread -Iinclude $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
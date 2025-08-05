NAME = philo_bonus
SRC = philo_bonus.c utils.c atoi.c init.c routines.c
SRC_DIR = ./src
OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

CFLAGS += -Wall -Wextra -Werror

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

NAME = ft_ls

SRC_DIR = src/
OBJ_DIR = obj/
LIBFT_DIR = libft/

FLAGS = -Wall -Wextra -Werror -g
INC = -I ./inc/

SRC_NAME = main.c \
checks.c \
flags.c \
sort.c \
print.c \
print_helpers.c \
utils.c \
layout.c \
details.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@gcc $(FLAGS) $(OBJS) $(INC) -L $(LIBFT_DIR) -lft -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p obj
	@gcc -c $(FLAGS) $(INC) $< -o $@

clean:
	@make -C $(LIBFT_DIR)/ clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT_DIR)/ fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

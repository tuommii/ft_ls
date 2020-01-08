# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 12:40:34 by mtuomine          #+#    #+#              #
#    Updated: 2019/12/05 08:19:58 by mtuomine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
CFLAGS		= -Wall -Wextra -Werror
SOURCE_LIST	= ft_memset.c \
ft_putchar.c \
ft_strlen.c \
ft_putstr.c \
ft_putnbr.c \
ft_bzero.c \
ft_memcpy.c \
ft_memccpy.c \
ft_memmove.c \
ft_memchr.c \
ft_memcmp.c \
ft_strdup.c \
ft_strcpy.c \
ft_strncpy.c \
ft_strcat.c \
ft_strncat.c \
ft_strlcat.c \
ft_strchr.c \
ft_strrchr.c \
ft_strstr.c \
ft_strnstr.c \
ft_strcmp.c \
ft_strncmp.c \
ft_atoi.c \
ft_isalpha.c \
ft_isdigit.c \
ft_isalnum.c \
ft_isascii.c \
ft_isprint.c \
ft_toupper.c \
ft_isspace.c \
ft_isupper.c \
ft_islower.c \
ft_memalloc.c \
ft_memdel.c \
ft_strnew.c \
ft_strnew.c \
ft_strdel.c \
ft_strclr.c \
ft_striter.c \
ft_striteri.c \
ft_strmap.c \
ft_strmapi.c \
ft_strequ.c \
ft_strnequ.c \
ft_strsub.c \
ft_strjoin.c \
ft_strtrim.c \
ft_putendl.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_toupper.c \
ft_tolower.c \
ft_itoa.c \
ft_strsplit.c \
ft_lstnew.c \
ft_lstdelone.c \
ft_lstdel.c \
ft_lstadd.c \
ft_lstiter.c \
ft_lstmap.c \
ft_lstreverse.c \
ft_lstcount.c \
ft_strrev.c \
ft_strlen_char.c \
ft_invert_padding.c \
ft_count_digits_only.c \
ft_count_digits_and_sign.c \
ft_uitoa_base.c \
ft_pad_left.c \
ft_pad_right.c \
ft_cut_left.c \
ft_ishex.c \
get_next_line.c \
ft_printf.c \
pf_write.c \
pf_args.c \
pf_parsers.c \
pf_ftoa.c \
pf_pad_cut.c \
pf_print_hex.c \
pf_print_uint.c \
pf_print_percent.c \
pf_print_decimal.c \
pf_print_char.c \
pf_print_float.c \
pf_print_pointer.c \
pf_print_octal.c \
pf_flags.c \
pf_print_string.c \
pf_print_binary.c


OBJECTS	= $(SOURCE_LIST:.c=.o)

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) -c $(SOURCE_LIST) -I includes/
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)


main: all
	gcc $(FLAGS) -I . -c main.c
	gcc -o main main.o libft.a

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re

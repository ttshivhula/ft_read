# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/07 08:36:01 by ttshivhu          #+#    #+#              #
#    Updated: 2017/09/07 10:18:44 by ttshivhu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftread.a

SRC = ft_key.c  init_term.c navigation.c \
	  window.c history.c tc_print.c \
	  cmove.c  input.c ft_read.c \

FLAG = -Wall -Werror -Wextra
SILENT = --no-print-directory

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@make -C libft $(SILENT)
	@gcc $(FLAG) -c $(SRC)
	@ar rc $(NAME) $(OBJ) libft/*.o 
	@ranlib $(NAME)
	@printf "\x1b[32mCompiled $(NAME) successfully\x1b[31m\n"

clean:
	@make clean -C libft $(SILENT)
	@/bin/rm -f $(OBJ) $(LOBJ) *.o

fclean: clean
		@/bin/rm -f $(NAME)
		@make fclean -C libft $(SILENT)

re: fclean all

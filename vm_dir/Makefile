# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 16:07:39 by jleblond          #+#    #+#              #
#    Updated: 2020/02/21 11:20:05 by flhember         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

CC		=	gcc
# CFLAGS =	-Wall -Werror -Wextra -g
CFLAGS	=	-Wall -Werror -Wextra -g -fsanitize=address
NAME	=	corewar

SRCS	=	main_vm.c parse.c free.c parse_file.c parse_argv.c parse_argv_bis.c \
			list.c run_vm.c dump_mem.c instructions.c tools.c params.c \
			params_bis.c bytes.c init_players.c print.c \
			op_add_sub.c op_live_zjmp.c op_ld.c op_st.c op_fork.c\
			op_and_or.c op_aff.c

OBJ		=	$(SRCS:.c=.o)

HEAD_P	=	../includes \
			libft2/includes

IFLAG	=	$(foreach dir, $(HEAD_P), -I$(dir))

HEADER	=	../includes/*.h \
			libft2/includes/*.h

LIBFTA	=	./libft2/libft.a

all: $(NAME)

$(NAME):$(OBJ) $(LIBFTA)
	$(CC)  $(CFLAGS) -o $(NAME) $(SRC) $(OBJ) $(LIBFTA) $(IFLAG)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $< $(IFLAG)

$(LIBFTA): FORCE
	make -C libft2

FORCE:

clean:
	make clean -C libft2
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft2
	rm -f $(NAME)

re: fclean all

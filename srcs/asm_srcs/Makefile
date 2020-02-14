#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naali <naali@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 16:13:53 by naali             #+#    #+#              #
#    Updated: 2020/02/12 20:00:37 by naali            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

rose			=	\033[1;31m
neutre			=	\033[0m
vertfonce		=	\033[0;32m

NAME			=	asm

CC				=	gcc

CFLAG 			=	-Wall -Wextra -Werror
CFLAG 			+=	-fsanitize=address

INCLUDES		=	-I../../includes/asm_incs	\
					-I../../includes			\
					-I../../libft

OBJ_PATH		=	../objs_asm

SRC				=	checking_things.c		get_info.c			\
					lst_label.c				op.c				\
					print_error.c			skip.c				\
					arguments_analysis.c	get_code.c			\
					set_champ_value.c		get_name_comment.c	\
					lst_champion.c			line_checker.c		\
					main.c					open_file.c			\
					lst_clear.c				is_label.c			\
					sort_lst.c				write_str_type.c	\
					write_int_type.c		write_header.c		\
					write_body.c			print_verbose.c		\
					lst_label_bis.c			write_ocp.c			\
					name_get.c				comment_get.c

OBJ				=	$(addprefix $(OBJ_PATH)/, $(SRC:%.c=%.o))

LIB_PATH		=	-L../../libft

LIBS 			=	-lft

LFLAG			=	$(LIB_PATH) $(LIBS)

######################################################################

vpath %.c .:

all				:	libs $(NAME)

$(NAME)			:	$(OBJ)
					@echo "${vertfonce}Compiling ...${neutre}\c"
					@$(CC) $(CFLAG) -o $(NAME) $(OBJ) $(LFLAG) $(INCLUDES)
					@echo "${rose}DONE${neutre}"

$(OBJ_PATH)/%.o	:	%.c
					@mkdir $(OBJ_PATH) 2> /dev/null || true
					@echo "${vertfonce}Creating $@ ...\c${neutre}"
					@$(CC) $(CFLAG) -o $@ -c $< $(INCLUDES)
					@echo "${rose}DONE${neutre}"

clean			:
					@echo "${rose}Cleaning the project ...${neutre}\c"
					@make clean -C ../../libft
					@rm -rf $(OBJ_PATH)
					@echo "${vertfonce}DONE${neutre}"

fclean			:	clean
					@echo "${rose}Fcleaning the project ...${neutre}\c"
					@make fclean -C ../../libft
					@rm -rf $(NAME)
					@echo "${vertfonce}DONE${neutre}"

libs			:
					make -C ../../libft/

re				:	fclean all

.PHONY			:	all clean fclean re

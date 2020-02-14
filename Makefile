#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naali <naali@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 16:13:53 by naali             #+#    #+#              #
#    Updated: 2020/02/14 08:07:39 by naali            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

rose			=	\033[1;31m
neutre			=	\033[0m
vertfonce		=	\033[0;32m

NAME			=	corewar
NAME_ASM		=	asm

CC				=	gcc

CFLAG 			=	-Wall -Wextra -Werror
CFLAG 			+=	-g

INCLUDES		=	-I./includes			\
					-I./libft				\
					-I./asm/incs			\
					-I./asm/libft/includes	\

OBJ_PATH		=	./objs

SRC_CORE		=	main.c

SRC_ASM			=	main.c

OBJ_CORE		=	$(addprefix $(OBJ_PATH)/, $(SRC:%.c=%.o))

LIB_PATH		=	-L./libft

ASM_PATH		=	./srcs/asm_srcs

LIBS 			=	-lft

LFLAG			=	$(LIB_PATH) $(LIBS)

######################################################################

vpath %.c ./srcs/:

all				:	asm libs $(NAME)

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
					@make clean -C libft
					@make clean -C $(ASM_PATH)
					@rm -rf $(OBJ_PATH)
					@echo "${vertfonce}DONE${neutre}"

fclean			:	clean
					@echo "${rose}Fcleaning the project ...${neutre}\c"
					@make fclean -C libft
					@rm -rf $(NAME)
					@make fclean -C $(ASM_PATH)
					@rm -rf $(NAME_ASM)
					@echo "${vertfonce}DONE${neutre}"

libs			:
					make -C ./libft/

asm				:
					@make -C $(ASM_PATH)
					@mv $(ASM_PATH)/asm ./asm

asm_re			:
					@make fclean -C $(ASM_PATH)
					@make -C $(ASM_PATH)
					@mv $(ASM_PATH)/asm ./asm

re				:	fclean all

.PHONY			:	all clean fclean re image asm

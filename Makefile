#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naali <naali@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 16:13:53 by naali             #+#    #+#              #
#    Updated: 2020/03/01 13:32:38 by nabih            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

rose			=	\033[1;31m
neutre			=	\033[0m
vertfonce		=	\033[0;32m

NAME_VM			=	corewar

NAME_ASM		=	asm

CC				=	gcc

CFLAG 			=	-Wall -Wextra -Werror

INCLUDES		=	-I./includes			\
					-I./libft

INCLUDE_VM		=	-I./includes/vm_inc

INCLUDE_ASM		=	-I./includes/asm_inc

SRCS_VM			=	main_vm.c				parse.c			\
					free.c					parse_file.c	\
					parse_argv.c			tools.c			\
					parse_argv_bis.c	 	list.c			\
					run_vm.c				dump_mem.c		\
					instructions.c			params.c		\
					params_bis.c			bytes.c			\
					init_players.c			winner.c		\
					print.c					op_add_sub.c	\
					op_live_zjmp.c			op_ld.c			\
					op_st.c					op_fork.c		\
					op_and_or.c				op_aff.c

SRCS_ASM		=	checking_things.c		get_info.c			\
					lst_label.c				op.c				\
					print_error.c			skip.c				\
					arguments_analysis.c	get_code.c			\
					set_champ_value.c		get_name_comment.c	\
					lst_champion.c			main_asm.c			\
					lst_clear.c				is_label.c			\
					sort_lst.c				write_str_type.c	\
					write_int_type.c		write_header.c		\
					write_body.c			print_verbose.c		\
					lst_label_bis.c			write_ocp.c			\
					name_get.c				comment_get.c		\
					open_file.c

OBJ_VM_PATH		=	./vm_objs

OBJ_ASM_PATH	=	./asm_objs

OBJ_VM_CORE		=	$(addprefix $(OBJ_VM_PATH)/, $(SRCS_VM:%.c=%.o))

OBJ_ASM_CORE	=	$(addprefix $(OBJ_ASM_PATH)/, $(SRCS_ASM:%.c=%.o))

LIB_PATH		=	-L./libft

LIBS 			=	-lft

LFLAG			=	$(LIB_PATH) $(LIBS)

######################################################################

vpath %.c ./asm_dir/:./vm_dir/
vpath %.h ./includes/:./includes/vm_inc:./includes/asm_inc:./libft/

.PHONY			:	all clean fclean re image vm_c asm_c libs clean_vm clean_asm fclean_vm fclean_asm vm_re asm_re

all					:	libs vm_c asm_c

$(NAME_VM)			:	$(OBJ_VM_CORE)
					@echo "${vertfonce}Compiling ...${neutre}\c"
					@$(CC) $(CFLAG) -o $(NAME_VM) $(OBJ_VM_CORE) $(LFLAG) $(INCLUDES) $(INCLUDE_VM)
					@echo "${rose}DONE${neutre}"

$(NAME_ASM)			:	$(OBJ_ASM_CORE)
					@echo "${vertfonce}Compiling ...${neutre}\c"
					@$(CC) $(CFLAG) -o $(NAME_ASM) $(OBJ_ASM_CORE) $(LFLAG) $(INCLUDES) $(INCLUDE_ASM)
					@echo "${rose}DONE${neutre}"

$(OBJ_VM_PATH)/%.o	:	%.c
					@mkdir $(OBJ_VM_PATH) 2> /dev/null || true
					@echo "${vertfonce}Creating $@ ...\c${neutre}"
					@$(CC) $(CFLAG) -o $@ -c $< $(INCLUDES) $(INCLUDE_VM)
					@echo "${rose}DONE${neutre}"

$(OBJ_ASM_PATH)/%.o	:	%.c
					@mkdir $(OBJ_ASM_PATH) 2> /dev/null || true
					@echo "${vertfonce}Creating $@ ...\c${neutre}"
					@$(CC) $(CFLAG) -o $@ -c $< $(INCLUDES) $(INCLUDE_ASM)
					@echo "${rose}DONE${neutre}"

clean			:
					@echo "${rose}Cleaning the project ...${neutre}\c"
					@make clean -C libft/
					@rm -rf $(OBJ_VM_PATH)
					@rm -rf $(OBJ_ASM_PATH)
					@echo "${vertfonce}DONE${neutre}"

fclean			:	clean
					@echo "${rose}Fcleaning the project ...${neutre}\c"
					@make fclean -C libft
					@rm -rf $(NAME_VM)
					@rm -rf $(NAME_ASM)
					@echo "${vertfonce}DONE${neutre}"

libs			:
					@echo "Libft"
					@make -C libft/

vm_c			:	libs $(NAME_VM)

asm_c			:	libs $(NAME_ASM)

clean_vm		:
					@rm -rf $(OBJ_VM_PATH)

clean_asm		:
					@rm -rf $(OBJ_ASM_PATH)

fclean_vm		:	clean_vm
					@rm -rf $(NAME_VM)

fclean_asm		:	clean_asm
					@rm -rf $(NAME_ASM)

vm_re			:	fclean_vm $(NAME_VM)

asm_re			:	fclean_asm $(NAME_ASM)

re				:	fclean all

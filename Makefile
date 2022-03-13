# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 17:52:43 by orahmoun          #+#    #+#              #
#    Updated: 2022/03/13 22:59:05 by orahmoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- VARIABLE DECLARATION --- #

NAME				=	minishell

CC					=	cc

FLAGS				=	-Wall -Wextra -Werror -I libft

READLINE			=	-lreadline

LDFLAGS			=	-L /goinfre/orahmoun/.brew/opt/readline/lib \

CPPFLAGS			=	-I /goinfre/orahmoun/.brew/opt/readline/include

READLINE_FIX	=	-I .brew/opt/readline/include \
						${LDFLAGS} \
						${CPPFLAGS}

DEBUG				=	-g -D DEBUG

HEADER			=	d_minishell/main.h

LIBFT 			=	libft/libft.a

MAKE_LIBFT 		=	libft/

SRC 				=	d_minishell/main.c \
						d_minishell/tokenizer.c \
						d_minishell/print_logo.c \
						d_minishell/tokenizer_utils.c \
						d_minishell/tokenizer_utils_2.c \
						d_minishell/add_token.c \
						d_minishell/add_token_2.c \
						d_minishell/utils.c \
						d_minishell/syntax_analysis.c \
						d_minishell/env.c \
						d_minishell/env_utils.c \
						d_minishell/expander.c \
						d_minishell/corrector.c \
						d_minishell/parser.c \
						d_minishell/parsing.c \
						d_minishell/eval.c \
						d_minishell/eval_builtins.c \
						d_minishell/shell_loop.c \
						d_minishell/exec.c \
						d_minishell/echo.c \
						d_minishell/pwd.c \
						d_minishell/cd.c \
						d_minishell/export.c \
						d_minishell/exit.c \
						d_minishell/unset.c \
						d_minishell/add_history.c \
						d_minishell/2d_array_utils.c \
						d_minishell/2d_array_utils_2.c \
						# d_minishell/print_tokens.c \

OBJDIR 			=	obj

OBJ 				=	$(addprefix ${OBJDIR}/, ${SRC:%.c=%.o})

# ---------------------------- #
	
# RULES

all	: ${NAME}

debug : ${SRC} ${LIBFT}
	@echo "${MGN}[DEBUG MODE]${NC}"
	@${CC} ${FLAGS} ${READLINE} ${READLINE_FIX} ${DEBUG} $^ -o ${NAME}

${LIBFT} :
	@echo "${YEL}MAKING LIBFT ...${NC}"
	@make -C ${MAKE_LIBFT}

${NAME} : ${OBJ} ${LIBFT}
	@echo "${YEL}LINKING PROCESS ...${NC}"
	@echo "${GRN}COMPILATION COMPLETE${NC}"
	@${CC} ${FLAGS} ${READLINE} ${READLINE_FIX} $^ -o ${NAME}

$(OBJDIR)/%.o : %.c ${HEADER}
	@mkdir -p $(dir $@)
	@${CC} ${FLAGS} ${CPPFLAGS} -c $< -o $@
	@echo "${BLU}MAKING ::	$@${NC}"

clean : 
	@rm -rf ${OBJDIR}
	@make clean -C ${MAKE_LIBFT}

fclean : clean
	@rm -f ${NAME}
	@make fclean -C ${MAKE_LIBFT}

re : fclean all

.PHONY : bonus clean fclean all

# ---------------------------- #

# --- Terminal Color Codes --- #

NC		:= \033[31;0m
RED 	:= \033[0;31;1m
YEL 	:= \033[0;33;1m
GRA	:= \033[0;37;1m
CYN 	:= \033[0;36;1m
GRN 	:= \033[0;32;1m
MGN	:= \033[0;35;1m
BLU 	:= \033[0;34;1m

# ---------------------------- #

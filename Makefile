# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 17:52:43 by orahmoun          #+#    #+#              #
#    Updated: 2022/03/15 20:17:05 by orahmoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- VARIABLE DECLARATION --- #

NAME				=	minishell

CC					=	cc

FLAGS				=	-Wall -Wextra -I libft

READLINE			=	-lreadline

LDFLAGS			=	-L /goinfre/orahmoun/.brew/opt/readline/lib \

CPPFLAGS			=	-I /goinfre/orahmoun/.brew/opt/readline/include

READLINE_FIX	=	-I .brew/opt/readline/include \
						${LDFLAGS} \
						${CPPFLAGS}

DEBUG				=	-g -D DEBUG

HEADER			=	src/main.h

LIBFT 			=	libft/libft.a

MAKE_LIBFT 		=	libft/

SRC 				=	src/main.c \
						src/tokenizer.c \
						src/tokenizer_utils.c \
						src/tokenizer_utils_2.c \
						src/add_token.c \
						src/add_token_2.c \
						src/utils.c \
						src/syntax_analysis.c \
						src/env.c \
						src/env_utils.c \
						src/expander.c \
						src/corrector.c \
						src/parser.c \
						src/parser_utils.c \
						src/parsing.c \
						src/eval.c \
						src/eval_utils.c \
						src/eval_builtins.c \
						src/shell_loop.c \
						src/exec.c \
						src/echo.c \
						src/pwd.c \
						src/cd.c \
						src/export.c \
						src/exit.c \
						src/unset.c \
						src/add_history.c \
						src/2d_array_utils.c \
						src/2d_array_utils_2.c \
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

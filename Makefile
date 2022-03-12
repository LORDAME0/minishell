# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 17:52:43 by orahmoun          #+#    #+#              #
#    Updated: 2022/03/12 12:21:50 by orahmoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

FLAGS = -Wall -Wextra -I libft

READLINE = -lreadline

HEADER = mandatory/main.h

# B_HEADER = bonus/main_bonus.h

LIBFT = libft/libft.a

MAKE_LIBFT = libft/

SRC =	mandatory/main.c \
		mandatory/tokenizer.c \
		mandatory/print_logo.c \
		mandatory/tokenizer_utils.c \
		mandatory/tokenizer_utils_2.c \
		mandatory/print_tokens.c \
		mandatory/add_token.c \
		mandatory/add_token_2.c \
		mandatory/utils.c \
		mandatory/syntax_analysis.c \
		mandatory/dup_env.c \
		mandatory/expander.c \
		mandatory/corrector.c \
		mandatory/parser.c \
		mandatory/parsing.c \
		mandatory/eval.c \
		mandatory/shell_loop.c \
		mandatory/exec.c \
		mandatory/echo.c \
		mandatory/pwd.c \
		mandatory/cd.c \
		mandatory/export.c \
		mandatory/exit.c \
		mandatory/unset.c \
		mandatory/add_history.c \
		mandatory/2d_array_utils.c \
		mandatory/2d_array_utils_2.c \
		mandatory/2d_array_utils_3.c \

# B_SRC =		bonus/ \

OBJDIR = obj

OBJ = $(addprefix ${OBJDIR}/, ${SRC:%.c=%.o})

# B_OBJ = $(addprefix ${OBJDIR}/, ${B_SRC:%.c=%.o})

all : ${NAME}

debug : ${SRC} ${LIBFT}
	@echo "[DEBUG MODE]"
	@${CC} ${FLAGS} ${READLINE} -D DEBUG $^ -o ${NAME} -g

# bonus : bonus_binary ${B_HEADER}

# bonus_binary : ${B_NAME_OBJ} ${B_OBJ} ${B_G_OBJ}
# 	${CC} ${FLAGS} ${READLINE} $^ -o ${NAME}

${LIBFT} :
	@echo "${YEL}MAKING LIBFT ...${NC}"
	@make -C ${MAKE_LIBFT}

${NAME} : ${OBJ} ${LIBFT}
	@echo "${YEL}LINKING PROCESS ...${NC}"
	@echo "${GRN}COMPILATION COMPLETE${NC}"
	@${CC} ${FLAGS} ${READLINE} $^ -o ${NAME}

$(OBJDIR)/%.o : %.c ${HEADER}
	@mkdir -p $(dir $@)
	@${CC} ${FLAGS} -c $< -o $@
	@echo "${BLU}MAKING ::\t$@${NC}"

clean : 
	@rm -rf ${OBJDIR}
	@make clean -C ${MAKE_LIBFT}

fclean : clean
	@rm -f ${NAME}
	@make fclean -C ${MAKE_LIBFT}

re : fclean all

.PHONY : bonus clean fclean all

# --------------------------- Terminal Color Codes --------------------------- #
NC := \033[31;0m
RED := \033[0;31;1m
YEL := \033[0;33;1m
GRA := \033[0;37;1m
CYN := \033[0;36;1m
GRN := \033[0;32;1m
MGN := \033[0;35;1m
BLU := \033[0;34;1m
# ---------------------------------------------------------------------------- #

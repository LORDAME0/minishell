# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 17:52:43 by orahmoun          #+#    #+#              #
#    Updated: 2022/03/07 14:07:50 by orahmoun         ###   ########.fr        #
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
		mandatory/eval.c \
		mandatory/2d_array_utils.c \
		mandatory/2d_array_utils_2.c \
		mandatory/2d_array_utils_3.c \

B_SRC =		bonus/ \

OBJDIR = obj

OBJ = $(addprefix ${OBJDIR}/, ${SRC:%.c=%.o})

# B_OBJ = $(addprefix ${OBJDIR}/, ${B_SRC:%.c=%.o})

all : ${NAME}

# bonus : bonus_binary ${B_HEADER}

# bonus_binary : ${B_NAME_OBJ} ${B_OBJ} ${B_G_OBJ}
# 	${CC} ${FLAGS} ${READLINE} $^ -o ${NAME}

${LIBFT} :
	make -C ${MAKE_LIBFT}

${NAME} : ${OBJ} ${LIBFT}
	${CC} ${FLAGS} ${READLINE} $^ -o ${NAME}

$(OBJDIR)/%.o : %.c ${HEADER}
	@mkdir -p $(dir $@)
	${CC} ${FLAGS} -c $< -o $@

clean : 
	rm -rf ${OBJDIR}
	@make clean -C ${MAKE_LIBFT}

fclean : clean
	rm -f ${NAME}
	@make fclean -C ${MAKE_LIBFT}

re : fclean all

.PHONY : bonus clean fclean all

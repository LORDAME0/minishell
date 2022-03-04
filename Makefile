# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 17:52:43 by orahmoun          #+#    #+#              #
#    Updated: 2022/03/04 12:41:57 by orahmoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

FLAGS = -Wall -Wextra -Werror -Ilibft

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

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY : bonus clean fclean all

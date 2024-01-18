# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 15:32:20 by anraymon          #+#    #+#              #
#    Updated: 2024/01/18 04:57:33 by anraymon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = so_long
CC     = gcc
CFLAGS = -g#-Wall -Wextra -Werror
MLX = minilibx-linux/libmlx.a
SRCS   = so_long.c \

OBJS = ${SRCS:.c=.o}

all:	${NAME}

$(MLX):
	make -C minilibx-linux

${NAME}: $(MLX) $(OBJS)
	@echo "Compiling so_long..."
	$(CC) ${FLAGS}  $(OBJS) ./minilibx-linux/libmlx.a -lXext -lX11  -o $(NAME)

clean:
	rm -f ${OBJS} ${NAME}

fclean: clean
	rm -f ${NAME}
	@$(MAKE) -C minilibx-linux clean

re: clean all

.PHONY: all clean fclean re
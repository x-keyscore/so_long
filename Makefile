# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 15:32:20 by anraymon          #+#    #+#              #
#    Updated: 2024/02/04 23:50:47 by anraymon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = so_long
CC     = gcc
CFLAGS = -O3 -g #-Wall -Wextra -Werror
MLX = minilibx-linux-v2/libmlx.a
SRCS   = so_long.c \
		util.c \
		util_xpm.c \
		parser/parser.c \
		parser/map_1.c \
		parser/map_2.c \
		home/home.c \
		game/game.c \
		game/specific/tree.c \
		game/specific/star.c \
		game/specific/fish_1.c \
		game/specific/fish_2.c \
		game/specific/light.c \
		game/specific/ground.c \
		game/specific/player.c \
		game/specific/spaceship.c \
		game/global/ctrl.c \
		game/global/entity.c \
		game/global/screen.c \
		game/global/entity_move.c \
		game/global/key_and_btn.c \

OBJS = ${SRCS:.c=.o}

all:	${NAME}

$(MLX):
	make -C minilibx-linux-v2

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

${NAME}: $(MLX) $(OBJS)
	@echo "Compiling so_long..."
	$(CC) ${CFLAGS}  $(OBJS) ./minilibx-linux-v2/libmlx.a -lXext -lX11 -lXpm -o $(NAME)

clean:
	rm -f ${OBJS} ${NAME}

fclean: clean
	rm -f ${NAME}
	@$(MAKE) -C minilibx-linux-v2 clean

re: clean all

.PHONY: all clean fclean re
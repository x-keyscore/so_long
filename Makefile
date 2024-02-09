# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 15:32:20 by anraymon          #+#    #+#              #
#    Updated: 2024/02/09 01:32:49 by anraymon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = so_long
CC     = gcc
CFLAGS = -Wall -Wextra -Werror -g
MLX = minilibx-linux-v2/libmlx.a
SRCS   = so_long.c \
		util.c \
		util_img.c \
		parser/parser.c \
		parser/map_1.c \
		parser/map_2.c \
		game/game.c \
		game/game_loop.c \
		game/global/ctrl.c \
		game/global/entity.c \
		game/global/screen.c \
		game/global/entity_move.c \
		game/global/key_and_btn.c \
		game/specific/bg.c \
		game/specific/home.c \
		game/specific/scoreboard.c \
		game/specific/tree.c \
		game/specific/fish.c \
		game/specific/fish_move.c \
		game/specific/light.c \
		game/specific/ground.c \
		game/specific/player.c \
		game/specific/spaceship.c \
		

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
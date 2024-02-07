/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 06:38:48 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/07 05:10:36 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./minilibx-linux-v2/mlx.h"
# include <time.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

# include <stdio.h> //delete

# define CHAR_LIST "01CEPFT"
# define CHAR_WALL '1'
# define CHAR_ITEM 'C'
# define CHAR_EXIT 'E'
# define CHAR_PERS 'P'
# define CHAR_FISH 'F'
# define CHAR_TREE 'T'

# define BASE 64

# define FPS_TARGET 750
# define FPS_INTERVAL 1.0

# define MAP_MAX_WIDTH 1500
# define MAP_MAX_HEIGHT 1499

typedef struct s_axis
{
	int	x;
	int	y;
} t_axis;

typedef struct s_size
{
	int	w;
	int	h;
} t_size;

typedef struct s_move
{
	int	left;
	int	right;
	int	up;
	int	down;
} t_move;

typedef struct s_img
{
	t_size	size;
	void	*ptr;
} t_img;

typedef struct s_entity
{
	t_axis	axis;
	t_size	size;
	double	mv_pix;
	double	mv_spd;
	int		dir;
	int		on_dir;
	int		on_thruster;
	int		on_display;
} t_entity;

typedef struct s_light
{
	t_axis	axis;
	int		on_active;

} t_light;

typedef struct s_ground
{
	t_axis	axis;
	int		size;
} t_ground;

typedef struct s_object
{
	t_axis	axis;
	t_size	size;
	int		action;
} t_object;

typedef struct s_home
{
	int 	id_msg;
	int		id_select;
	int		on_active;
} t_home;

typedef struct s_vars
{
	time_t 			FPS_start_time;
	int 			FPS_frame_count;
	int 			FPS;

	void			*mlx;
	void			*win;
	char			*map;
	t_size			win_view;
	t_size			win_real;
	t_axis			win_move;
	t_axis			win_gap;
	double			ctrl_step;
	int				ctrl_state;

	t_img			home_xpm[7];
	t_home			home[1];
	size_t			home_len;

	t_img			player_xpm[2];
	t_entity		player[1];
	size_t			player_len;

	t_img			spaceship_xpm[2];
	t_entity		spaceship[1];
	size_t			spaceship_len;

	t_img			fish_xpm[2];
	t_entity		*fish;
	size_t			fish_len;

	t_img			light_xpm[2];
	t_light			*light;
	size_t			light_len;
	size_t			light_on;

	t_img			ground_xpm[4];
	t_ground		*ground;
	size_t			ground_len;

	t_img			tree_xpm[1];
	t_axis			*tree;
	size_t			tree_len;

	t_img			bg_img[1];
} t_vars;

int		check_spawn(t_vars *vars, char *map, t_size size, t_axis axis, int mode);
void	check_path(t_vars *vars, char *map_path);
void	parser_get_map(t_vars *vars, char *map_path, t_size *size);
void	parser_set_value(t_vars *vars, char *map, t_size map_size);

char	*map_read(char *filename);
void	map_size(t_vars *vars, char *map, t_size *size);
void	map_ground_border(t_vars *vars, char *map, t_size size);
void	map_ground_platform(t_vars *vars, char *map, t_size size);

void	map_tree(t_vars *vars, char *map, t_size size);
void	map_fish(t_vars *vars, char *map, t_size size);
void	map_light(t_vars *vars, char *map, t_size size);
void	map_pers_and_exit(t_vars *vars, char *map, t_size size);

void	bg_init(t_vars *vars);
void	bg_setup(t_vars *vars);
void	bg_render(t_vars *vars);

void	home_init(t_vars *vars);
void	home_setup(t_vars *vars);
void	home_handler(t_vars *vars, int state);
void	home_render(t_vars *vars);

void	scoreboard_render(t_vars *vars);

void	tree_init(t_vars *vars);
void	tree_add(t_vars *vars, int x, int y);
void	tree_setup(t_vars *vars);
void	tree_render(t_vars *vars);

void	light_init(t_vars *vars);
void	light_setup(t_vars *vars);
void	light_add(t_vars *vars, int x, int y);
void    light_collision(t_vars *vars, t_axis axis, t_size size);
void	light_render(t_vars *vars);

void	ground_init(t_vars *vars);
void	ground_setup(t_vars *vars);
void	ground_add(t_vars *vars, int x, int y, int size);
int		ground_collision(t_vars *vars, t_axis pos_1, int size_1_w, int size_1_h);
void	ground_render(t_vars *vars);

void	fish_init(t_vars *vars);
void	fish_setup(t_vars *vars);
void	fish_add(t_vars *vars, int x, int y);
void	fish_collision(t_vars *vars);
void	fish_render(t_vars *vars);

void	fish_move(t_vars *vars);

void	player_init(t_vars *vars);
void	player_setup(t_vars *vars);
void	player_add(t_vars *vars, int x, int y);

void	spaceship_init(t_vars *vars);
void	spaceship_setup(t_vars *vars);
void	spaceship_add(t_vars *vars, int x, int y);
void	spaceship_collision(t_vars *vars, t_axis axis, t_size size);

void    entity_init(t_vars *vars, t_entity *entity);
void    entity_set(t_vars *vars, t_entity *entity, t_size size);
void	entity_key_press(t_entity *entity, int type);
void	entity_key_release(t_entity *entity, int type);
void	entity_render(t_vars *vars, t_entity *entity, t_img *xpm);

int		entity_move_up(t_vars *vars, t_entity *entity, t_size e_size);
int		entity_move_left(t_vars *vars, t_entity *entity, t_size e_size);
int		entity_move_right(t_vars *vars, t_entity *entity, t_size e_size);
int		entity_move_gravity(t_vars *vars, t_entity *entity, t_size e_size);
t_move	entity_move(t_vars *vars, t_entity *entity);

void	screen_setup(t_vars *vars, int w, int h);
int		screen_in(t_size win_view, int x, int y, int w, int h);
void	screen_move(t_vars *vars);

void	ctrl_handler(t_vars *vars, int state);
t_entity	*ctrl_get(t_vars *vars);

void	img_list_init(size_t length, t_img *img_list);
void	img_list_destroy(void *mlx_ptr, size_t length, t_img *img_list);
void	img_xpm_load(t_vars *vars, t_img *img, char *file_path);

int		btn_close(t_vars *vars);
int		key_press(int keycode, t_vars *vars);
int		key_release(int keycode, t_vars *vars);

void	game_setup(t_vars *vars, t_size map_size);
void	game_start(t_vars *vars);
void	game_restart(t_vars *vars, t_size map_size);
void	game_exit(t_vars *vars, char *msg);

int		game_loop(void *void_vars);

char*	nbrstr(int n);
void	putstr(char *s, int fd);
int		cmp_c(char c, char *cmp);
int		tern(int cond, int resp_1, int resp_2);
int		overlap(t_axis pos_1, t_size size_1, t_axis pos_2, t_size size_2);

void	vars_init(t_vars *vars);
void	free_vars_list(t_vars *vars);
void	free_vars(t_vars *vars);
void	err(t_vars *vars, char *msg, char *info, int nbr);
int		main(int argc, char **argv);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:34:31 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/09 01:00:52 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_spawn(t_vars *vars, char *map, t_size size, t_axis axis)
{
	int	mode;
	int	x;
	int	y;

	mode = 0;
	x = axis.x;
	y = axis.y;
	if (map[(y * size.w) + (x + y)] == CHAR_PERS)
		mode = 1 * 2;
	if (map[(y * size.w) + (x + y)] == CHAR_FISH
		|| map[(y * size.w) + (x + y)] == CHAR_EXIT)
		mode = 2 * 2;
	else if (map[(y * size.w) + (x + y)] == CHAR_TREE)
		mode = 1 * 3;
	if ((mode == 1 * 2 || mode == 1 * 3 || mode == 2 * 2)
		&& (map[((y + 1) * size.w) + (x + (y + 1))] == CHAR_WALL))
		err(vars, "Invalid spawn.\n", "Line : ", y + 1);
	if (mode == 1 * 3
		&& (map[((y + 2) * size.w) + (x + (y + 2))] == CHAR_WALL))
		err(vars, "Invalid spawn.\n", "Line : ", y + 1);
	if (mode == 2 * 2
		&& ((map[(y * size.w) + ((x + 1) + y)] == CHAR_WALL)
			|| (map[((y + 1) * size.w) + ((x + 1) + (y + 1))] == CHAR_WALL)))
		err(vars, "Invalid spawn.\n", "Line : ", y + 1);
	return (1);
}

void	check_path(t_vars *vars, char *map_path)
{
	int	i;
	int	j;

	i = 0;
	while (map_path[i])
		i++;
	i -= 4;
	if (i <= 0)
		err(vars, "Invalid file type :", "./so_lang [file].ber", -1);
	j = 0;
	while (map_path[i])
	{
		if (map_path[i] != ".ber"[j])
			err(vars, "Invalid file type :", "./so_lang [file].ber", -1);
		i++;
		j++;
	}
}

void	check_spawn_ctrl(t_vars *vars)
{
	t_size	player_s;
	t_axis	player_a;
	t_size	spaceship_s;
	t_axis	spaceship_a;
	int		hover;

	hover = 0;
	player_s = vars->player[0].size;
	player_a = vars->player[0].axis;
	spaceship_a = vars->spaceship[0].axis;
	spaceship_s = vars->spaceship[0].size;
	player_a.x = vars->player[0].axis.x - vars->player[0].size.w;
	if (overlap(player_a, player_s, spaceship_a, spaceship_s))
		hover = 1;
	player_a.x = vars->player[0].axis.x + vars->player[0].size.w;
	if (overlap(player_a, player_s, spaceship_a, spaceship_s))
		hover = 1;
	if (!hover)
		err(vars, "The exit is too far from the player.", NULL, -1);
}

void	parser_get_map(t_vars *vars, char *map_path, t_size *size)
{
	check_path(vars, map_path);
	vars->map = map_read(map_path);
	if (!vars->map)
		err(vars, "A problem occurred while reading the file.", NULL, -1);
	if (!vars->map[0])
		err(vars, "La map est vide.", NULL, -1);
	map_size(vars, vars->map, size);
	if (size->w <= size->h
		|| size->w < 6 || size->h < 4
		|| size->w > MAP_MAX_WIDTH || size->h > MAP_MAX_HEIGHT)
		err(vars, "Invalid map size.\n", NULL, -1);
}

void	parser_set_value(t_vars *vars, char *map, t_size size)
{
	map_ground_border(vars, map, size);
	map_ground_platform(vars, map, size);
	map_fish(vars, map, size);
	map_light(vars, map, size);
	map_tree(vars, map, size);
	map_pers_and_exit(vars, map, size);
	check_spawn_ctrl(vars);
}

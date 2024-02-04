/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:34:31 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/04 23:18:10 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	valid_spawn(t_vars *vars, char *map, t_size size, t_axis axis, int mode)
{
	int x;
	int y;

	x = axis.x;
	y = axis.y;
	if ((mode == 1 * 2 || mode == 1 * 3 || mode == 2 * 2)
	&& (map[((y + 1) * size.w) + (x + (y + 1))] == CHAR_WALL))
		err(vars, NULL, map, "Invalide spawn.\n");
	if (mode == 1 * 3
	&& (map[((y + 2) * size.w) + (x + (y + 2))] == CHAR_WALL))
		err(vars, NULL, map, "Invalide spawn.\n");
	if (mode == 2 * 2
	&& (map[(y * size.w) + ((x + 1) + y)] == CHAR_WALL)
	|| (map[((y + 1) * size.w) + ((x + 1) + ( y + 1))] == CHAR_WALL))
		err(vars, NULL, map, "Invalide spawn.\n");
	return (1);
}

void	parser_start(t_vars *vars, char *map_path)
{
	char	*map;
	t_size	size;

	map = map_read(map_path);
	if (!map)
		err(vars, NULL, map, "Un probleme est survenue lors de la lecture.\n");
	if (!map[0])
		err(vars, NULL, map, "La map est vide.\n");
	map_size(vars, map, &size);
	if (size.w <= size.h
	|| size.w < 6 || size.h < 4
	|| size.w > 1500 || size.h > 1499)
		err(vars, NULL, map, "Taille de map non valide.\n");
	screen_size(vars, (size.w - 2) * BASE, (size.h - 2) * BASE);
	map_ground_border(vars, map, size);
	map_ground_platform(vars, map, size);
	map_fish(vars, map, size);
	map_light(vars, map, size);
	map_tree(vars, map, size);
	map_pers_and_exit(vars, map, size);
	free_map(map);
}
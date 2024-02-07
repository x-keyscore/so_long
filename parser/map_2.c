/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:26:24 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/07 03:47:09 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	map_fish(t_vars *vars, char *map, t_size size)
{
	t_axis	po;
	int		i;

	i = -1;
	po.x = 0;
	po.y = 0;
	while (map[++i])
	{
		if ((po.y && po.y + 1 != size.h && po.x && po.x + 1 != size.w)
		&& map[i] != '\n' && map[i] == CHAR_FISH
		&& check_spawn(vars, map, size, po, 2 * 2))
			fish_add(vars, (po.x - 1) * BASE, (po.y - 1) * BASE);
		po.x = tern((map[i] == '\n' && ++po.y), 0, po.x + 1);
	}
}

void	map_light(t_vars *vars, char *map, t_size size)
{
	t_axis	po;
	int		i;

	i = -1;
	po.x = 0;
	po.y = 0;
	while (map[++i])
	{
		if ((po.y && po.y + 1 != size.h && po.x && po.x + 1 != size.w)
		&& map[i] != '\n' && map[i] == CHAR_ITEM)
			light_add(vars, (po.x - 1) * BASE, (po.y - 1) * BASE);
		po.x = tern((map[i] == '\n' && ++po.y), 0, po.x + 1);
	}
}

void	map_tree(t_vars *vars, char *map, t_size size)
{
	t_axis	po;
	int		i;

	i = -1;
	po.x = 0;
	po.y = 0;
	while (map[++i])
	{
		if ((po.y && po.y + 1 != size.h && po.x && po.x + 1 != size.w)
		&& map[i] != '\n' && map[i] == CHAR_TREE
		&& check_spawn(vars, map, size, po, 1 * 3))
			tree_add(vars, (po.x - 1) * BASE, (po.y - 1) * BASE);
		po.x = tern((map[i] == '\n' && ++po.y), 0, po.x + 1);
	}
}

void	map_pers_and_exit(t_vars *vars, char *map, t_size size)
{
	t_axis	po;
	int		i;
	int		pers;
	int		exit;

	i = -1;
	po.x = 0;
	po.y = 0;
	pers = 0;
	exit = 0;
	while (map[++i])
	{
		if ((po.y && po.y + 1 != size.h && po.x && po.x + 1 != size.w)
		&& map[i] != '\n' && map[i] == CHAR_PERS && ++pers
		&& check_spawn(vars, map, size, po, 1 * 2))
			player_add(vars, (po.x - 1) * BASE, (po.y - 1) * BASE);
		else if ((po.y && po.y + 1 != size.h && po.x && po.x + 1 != size.w)
		&& map[i] != '\n' && map[i] == CHAR_EXIT && ++exit
		&& check_spawn(vars, map, size, po, 2 * 2))
			spaceship_add(vars, (po.x - 1) * BASE, (po.y - 1) * BASE);
		po.x = tern((map[i] == '\n' && ++po.y), 0, po.x + 1);
	}
	if (pers != 1 || exit != 1)
		err(vars, "It takes a player and an exit.", NULL, -1);
}
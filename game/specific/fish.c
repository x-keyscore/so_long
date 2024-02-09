/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fish.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:10:40 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/09 01:36:23 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	fish_init(t_vars *vars)
{
	img_list_init(2, vars->fish_xpm);
	vars->fish_len = 0;
	vars->fish = malloc(vars->fish_len * sizeof(t_entity));
	if (!vars->fish)
		err(vars, "Malloc fail", NULL, -1);
}

void	fish_setup(t_vars *vars)
{
	img_xpm_load(vars, &vars->fish_xpm[0], "./assets/dyn/fish_left.xpm");
	img_xpm_load(vars, &vars->fish_xpm[1], "./assets/dyn/fish_right.xpm");
}

void	fish_add(t_vars *vars, int x, int y)
{
	t_entity	new_fish;

	entity_init(&new_fish);
	vars->fish_len++;
	if (vars->fish_len > 0 && vars->fish_len < INT_MAX)
	{
		vars->fish = realloc(vars->fish, vars->fish_len * sizeof(t_entity));
		if (!vars->fish)
			err(vars, "Realloc fail", NULL, -1);
	}
	new_fish.axis.x = x;
	new_fish.axis.y = y;
	new_fish.mv_spd = SPEED_FISH;
	entity_set(vars, &new_fish, vars->fish_xpm[0].size);
	vars->fish[vars->fish_len - 1] = new_fish;
}

void	fish_collision(t_vars *vars)
{
	t_entity	*entity;
	t_axis		axis;
	t_size		size;
	int			i;

	entity = ctrl_get(vars);
	axis = entity->axis;
	size = entity->size;
	i = vars->fish_len;
	while (--i > -1)
	{
		if (overlap(axis, size, vars->fish[i].axis, vars->fish_xpm[0].size))
		{
			vars->home->id_msg = 5;
			mlx_loop_end(vars->mlx);
		}
	}
}

void	fish_render(t_vars *vars)
{
	int	i;

	i = vars->fish_len;
	while (--i > -1)
		entity_render(vars, &vars->fish[i], vars->fish_xpm);
}

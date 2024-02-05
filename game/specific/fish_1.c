/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fish_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:10:40 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/05 01:43:08 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	fish_init(t_vars *vars)
{
	vars->fish_len = 0;
	vars->fish = malloc(vars->fish_len * sizeof(t_entity));
	if (!vars->fish)
		err(vars, NULL, NULL, "Malloc fail: fish.\n");
}

void	fish_add(t_vars *vars, int x, int y)
{
	t_entity	new_fish;

	vars->fish_len++;
	if (vars->fish_len > 0)
	{
		vars->fish = realloc(vars->fish, vars->fish_len * sizeof(t_entity));
		if (!vars->fish)
			err(vars, NULL, NULL, "Realloc fail: fish.\n");
	}
	new_fish.axis.x = x;
	new_fish.axis.y = y;
	new_fish.velocity_x = 1;
	new_fish.velocity_y = 1;
	vars->fish[vars->fish_len - 1] = new_fish;
}

void	fish_setup(t_vars *vars)
{
	size_t	i;

	xpm_load(vars->mlx, &vars->fish_xpm[0], "./assets/dyn/fish_left.xpm");
	xpm_load(vars->mlx, &vars->fish_xpm[1], "./assets/dyn/fish_right.xpm");
	if (!vars->fish_xpm[0].img || !vars->fish_xpm[1].img)
		err(vars, NULL, NULL, "Xpm loading fail: fish.\n");
	i = 0;
	while (vars->fish_len && i < vars->fish_len)
	{
		entity_setup(vars, &vars->fish[i], vars->fish_xpm[0].size);
		i++;
	}
}

void	fish_collision(t_vars *vars)
{
	t_entity	*entity;
	t_axis	axis;
	t_size	size;
	int	i;

	entity = ctrl_get(vars);
	axis = entity->axis;
	size = entity->size;
	i = -1;
	while (vars->fish_len && ++i < vars->fish_len)
	{
		if (overlap(axis, size, vars->fish[i].axis, vars->fish_xpm[0].size))
			mlx_loop_end(vars->mlx);
	}
}

void 	fish_render(t_vars *vars)
{
	int	i;

	i = vars->fish_len;
	while (--i > -1)
		entity_render(vars, &vars->fish[i], vars->fish_xpm);
}
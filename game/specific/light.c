/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 06:40:49 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/04 20:37:12 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	light_init(t_vars *vars)
{
	vars->light_len = 0;
	vars->light = malloc(vars->light_len * sizeof(t_light));
	if (!vars->light)
		err(vars, NULL, NULL, "Malloc fail: light.\n");
}

void	light_add(t_vars *vars, int x, int y)
{
	t_light	new_light;

	vars->light_len++;
	if (vars->light_len > 0)
	{
		vars->light = realloc(vars->light, vars->light_len * sizeof(t_light));
		if (!vars->light)
			err(vars, NULL, NULL, "Realloc fail: light.\n");
	}
	new_light.axis.x = x;
	new_light.axis.y = y;
	new_light.on_active = 0;
	vars->light[vars->light_len - 1] = new_light;
}

void	light_setup(t_vars *vars)
{
	xpm_load(vars->mlx, &vars->light_xpm[0], "./assets/dyn/light_off.xpm");
	xpm_load(vars->mlx, &vars->light_xpm[1], "./assets/dyn/light_on.xpm");
	if (!vars->light_xpm[0].img || !vars->light_xpm[1].img)
		err(vars, NULL, NULL, "Xpm loading fail: light.\n");
}

void    light_collision(t_vars *vars, t_axis axis, t_size size)
{
	int		i;
	
	i = vars->light_len;
	while (--i > -1)
	{
		if (vars->light[i].on_active)
			continue ;
		if (overlap(axis, size, vars->light[i].axis, vars->light_xpm[0].size))
			vars->light[i].on_active = 1;
	}
}

void	light_render(t_vars *vars)
{
	int	count;
	int	i;

	count = 0;
	i = vars->light_len;
	while (--i > -1)
	{
		if (vars->light[i].on_active)
			 count++;
		vars->light[i].axis.x += vars->win_move.x;
		vars->light[i].axis.y += vars->win_move.y;
		mlx_put_image_to_window(vars->mlx, vars->win, vars->light_xpm[vars->light[i].on_active].img, vars->light[i].axis.x, vars->light[i].axis.y);
	}
	if (count == vars->light_len && vars->ctrl_toggler)
		mlx_loop_end(vars->mlx);
}
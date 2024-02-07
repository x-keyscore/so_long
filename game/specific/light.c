/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 06:40:49 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/07 03:42:24 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	light_init(t_vars *vars)
{
	img_list_init(2, vars->light_xpm);
	vars->light_len = 0;
	vars->light = malloc(vars->light_len * sizeof(t_light));
	if (!vars->light)
		err(vars, "Malloc fail", NULL, -1);
}

void	light_setup(t_vars *vars)
{
	img_xpm_load(vars, &vars->light_xpm[0], "./assets/dyn/light_off.xpm");
	img_xpm_load(vars, &vars->light_xpm[1], "./assets/dyn/light_on.xpm");
}

void	light_add(t_vars *vars, int x, int y)
{
	t_light	new_light;

	vars->light_len++;
	if (vars->light_len > 0 && vars->light_len < INT_MAX)
	{
		vars->light = realloc(vars->light, vars->light_len * sizeof(t_light));
		if (!vars->light)
			err(vars, "Realloc fail", NULL, -1);
	}
	new_light.axis.x = x;
	new_light.axis.y = y;
	new_light.on_active = 0;
	vars->light[vars->light_len - 1] = new_light;
}

void    light_collision(t_vars *vars, t_axis axis, t_size size)
{
	int	i;
	
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
	t_size	light;
	int		i;

	light = vars->light_xpm[0].size;
	vars->light_on = 0;
	i = vars->light_len;
	while (--i > -1)
	{
		if (vars->light[i].on_active)
			 vars->light_on++;
		vars->light[i].axis.x += vars->win_move.x;
		vars->light[i].axis.y += vars->win_move.y;
		if (screen_in(vars->win_view, vars->light[i].axis.x,
			vars->light[i].axis.y, light.w, light.h))
			continue ;
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->light_xpm[vars->light[i].on_active].ptr,
			vars->light[i].axis.x, vars->light[i].axis.y);
	}
	if (vars->light_on == vars->light_len && vars->ctrl_state)
	{
		vars->home->id_msg = 4;
		mlx_loop_end(vars->mlx);
	}
}

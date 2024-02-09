/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaceship.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 04:15:07 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/09 01:34:52 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	spaceship_init(t_vars *vars)
{
	img_list_init(2, vars->spaceship_xpm);
	entity_init(vars->spaceship);
	vars->spaceship_len = 0;
}

void	spaceship_setup(t_vars *vars)
{
	img_xpm_load(vars, &vars->spaceship_xpm[0], "./assets/dyn/ship_left.xpm");
	img_xpm_load(vars, &vars->spaceship_xpm[1], "./assets/dyn/ship_right.xpm");
}

void	spaceship_add(t_vars *vars, int x, int y)
{
	vars->spaceship_len = 1;
	vars->spaceship[0].axis.x = x;
	vars->spaceship[0].axis.y = y;
	vars->spaceship[0].mv_spd = SPEED_SPACESHIP;
	entity_set(vars, &vars->spaceship[0], vars->spaceship_xpm[0].size);
}

void	spaceship_collision(t_vars *vars, t_axis axis, t_size size)
{
	if (vars->ctrl_state == 1)
		return ;
	if (overlap(axis, size, vars->spaceship[0].axis, vars->spaceship[0].size))
		ctrl_handler(vars, 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaceship.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 04:15:07 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/05 01:28:02 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	spaceship_init(t_vars *vars)
{
	vars->spaceship_len = 1;
}

void	spaceship_axis(t_vars *vars, int x, int y)
{
	vars->spaceship[0].axis.x = x;
	vars->spaceship[0].axis.y = y;
}

void	spaceship_setup(t_vars *vars)
{
	xpm_load(vars->mlx, &vars->spaceship_xpm[0], "./assets/dyn/ship_left.xpm");
	xpm_load(vars->mlx, &vars->spaceship_xpm[1], "./assets/dyn/ship_right.xpm");
	if (!vars->spaceship_xpm[0].img || !vars->spaceship_xpm[1].img)
		err(vars, NULL, NULL, "Xpm loading fail: fish.\n");
	vars->spaceship[0].velocity_x = VELOCITY;
	vars->spaceship[0].velocity_y = GRAVITY;
	entity_setup(vars, &vars->spaceship[0], vars->spaceship_xpm[0].size);
}

void	spaceship_collision(t_vars *vars, t_axis axis, t_size size)
{
	if (vars->ctrl_toggler == 1)
		return ;
	if (overlap(axis, size, vars->spaceship[0].axis, vars->spaceship[0].size))
		ctrl_handler(vars, 1);
}

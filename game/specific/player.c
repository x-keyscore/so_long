/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 04:14:56 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/05 01:25:05 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	player_init(t_vars *vars)
{
	vars->player_len = 1;
}

void	player_axis(t_vars *vars, int x, int y)
{
	vars->player[0].axis.x = x;
	vars->player[0].axis.y = y;
}

void	player_setup(t_vars *vars)
{
	xpm_load(vars->mlx, &vars->player_xpm[0], "./assets/dyn/pers_left.xpm");
	xpm_load(vars->mlx, &vars->player_xpm[1], "./assets/dyn/pers_right.xpm");
	if (!vars->fish_xpm[0].img || !vars->fish_xpm[0].img)
		err(vars, NULL, NULL, "Xpm loading fail: player.\n");
	vars->player[0].velocity_x = VELOCITY;
	vars->player[0].velocity_y = GRAVITY;
	entity_setup(vars, &vars->player[0], vars->player_xpm[0].size);
}

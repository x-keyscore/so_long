/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 04:14:56 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/09 01:34:49 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	player_init(t_vars *vars)
{
	img_list_init(2, vars->player_xpm);
	entity_init(vars->player);
	vars->player_len = 0;
}

void	player_setup(t_vars *vars)
{
	img_xpm_load(vars, &vars->player_xpm[0], "./assets/dyn/pers_left.xpm");
	img_xpm_load(vars, &vars->player_xpm[1], "./assets/dyn/pers_right.xpm");
}

void	player_add(t_vars *vars, int x, int y)
{
	vars->player_len = 1;
	vars->player[0].axis.x = x;
	vars->player[0].axis.y = y;
	vars->player[0].mv_spd = SPEED_PLAYER;
	entity_set(vars, &vars->player[0], vars->player_xpm[0].size);
}

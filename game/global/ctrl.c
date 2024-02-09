/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 04:44:29 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/09 01:05:08 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	ctrl_handler(t_vars *vars, int state)
{
	if (state == 0 && vars->ctrl_state == 1)
	{
		if (vars->spaceship[0].dir == 0)
			vars->player[0].axis.x = vars->spaceship[0].axis.x
				+ (vars->spaceship[0].size.w);
		else if (vars->spaceship[0].dir == 1)
			vars->player[0].axis.x = vars->spaceship[0].axis.x
				- (vars->player[0].size.w);
		vars->player[0].axis.y = vars->spaceship[0].axis.y;
		if (!ground_collision(vars, vars->player[0].axis,
				vars->player[0].size.w, vars->player[0].size.h))
		{
			vars->spaceship[0].on_dir = 0;
			vars->spaceship[0].on_thruster = 0;
			vars->player[0].on_display = 1;
			vars->ctrl_state = 0;
		}
	}
	else if (state == 1 && vars->ctrl_state == 0)
	{
		vars->player[0].on_dir = 0;
		vars->player[0].on_display = 0;
		vars->ctrl_state = 1;
	}
}

t_entity	*ctrl_get(t_vars *vars)
{
	if (!vars->ctrl_state)
		return (&vars->player[0]);
	return (&vars->spaceship[0]);
}

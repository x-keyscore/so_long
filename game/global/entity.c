/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:27:29 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/09 01:33:21 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	entity_init(t_entity *entity)
{
	entity->on_display = 0;
	entity->axis.x = 0;
	entity->axis.y = 0;
	entity->size.w = 0;
	entity->size.h = 0;
	entity->dir = 0;
	entity->on_dir = 0;
	entity->on_thruster = 0;
	entity->mv_spd = 0;
	entity->mv_pix = 1;
}

void	entity_set(t_vars *vars, t_entity *entity, t_size size)
{
	entity->on_display = 1;
	entity->on_dir = 0;
	entity->on_thruster = 0;
	entity->size = size;
	if (vars->win_view.w / 2 > entity->axis.x)
		entity->dir = 1;
	else
		entity->dir = 0;
}

void	entity_key_press(t_entity *entity, int dir)
{
	if (dir == 0 || dir == 1)
	{
		entity->dir = dir;
		entity->on_dir = 1;
	}
	else if (dir == 2)
		entity->on_thruster = 1;
}

void	entity_key_release(t_entity *entity, int dir)
{
	if ((dir == 0 && entity->on_dir && entity->dir == 0)
		|| (dir == 1 && entity->on_dir && entity->dir == 1))
		entity->on_dir = 0;
	else if (dir == 2)
		entity->on_thruster = 0;
}

void	entity_render(t_vars *vars, t_entity *entity, t_img *xpm)
{
	if (!entity->on_display)
		return ;
	entity->axis.x += vars->win_move.x;
	entity->axis.y += vars->win_move.y;
	if (screen_in(vars->win_view, entity->axis.x, entity->axis.y, entity->size))
		return ;
	mlx_put_image_to_window(vars->mlx, vars->win, xpm[entity->dir].ptr,
		entity->axis.x, entity->axis.y);
}

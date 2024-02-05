/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:27:29 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/05 01:41:21 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void    entity_setup(t_vars *vars, t_entity *entity, t_size size)
{
	entity->on_dir = 0;
	entity->on_thruster = 0;
	entity->on_diplay = 1;
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
	if ((dir == 0 && entity->on_dir && entity->dir == 0) || (dir == 1 && entity->on_dir && entity->dir == 1))
		entity->on_dir = 0;
	else if (dir == 2)
		entity->on_thruster = 0;
}

void	entity_render(t_vars *vars, t_entity *entity, t_img *xpm)
{
	if (!entity->on_diplay)
		return ;
	entity->axis.x += vars->win_move.x;
	entity->axis.y += vars->win_move.y;
	if (screen_in(vars->win_view, entity->axis.x, entity->axis.y, entity->size.w, entity->size.h))
		return ;
	mlx_put_image_to_window(vars->mlx, vars->win, xpm[entity->dir].img, entity->axis.x, entity->axis.y);
}
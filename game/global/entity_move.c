/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:34:24 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/09 01:10:23 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

int	entity_move_left(t_vars *vars, t_entity *entity, t_size e_size)
{
	int		i;
	int		dist;
	t_axis	*e_axis;
	t_axis	g_axis;
	t_size	g_size;

	e_axis = &entity->axis;
	g_size = vars->ground_xpm[0].size;
	dist = vars->win_gap.x;
	i = vars->ground_len;
	while (--i > -1)
	{
		g_axis = vars->ground[i].axis;
		if (((g_axis.x + (vars->ground[i].size * g_size.w)) - 1 < e_axis->x)
			&& (g_axis.y - e_size.h < e_axis->y)
			&& (g_axis.y + g_size.w > e_axis->y)
			&& (dist < g_axis.x + (vars->ground[i].size * g_size.w)))
			dist = g_axis.x + (vars->ground[i].size * g_size.w);
	}
	if (e_axis->x - entity->mv_pix > dist)
		e_axis->x -= (int)entity->mv_pix;
	else
		e_axis->x = dist;
	return (tern((e_axis->x - entity->mv_pix > dist), 1, 0));
}

int	entity_move_right(t_vars *vars, t_entity *entity, t_size e_size)
{
	t_axis	*e_axis;
	t_axis	g_axis;
	t_size	g_size;
	int		dist;
	int		i;

	e_axis = &entity->axis;
	g_size = vars->ground_xpm[0].size;
	dist = (vars->win_real.w - (vars->win_gap.x * -1)) - e_size.w;
	i = vars->ground_len;
	while (--i > -1)
	{
		g_axis = vars->ground[i].axis;
		if ((g_axis.x + (vars->ground[i].size * g_size.w) > e_axis->x)
			&& (g_axis.y - e_size.h < e_axis->y)
			&& (g_axis.y + g_size.w > e_axis->y)
			&& (dist > g_axis.x - e_size.w))
			dist = g_axis.x - e_size.w;
	}
	if (e_axis->x + entity->mv_pix < dist)
		e_axis->x += (int)entity->mv_pix;
	else
		e_axis->x = dist;
	return (tern((e_axis->x + entity->mv_pix < dist), 1, 0));
}

int	entity_move_up(t_vars *vars, t_entity *entity, t_size e_size)
{
	int		i;
	int		dist;
	t_axis	*e_axis;
	t_axis	g_axis;
	t_size	g_size;

	e_axis = &entity->axis;
	g_size = vars->ground_xpm[0].size;
	dist = vars->win_gap.y;
	i = vars->ground_len;
	while (--i > -1)
	{
		g_axis = vars->ground[i].axis;
		if (((g_axis.y + g_size.h) <= e_axis->y)
			&& (g_axis.x - e_size.w < e_axis->x)
			&& (g_axis.x + (vars->ground[i].size * g_size.w) > e_axis->x)
			&& (dist < g_axis.y + g_size.h))
			dist = g_axis.y + g_size.h;
	}
	if (e_axis->y - entity->mv_pix > dist)
		e_axis->y -= (int)entity->mv_pix;
	else
		e_axis->y = dist;
	return (tern((e_axis->y - entity->mv_pix > dist), 1, 0));
}

int	entity_move_gravity(t_vars *vars, t_entity *entity, t_size e_size)
{
	int		i;
	int		dist;
	t_axis	*e_axis;
	t_axis	g_axis;
	t_size	g_size;

	e_axis = &entity->axis;
	g_size = vars->ground_xpm[0].size;
	dist = vars->win_real.h;
	i = vars->ground_len;
	while (--i > -1)
	{
		g_axis = vars->ground[i].axis;
		if ((g_axis.y > e_axis->y)
			&& (g_axis.x - e_size.w < e_axis->x)
			&& (g_axis.x + (vars->ground[i].size * g_size.w) > e_axis->x)
			&& (dist > g_axis.y - e_size.h))
			dist = g_axis.y - e_size.h;
	}
	if (e_axis->y + entity->mv_pix < dist)
		e_axis->y += entity->mv_pix;
	else
		e_axis->y = dist;
	return (tern((e_axis->y + entity->mv_pix < dist), 1, 0));
}

t_move	entity_move(t_vars *vars, t_entity *entity)
{
	t_move	move;

	move.left = 0;
	move.right = 0;
	move.up = 0;
	move.down = 0;
	if (entity->on_dir)
	{
		if (entity->dir == 0)
			move.left = entity_move_left(vars, entity, entity->size);
		else if (entity->dir == 1)
			move.right = entity_move_right(vars, entity, entity->size);
	}
	if (entity->on_thruster)
		move.up = entity_move_up(vars, entity, entity->size);
	else
		move.down = entity_move_gravity(vars, entity, entity->size);
	return (move);
}

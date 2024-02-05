/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 23:16:20 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/05 16:15:40 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	screen_set(t_vars *vars, int map_w, int map_h)
{
	t_size view;

	mlx_get_screen_size(vars->mlx, &view.w, &view.h);
	if (map_w > view.w)
		vars->win_view.w = view.w;
	else
		vars->win_view.w = map_w;
	if (map_h > view.h)
		vars->win_view.h = view.h;
	else
		vars->win_view.h = map_h;
	vars->win_real.w = map_w;
	vars->win_real.h = map_h;
	vars->win_move.x = 0;
	vars->win_move.y = 0;
	vars->win_gap = vars->win_move;
}

int	screen_in(t_size win_view, int x, int y, int w, int h)
{
	if (x + w < 0 || y + h < 0
		|| x > win_view.w || y > win_view.h)
		return (1);
	return (0);
}

void	screen_move(t_vars *vars)
{
	t_entity	*entity;
	t_axis		e_axis;
	t_size		e_size;

	entity = ctrl_get(vars);
	e_axis = entity->axis;
	e_size = entity->size;
	if ((vars->win_gap.x * -1 < vars->win_real.w - vars->win_view.w)
		&& (e_axis.x + (e_size.w / 2) > vars->win_view.w / 2))
		vars->win_move.x = tern(((e_axis.x > vars->win_view.w)), -2, -1);
	else if ((vars->win_gap.x < 0)
	&& (e_axis.x + (e_size.w / 2) < vars->win_view.w / 2))
		vars->win_move.x = +1;
	if ((vars->win_gap.y * -1 < vars->win_real.h - vars->win_view.h)
		&& (e_axis.y + (e_size.w / 2) > vars->win_view.h / 2))
		vars->win_move.y = tern(((e_axis.y > vars->win_view.h)), -2, -1);
	else if ((vars->win_gap.y < 0)
	&& (e_axis.y + (e_size.w / 2) < vars->win_view.h / 2))
		vars->win_move.y = +1;
	vars->win_gap.x += vars->win_move.x;
	vars->win_gap.y += vars->win_move.y;
}

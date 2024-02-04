/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ground.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 07:03:41 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/04 20:37:13 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	ground_init(t_vars *vars)
{
	vars->ground_len = 0;
	vars->ground = malloc(vars->ground_len * sizeof(t_ground));
	if (!vars->ground)
		err(vars,  NULL, NULL, "Malloc fail: ground.\n");
}

void	ground_add(t_vars *vars, int x, int y, int size)
{
	t_ground	new_ground;

	vars->ground_len++;
	if (vars->ground_len > 0)
	{
		vars->ground = realloc(vars->ground, vars->ground_len * sizeof(t_ground));
		if (!vars->ground)
			err(vars,  NULL, NULL, "Realloc fail: ground.\n");
	}
	new_ground.axis.x = x;
	new_ground.axis.y = y;
	new_ground.size = size;
	vars->ground[vars->ground_len - 1] = new_ground;
}

void	ground_setup(t_vars *vars)
{
	xpm_load(vars->mlx, &vars->ground_xpm[0], "./assets/stc/ground_1.xpm");
	xpm_load(vars->mlx, &vars->ground_xpm[1], "./assets/stc/ground_2.xpm");
	xpm_load(vars->mlx, &vars->ground_xpm[2], "./assets/stc/ground_3.xpm");
	xpm_load(vars->mlx, &vars->ground_xpm[3], "./assets/stc/ground_4.xpm");
	if (!vars->ground_xpm[0].img || !vars->ground_xpm[1].img
	|| !vars->ground_xpm[2].img || !vars->ground_xpm[3].img)
		err(vars, NULL, NULL, "Xpm loading fail: ground.\n");
}

int	ground_collision(t_vars *vars, t_axis pos_1, int size_1_w, int size_1_h)
{
	size_t	i;
	int		size;
	t_axis	pos_2;
	t_img	xpm_2;

	xpm_2 = vars->ground_xpm[0];
	i = 0;
	while (vars->ground_len && i < vars->ground_len)
	{
		pos_2 = vars->ground[i].axis;
		size = vars->ground[i].size;
		if ((pos_1.x < pos_2.x + (size * xpm_2.size.w))
		&& (pos_1.x + size_1_w > pos_2.x)
		&& (pos_1.y < pos_2.y + xpm_2.size.h)
		&& (pos_1.y + size_1_h > pos_2.y))
			return (1);
		i++;
	}
	return (0);
}

void	ground_render(t_vars *vars)
{
	int		i;
	int		i_grd;
	int		i_img;
	t_axis	axis;
	t_size	size;

	size = vars->ground_xpm[0].size;
	i_img = 0;
	i = vars->ground_len;
	while (--i > -1)
	{
		vars->ground[i].axis.x += vars->win_move.x;
		vars->ground[i].axis.y += vars->win_move.y;
		axis = vars->ground[i].axis;
		i_grd = vars->ground[i].size;
		while (--i_grd > -1)
		{
			mlx_put_image_to_window(vars->mlx, vars->win, vars->ground_xpm[i_img].img, axis.x + (i_grd * size.w), axis.y);
			if (++i_img > 3)
				i_img = 0;
		}
	}
}
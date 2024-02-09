/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ground.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 07:03:41 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/09 01:15:21 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	ground_init(t_vars *vars)
{
	img_list_init(4, vars->ground_xpm);
	vars->ground_len = 0;
	vars->ground = malloc(vars->ground_len * sizeof(t_ground));
	if (!vars->ground)
		err(vars, "Malloc fail", NULL, -1);
}

void	ground_setup(t_vars *vars)
{
	img_xpm_load(vars, &vars->ground_xpm[0], "./assets/stc/ground_1.xpm");
	img_xpm_load(vars, &vars->ground_xpm[1], "./assets/stc/ground_2.xpm");
	img_xpm_load(vars, &vars->ground_xpm[2], "./assets/stc/ground_3.xpm");
	img_xpm_load(vars, &vars->ground_xpm[3], "./assets/stc/ground_4.xpm");
}

void	ground_add(t_vars *vars, int x, int y, int size)
{
	t_ground	new_ground;

	vars->ground_len++;
	if (vars->ground_len > 0 && vars->ground_len < INT_MAX)
	{
		vars->ground = realloc(vars->ground,
				vars->ground_len * sizeof(t_ground));
		if (!vars->ground)
			err(vars, "Realloc fail", NULL, -1);
	}
	new_ground.axis.x = x;
	new_ground.axis.y = y;
	new_ground.size = size;
	vars->ground[vars->ground_len - 1] = new_ground;
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
	t_img	*xpm;
	t_axis	axis;
	int		i_grd;
	int		i_xpm;
	int		i;

	xpm = vars->ground_xpm;
	i_xpm = 0;
	i = vars->ground_len;
	while (--i > -1)
	{
		vars->ground[i].axis.x += vars->win_move.x;
		vars->ground[i].axis.y += vars->win_move.y;
		axis = vars->ground[i].axis;
		i_grd = vars->ground[i].size;
		while (--i_grd > -1)
		{
			i_xpm = tern((i_xpm > 2), 0, i_xpm + 1);
			if (screen_in(vars->win_view, axis.x + (i_grd * xpm[0].size.w),
					axis.y, xpm[0].size))
				continue ;
			mlx_put_image_to_window(vars->mlx, vars->win, xpm[i_xpm].ptr,
				axis.x + (i_grd * xpm[0].size.w), axis.y);
		}
	}
}

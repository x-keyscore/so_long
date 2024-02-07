/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:48:45 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/07 15:50:15 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	bg_init(t_vars *vars)
{
	img_list_init(1, vars->bg_img);
}

void	bg_setup(t_vars *vars)
{
	int		i;
	t_axis	pos;

	vars->bg_img[0].ptr = mlx_new_image(vars->mlx, vars->win,
		vars->win_view.w, vars->win_view.h);
	if (!vars->bg_img[0].ptr)
		err(vars, "Failed to create new image.", NULL, -1);
	i = -1;
	while (++i < 125)
	{
		pos.x = rand() % vars->win_view.w;
		pos.y = rand() % vars->win_view.h;
		mlx_pixel_put_image(vars->mlx, vars->bg_img[0].ptr,
			pos.x, pos.y, 0x00FFFFFF);
	}
	mlx_load_image(vars->mlx,vars->win, vars->bg_img[0].ptr);
}

void	bg_render(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg_img[0].ptr, 0, 0);
}

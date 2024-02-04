/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:48:45 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/04 21:55:00 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	star_setup(t_vars *vars)
{
	int		i;
	t_axis	pos;

	vars->star_img[0].img = mlx_new_image(vars->mlx, vars->win_view.w, vars->win_view.h);
	if (!vars->star_img[0].img)
		err(vars, NULL, NULL, "Create new image fail: start.\n");
	i = -1;
	while (++i < 125)
	{
		pos.x = rand() % vars->win_view.w;
		pos.y = rand() % vars->win_view.h;
		mlx_pixel_put_image(vars->mlx, vars->star_img[0].img, pos.x, pos.y, 0x00FFFFFF);
	}
	mlx_load_image(vars->mlx, vars->star_img[0].img);
}

void	star_render(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->star_img[0].img, 0, 0);
}
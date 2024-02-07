/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:06:22 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/07 03:42:35 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	home_init(t_vars *vars)
{
	img_list_init(4, vars->home_xpm);
	vars->home_len = 0;
	vars->home->on_active = 0;
	vars->home->id_msg = 0;
	vars->home->id_select = 0;
}

void	home_setup(t_vars *vars)
{
	vars->home_len = 1;
	vars->home->on_active = 1;
	vars->home->id_msg = 6;
	vars->home->id_select = 0;
	img_xpm_load(vars, &vars->home_xpm[0], "./assets/dyn/play_1.xpm");
	img_xpm_load(vars, &vars->home_xpm[1], "./assets/dyn/play_2.xpm");
	img_xpm_load(vars, &vars->home_xpm[2], "./assets/dyn/exit_1.xpm");
	img_xpm_load(vars, &vars->home_xpm[3], "./assets/dyn/exit_2.xpm");
	img_xpm_load(vars, &vars->home_xpm[4], "./assets/stc/win.xpm");
	img_xpm_load(vars, &vars->home_xpm[5], "./assets/stc/loss.xpm");
	img_xpm_load(vars, &vars->home_xpm[6], "./assets/stc/pulsar.xpm");
}

void	home_handler(t_vars *vars, int state)
{
	if (state == 0)
	{
		if (vars->home->id_select == 0)
			vars->home->id_select = 1;
		else if (vars->home->id_select == 1)
			vars->home->id_select = 0;
	}
	else if (state == 1)
	{
		if (vars->home->id_select == 0)
			vars->home->on_active = 0;
		else if (vars->home->id_select == 1)
			game_exit(vars, "You leaved the game.\n");
	}
}

void	home_render(t_vars *vars)
{
	void	*mlx;
	void	*win;
	t_home	*home;
	t_img	*xpm;
	t_axis	axis;

	mlx = vars->mlx;
	win = vars->win;
	home = vars->home;
	xpm = vars->home_xpm;
	axis.x = (vars->win_view.w / 2) - 128;
	axis.y = (vars->win_view.h / 2) - 64;
	if (!vars->home->on_active)
		return ;
	mlx_put_image_to_window(mlx, win, xpm[home->id_msg].ptr, axis.x, axis.y);
	axis.y += 64;
	if (vars->home->id_select == 0)
		mlx_put_image_to_window(mlx, win, xpm[1].ptr, axis.x, axis.y);
	else
		mlx_put_image_to_window(mlx, win, xpm[0].ptr, axis.x, axis.y);
	if (vars->home->id_select == 1)
		mlx_put_image_to_window(mlx, win, xpm[3].ptr, axis.x + 128, axis.y);
	else
		mlx_put_image_to_window(mlx, win, xpm[2].ptr, axis.x + 128, axis.y);
}

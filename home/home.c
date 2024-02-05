/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:00:57 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/05 15:49:30 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	home_init_and_setup(t_home *home)
{
	home->mlx = mlx_init();
	home->select = 0;
	home->win = mlx_new_window(home->mlx, 300, 75, "Pulsar Home");
	xpm_load(home->mlx, &home->play_xpm[0], "./assets/dyn/play_1.xpm");
	xpm_load(home->mlx, &home->play_xpm[1], "./assets/dyn/play_2.xpm");
	xpm_load(home->mlx, &home->exit_xpm[0], "./assets/dyn/exit_1.xpm");
	xpm_load(home->mlx, &home->exit_xpm[1], "./assets/dyn/exit_2.xpm");
}

int	home_render(void *void_home)
{
	t_home	*home = (t_home*)void_home;

	if (home->select == 0)
		mlx_put_image_to_window(home->mlx, home->win, home->play_xpm[1].img, 0, 0);
	else
		mlx_put_image_to_window(home->mlx, home->win, home->play_xpm[0].img, 0, 0);
	if (home->select == 1)
		mlx_put_image_to_window(home->mlx, home->win, home->exit_xpm[1].img, 150, 0);
	else
		mlx_put_image_to_window(home->mlx, home->win, home->exit_xpm[0].img, 150, 0);
	return (0);
}

int	home_close(t_home *home)
{
	home->select = 1;
	mlx_loop_end(home->mlx);
	return (0);
}

int	home_select(int keycode, t_home *home)
{
	if (keycode == 65307)
	{
		home->select = 1;
		mlx_loop_end(home->mlx);
	}
	else if (keycode == 65289)
	{
		if (home->select == 0)
			home->select = 1;
		else if (home->select == 1)
			home->select = 0;
	}
	else if (keycode == 65293)
	{
		if (home->select == 0 || home->select == 1)
			mlx_loop_end(home->mlx);
	}
	return (0);
}

void	home_start(t_home *home)
{
	mlx_hook(home->win, 2, 1L<<0, home_select, home);
	mlx_hook(home->win, 17, 0L, home_close, home);
	mlx_loop_hook(home->mlx, home_render, home);
	mlx_loop(home->mlx, 60);
}
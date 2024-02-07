/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:47:01 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/07 04:57:52 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	game_setup(t_vars *vars, t_size	map_size)
{
	vars->mlx = mlx_init();
	screen_setup(vars, (map_size.w - 2) * BASE, (map_size.h - 2) * BASE);
	vars->win = mlx_new_window(vars->mlx, vars->win_view.w, vars->win_view.h,
		"so_long");
	mlx_string_put(vars->mlx, vars->win, 35, 40, 0x00FFFFFF, "Loading...");
	bg_setup(vars);
	home_setup(vars);
	tree_setup(vars);
	fish_setup(vars);
	light_setup(vars);
	ground_setup(vars);
	player_setup(vars);
	spaceship_setup(vars);
}

void	game_start(t_vars *vars)
{
	mlx_hook(vars->win, 17, 0, btn_close, vars);
	mlx_hook(vars->win, 2, 1L<<0, key_press, vars);
	mlx_hook(vars->win, 3, 1L<<1, key_release, vars);
	mlx_loop_hook(vars->mlx, game_loop, vars);
	mlx_do_key_autorepeatoff(vars->mlx);
	mlx_do_sync(vars->mlx);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_loop_restart(vars->mlx);
	mlx_loop(vars->mlx, FPS_TARGET);
}

void	game_restart(t_vars *vars, t_size map_size)
{
	mlx_loop_restart(vars);
	screen_setup(vars, (map_size.w - 2) * BASE, (map_size.h - 2) * BASE);
	vars->home->on_active = 1;
	vars->ctrl_state = 0;
	vars->ctrl_step = 0;
	vars->light_on = 0;
	vars->fish_len = 0;
	vars->tree_len = 0;
	vars->light_len = 0;
	vars->ground_len = 0;
}

void	game_exit(t_vars *vars, char *msg)
{
	if (msg)
		putstr(msg, 1);
	free_vars(vars);
	exit(0);
}

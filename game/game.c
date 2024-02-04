/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:47:01 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/04 21:54:37 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	game_init(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = NULL;
	vars->ctrl_toggler = 0;
	tree_init(vars);
	fish_init(vars);
	light_init(vars);
	ground_init(vars);
	player_init(vars);
	spaceship_init(vars);
}

void	game_setup(t_vars *vars)
{
	vars->win = mlx_new_window(vars->mlx, vars->win_view.w, vars->win_view.h, "Pulsar Game");
	tree_setup(vars);
	fish_setup(vars);
	star_setup(vars);
	light_setup(vars);
	ground_setup(vars);
	player_setup(vars);
	spaceship_setup(vars);
}

int game_render(void *void_vars)
{
	t_vars	*vars = (t_vars*)void_vars;

	usleep(SLEEP_TIME);
	mlx_clear_window(vars->mlx, vars->win);
	fish_move(vars);
	entity_move(vars, &vars->player[0]);
	entity_move(vars, &vars->spaceship[0]);
	fish_collision(vars);
	spaceship_collision(vars, vars->player[0].axis, vars->player_xpm[0].size);
	if (!vars->ctrl_toggler)
		light_collision(vars, vars->player[0].axis, vars->player_xpm[0].size);
	screen_move(vars);
	star_render(vars);
	tree_render(vars);
	ground_render(vars);
	entity_render(vars, &vars->player[0], vars->player_xpm);
	entity_render(vars, &vars->spaceship[0], vars->spaceship_xpm);
	fish_render(vars);
	light_render(vars);
	vars->win_move.x = 0;
	vars->win_move.y = 0;
	return (0);
}

void	game_start(t_vars *vars)
{
	mlx_hook(vars->win, 17, 0, btn_close, vars);
	mlx_hook(vars->win, 2, 1L<<0, key_press, vars);
	mlx_hook(vars->win, 3, 1L<<1, key_release, vars);
	mlx_loop_hook(vars->mlx, game_render, vars);
	mlx_do_key_autorepeatoff(vars->mlx);
	mlx_loop(vars->mlx);
}

void	game_exit(t_vars *vars, char *msg)
{
	if (msg)
		putstr(msg, 1);
	free_vars(vars);
	exit(0);
}

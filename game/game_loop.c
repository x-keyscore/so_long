/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:39:36 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/07 04:56:44 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	game_move(t_vars *vars)
{
	t_move	move;
	
	move = entity_move(vars, &vars->player[0]);
	if (!vars->ctrl_state && (move.left || move.right || move.up || move.down))
		vars->ctrl_step += 0.04;
	move = entity_move(vars, &vars->spaceship[0]);
	if (vars->ctrl_state && (move.left || move.right || move.up || move.down))
		vars->ctrl_step += 0.04;
	fish_move(vars);
	screen_move(vars);
}

void	game_collision(t_vars *vars)
{
	fish_collision(vars);
	if (!vars->ctrl_state)
	{
		spaceship_collision(vars, vars->player[0].axis, vars->player[0].size);
		light_collision(vars, vars->player[0].axis, vars->player[0].size);
	}
}

void	game_render(t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	bg_render(vars);
	light_render(vars);
	tree_render(vars);
	ground_render(vars);
	entity_render(vars, &vars->player[0], vars->player_xpm);
	entity_render(vars, &vars->spaceship[0], vars->spaceship_xpm);
	fish_render(vars);
	scoreboard_render(vars);
}

int game_loop(void *void_vars)
{
	t_vars	*vars;
	time_t	FPS_end_time;
	double	FPS_elapsed_time;

	vars = (t_vars*)void_vars;
	vars->FPS_frame_count++;
	FPS_end_time = time(NULL);
	FPS_elapsed_time = difftime(FPS_end_time, vars->FPS_start_time);
	if (FPS_elapsed_time >= FPS_INTERVAL)
	{
		vars->FPS = vars->FPS_frame_count / FPS_elapsed_time;
		vars->FPS_frame_count = 0;
		vars->FPS_start_time = time(NULL);
	}
	if (vars->home->on_active)
	{
		bg_render(vars);
		home_render(vars);
		return (0);
	}
	game_move(vars);
	game_collision(vars);
	game_render(vars);
	return (0);
}
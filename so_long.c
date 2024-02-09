/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:28:57 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/09 01:23:33 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	vars_init(t_vars *vars)
{
	vars->mlx = NULL;
	vars->win = NULL;
	vars->map = NULL;
	vars->fps = 0;
	vars->fps_start_time = time(NULL);
	vars->fps_frame_count = 0;
	vars->ctrl_state = 0;
	vars->ctrl_step = 0;
	vars->light_on = 0;
	bg_init(vars);
	home_init(vars);
	tree_init(vars);
	fish_init(vars);
	light_init(vars);
	ground_init(vars);
	player_init(vars);
	spaceship_init(vars);
}

void	free_vars_list(t_vars *vars)
{
	free(vars->ground);
	vars->ground = NULL;
	free(vars->fish);
	vars->fish = NULL;
	free(vars->light);
	vars->light = NULL;
	free(vars->tree);
	vars->tree = NULL;
}

void	free_vars(t_vars *vars)
{
	if (!vars)
		return ;
	if (vars->map)
		free(vars->map);
	if (vars->mlx && vars->win)
	{
		img_list_destroy(vars->mlx, 1, vars->bg_img);
		img_list_destroy(vars->mlx, 7, vars->home_xpm);
		img_list_destroy(vars->mlx, 1, vars->tree_xpm);
		img_list_destroy(vars->mlx, 2, vars->fish_xpm);
		img_list_destroy(vars->mlx, 2, vars->light_xpm);
		img_list_destroy(vars->mlx, 4, vars->ground_xpm);
		img_list_destroy(vars->mlx, 2, vars->player_xpm);
		img_list_destroy(vars->mlx, 2, vars->spaceship_xpm);
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
	}
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		vars->mlx = NULL;
	}
	free_vars_list(vars);
}

/**
* @param msg strings or NULL
* @param info strings or NULL
* @param nbr number or -1 if not used
*/
void	err(t_vars *vars, char *msg, char *info, int nbr)
{
	free_vars(vars);
	putstr("Error\n", 2);
	if (msg)
		putstr(msg, 2);
	if (info)
		putstr(info, 2);
	if (nbr > -1)
		putstr(nbrstr(nbr), 2);
	putstr("\n", 2);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_size	map_size;

	if (argc <= 1 || argc >= 3)
		err(NULL, "Il faut 1 argument.", "./so_long [map].ber", -1);
	vars_init(&vars);
	parser_get_map(&vars, argv[1], &map_size);
	game_setup(&vars, map_size);
	parser_set_value(&vars, vars.map, map_size);
	while (1)
	{
		game_start(&vars);
		game_restart(&vars, map_size);
	}
	free_vars(&vars);
	return (0);
}

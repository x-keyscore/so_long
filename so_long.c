/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:28:57 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/04 23:43:18 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	free_map(char *map)
{
	if (!map)
		return ;
	free(map);
	map = NULL;
}

void	free_home(t_home *home)
{
	if (!home || !home->mlx)
		return ;
	if (home->win)
	{
		xpm_destroy_list(home->mlx, 2, home->play_xpm);
		xpm_destroy_list(home->mlx, 2, home->exit_xpm);
		mlx_destroy_window(home->mlx, home->win);
		home->win = NULL;
	}
	mlx_destroy_display(home->mlx);
	free(home->mlx);
	home->mlx = NULL;
}

void	free_vars(t_vars *vars)
{
	if (!vars || !vars->mlx)
		return ;
	if (vars->win)
	{
		xpm_destroy_list(vars->mlx, 1, vars->star_img);
		xpm_destroy_list(vars->mlx, 1, vars->tree_xpm);
		xpm_destroy_list(vars->mlx, 2, vars->fish_xpm);
		xpm_destroy_list(vars->mlx, 2, vars->light_xpm);
		xpm_destroy_list(vars->mlx, 4, vars->ground_xpm);
		xpm_destroy_list(vars->mlx, 2, vars->player_xpm);
		xpm_destroy_list(vars->mlx, 2, vars->spaceship_xpm);
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
	}
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	vars->mlx = NULL;
	free(vars->ground);
	vars->ground = NULL;
	free(vars->fish);
	vars->fish = NULL;
	free(vars->light);
	vars->light = NULL;
	free(vars->tree);
	vars->tree = NULL;
}

void	err(t_vars *vars, t_home *home, char *map, char *msg)
{
	free_vars(vars);
	free_home(home);
	free_map(map);
	putstr("Error\n", 2);
	putstr(msg, 2);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_home	home;

	vars.mlx = NULL;
	home.mlx = NULL;
	vars.win = NULL;
	home.win = NULL;
	if (argc <= 1 || argc >= 3)
			err(NULL, NULL, NULL, "Il faut 1 argument.\n");
	while (1)
	{
		game_init(&vars);
		parser_start(&vars, argv[1]);
		home_init_and_setup(&home);
		home_start(&home);
		if (home.select == 1)
		{
			free_home(&home);
			free_vars(&vars);
			exit(EXIT_SUCCESS);
		}
		free_home(&home);
		game_setup(&vars);
		game_start(&vars);
		free_vars(&vars);
	}
	return (0);
}
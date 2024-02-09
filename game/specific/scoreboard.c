/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scoreboard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:41:28 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/09 01:16:58 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	scoreboard_render(t_vars *vars)
{
	void	*mlx;
	void	*win;

	mlx = vars->mlx;
	win = vars->win;
	mlx_string_put(mlx, win, 25, 20, 0x00FDAE40, "FPS :");
	mlx_string_put(mlx, win, 95, 20, 0x00FDAE40,
		nbrstr(vars->fps));
	mlx_string_put(mlx, win, 25, 40, 0x00E96C38, "Step :");
	mlx_string_put(mlx, win, 95, 40, 0x00E96C38,
		nbrstr((int)vars->ctrl_step));
	mlx_string_put(mlx, win, 25, 60, 0x004C3C2B, "Light off :");
	mlx_string_put(mlx, win, 95, 60, 0x004C3C2B,
		nbrstr((int)vars->light_len - vars->light_on));
	mlx_string_put(mlx, win, 25, 80, 0x003C6B3A, "Light on :");
	mlx_string_put(mlx, win, 95, 80, 0x003C6B3A,
		nbrstr((int)vars->light_on));
}

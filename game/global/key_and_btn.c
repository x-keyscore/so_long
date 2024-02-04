/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_btn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:40:41 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/03 16:09:27 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"


int key_press(int keycode, t_vars *vars)
{
	t_entity	*entity;

	entity = ctrl_get(vars);
	if (keycode == 65307)
		game_exit(vars, "You leaved the game.\n");
	else if (keycode == 65361 || keycode == 113)//119 w 113 q 115 s 100 d
		entity_key_press(entity, 0);
	else if (keycode == 65363 || keycode == 100)
		entity_key_press(entity, 1);
	else if ((keycode == 65362 || keycode == 119) && vars->ctrl_toggler && !entity->on_thruster)
		entity_key_press(entity, 2);
	else if (keycode == 65505)
		ctrl_handler(vars, 0);
	else if (keycode == 65480)
		mlx_set_full_screen(vars->mlx, vars->win);
	return (0);
}

int key_release(int keycode, t_vars *vars)
{
	t_entity	*entity;

	entity = ctrl_get(vars);
	if (keycode == 65361 || keycode == 113)
		entity_key_release(entity, 0);
	else if (keycode == 65363 || keycode == 100)
		entity_key_release(entity, 1);
	else if ((keycode == 65362 || keycode == 119) && entity->on_thruster)
		entity_key_release(entity, 2);
	return (0);
}

int	btn_close(t_vars *vars)
{
	game_exit(vars, "You leaved the game.\n");
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_btn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:40:41 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/07 03:28:21 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"


int key_press(int keycode, t_vars *vars)
{
	t_entity	*entity;

	entity = ctrl_get(vars);
	if (keycode == 65307)
		game_exit(vars, "You leaved the game.\n");
	else if (keycode == 65361 || keycode == 113)
		entity_key_press(entity, 0);
	else if (keycode == 65363 || keycode == 100)
		entity_key_press(entity, 1);
	else if ((keycode == 65362 || keycode == 119) && vars->ctrl_state)
		entity_key_press(entity, 2);
	else if (keycode == 65505)
		ctrl_handler(vars, 0);
	else if (keycode == 65289)
		home_handler(vars, 0);
	else if (keycode == 65293)
		home_handler(vars, 1);
	else if (keycode == 112)
	{
		vars->home->on_active = 1;
		vars->home->id_msg = 6;
	}
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
	else if ((keycode == 65362 || keycode == 119))
		entity_key_release(entity, 2);
	return (0);
}

int	btn_close(t_vars *vars)
{
	game_exit(vars, "You leaved the game.\n");
	return (0);
}
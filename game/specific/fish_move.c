/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fish_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:56:55 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/06 15:14:18 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	fish_move(t_vars *vars)
{
	t_size	fi_size;
	t_move	fi_move;
	t_axis	tmp_a;
	int		i;
	int		j;

	i = vars->fish_len;
	while (--i > -1)
	{
		vars->fish[i].mv_pix += vars->fish[i].mv_spd;
		if (vars->fish[i].mv_pix < 1)
			continue ;
		fi_move = entity_move(vars, &vars->fish[i]);
		vars->fish[i].mv_pix = 0;
		vars->fish[i].on_dir = tern((fi_move.down), 0, 1);
		if (!vars->fish[i].on_dir)
			continue ;
		if (!fi_move.left && !fi_move.right)
			vars->fish[i].dir = tern((vars->fish[i].dir), 0, 1);
		fi_size = vars->fish[i].size;
		tmp_a = vars->fish[i].axis;
		tmp_a.x += tern(!vars->fish[i].dir, -1, (fi_size.w + 1));
		if (!fi_move.down && !ground_collision(vars, tmp_a, 0, fi_size.h + 1))
			vars->fish[i].dir = tern((vars->fish[i].dir), 0, 1);
	}
}
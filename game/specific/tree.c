/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:48:00 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/05 01:44:02 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	tree_init(t_vars *vars)
{
	vars->tree_len = 0;
	vars->tree = malloc(vars->tree_len * sizeof(t_axis));
	if (!vars->tree)
		err(vars, NULL, NULL, "Malloc fail: tree.\n");
}

void	tree_add(t_vars *vars, int x, int y)
{
	t_axis	new_tree;

	vars->tree_len++;
	if (vars->tree_len > 0)
	{
		vars->tree = realloc(vars->tree, vars->tree_len * sizeof(t_axis));
		if (!vars->tree)
			err(vars, NULL, NULL, "Realloc fail: tree.\n");
	}
	new_tree.x = x;
	new_tree.y = y;
	vars->tree[vars->tree_len - 1] = new_tree;
}

void	tree_setup(t_vars *vars)
{
	xpm_load(vars->mlx, &vars->tree_xpm[0], "./assets/stc/firtree.xpm");
	if (!vars->tree_xpm[0].img)
		err(vars, NULL, NULL, "Xpm loading fail: tree.\n");
}

void	tree_render(t_vars *vars)
{
	t_size view;
	t_size tree;
	int	i;

	view = vars->win_view;
	tree = vars->tree_xpm[0].size;
	i = vars->tree_len;
	while (--i > -1)
	{
		vars->tree[i].x += vars->win_move.x;
		vars->tree[i].y += vars->win_move.y;
		if (screen_in(vars->win_view, vars->tree[i].x, vars->tree[i].y, tree.w, tree.h))
			continue ;
		mlx_put_image_to_window(vars->mlx, vars->win, vars->tree_xpm[0].img, vars->tree[i].x, vars->tree[i].y);
	}
}

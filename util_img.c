/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:39:08 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/07 16:51:22 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	img_list_init(size_t length, t_img *img_list)
{
	int	i;

	if (length == 0)
		return ;
	i = length;
	while (--i > -1)
	{
		img_list[i].ptr = NULL;
		img_list[i].size.w = 0;
		img_list[i].size.h = 0;
	}
}

void	img_list_destroy(void *mlx_ptr, size_t length, t_img *xpm_list)
{
	int	i;

	if (length == 0)
		return ;
	i = length;
	while (--i > -1)
	{
		if (!xpm_list[i].ptr)
			continue ;
		mlx_destroy_image(mlx_ptr, xpm_list[i].ptr);
		xpm_list[i].ptr = NULL;
	}
}

void	img_xpm_load(t_vars *vars, t_img *img, char *file_path)
{
	img->ptr = mlx_xpm_file_to_image(vars->mlx, vars->win,
		(char *)file_path, &img->size.w, &img->size.h);
	if (!img->ptr)
		err(vars, "Xpm loading fail of :", file_path, -1);
}
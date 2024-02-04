/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:39:08 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/04 23:02:36 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	xpm_load(void *mlx_ptr, t_img *xpm, char *file_path)
{
	xpm->img = mlx_xpm_file_to_image(mlx_ptr, (char *)file_path,
		&xpm->size.w, &xpm->size.h);
}

void	xpm_destroy_list(void *mlx_ptr, size_t length, t_img *xpm_list)
{
	int	i;

	if (length == 0)
		return ;
	i = length; 
	while (--i > -1)
	{
		mlx_destroy_image(mlx_ptr, xpm_list[i].img);
		xpm_list[i].img = NULL;
	}
}
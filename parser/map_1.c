/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:23:15 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/04 17:50:50 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	*map_read(char *filename)
{
	char	c;
	char	*res;
	int		file;
	int		i;

	i = 0;
	file = open(filename, O_RDONLY);
	if (file == -1)
		return (0);
	while (read(file, &c, 1))
		i++;
	close(file);
	res = malloc((i + 1) * sizeof(char));
	file = open(filename, O_RDONLY);
	if (file == -1)
	{
		free(res);
		return (0);
	}
	i = 0;
	while (read(file, &c, 1))
		res[i++] = c;
	res[i] = 0;
	close(file);
	return (res);
}

void	map_size(t_vars *vars, char *map, t_size *size)
{
	size_t	i;
	int		w;
	int		h;

	w = 0;
	while (map[w] && map[w] != '\n' && cmp_c(map[w], CHAR_LIST))
		w++;
	size->w = w;
	i = w;
	h = 0;
	while (map[i] && (map[i] == '\n' || cmp_c(map[i], CHAR_LIST)))
	{
		if (map[i] == '\n' && ++h && w != size->w)
			err(vars, NULL, map, "Une ligne n'est pas valide.\n");
		w = tern((map[i] == '\n'), 0, w + 1);
		i++;
	}
	if (map[i] && !cmp_c(map[i], CHAR_LIST))
		err(vars, NULL, map, "Caractere non valide.\n");
	if (w != size->w)
	err(vars, NULL, map, "Une ligne n'est pas valide.\n");
	size->h = h + 1;
}

void	map_ground_border(t_vars *vars, char *map, t_size size)
{
	t_axis po;
	int	i;

	i = 0;
	po.x = 0;
	po.y = 0;
	while (map[i])
	{
		if ((!po.y || po.y + 1 == size.h || !po.x || po.x + 1 == size.w)
		&& map[i] != '\n' && map[i] != CHAR_WALL)
			err(vars, NULL, map, "Bordures non valide.\n");
		po.x = tern((map[i] == '\n' && ++po.y), 0, po.x + 1);
		i++;
	}
}

void	map_ground_platform(t_vars *vars, char *map, t_size size)
{
	t_axis po;
	t_axis gr;
	int	i;
	int	p;

	p = 0;
	i = -1;
	po.x = 0;
	po.y = 0;
	while (map[++i])
	{
		if ((po.y && po.y + 1 != size.h && po.x && po.x + 1 != size.w)
		&& map[i] != '\n' && map[i] == CHAR_WALL)
		{
			if (!p++)
				gr = po;
		}
		else if (p)
		{
			ground_add(vars, (gr.x - 1) * BASE, (gr.y - 1) * BASE, p);
			p = 0;
		}
		po.x = tern((map[i] == '\n' && ++po.y), 0, po.x + 1);
	}
	ground_add(vars, 0, (po.y - 1) * BASE, (size.w - 2));
}
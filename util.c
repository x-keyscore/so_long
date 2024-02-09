/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anraymon <anraymon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:19:13 by anraymon          #+#    #+#             */
/*   Updated: 2024/02/09 00:04:47 by anraymon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

char	*nbrstr(int n)
{
	static char	str[12];
	long long	nl;
	int			neg;
	int			i;

	neg = tern((n < 0), 1, 0);
	i = 10;
	nl = (long long)n;
	if (nl == 0 || nl > INT_MAX)
		return ("0");
	if (nl < 0)
		nl = -nl;
	str[11] = '\0';
	while (nl != 0)
	{
		str[i--] = nl % 10 + '0';
		nl /= 10;
	}
	if (neg)
		str[i] = '-';
	else
		i++;
	return (&str[i]);
}

void	putstr(char *s, int fd)
{
	size_t	i;

	if (!s || !s[0])
		return ;
	i = 0;
	while (s[i])
		i++;
	i = write(fd, s, i);
}

int	cmp_c(char c, char *cmp)
{
	size_t	i;

	i = 0;
	while (cmp[i])
	{
		if (c == cmp[i])
			return (1);
		i++;
	}
	return (0);
}

int	tern(int cond, int resp_1, int resp_2)
{
	if (cond)
		return (resp_1);
	return (resp_2);
}

int	overlap(t_axis pos_1, t_size size_1, t_axis pos_2, t_size size_2)
{
	return ((pos_1.x < pos_2.x + size_2.w)
		&& (pos_1.x + size_1.w > pos_2.x)
		&& (pos_1.y < pos_2.y + size_2.h)
		&& (pos_1.y + size_1.h > pos_2.y));
}

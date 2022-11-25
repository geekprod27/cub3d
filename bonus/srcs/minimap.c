/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:52:03 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/25 14:59:36 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	img(t_data *d, int coords, int i, int j)
{
	if (d->map[i][j] == '0' || d->map[i][j] == d->spawn)
	{
		d->mlx->mlx_imgadr[coords] = 255;
		d->mlx->mlx_imgadr[coords + 1] = 204;
		d->mlx->mlx_imgadr[coords + 2] = 153;
		d->mlx->mlx_imgadr[coords + 3] = 1;
	}
	if (i == (int)d->posy && j == (int)d->posx)
	{
		d->mlx->mlx_imgadr[coords] = 0;
		d->mlx->mlx_imgadr[coords + 1] = 0;
		d->mlx->mlx_imgadr[coords + 2] = 153;
		d->mlx->mlx_imgadr[coords + 3] = 1;
	}
	if (d->map[i][j] == '1')
	{
		d->mlx->mlx_imgadr[coords] = 255;
		d->mlx->mlx_imgadr[coords + 1] = 153;
		d->mlx->mlx_imgadr[coords + 2] = 153;
		d->mlx->mlx_imgadr[coords + 3] = 1;
	}
}

static int	verif_jump(int *j, size_t l)
{
	if (*j < 0 || *j >= (int)l)
	{
		if (*j < 0)
			*j += 1;
		return (1);
	}
	return (0);
}

static void	y_loop(t_data *d, int i, int *j, size_t l)
{
	int	coords;

	while (d->my < 210 && *j < (int)l)
	{
		coords = d->mx * d->mlx->line_size + d->my * (d->mlx->bitperpixel / 8);
		if (verif_jump(j, l))
			continue ;
		img(d, coords, i, *j);
		if ((d->my + 1) % 10 == 0)
			*j += 1;
		d->my++;
	}
}

void	minimap(t_data *d)
{
	int		i;
	int		j;
	size_t	l;

	i = (int)d->posy - 10;
	while (d->mx < 210 && i < d->xmax)
	{
		j = (int)d->posx - 10;
		d->my = 9;
		if (i < 0 || i >= d->xmax)
		{
			i++;
			continue ;
		}
		l = ft_strlen(d->map[i]);
		y_loop(d, i, &j, l);
		if ((d->mx + 1) % 10 == 0)
			i++;
		d->mx++;
	}
}

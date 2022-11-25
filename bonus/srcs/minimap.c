/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:52:03 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/25 14:48:42 by llepiney         ###   ########.fr       */
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

void	minimap(t_data *d, int x)
{
	int	y;
	int	i;
	int	j;
	size_t	l;
	int	coords;

	i = (int)d->posy - 10;
	while (x < 210 && i < d->xmax)
	{
		j = (int)d->posx - 10;
		y = 9;
		if (i < 0 || i >= d->xmax)
		{
			i++;
			continue ;
		}
		l = ft_strlen(d->map[i]);
		while (y < 210 && j < (int)l)
		{
			coords = x * d->mlx->line_size + y * (d->mlx->bitperpixel / 8);
			if (verif_jump(&j, l))
				continue ;
			img(d, coords, i, j);
			if ((y + 1) % 10 == 0)
				j++;
			y++;
		}
		if ((x + 1) % 10 == 0)
			i++;
		x++;
	}
}

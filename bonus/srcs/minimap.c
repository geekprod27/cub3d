/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:52:03 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/23 18:11:20 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"


void	minimap(t_data *d)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		coords;


	x = 9;
	//printf("posx %f, posy %f\n", d->posx, d->posy);
	i = (int)d->posy - 5;
	while (x < 110 && i < d->xmax)
	{
		j = (int)d->posx - 5;
		y = 9;
		while (y < 110 && j < d->ymax)
		{
			coords = x * d->mlx->line_size + y * (d->mlx->bitperpixel / 8);
			if (i < 0 || i >= d->xmax || j < 0 || j >= d->ymax)
			{
				if (i < 0)
					i++;
				if (j < 0)
					j++;
				continue;
			}
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
			//printf("i:%d, j:%d\n", i, j);
			if ((y + 1) % 10 == 0)
				j++;
			y++;
		}
		if ((x + 1) % 10 == 0)
			i++;
		x++;
	}
}
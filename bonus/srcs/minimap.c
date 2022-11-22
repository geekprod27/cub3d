/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:52:03 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/22 17:39:46 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"


void	minimap(t_data *d)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		tmp;
	int		coords;


	x = 9;
	while (x < 60)
	{
		y = 9;
		while (y < 60)
		{
			tmp = 0;
			while (y < 60 && tmp < 10)
			{
				i = d->posx - 2;
				j =  d->posy - 2;
				coords = x * d->mlx->line_size + y * (d->mlx->bitperpixel / 8);
				if (i < 0 || j < 0)
				{
					d->mlx->mlx_imgadr[coords] = 0;
					d->mlx->mlx_imgadr[coords + 1] = 0;
					d->mlx->mlx_imgadr[coords + 2] = 0;
					d->mlx->mlx_imgadr[coords + 3] = 1;
				}
				else if (i == d->posy && j == d->posx)
				{
					d->mlx->mlx_imgadr[coords] = 0;
					d->mlx->mlx_imgadr[coords + 1] = 0;
					d->mlx->mlx_imgadr[coords + 2] = 153;
					d->mlx->mlx_imgadr[coords + 3] = 1;
				}
				else if (d->map[x / 10][y / 10] == '1')
				{
					d->mlx->mlx_imgadr[coords] = 255;
					d->mlx->mlx_imgadr[coords + 1] = 153;
					d->mlx->mlx_imgadr[coords + 2] = 153;
					d->mlx->mlx_imgadr[coords + 3] = 1;
				}
				else if (d->map[x / 10][y / 10] == '0')
				{
					d->mlx->mlx_imgadr[coords] = 255;
					d->mlx->mlx_imgadr[coords + 1] = 204;
					d->mlx->mlx_imgadr[coords + 2] = 153;
					d->mlx->mlx_imgadr[coords + 3] = 1;
				}
				y++;
				tmp++;
				if (tmp == 10)
					tmp = 0;
			}
			y++;
		}
		x++;
	}
}
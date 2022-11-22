/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:52:03 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/22 16:31:29 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"


void	minimap(t_data *d, t_ray *rays)
{
	int		x;
	int		y;
	int		coords;

	x = 9;
	while (x < 60)
	{
		y = 9;
		while (y < 60)
		{
			coords = x * d->mlx->line_size + y * (d->mlx->bitperpixel / 8);
			if (d->posx == y && d->posy == x)
			{
				d->mlx->mlx_imgadr[coords] = 0;
				d->mlx->mlx_imgadr[coords + 1] = 0;
				d->mlx->mlx_imgadr[coords + 2] = 153;
				d->mlx->mlx_imgadr[coords + 3] = 1;
			}
			else if (d->map[x][y] == '1')
			{
				d->mlx->mlx_imgadr[coords] = 255;
				d->mlx->mlx_imgadr[coords + 1] = 153;
				d->mlx->mlx_imgadr[coords + 2] = 153;
				d->mlx->mlx_imgadr[coords + 3] = 1;
			}
			else if (d->map[x][y] == '0')
			{
				d->mlx->mlx_imgadr[coords] = 255;
				d->mlx->mlx_imgadr[coords + 1] = 204;
				d->mlx->mlx_imgadr[coords + 2] = 153;
				d->mlx->mlx_imgadr[coords + 3] = 1;
			}
			y++;
		}
		x++;
	}
}
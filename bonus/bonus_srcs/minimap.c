/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:52:03 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/22 16:15:04 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"


void	minimap(t_data *d)
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
			coords = y * d->mlx->line_size + 
					rays->x * (d->mlx->bitperpixel / 8);
			if (map[x][y] == 'N' || map[x][y] == 'S'
					||map[x][y] == 'E' ||map[x][y] == 'W')
			{
				d->mlx->mlx_imgadr[coords] = 73;
				d->mlx->mlx_imgadr[coords + 1] = 238;
				d->mlx->mlx_imgadr[coords + 2] = 255;
				d->mlx->mlx_imgadr[coords + 3] = 1;
			}
			else if (map[x][y] == '1')
			{
				d->mlx->mlx_imgadr[coords] = 255;
				d->mlx->mlx_imgadr[coords + 1] = 153;
				d->mlx->mlx_imgadr[coords + 2] = 153;
				d->mlx->mlx_imgadr[coords + 3] = 1;
			}
			else if (map[x][y] == '1')
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
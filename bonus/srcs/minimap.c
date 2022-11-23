/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:52:03 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/23 17:39:50 by nfelsemb         ###   ########.fr       */
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
	i = d->posy - 5;
	while (x < 110)
	{
		j = d->posx - 5;
		y = 9;
		while (y < 110)
		{
			coords = x * d->mlx->line_size + y * (d->mlx->bitperpixel / 8);
			if (i < 0 || j < 0)
			{
				continue;
			}
			else if (i == d->posy && j == d->posx)
			{
				d->mlx->mlx_imgadr[coords] = 0;
				d->mlx->mlx_imgadr[coords + 1] = 0;
				d->mlx->mlx_imgadr[coords + 2] = 153;
				d->mlx->mlx_imgadr[coords + 3] = 1;
			}
			else if (d->map[i][j] == '1')
			{
				//printf("1:%c\n", d->map[(x + 1) / 10][(y + 1) / 10]);
				d->mlx->mlx_imgadr[coords] = 255;
				d->mlx->mlx_imgadr[coords + 1] = 153;
				d->mlx->mlx_imgadr[coords + 2] = 153;
				d->mlx->mlx_imgadr[coords + 3] = 1;
			}
			else if (d->map[i][j] == '0' || d->map[i][j] == d->spawn)
			{
				//printf("0:%c\n", d->map[(x + 1) / 10][(y + 1) / 10]);
				d->mlx->mlx_imgadr[coords] = 255;
				d->mlx->mlx_imgadr[coords + 1] = 204;
				d->mlx->mlx_imgadr[coords + 2] = 153;
				d->mlx->mlx_imgadr[coords + 3] = 1;
			}
			printf("i:%d, j:%d\n", i, j);
			if ((y + 1) % 10 == 0)
				j++;
			y++;
		}
		if ((x + 1) % 10 == 0)
			i++;
		x++;
	}
}
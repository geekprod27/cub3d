/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:28:13 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/21 15:52:45 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	x_tex_calc(t_data *d, t_ray *rays, int id)
{
	if (rays->side == 0)
		rays->wallx = d->posy + rays->perpwalldist * rays->raydiry;
	else
		rays->wallx = d->posx + rays->perpwalldist * rays->raydirx;
	rays->wallx -= floor(rays->wallx);
	rays->texx = (int)(rays->wallx * (double)(d->tex[id].texwidth));
	if (rays->side == 0 && rays->raydirx > 0)
		rays->texx = d->tex[id].texwidth - rays->texx - 1;
	if (rays->side == 1 && rays->raydiry < 0)
		rays->texx = d->tex[id].texwidth - rays->texx - 1;
}

void	roof_ceil_tex(t_data *d, t_ray *rays, int y)
{
	int	coords;

	if (y < rays->drawstart)
	{
		coords = y * d->mlx->line_size + rays->x * (d->mlx->bitperpixel / 8);
		d->mlx->mlx_imgadr[coords] = d->cb;
		d->mlx->mlx_imgadr[coords + 1] = d->cg;
		d->mlx->mlx_imgadr[coords + 2] = d->cr;
		d->mlx->mlx_imgadr[coords + 3] = 1;
	}
	else if (y > rays->drawend)
	{
		coords = y * d->mlx->line_size + rays->x * (d->mlx->bitperpixel / 8);
		d->mlx->mlx_imgadr[coords] = d->fb;
		d->mlx->mlx_imgadr[coords + 1] = d->fg;
		d->mlx->mlx_imgadr[coords + 2] = d->fr;
		d->mlx->mlx_imgadr[coords + 3] = 1;
	}
}

void	wall_tex(t_data *d, t_ray *rays, int y, int id)
{
	int		coords;
	char	colour[4];

	if (y >= rays->drawstart && y <= rays->drawend)
	{
		rays->texy = (int)rays->texpos & (d->tex[id].texheight - 1);
		rays->texpos += rays->step;
		coords = rays->texy * d->tex[id].line_size + rays->texx * (d->tex[id].bitperpixel / 8);
		colour[0] = d->tex[id].imgadr[coords];
		colour[1] = d->tex[id].imgadr[coords + 1];
		colour[2] = d->tex[id].imgadr[coords + 2];
		colour[3] = d->tex[id].imgadr[coords + 3];
		coords = y * d->mlx->line_size + rays->x * (d->mlx->bitperpixel / 8);
		d->mlx->mlx_imgadr[coords] = colour[0];
		d->mlx->mlx_imgadr[coords+ 1] = colour[1];
		d->mlx->mlx_imgadr[coords + 2] = colour[2];
		d->mlx->mlx_imgadr[coords + 3] = colour[3];
	}
}

void	texture(t_data *d, t_ray *rays, int id)
{
	int	y;

	x_tex_calc(d, rays, id);
	rays->step = 1.0 * d->tex[id].texheight / rays->lineheight;
	rays->texpos = (rays->drawstart - HEIGHT / 2 + rays->lineheight / 2) * rays->step;
	y = 0;
	while (y < HEIGHT)
	{
		wall_tex(d, rays, y, id);
		roof_ceil_tex(d, rays, y);
		y++;
	}
}

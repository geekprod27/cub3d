/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:40:12 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/21 13:02:34 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	base_calc(t_data *data, t_ray *rays)
{
	rays->hit = 0;
	rays->camerax = 2 * rays->x / (double)(WIDTH) - 1;
	rays->raydirx = data->dirx + data->planx * rays->camerax;
	rays->raydiry = data->diry + data->plany * rays->camerax;
	rays->mapx = (int)(data->posx);
	rays->mapy = (int)(data->posy);
	if (rays->raydirx == 0)
		rays->deltadistx = 1e30;
	else
		rays->deltadistx = fabs((1 / rays->raydirx));
	if (rays->raydiry == 0)
		rays->deltadisty = 1e30;
	else
		rays->deltadisty = fabs((1 / rays->raydiry));
}

void	step_first_dist(t_data *data, t_ray *rays)
{
	if (rays->raydirx < 0)
	{
		rays->stepx = -1;
		rays->sidedistx = (data->posx - rays->mapx) * rays->deltadistx;
	}
	else
	{
		rays->stepx = 1;
		rays->sidedistx = (rays->mapx + 1.0 - data->posx) * rays->deltadistx;
	}
	if (rays->raydiry < 0)
	{
		rays->stepy = -1;
		rays->sidedisty = (data->posy - rays->mapy) * rays->deltadisty;
	}
	else
	{
		rays->stepy = 1;
		rays->sidedisty = (rays->mapy + 1.0 - data->posy) * rays->deltadisty;
	}
}

void	dda_one(t_data *data, t_ray *rays)
{
	if (rays->sidedistx < rays->sidedisty)
	{
		rays->sidedistx += rays->deltadistx;
		rays->mapx += rays->stepx;
		rays->side = 0;
	}
	else
	{
		rays->sidedisty += rays->deltadisty;
		rays->mapy += rays->stepy;
		rays->side = 1;
	}
	if (data->map[rays->mapy][rays->mapx] == '1')
		rays->hit = 1;
	if (rays->side == 0)
		rays->perpwalldist = rays->sidedistx - rays->deltadistx;
	else
		rays->perpwalldist = rays->sidedisty - rays->deltadisty;
}

void	dda_two(t_ray *rays)
{
	if (rays->perpwalldist == 0)
		rays->lineheight = HEIGHT - 2;
	else
		rays->lineheight = (int)(HEIGHT / rays->perpwalldist);
	rays->drawstart = -(rays->lineheight) / 2 + HEIGHT / 2;
	if (rays->drawstart < 0)
		rays->drawstart = 0;
	rays->drawend = rays->lineheight / 2 + HEIGHT / 2;
	if (rays->drawend >= HEIGHT)
		rays->drawend = HEIGHT - 1;
}

void	side_texture(t_data *data, t_ray *rays)
{
	if (rays->side == 0)
	{
		if (rays->mapx < data->posx)
			texture(data, rays, 0);
		else
			texture(data, rays, 1);
	}
	else
	{
		if (rays->mapy < data->posy)
			texture(data, rays, 2);
		else
			texture(data, rays, 3);
	}
}

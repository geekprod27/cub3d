/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:09:19 by llepiney          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/15 12:27:28 by llepiney         ###   ########.fr       */
=======
/*   Updated: 2022/11/15 13:02:21 by nfelsemb         ###   ########.fr       */
>>>>>>> c828b9ac37a83f94312d5aead39a0f5653969bf4
/*                                                                            */
/* ************************************************************************** */

#include  "../cub3D.h"

void	init_dir_plan_time(t_data *tex)
{
	tex->dirx = 0;
	tex->diry = 0;
	tex->planx = 0;
	tex->plany = 0;

	if (tex->spawn == 'N')
	{
		tex->planx = 0.66;
		tex->dirx = -1;
	}
	else if (tex->spawn == 'S')
	{
		tex->planx = -0.66;
		tex->dirx = 1;
	}
	else if (tex->spawn == 'E')
	{
		tex->plany = 0.66;
		tex->dirx = 1;
	}
	else if (tex->spawn == 'W')
	{
		tex->plany = -0.66;
		tex->dirx = -1;
	}
}

void	raycasting_loop(t_data *tex, t_mlx *mlx)
{
	int		x;
	t_ray	*rays;

	x = 0;
	rays = malloc(sizeof(t_ray));
	rays->hit = 0;
		while (x < WIDTH)
		{
			//INIT camerax(x point on cam plane (-1, 0, 1)) + ray directions + current square info
			rays->camerax = 2 * x / (double)(WIDTH) - 1;
			rays->raydirx = tex->dirx + tex->planx * rays->camerax;
			rays->raydiry = tex->diry + tex->plany * rays->camerax;
			rays->mapx = (int)(tex->posx);
			rays->mapy = (int)(tex->posy);

			//CALC first dist to next square, avoiding div by 0
			if (rays->raydirx == 0)
				rays->deltadistx = 1e30;
			else
				rays->deltadistx = abs((int)(1 / rays->raydirx));
			if (rays->raydiry == 0)
				rays->deltadisty = 1e30;
			else
				rays->deltadisty = abs((int)(1 / rays->raydiry));

			//INIT step(square info) and dist to do to jump to each square
			if (rays->raydirx < 0)
			{
				rays->stepx = -1;
				rays->sidedistx = (tex->posx - rays->mapx) * rays->deltadistx;
			}
			else
			{
				rays->stepx = 1;
				rays->sidedistx = (rays->mapx + 1.0 - tex->posx) * rays->deltadistx;
			}
			if (rays->raydiry < 0)
			{
				rays->stepy = -1;
				rays->sidedisty = (tex->posy - rays->mapy) * rays->deltadisty;
			}
			else
			{
				rays->stepy = 1;
				rays->sidedisty = (rays->mapy + 1.0 - tex->posy) * rays->deltadisty;
			}

			//DDA algorithm
			while (rays->hit == 0)
			{
				fprintf(stderr, "hit\n");
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
				//have we hit a wall (mapx, mapy) ?
				if (tex->map[rays->mapy][rays->mapx] > '0')
					rays->hit = 1;

				//calc perpendicular dist ray to hit wall AKA perpwalldist
				if (rays->side == 0)
					rays->perpwalldist = rays->sidedistx - rays->deltadistx;
				else
					rays->perpwalldist = rays->sidedisty - rays->deltadisty;

				//calc lineHeight AKA line to be drawn + 
				//start and end of it (lowest/highest pixel to fill in current stripe)
				rays->lineheight = (int)(HEIGHT / rays->perpwalldist);
				rays->drawstart = -(rays->lineheight) / 2 + HEIGHT / 2;
				if (rays->drawstart < 0)
					rays->drawstart = 0;
			
				rays->drawend = rays->lineheight / 2 + HEIGHT / 2;
				if (rays->drawend < 0)
					rays->drawend = HEIGHT - 1;
			}
			//diff colours for walls
				int	colour;
				if (tex->map[rays->mapy][rays->mapx] == '1')
					colour = create_trgb(1, 0, 0, 255);
				else
					colour = create_trgb(1, 255, 0, 0);
				
				if (rays->side == 1)
					colour /= 2;
				verline(x, rays->drawstart, rays->drawend, colour, mlx);
			x++;
		}
}
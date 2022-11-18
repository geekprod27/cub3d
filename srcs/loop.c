/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:09:19 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/18 15:40:13 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../cub3D.h"

void	print_data(t_data *tex)
{
	printf("[******************DATA]*****************\n");
	printf("posx : %f\n", tex->posx);
	printf("posy : %f\n", tex->posy);
	printf("planx : %f\n", tex->planx);
	printf("plany : %f\n", tex->plany);
	printf("dirx : %f\n", tex->dirx);
	printf("diry : %f\n\n", tex->diry);
}
void	print_ray(t_ray *rays)
{
	printf("[******************RAY DATA]*****************\n");
	printf("camerax : %f\n", rays->camerax);
	printf("raydirx : %f\n", rays->raydirx);
	printf("raydiry : %f\n", rays->raydiry);
	printf("mapx : %d\n", rays->mapx);
	printf("mapy : %d\n", rays->mapy);
	printf("deltadistx : %f\n", rays->deltadistx);
	printf("deltadisty : %f\n", rays->deltadisty);
	printf("stepx : %d\n", rays->stepx);
	printf("stepy : %d\n", rays->stepy);
	printf("sidedistx : %f\n", rays->sidedistx);
	printf("sidedisty : %f\n", rays->sidedisty);
	printf("perpwalldist : %f\n", rays->perpwalldist);
	printf("hit : %d\n", rays->hit);
	printf("side : %d\n", rays->side);
	printf("lineheight : %d\n", rays->lineheight);
	printf("drawstart : %d\n", rays->drawstart);
	printf("drawend : %d\n\n", rays->drawend);
}

void	init_dir_plan_time(t_data *tex)
{
	tex->dirx = 0;
	tex->diry = 0;
	tex->planx = 0;
	tex->plany = 0;

	if (tex->spawn == 'N')
	{
		tex->plany = 0.66;
		tex->dirx = -1;
	}
	else if (tex->spawn == 'S')
	{
		tex->plany = -0.66;
		tex->dirx = 1;
	}
	else if (tex->spawn == 'E')
	{
		tex->planx = 0.66;
		tex->diry = 1;
	}
	else if (tex->spawn == 'W')
	{
		tex->planx = -0.66;
		tex->diry = -1;
	}
	tex->olddirx = tex->dirx;
	tex->olddiry = tex->diry;
	tex->oldplanx = tex->planx;
	tex->oldplany = tex->plany;
}

void	raycasting_loop(t_data *tex, t_mlx *mlx)
{
	int		x;
	t_ray	*rays;

	x = 0;
	rays = malloc(sizeof(t_ray));
	while (x < WIDTH)
	{
		rays->hit = 0;
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
			rays->deltadistx = fabs((1 / rays->raydirx));
		if (rays->raydiry == 0)
			rays->deltadisty = 1e30;
		else
			rays->deltadisty = fabs((1 / rays->raydiry));

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
			if (tex->map[rays->mapy][rays->mapx] == '1')
				rays->hit = 1;

			//calc perpendicular dist ray to hit wall AKA perpwalldist
			if (rays->side == 0)
				rays->perpwalldist = rays->sidedistx - rays->deltadistx;
			else
				rays->perpwalldist = rays->sidedisty - rays->deltadisty;

			//calc lineHeight AKA line to be drawn + 
			//start and end of it (lowest/highest pixel to fill in current stripe)
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
		//diff colours for walls
		// int	colour;
		// if (tex->map[rays->mapy][rays->mapx] == '1')
		// colour = create_trgb(1, 0, 255, 0);
		// else
		// 	colour = create_trgb(1, 255, 0, 0);
		
		// if (rays->side == 1)
		// 	colour = create_trgb(1, 0, 255 /2, 0);
		// print_data(tex);
		// print_ray(rays);

		// verline(x, rays->drawstart, rays->drawend, colour, mlx);
		// (void)colour;
		texture(tex, rays, 0, mlx, x);
		x++;
	}
}
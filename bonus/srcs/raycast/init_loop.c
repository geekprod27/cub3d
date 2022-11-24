/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:38:37 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/23 18:39:24 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../cub3D.h"

void	print_data(t_data *data)
{
	printf("[******************DATA]*****************\n");
	printf("posx : %f\n", data->posx);
	printf("posy : %f\n", data->posy);
	printf("planx : %f\n", data->planx);
	printf("plany : %f\n", data->plany);
	printf("dirx : %f\n", data->dirx);
	printf("diry : %f\n\n", data->diry);
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

void	set_dir_plan(t_data *data)
{
	if (data->spawn == 'N')
	{
		data->plany = 0.66;
		data->dirx = -1;
	}
	else if (data->spawn == 'S')
	{
		data->plany = -0.66;
		data->dirx = 1;
	}
	else if (data->spawn == 'E')
	{
		data->planx = -0.66;
		data->diry = -1;
	}
	else if (data->spawn == 'W')
	{
		data->planx = 0.66;
		data->diry = 1;
	}
}

void	init_dir_plan(t_data *data)
{
	data->dirx = 0;
	data->diry = 0;
	data->planx = 0;
	data->plany = 0;
	set_dir_plan(data);
	data->olddirx = data->dirx;
	data->olddiry = data->diry;
	data->oldplanx = data->planx;
	data->oldplany = data->plany;
}

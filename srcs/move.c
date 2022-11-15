/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:08:44 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/15 12:55:30 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	avancer(t_data *data)
{
	int	x;

	x = (int)(data->posx + data->dirx * MOVESPEED);
	if (data->map[x][(int) data->posy] == '0')
		data->posx += data->dirx * MOVESPEED;
	x = (int)(data->posy + data->diry * MOVESPEED);
	if (data->map[(int) data->posx][x] == '0')
		data->posy += data->diry * MOVESPEED;
	raycasting_loop(data, data->mlx);
}

void	reculer(t_data	*data)
{
	int	x;

	x = (int)(data->posx - data->dirx * MOVESPEED);
	if (data->map[x][(int)(data->posy)] == '0')
		data->posx -= data->dirx * MOVESPEED;
	x = (int)(data->posy - data->diry * MOVESPEED);
	if (data->map[(int)(data->posx)][x] == '0')
		data->posy -= data->diry * MOVESPEED;
	raycasting_loop(data, data->mlx);
}

void	rotr(t_data *data)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->dirx;
	data->dirx = data->dirx * cos(-ROTSPEED) - data->diry * sin(-ROTSPEED);
	data->diry = olddirx * sin(-ROTSPEED) + data->diry * cos(-ROTSPEED);
	oldplanex = data->planx;
	data->planx = data->planx * cos(-ROTSPEED) - data->plany * sin(-ROTSPEED);
	data->plany = oldplanex * sin(-ROTSPEED) + data->plany * cos(-ROTSPEED);
	raycasting_loop(data, data->mlx);
}

void	rotl(t_data	*data)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->dirx;
	data->dirx = data->dirx * cos(ROTSPEED) - data->diry * sin(ROTSPEED);
	data->diry = olddirx * sin(ROTSPEED) + data->diry * cos(ROTSPEED);
	oldplanex = data->planx;
	data->planx = data->planx * cos(ROTSPEED) - data->plany * sin(ROTSPEED);
	data->plany = oldplanex * sin(ROTSPEED) + data->plany * cos(ROTSPEED);
	raycasting_loop(data, data->mlx);
}

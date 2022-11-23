/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:40:03 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/23 13:26:24 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
}

void	checkmouse(t_data *d)
{
	int		x;
	int		y;
	double	dd;

	mlx_mouse_get_pos(d->mlx->mlx_ptr, d->mlx->mlx_win, &x, &y);
	if (x < (HEIGHT / 2))
	{
		dd = (x - (HEIGHT / 2)) * 0.05 * -1;
		rotlmouse(d, dd);
	}
	else if (x > (HEIGHT / 2))
	{
		dd = (x - (HEIGHT / 2)) * 0.05;
		rotrmouse(d, dd);
	}
	mlx_mouse_move(d->mlx->mlx_ptr, d->mlx->mlx_win, HEIGHT / 2, WIDTH / 2);
}

void	rotrmouse(t_data *data, double speed)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->dirx;
	data->dirx = data->dirx * cos(-speed) - data->diry * sin(-speed);
	data->diry = olddirx * sin(-speed) + data->diry * cos(-speed);
	oldplanex = data->planx;
	data->planx = data->planx * cos(-speed) - data->plany * sin(-speed);
	data->plany = oldplanex * sin(-speed) + data->plany * cos(-speed);
}

void	rotlmouse(t_data	*data, double speed)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->dirx;
	data->dirx = data->dirx * cos(speed) - data->diry * sin(speed);
	data->diry = olddirx * sin(speed) + data->diry * cos(speed);
	oldplanex = data->planx;
	data->planx = data->planx * cos(speed) - data->plany * sin(speed);
	data->plany = oldplanex * sin(speed) + data->plany * cos(speed);
}

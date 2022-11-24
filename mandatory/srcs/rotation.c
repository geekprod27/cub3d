/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:40:03 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/24 14:59:03 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	rotl(t_data *data)
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

void	rotr(t_data	*data)
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

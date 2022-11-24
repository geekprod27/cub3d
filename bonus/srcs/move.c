/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:08:44 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/24 14:05:21 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	avancer(t_data *data)
{
	int	x;

	x = (int)(data->posx + data->dirx * MOVESPEED);
	if (data->map[(int) data->posy][x] != '1')
		data->posx += data->dirx * MOVESPEED;
	x = (int)(data->posy + data->diry * MOVESPEED);
	if (data->map[x][(int) data->posx] != '1')
		data->posy += data->diry * MOVESPEED;
}

void	reculer(t_data	*data)
{
	int	x;

	x = (int)(data->posx - data->dirx * MOVESPEED);
	if (data->map[(int)(data->posy)][x] != '1')
		data->posx -= data->dirx * MOVESPEED;
	x = (int)(data->posy - data->diry * MOVESPEED);
	if (data->map[x][(int)(data->posx)] != '1')
		data->posy -= data->diry * MOVESPEED;
}

void	gauche(t_data	*data)
{
	int	x;

	x = (int)(data->posx + data->diry * MOVESPEED);
	if (data->map[(int)(data->posy)][x] != '1')
		data->posx += data->diry * MOVESPEED;
	x = (int)(data->posy - data->dirx * MOVESPEED);
	if (data->map[x][(int)(data->posx)] != '1')
		data->posy -= data->dirx * MOVESPEED;
}

void	droite(t_data	*data)
{
	int	x;

	x = (int)(data->posx - data->diry * MOVESPEED);
	if (data->map[(int)(data->posy)][x] != '1')
		data->posx -= data->diry * MOVESPEED;
	x = (int)(data->posy + data->dirx * MOVESPEED);
	if (data->map[x][(int)(data->posx)] != '1')
		data->posy += data->dirx * MOVESPEED;
}

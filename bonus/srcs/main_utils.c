/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:47:42 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/25 13:53:23 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	saveold(t_data *data)
{
	data->oldposx = data->posx;
	data->oldposy = data->posy;
	data->olddirx = data->dirx;
	data->olddiry = data->diry;
	data->oldplanx = data->planx;
	data->oldplany = data->plany;
}

void	freetab(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	ft_exit(t_data	*data, int exi)
{
	if (data->map)
		freetab(data->map);
	if (data->mlx->mlx_img)
		mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->mlx_img);
	if (data->tex[0].img)
		mlx_destroy_image(data->mlx->mlx_ptr, data->tex[0].img);
	if (data->tex[1].img)
		mlx_destroy_image(data->mlx->mlx_ptr, data->tex[1].img);
	if (data->tex[2].img)
		mlx_destroy_image(data->mlx->mlx_ptr, data->tex[2].img);
	if (data->tex[3].img)
		mlx_destroy_image(data->mlx->mlx_ptr, data->tex[3].img);
	if (data->mlx->mlx_win)
		mlx_destroy_window(data->mlx->mlx_ptr, data->mlx->mlx_win);
	if (data->mlx->mlx_ptr)
	{
		mlx_destroy_display(data->mlx->mlx_ptr);
		free(data->mlx->mlx_ptr);
	}
	free(data->mlx);
	free(data);
	exit(exi);
}

void	data_error(t_mlx *mlx)
{
	ft_putstr_fd("Error\nData creation failed\n", 2);
	if (mlx->mlx_img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->mlx_img);
	if (mlx->mlx_win)
		mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	if (mlx->mlx_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
	if (mlx)
		free(mlx);
	exit(2);
}

int	reaf(void *param)
{
	t_data	*data;

	data = param;
	if (data->w)
		avancer(data);
	if (data->s)
		reculer(data);
	if (data->a)
		gauche(data);
	if (data->d)
		droite(data);
	if (data->dr)
		rotr(data);
	if (data->ga)
		rotl(data);
	checkmouse(data);
	if (data->oldposx != data->posx || data->oldposy != data->posy
		|| data->olddirx != data->dirx || data->olddiry != data->diry
		|| data->oldplanx != data->planx || data->oldplany != data->plany)
	{
		saveold(data);
		raycasting_loop(data, data->mlx);
	}
	return (0);
}

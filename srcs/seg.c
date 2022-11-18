/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:01:19 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/18 15:35:39 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	verline(int x, int strat, int end, t_data *data)
{
	int		d;
	t_mlx	*mlx;

	mlx = data->mlx;
	d = 0;
	while (d <= 1000)
	{
		if (d < strat)
		{
			(mlx->mlx_imgadr[(d * mlx->line_size + x * (mlx->bitperpixel / 8))]) = data->cb;
			(mlx->mlx_imgadr[(d * mlx->line_size + x * (mlx->bitperpixel / 8)) + 1]) = data->cg;
			(mlx->mlx_imgadr[(d * mlx->line_size + x * (mlx->bitperpixel / 8)) + 2]) = data->cr;
			(mlx->mlx_imgadr[(d * mlx->line_size + x * (mlx->bitperpixel / 8)) + 3]) = 1;
		}
		else if (d >= strat && d <= end)
		{
			(mlx->mlx_imgadr[(d * mlx->line_size + x * (mlx->bitperpixel / 8))]) = 0;
			(mlx->mlx_imgadr[(d * mlx->line_size + x * (mlx->bitperpixel / 8)) + 1]) = 125;
			(mlx->mlx_imgadr[(d * mlx->line_size + x * (mlx->bitperpixel / 8)) + 2]) = 0;
			(mlx->mlx_imgadr[(d * mlx->line_size + x * (mlx->bitperpixel / 8)) + 3]) = 1;
		}
		else if (d > end)
		{
			(mlx->mlx_imgadr[(d * mlx->line_size + x * (mlx->bitperpixel / 8))]) = data->fb;
			(mlx->mlx_imgadr[(d * mlx->line_size + x * (mlx->bitperpixel / 8)) + 1]) = data->fg;
			(mlx->mlx_imgadr[(d * mlx->line_size + x * (mlx->bitperpixel / 8)) + 2]) = data->fr;
			(mlx->mlx_imgadr[(d * mlx->line_size + x * (mlx->bitperpixel / 8)) + 3]) = 1;
		}
		d++;
	}
}

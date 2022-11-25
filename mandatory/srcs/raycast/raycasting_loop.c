/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:09:19 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/25 13:39:29 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../cub3D.h"

void	raycasting_loop(t_data *data, t_mlx *mlx)
{
	int		x;
	t_ray	*rays;

	x = 0;
	rays = malloc(sizeof(t_ray));
	if (!rays)
		return ;
	while (x < WIDTH)
	{
		rays->x = x;
		base_calc(data, rays);
		step_first_dist(data, rays);
		while (rays->hit == 0)
		{
			dda_one(data, rays);
			dda_two(rays);
		}
		side_texture(data, rays);
		x++;
	}
	free(rays);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->mlx_img, 0, 0);
}

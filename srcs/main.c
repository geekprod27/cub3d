/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:26:08 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/10/28 13:52:25 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	main(void)
{
	void	*mlx_ptr;
	void	*mlx_win;

	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, 1000, 1000, "cub3D");
	(void) mlx_win;
	mlx_loop(mlx_ptr);
}

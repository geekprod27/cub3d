/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:26:08 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/10 13:31:06 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	key_hook(int keycode, void *vars)
{
	if (keycode == 65307)
		exit(6);
	(void) vars;
	return (0);
}

int	main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_data	*tex;
	int		i;
	int		y;

	if (argc != 2)
		return (1);
	tex = get_data(argv[1]);
	i = 0;
	if (!verifmap(tex->map))
	{
		ft_putstr_fd("Error\nMap invalide", 2);
		exit(2);
	}
	replace_space(tex->map);
	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, 1000, 1000, "cub3D");
	y = 0;
	while (y < 100)
	{
		i = 0;
		while (i < 1000)
		{
			mlx_pixel_put(mlx_ptr, mlx_win, i, 0 + y, tex->c);
			i++;
		}
		y++;
	}
	y = 100;
	while (y > 0)
	{
		i = 0;
		while (i < 1000)
		{
			mlx_pixel_put(mlx_ptr, mlx_win, i, 1000 - y, tex->f);
			i++;
		}
		y--;
	}
	mlx_key_hook(mlx_win, key_hook, 0);
	mlx_loop(mlx_ptr);
}

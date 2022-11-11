/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:26:08 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/11 14:15:25 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	redcross(void *param)
{
	(void) param;
	exit(0);
}

int	keydown(int keycode, void *param)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 119)
		printf("w down\n");
	else if (keycode == 115)
		printf("s down\n");
	else if (keycode == 97)
		printf("a down\n");
	else if (keycode == 100)
		printf("d down\n");
	else if (keycode == 65361)
		printf("<- down\n");
	else if (keycode == 65363)
		printf("-> down\n");
	(void) param;
	return (0);
}

void	error(char *d)
{
	ft_putstr_fd("Error\nMultiple ID :\n", 2);
	ft_putstr_fd(d, 2);
	exit(3);
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
	if (!tex)
	{
		ft_putstr_fd("Error\n", 2);
		exit(2);
	}
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
	mlx_hook(mlx_win, ON_KEYDOWN, 1L << 0, keydown, 0);
	mlx_hook(mlx_win, ON_DESTROY, 0, redcross, 0);
	mlx_loop(mlx_ptr);
}

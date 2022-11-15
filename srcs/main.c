/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:26:08 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/15 15:47:42 by llepiney         ###   ########.fr       */
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
	t_data	*data;

	data = param;
	if (keycode == 65307)
		exit(0);
	if (keycode == 119)
		avancer(data);
	else if (keycode == 115)
		reculer(data);
	else if (keycode == 97)
		printf("a down\n");
	else if (keycode == 100)
		printf("d down\n");
	else if (keycode == 65361)
		rotl(data);
	else if (keycode == 65363)
		rotr(data);
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
	t_data	*tex;
	t_mlx	*mlx;

	if (argc != 2)
		return (1);
	/*get toutes les daata du fichier*/
	tex = get_data(argv[1]);
	if (!tex)
	{
		ft_putstr_fd("Error\n", 2);
		exit(2);
	}
	if (!verifmap(tex->map, tex))
	{
		ft_putstr_fd("Error\nMap invalide", 2);
		exit(2);
	}
	replace_space(tex->map);
	mlx = malloc(sizeof(t_mlx));
	mlx->mlx_ptr = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, 1000, 1000, "cub3D");
	tex->mlx = mlx;
	mlx_hook(mlx->mlx_win, ON_KEYDOWN, 1L << 0, keydown, tex);
	mlx_hook(mlx->mlx_win, ON_DESTROY, 0, redcross, 0);
	init_dir_plan_time(tex);
	raycasting_loop(tex, tex->mlx);
	mlx_loop(mlx->mlx_ptr);
}

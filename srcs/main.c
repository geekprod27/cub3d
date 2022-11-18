/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:26:08 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/18 15:17:41 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
	fprintf(stderr, "ft_exit\n");
	freetab(data->map);
	mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->mlx_img);
	mlx_destroy_image(data->mlx->mlx_ptr, data->tex[0].img);
	mlx_destroy_image(data->mlx->mlx_ptr, data->tex[1].img);
	mlx_destroy_image(data->mlx->mlx_ptr, data->tex[2].img);
	mlx_destroy_image(data->mlx->mlx_ptr, data->tex[3].img);
	mlx_destroy_window(data->mlx->mlx_ptr, data->mlx->mlx_win);
	free(data->mlx->mlx_ptr);
	free(data->mlx);
	free(data);
	exit(exi);
}

int	redcross(void *param)
{
	t_data	*data;

	data = param;
	ft_exit(data, 0);
	return (0);
}

int	keydown(int keycode, void *param)
{
	t_data	*data;

	data = param;
	if (keycode == 65307)
		ft_exit(data, 0);
	if (keycode == 119)
		avancer(data);
	else if (keycode == 115)
		reculer(data);
	else if (keycode == 97)
		gauche(data);
	else if (keycode == 100)
		droite(data);
	else if (keycode == 65361)
		rotl(data);
	else if (keycode == 65363)
		rotr(data);
	raycasting_loop(data, data->mlx);
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
	if (!name_check(argv[1]))
		return (1);
	mlx = malloc(sizeof(t_mlx));
	mlx->mlx_ptr = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	mlx->mlx_img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	/*get toutes les daata du fichier*/
	tex = get_data(argv[1], mlx);
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
	mlx->mlx_imgadr = mlx_get_data_addr(mlx->mlx_img, &mlx->bitperpixel, &mlx->line_size, &mlx->endian);
	tex->mlx = mlx;
	mlx_hook(mlx->mlx_win, ON_KEYDOWN, 1L << 0, keydown, tex);
	mlx_hook(mlx->mlx_win, ON_DESTROY, 0, redcross, 0);
	init_dir_plan_time(tex);
	raycasting_loop(tex, tex->mlx);
	mlx_loop(mlx->mlx_ptr);
}

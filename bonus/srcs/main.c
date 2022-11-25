/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:26:08 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/25 13:53:37 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	reaf(void *param);

int	keydown(int keycode, void *param)
{
	t_data	*data;

	data = param;
	if (keycode == 65307)
		ft_exit(data, 0);
	if (keycode == 119)
		data->w = 1;
	else if (keycode == 115)
		data->s = 1;
	else if (keycode == 97)
		data->a = 1;
	else if (keycode == 100)
		data->d = 1;
	else if (keycode == 65361)
		data->ga = 1;
	else if (keycode == 65363)
		data->dr = 1;
	return (0);
}

int	keyup(int keycode, void *param)
{
	t_data	*data;

	data = param;
	if (keycode == 119)
		data->w = 0;
	else if (keycode == 115)
		data->s = 0;
	else if (keycode == 97)
		data->a = 0;
	else if (keycode == 100)
		data->d = 0;
	else if (keycode == 65361)
		data->ga = 0;
	else if (keycode == 65363)
		data->dr = 0;
	return (0);
}

int	redcross(void *param)
{
	t_data	*data;

	data = param;
	ft_exit(data, 0);
	return (0);
}

void	mlx_events(t_data *data, t_mlx *mlx, char *file)
{
	file = ft_strjoin("cub3D - ", file);
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, file);
	if (!mlx->mlx_win)
		ft_exit(data, 1);
	free(file);
	mlx->mlx_img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (!mlx->mlx_img)
		ft_exit(data, 1);
	mlx->mlx_imgadr = mlx_get_data_addr(mlx->mlx_img, &mlx->bitperpixel,
			&mlx->line_size, &mlx->endian);
	if (!mlx->mlx_imgadr)
		ft_exit(data, 1);
	mlx_hook(mlx->mlx_win, ON_KEYDOWN, 1L << 0, keydown, data);
	mlx_hook(mlx->mlx_win, ON_KEYUP, 1L << 1, keyup, data);
	mlx_hook(mlx->mlx_win, ON_DESTROY, 0, redcross, data);
	mlx_loop_hook(mlx->mlx_ptr, reaf, data);
	init_dir_plan(data);
	mlx_mouse_move(mlx->mlx_ptr, mlx->mlx_win, HEIGHT / 2, WIDTH / 2);
	raycasting_loop(data, data->mlx);
	mlx_loop(mlx->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_mlx	*mlx;

	if (argc != 2)
		return (ft_error("Need 2 arguments\n"));
	if (!name_check(argv[1]))
		return (ft_error("Wrong file format, need .cub\n"));
	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (ft_error("Mlx creation failed\n"));
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (ft_error("Mlx creation failed\n"));
	data = get_data(argv[1], mlx);
	if (!data)
		data_error(mlx);
	if (!data->map || !verifmap(data->map, data))
	{
		ft_putstr_fd("Error\nInvalid map\n", 2);
		ft_exit(data, 2);
	}
	replace_space(data->map, data);
	mlx_events(data, mlx, argv[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:26:08 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/21 11:43:48 by llepiney         ###   ########.fr       */
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

void	saveold(t_data *data)
{
	data->oldposx = data->posx;
	data->oldposy = data->posy;
	data->olddirx = data->dirx;
	data->olddiry = data->diry;
	data->oldplanx = data->planx;
	data->oldplany = data->plany;
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
	if (data->oldposx != data->posx || data->oldposy != data->posy
		|| data->olddirx != data->dirx || data->olddiry != data->diry
		|| data->oldplanx != data->planx || data->oldplany != data->plany)
	{
		saveold(data);
		raycasting_loop(data, data->mlx);
	}
	return (0);
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
	if (!mlx)
		return (0);
	mlx->mlx_ptr = mlx_init();
	/*get toutes les daata du fichier*/
	tex = get_data(argv[1], mlx);
	if (!tex)
	{
		ft_putstr_fd("Error\n", 2);
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
	if (!tex->map || !verifmap(tex->map, tex))
	{
		ft_putstr_fd("Error\nMap invalide", 2);
		ft_exit(tex, 2);
	}
	replace_space(tex->map);
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	mlx->mlx_img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->mlx_imgadr = mlx_get_data_addr(mlx->mlx_img, &mlx->bitperpixel, &mlx->line_size, &mlx->endian);
	mlx_hook(mlx->mlx_win, ON_KEYDOWN, 1L << 0, keydown, tex);
	mlx_hook(mlx->mlx_win, ON_KEYUP, 1L << 1, keyup, tex);
	mlx_hook(mlx->mlx_win, ON_DESTROY, 0, redcross, tex);
	mlx_loop_hook(mlx->mlx_ptr, reaf, tex);
	init_dir_plan(tex);
	raycasting_loop(tex, tex->mlx);
	mlx_loop(mlx->mlx_ptr);
}

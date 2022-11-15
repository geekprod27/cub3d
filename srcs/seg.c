/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:01:19 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/15 12:13:47 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	troi(t_mlx *ptr, t_point *un, t_point *de, t_point d)
{
	int	e;

	e = d.x;
	d.x = e * 2;
	d.y = d.y * 2;
	while (1)
	{
		mlx_pixel_put(ptr->mlx_ptr, ptr->mlx_win, un->x, un->y, ptr->color);
		un->x = un->x + 1;
		if (un->x == de->x)
			break ;
		e = e + d.y;
		if (e < 0)
		{
			un->y = un->y - 1;
			e = e + d.x;
		}
	}
}

void	quatre(t_mlx *ptr, t_point *un, t_point *de, t_point d)
{
	int	e;

	e = d.y;
	d.y = e * 2;
	d.x = d.x * 2;
	while (1)
	{
		mlx_pixel_put(ptr->mlx_ptr, ptr->mlx_win, un->x, un->y, ptr->color);
		un->y = un->y - 1;
		if (un->y == de->y)
			break ;
		e = e + d.x;
		if (e > 0)
		{
			un->x = un->x + 1;
			e = e + d.y;
		}
	}
}

void	cinq(t_mlx *ptr, t_point *un, t_point *de)
{
	while (un->x != de->x)
	{
		mlx_pixel_put(ptr->mlx_ptr, ptr->mlx_win, un->x, un->y, ptr->color);
		un->x = un->x + 1;
	}
}

void	sis(t_mlx *ptr, t_point *un, t_point *de, t_point d)
{
	d.y = de->y - un->y;
	if (d.y != 0)
	{
		if (d.y > 0)
		{
			while (un->y != de->y)
			{
				mlx_pixel_put(ptr->mlx_ptr, ptr->mlx_win, un->x, un->y,
					ptr->color);
				un->y = un->y + 1;
			}
		}
		else
		{
			while (un->y != de->y)
			{
				mlx_pixel_put(ptr->mlx_ptr, ptr->mlx_win, un->x, un->y,
					ptr->color);
				un->y = un->y - 1;
			}
		}
	}
}

void	seg(t_point un, t_point de, t_mlx *ptr)
{
	t_point	d;

	d.x = de.x - un.x;
	d.y = de.y - un.y;
	if (d.x != 0)
		if (d.x > 0)
			if (d.y != 0)
				if (d.y > 0)
					if (d.x >= d.y)
						uno(ptr, &un, &de, d);
	else
		deux(ptr, &un, &de, d);
	else
		if (d.x >= -d.y)
			troi(ptr, &un, &de, d);
	else
		quatre(ptr, &un, &de, d);
	else
		cinq(ptr, &un, &de);
	else
		seg(de, un, ptr);
	else
		sis(ptr, &un, &de, d);
	mlx_pixel_put(ptr->mlx_ptr, ptr->mlx_win, de.x, de.y, ptr->color);
}

void	verline(int x, int strat, int end, int color, t_mlx	*mlx)
{
	t_point	un;
	t_point	de;

	un.x = x;
	de.x = x;
	un.y = strat;
	de.y = end;
	mlx->color = color;
}

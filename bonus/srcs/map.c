/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:43:01 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/23 17:46:35 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	maps(t_data *data, int x, int y, int *havespwn)
{
	if (data->map[x][y] == '0' || data->map[x][y] == 'N'
		|| data->map[x][y] == 'S' || data->map[x][y] == 'E'
		|| data->map[x][y] == 'W')
	{
		if (x == 0 || !data->map[x + 1] || y == 0 || !data->map[x][y + 1]
			|| data->map[x][y + 1] == '\n')
			return (0);
		if (data->map[x - 1][y] == ' ' || data->map[x + 1][y] == ' '
				|| data->map[x][y - 1] == ' ' || data->map[x][y + 1] == ' '
				|| data->map[x][y + 1] == '\n')
			return (0);
	}
	if (data->map[x][y] == 'N' || data->map[x][y] == 'S'
		|| data->map[x][y] == 'E' || data->map[x][y] == 'W')
	{
		if (*havespwn)
			return (0);
		*havespwn = 1;
		data->posx = y + 0.5;
		data->posy = x + 0.5;
		data->oldposx = y + 0.5;
		data->oldposy = x + 0.5;
		data->spawn = data->map[x][y];
	}
	return (1);
}

int	verifmap(char **map, t_data *data)
{
	int	x;
	int	y;
	int	havespwn;

	x = 0;
	havespwn = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (!maps(data, x, y, &havespwn))
				return (0);
			if (map[x][y] != '1' && map[x][y] != ' ' && map[x][y] != '\n'
				&& map[x][y] != '0' && data->map[x][y] != 'N'
				&& data->map[x][y] != 'S' && data->map[x][y] != 'E'
				&& data->map[x][y] != 'W')
				return (0);
			y++;
		}
		x++;
	}
	return (havespwn);
}

void	replace_space(char **map, t_data *d)
{
	int	x;
	int	y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == ' ')
				map[x][y] = '1';
			y++;
		}
		if (d->ymax < y)
			d->ymax = y;
		x++;
	}
	d->xmax = x;
}

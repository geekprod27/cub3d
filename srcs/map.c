/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:43:01 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/10 13:16:45 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	verifmap(char **map)
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
			if (map[x][y] == '0')
			{
				if (x == 0 || !map[x + 1] || y == 0 || !map[x][y + 1]
					|| map[x][y + 1] == '\n')
					return (0);
				if (map[x - 1][y] == ' ' || map[x + 1][y] == ' '
					|| map[x][y - 1] == ' ' || map[x][y + 1] == ' '
					|| map[x][y + 1] == '\n')
					return (0);
			}
			else if (map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'E'
				|| map[x][y] == 'W')
			{
				if (havespwn)
					return (0);
				havespwn = 1;
			}
			else if (map[x][y] != '1' && map[x][y] != ' ' && map[x][y] != '\n')
				return (0);
			y++;
		}
		x++;
	}
	return (havespwn);
}

void	replace_space(char **map)
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
		x++;
	}
}
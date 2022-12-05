/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:51:25 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/12/05 16:14:24 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	savedatac(t_data *data, int r, int g, int b)
{
		data->cr = r;
		data->cg = g;
		data->cb = b;
}

void	savedataf(t_data *data, int r, int g, int b)
{
		data->fr = r;
		data->fg = g;
		data->fb = b;
}

char	**add(char **map, int i, char *line)
{
	int		len;
	char	**ret;

	len = 0;
	while (map[len])
			len++;
	ret = malloc(sizeof(char *) * (len + 2));
	if (!ret)
		return (NULL);
	while (map[i])
	{
		ret[i] = map[i];
		i++;
	}
	ret[i] = line;
	ret[i + 1] = NULL;
	free(map);
	return (ret);
}

t_data	*get_data(char *file, t_mlx *mlx)
{
	int		fd;
	char	*line;
	t_data	*ret;

	fd = open(file, O_RDONLY);
	if (fd == 1 || fd == -1)
		return (NULL);
	ret = malloc(sizeof(t_data));
	if (!ret)
	{
		close(fd);
		return (NULL);
	}
	init_data(ret, mlx);
	ret = checkid(ret, fd);
	if (!ret)
	{
		close(fd);
		return (NULL);
	}
	line = get_next_line(fd);
	getmap(line, fd, ret);
	close(fd);
	return (ret);
}

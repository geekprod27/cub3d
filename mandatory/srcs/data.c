/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:51:25 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/22 17:23:38 by nfelsemb         ###   ########.fr       */
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

void	get_trgb(char *line, t_data	*data, char l)
{
	int		r;
	int		g;
	int		b;
	char	*saveline;

	saveline = line - 2;
	r = ft_atoi(line);
	while (*line && *line != ',')
		line++;
	line++;
	if (*line == ',')
		errorrgb(data, saveline);
	g = ft_atoi(line);
	while (*line && *line != ',')
		line++;
	line++;
	if (*line == ',')
		errorrgb(data, saveline);
	b = ft_atoi(line);
	if (r > 255 || g > 255 || b > 255)
		errorrgb(data, saveline);
	if (l == 'C')
		savedatac(data, r, g, b);
	else
		savedataf(data, r, g, b);
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
		return (NULL);
	init_data(ret, mlx);
	ret = checkid(ret, fd);
	if (!ret)
		return (NULL);
	line = get_next_line(fd);
	getmap(line, fd, ret);
	close(fd);
	return (ret);
}

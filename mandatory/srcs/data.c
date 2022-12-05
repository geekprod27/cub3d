/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:51:25 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/12/05 15:55:36 by nfelsemb         ###   ########.fr       */
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

void	checkvir(char *line, int i, t_data *data, int fd)
{
	int	contvir;

	contvir = 0;
	while (line[i])
	{
		if (line[i] == ',')
		{
			contvir++;
			if (!ft_isdigit(line[i - 1] || !ft_isdigit(line[i + 1])))
				errorrgb(data, line - 1, fd);
		}
		if (contvir > 2)
			errorrgb(data, line - 1, fd);
		i++;
	}
	if (contvir != 2)
		errorrgb(data, line - 1, fd);
}

void	checkchar(char *line, int i, t_data *data, int fd)
{
	while (line[i])
	{
		if (line[i] != ',' && !ft_isdigit(line[i]) && line[i] != '\n')
			errorrgb(data, line - 1, fd);
		i++;
	}
}

int	skipspaced(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

void	get_trgb(char *line, t_data	*data, char l, int fd)
{
	int		r;
	int		g;
	int		b;
	int		i;

	i = skipspaced(line);
	checkchar(line, i, data, fd);
	checkvir(line, i, data, fd);
	r = ft_atoi(line + i);
	while (line[i] && line[i] != ',')
		i++;
	if (line[i] && line[i + 1])
		i++;
	else
		errorrgb(data, line - 1, fd);
	g = ft_atoi(line + i);
	while (line[i] && line[i] != ',')
		i++;
	if (line[i] && line[i + 1])
		i++;
	else
		errorrgb(data, line - 1, fd);
	b = ft_atoi(line + i);
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

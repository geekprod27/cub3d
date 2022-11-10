/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:51:25 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/10 18:06:16 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_trgb(char *line)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(line);
	while (*line != ',')
		line++;
	line++;
	g = ft_atoi(line);
	while (*line != ',')
		line++;
	line++;
	b = ft_atoi(line);
	return (create_trgb(1, r, g, b));
}

char	**ft_addb(char **map, char *line)
{
	int		len;
	int		i;
	char	**ret;

	len = 0;
	i = 0;
	if (map)
	{
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
		return (ret);
	}
	ret = malloc(sizeof(char *) * 2);
	if (!ret)
		return (NULL);
	ret[i] = line;
	ret[i + 1] = NULL;
	return (ret);
}

t_data	*get_data(char *file)
{
	int		fd;
	char	*line;
	t_data	*ret;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd <= 0)
		return (NULL);
	ret = malloc(sizeof(t_data));
	ret->map = NULL;
	if (!ret)
		return (NULL);
	while (i < 6)
	{
		line = get_next_line(fd);
		if (ft_strncmp(line, "NO ", 3) == 0)
		{
			if (!ret->no)
				ret->no = ft_strdup(line + 3);
			else
				error(line);
			i++;
		}
		else if (ft_strncmp(line, "SO ", 3) == 0)
		{
			if (!ret->so)
				ret->so = ft_strdup(line + 3);
			else
				error(line);
			i++;
		}
		else if (ft_strncmp(line, "WE ", 3) == 0)
		{
			if (!ret->we)
				ret->we = ft_strdup(line + 3);
			else
				error(line);
			i++;
		}
		else if (ft_strncmp(line, "EA ", 3) == 0)
		{
			if (!ret->ea)
				ret->ea = ft_strdup(line + 3);
			else
				error(line);
			i++;
		}
		else if (ft_strncmp(line, "F ", 2) == 0)
		{
			if (!ret->f)
				ret->f = get_trgb(line + 2);
			else
				error(line);
			i++;
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			if (!ret->c)
				ret->c = get_trgb(line + 2);
			else
				error(line);
			i++;
		}
		else if (line[0] != '\n')
		{
			ft_putstr_fd("Error\nID inconue sur la ligne :\n", 2);
			ft_putstr_fd(line, 2);
			free(line);
			exit(1);
		}
		free(line);
	}
	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		ret->map = ft_addb(ret->map, line);
		line = get_next_line(fd);
	}
	close(fd);
	return (ret);
}

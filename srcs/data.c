/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:51:25 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/18 15:14:59 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	errorrgb(t_data *data)
{
	ft_putstr_fd("Error\nRGB", 2);
	ft_exit(data, 1);
}

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
	int	r;
	int	g;
	int	b;

	r = ft_atoi(line);
	while (*line && *line != ',')
		line++;
	line++;
	if (*line == ',')
		errorrgb(data);
	g = ft_atoi(line);
	while (*line && *line != ',')
		line++;
	line++;
	if (*line == ',')
		errorrgb(data);
	b = ft_atoi(line);
	if (r > 255 || g > 255 || b > 255)
		errorrgb(data);
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

char	**ft_addb(char **map, char *line)
{
	int		len;
	int		i;
	char	**ret;

	len = 0;
	i = 0;
	if (map)
		return (add(map, i, line));
	ret = malloc(sizeof(char *) * 2);
	if (!ret)
		return (NULL);
	ret[i] = line;
	ret[i + 1] = NULL;
	return (ret);
}

int	name_check(char *arg)
{
	int	i;
	int	len;

	len = ft_strlen(arg);
	i = 0;
	if (!ft_strncmp(arg, ".cub", 4))
		return (0);
	if (arg[i] == '.' || arg[i] == '\0')
		return (0);
	while (i < len - 4)
	{
		arg++;
		i++;
	}
	if (!ft_strncmp(arg, ".cub", (len - 1)))
		return (1);
	return (0);
}

void	openxpm(t_data *data, char *file, t_tex *tex, int i)
{
	char	*filed;

	filed = ft_strtrim(file, "\n");
	tex[i].img = mlx_xpm_file_to_image(data->mlx->mlx_ptr, filed,
			&(tex[i].texwidth), &(tex[i].texheight));
	free(filed);
	if (!tex[i].img)
	{
		printf("Error\n");
		free(file - 3);
		ft_exit(data, 1);
	}
	tex[i].imgadr = mlx_get_data_addr(tex[i].img, &tex[i].bitperpixel,
			&tex[i].line_size, &tex[i].endian);
}

t_data	*get_data(char *file, t_mlx *mlx)
{
	int		fd;
	char	*line;
	t_data	*ret;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == 1 || fd == -1)
		return (NULL);
	ret = malloc(sizeof(t_data));
	if (!ret)
		return (NULL);
	ret->map = NULL;
	ret->c = 0;
	ret->f = 0;
	ret->mlx = mlx;
	ret->tex[0].img = NULL;
	ret->tex[1].img = NULL;
	ret->tex[2].img = NULL;
	ret->tex[3].img = NULL;
	ret->w = 0;
	ret->s = 0;
	ret->a = 0;
	ret->d = 0;
	ret->dr = 0;
	ret->ga = 0;
	while (i < 6)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free(ret);
			return (NULL);
		}
		if (ft_strncmp(line, "NO ", 3) == 0)
		{
			if (!ret->tex[0].img)
				openxpm(ret, line + 3, ret->tex, 0);
			else
				error(line, ret);
			i++;
		}
		else if (ft_strncmp(line, "SO ", 3) == 0)
		{
			if (!ret->tex[1].img)
				openxpm(ret, line + 3, ret->tex, 1);
			else
				error(line, ret);
			i++;
		}
		else if (ft_strncmp(line, "WE ", 3) == 0)
		{
			if (!ret->tex[2].img)
				openxpm(ret, line + 3, ret->tex, 2);
			else
				error(line, ret);
			i++;
		}
		else if (ft_strncmp(line, "EA ", 3) == 0)
		{
			if (!ret->tex[3].img)
				openxpm(ret, line + 3, ret->tex, 3);
			else
				error(line, ret);
			i++;
		}
		else if (ft_strncmp(line, "F ", 2) == 0)
		{
			if (!ret->f)
			{
				ret->f = 1;
				get_trgb(line + 2, ret, line[0]);
			}
			else
				error(line, ret);
			i++;
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			if (!ret->c)
			{
				get_trgb(line + 2, ret, line[0]);
				ret->c = 1;
			}
			else
				error(line, ret);
			i++;
		}
		else if (line[0] != '\n')
		{
			ft_putstr_fd("Error\nID inconue sur la ligne :\n", 2);
			ft_putstr_fd(line, 2);
			free(line);
			ft_exit(ret, 1);
		}
		free(line);
	}
	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && line[0] != '\n')
	{
		ret->map = ft_addb(ret->map, line);
		line = get_next_line(fd);
	}
	if (line && line[0] == '\n')
		free(line);
	close(fd);
	return (ret);
}

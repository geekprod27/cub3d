/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:51:25 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/18 15:42:12 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	zeud2(char *line, t_data *ret, int *i)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (!ret->f)
		{
			ret->f = 1;
			get_trgb(line + 2, ret, line[0]);
		}
		else
			error(line, ret);
		*i = *i + 1;
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
		*i = *i + 1;
	}
	else if (line[0] != '\n')
		puterrorline(line, ret);
}

void	zeud(char *line, t_data *ret, int *i)
{
	if (ft_strncmp(line, "SO ", 3) == 0)
	{
		checkopenxpm(1, line, ret);
		*i = *i + 1;
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		checkopenxpm(2, line, ret);
		*i = *i + 1;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		checkopenxpm(3, line, ret);
		*i = *i + 1;
	}
	else
		zeud2(line, ret, i);
	free(line);
}

void	*checkid(t_data *ret, int fd)
{
	int		i;
	char	*line;

	i = 0;
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
		else
			zeud(line, ret, &i);
	}
	return (ret);
}

void	init_data(t_data *ret, t_mlx *mlx)
{
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
}

void	getmap(char *line, int fd, t_data *ret)
{
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
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:13:09 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/12/05 16:13:35 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

int	getnewi(char *line, int i, int fd, t_data *data)
{
	while (line[i] && line[i] != ',')
		i++;
	if (line[i] && line[i + 1])
		i++;
	else
		errorrgb(data, line - 1, fd);
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
	i = getnewi(line, i, fd, data);
	g = ft_atoi(line + i);
	i = getnewi(line, i, fd, data);
	b = ft_atoi(line + i);
	if (l == 'C')
		savedatac(data, r, g, b);
	else
		savedataf(data, r, g, b);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:51:25 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/23 13:09:20 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	**ft_addb(char **map, char *line)
{
	int		i;
	char	**ret;

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
		printf("Error\nopen fail on file %s", file);
		free(file - 3);
		ft_exit(data, 1);
	}
	tex[i].imgadr = mlx_get_data_addr(tex[i].img, &tex[i].bitperpixel,
			&tex[i].line_size, &tex[i].endian);
}

void	checkopenxpm(int id, char *line, t_data *ret)
{
	if (!ret->tex[id].img)
		openxpm(ret, line + 3, ret->tex, id);
	else
		error(line, ret);
}

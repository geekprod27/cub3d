/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:39:34 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/10 14:04:14 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include "mlx/mlx.h"
# include "libft/libft.h"

typedef struct s_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	char	**map;
}	t_data;

t_data		*get_data(char *file);
int			verifmap(char **map);
void		replace_space(char **map);
void		error(char *d);

#endif
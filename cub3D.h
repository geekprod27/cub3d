/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:39:34 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/07 18:09:57 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include "mlx/mlx.h"

typedef struct s_tex
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_tex;

t_tex	*get_tex(char *file);

#endif
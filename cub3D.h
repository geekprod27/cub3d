/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:39:34 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/15 14:18:58 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "mlx/mlx.h"
# include "libft/libft.h"

# define MOVESPEED 1
# define ROTSPEED 1
# define HEIGHT 1000
# define WIDTH 1000

typedef struct s_mlx	t_mlx;
struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
	int		color;
};

typedef struct s_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	char	**map;
	double	posx;
	double	posy;
	double	planx;
	double	plany;
	double	dirx;
	double	diry;
	char	spawn;
	t_mlx	*mlx;
}	t_data;

typedef struct s_ray
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;

}	t_ray;

typedef struct s_point	t_point;
struct s_point
{
	int		x;
	int		y;
};

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

t_data		*get_data(char *file);
int			verifmap(char **map, t_data *data);
void		replace_space(char **map);
void		error(char *d);
int			create_trgb(int t, int r, int g, int b);
void		init_dir_plan_time(t_data *tex);
void		raycasting_loop(t_data *tex, t_mlx *mlx);
void		verline(int x, int strat, int end, int color, t_mlx	*mlx);

//		MOUVEMENT

void		avancer(t_data *data);
void		reculer(t_data *data);
void		rotl(t_data	*data);
void		rotr(t_data	*data);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:39:34 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/16 17:32:49 by nfelsemb         ###   ########.fr       */
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

# define MOVESPEED 0.5
# define ROTSPEED 0.1
# define HEIGHT 1000
# define WIDTH 1000

typedef struct s_mlx	t_mlx;
struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*mlx_img;
	char	*mlx_imgadr;
	int		bitperpixel;
	int		line_size;
	int		endian;
	int		color;
};

typedef struct s_tex
{
	void	*img;
	char	*imgadr;
	int		bitperpixel;
	int		line_size;
	int		endian;
}	t_tex;


typedef struct s_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		fr;
	int		fg;
	int		fb;
	int		cr;
	int		cg;
	int		cb;
	char	**map;
	double	posx;
	double	posy;
	double	planx;
	double	plany;
	double	dirx;
	double	diry;
	char	spawn;
	t_tex	tex[3];
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
int			name_check(char *arg);
int			verifmap(char **map, t_data *data);
void		replace_space(char **map);
void		error(char *d);
int			create_trgb(int t, int r, int g, int b);
void		init_dir_plan_time(t_data *tex);
void		raycasting_loop(t_data *tex, t_mlx *mlx);
void		verline(int x, int strat, int end, int color, t_mlx	*mlx, t_data *data);

//		MOUVEMENT

void		avancer(t_data *data);
void		reculer(t_data *data);
void		droite(t_data *data);
void		gauche(t_data *data);
void		rotl(t_data	*data);
void		rotr(t_data	*data);

#endif
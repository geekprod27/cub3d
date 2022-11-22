/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:39:34 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/22 17:41:46 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define MOVESPEED 0.1
# define ROTSPEED 0.03
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
	int		texwidth;
	int		texheight;
}	t_tex;


typedef struct s_data
{
	int		f;
	int		c;
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
	t_tex	tex[4];
	t_mlx	*mlx;
	int		w;
	int		s;
	int		a;
	int		d;
	int		dr;
	int		ga;
	double	oldposx;
	double	oldposy;
	double	oldplanx;
	double	oldplany;
	double	olddirx;
	double	olddiry;
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

	double	wallx;
	int		texx;
	int		texy;
	double	step;
	double	texpos;
	int		x;

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

t_data		*get_data(char *file, t_mlx *mlx);
int			name_check(char *arg);
int			verifmap(char **map, t_data *data);
void		replace_space(char **map);
void		error(char *d, t_data *data);
int			ft_error(char *msg);
void		data_error(t_mlx *mlx);
void		mlx_events(t_data *data, t_mlx *mlx);
int			create_trgb(int t, int r, int g, int b);
void		ft_exit(t_data	*data, int exi);
char		**ft_addb(char **map, char *line);
void		saveold(t_data *data);
void		freetab(char **map);
void		ft_exit(t_data	*data, int exi);
void		minimap(t_data *d);

/*****************************************************************/
/*************************RAYCASTING_LOOP*************************/
/////////////
void		raycasting_loop(t_data *data, t_mlx *mlx);
/////////////

//inits dir, plan, and old ones
void		init_dir_plan(t_data *data);

//sets correct dir and plan with (NSWE)
void		set_dir_plan(t_data *data);

//INIT camx (x point on cam plane (-1, 0, 1)) +
//raydirX/Y (ray directions) +
//mapX/Y (current ray square info) +
//deltadistX/Y (dist to next wall to jump, avoid div by 0)
void		base_calc(t_data *data, t_ray *rays);

//INIT step (for square info mapX/Y) +
//CALC first dist to next side reached
void		step_first_dist(t_data *data, t_ray *rays);

//DDA algorithm part where decides which side/delta to jump +
//verifies wall hit +
//calc perpendicular dist ray to hit wall AKA perpwalldist
void		dda_one(t_data *data, t_ray *rays);

//calc lineHeight AKA line to be drawn + 
//start and end of it (lowest/highest pixel to fill in current stripe)
void		dda_two(t_ray *rays);

//gives texture depending on wall side
void		side_texture(t_data *data, t_ray *rays);

/*****************************************************************/
/*****************************************************************/

/*****************************************************************/
/****************************TEXTURING****************************/
/////////////
void		texture(t_data *d, t_ray *rays, int id);
/////////////

//calc of wallx (coords text on the wall)+
//calc texx = x coords of the texture, stays the same cause on as stripe
void		x_tex_calc(t_data *d, t_ray *rays, int id);

//texture pxl for roof and ceiling replaced
void		roof_ceil_tex(t_data *d, t_ray *rays, int y);

//texture pxl for wall replaced
void		wall_tex(t_data *d, t_ray *rays, int y, int id);

/*****************************************************************/
/*****************************************************************/

void		init_data(t_data *ret, t_mlx *mlx);
void		*checkid(t_data *ret, int fd);
void		errorrgb(t_data *data, char *line);
void		puterrorline(char *line, t_data *ret);
void		error(char *d, t_data *data);
void		getmap(char *line, int fd, t_data *ret);
char		**add(char **map, int i, char *line);
void		get_trgb(char *line, t_data	*data, char l);
void		checkopenxpm(int id, char *line, t_data *ret);
void		openxpm(t_data *data, char *file, t_tex *tex, int i);

/*****************************************************************/
/****************************MOVEMENTS****************************/
void		avancer(t_data *data);
void		reculer(t_data *data);
void		droite(t_data *data);
void		gauche(t_data *data);
void		rotl(t_data	*data);
void		rotr(t_data	*data);
void		rotrmouse(t_data *data, double speed);
void		rotlmouse(t_data *data, double speed);
/*****************************************************************/
/*****************************************************************/

#endif
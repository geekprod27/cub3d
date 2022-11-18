/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:13:22 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/18 15:32:42 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void    texture(t_data *data, t_ray *rays, int id, t_mlx *mlx, int x)
{
    //x coord of texture
    double  wallx;

    if (rays->side == 0)
        wallx = data->posy + rays->perpwalldist * rays->raydiry;
    else
        wallx = data->posx + rays->perpwalldist * rays->raydirx;
    wallx -= floor(wallx);

    //txx = x coord of the texture, stays the same cause on a stripe
    int texx;
    texx = (int)(wallx * (double)(data->tex[id].texwidth));
    if (rays->side == 0 && rays->raydirx > 0)
        texx = data->tex[id].texwidth - texx - 1;
    if (rays->side == 1 && rays->raydiry < 0)
        texx = data->tex[id].texwidth - texx - 1;

    //loop in y direction
    double  step;
    double  texpos;
    int     texy;
    int     y;
    char    colour[4];

    step = 1.0 * data->tex[id].texheight / rays->lineheight;
    texpos = (rays->drawstart - HEIGHT / 2 + rays->lineheight / 2) * step;
    y = rays->drawstart;
    while (y < rays->drawend)
    {
        if (y < rays->drawstart)
        {
            mlx->mlx_imgadr[(y * mlx->line_size + x * (mlx->bitperpixel / 8))] = data->cb;
			mlx->mlx_imgadr[(y * mlx->line_size + x * (mlx->bitperpixel / 8))+ 1] = data->cg;
			mlx->mlx_imgadr[(y * mlx->line_size + x * (mlx->bitperpixel / 8))+ 2] = data->cr;
			mlx->mlx_imgadr[(y * mlx->line_size + x * (mlx->bitperpixel / 8))+ 3] = 1;
        }
        else if (y >= rays->drawstart && y <= rays->drawend)
        {
            texy = (int)texpos & (data->tex[id].texheight - 1);
            texpos += step;
            colour[0] = data->tex[id].imgadr[texy * data->tex[id].texheight + texx * (mlx->bitperpixel / 8)];
            colour[1] = data->tex[id].imgadr[texy * data->tex[id].texheight + texx * (mlx->bitperpixel / 8) + 1];
            colour[2] = data->tex[id].imgadr[texy * data->tex[id].texheight + texx * (mlx->bitperpixel / 8) + 2];
            colour[3] = data->tex[id].imgadr[texy * data->tex[id].texheight + texx * (mlx->bitperpixel / 8) + 3];
            mlx->mlx_imgadr[(y * mlx->line_size + x * (mlx->bitperpixel / 8))] = colour[0];
            mlx->mlx_imgadr[(y * mlx->line_size + x * (mlx->bitperpixel / 8))+ 1] = colour[1];
            mlx->mlx_imgadr[(y * mlx->line_size + x * (mlx->bitperpixel / 8)) + 2] = colour[2];
            mlx->mlx_imgadr[(y * mlx->line_size + x * (mlx->bitperpixel / 8)) + 3] = colour[3];
            // colour = data->tex[id][data->tex->height * texy + texx];
            // buffer[y][x] = colour;
            // mlx->mlx_imgadr[y * mlx->line_size + x * (mlx->bitperpixel / 8)] = colour;
        }
        else if (y > rays->drawend)
        {
            mlx->mlx_imgadr[(y * mlx->line_size + x * (mlx->bitperpixel / 8))] = data->fb;
			mlx->mlx_imgadr[(y * mlx->line_size + x * (mlx->bitperpixel / 8)) + 1] = data->fg;
			mlx->mlx_imgadr[(y * mlx->line_size + x * (mlx->bitperpixel / 8)) + 2] = data->fr;
			mlx->mlx_imgadr[(y * mlx->line_size + x * (mlx->bitperpixel / 8)) + 3] = 1;
        }
        y++;
    }
    // drawbuffer(buffer[0]);

    //clear buffer
    // int x;
    // y = 0;
    // while (y < HEIGHT)
    // {
    //     x = 0;
    //     while (x < WIDTH)
    //     {
    //         buffer[y][x] = 0;
    //         x++;
    //     }
    //     y++;
    // }
}
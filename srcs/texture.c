/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:13:22 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/17 21:22:17 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void    texture(t_data *data, t_ray *rays, int id)
{
    //x coord of texture
    double  wallx;

    if (rays->side == 0)
        wallx = data->posy + rays->perpwalldist * rays->raydiry;
    else
        wallx = data->posx + rays->perpwalldist * rays->raydirx;
    wallx -= floor(wallx);

    //txx = x coord of the texture, stays the same cause on a stripe
    int texx = int(wallx * double(data->tex[id]->width));
    if (rays->side == 0 && rays->raydirx > 0)
        texx = data->tex[id]->width - texx - 1;
    if (rays->side == 1 && rays->raydiry < 0)
        texx = data->tex[id]->width - texx - 1;

    //loop in y direction
    double  step;
    double  texpos;
    int     texy;
    int     y;
    int     colour;

    step = 1.0 * data->tex[id]->height / rays->lineheight;
    texpos = (rays->drawstart - HEIGHT / 2 + rays->lineheight / 2) * step;
    y = rays->drawstart;
    while (y < rays->drawend)
    {
        texy = (int)texpos & (data->tex[id]->height - 1);
        texpos += step;
        colour = data->tex[id][data->tex->height * texy + texx];
        buffer[y][x] = colour;
        y++;
    }
    drawbuffer(buffer[0]);

    //clear buffer
    int x;
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            buffer[y][x] = 0;
            x++;
        }
        y++;
    }
}
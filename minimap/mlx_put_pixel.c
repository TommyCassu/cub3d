/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:23:55 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/09 15:58:30 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    pixels_to_image(t_img *image, int x, int y, int pixcolor)
{
    int    pi;

    pi = y * (image->line_s / 4) + x;
    ((int *)image->addr)[pi] = pixcolor;
}

void    draw_square(t_mlx *mlx, int x, int y, int pixcolor)
{
    int    i;
    int    j;

    i = 0;
    while (i < 32)
    {
        j = 0;
        while (j < 32)
        {
            pixels_to_image(mlx->img, x + j, i + y, pixcolor);
            j++;
        }
        i++;
    }
}

void    draw_map(t_data *data)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < data->map->height_map)
    {
        x = 0;
        while (x < data->map->width_map)
        {
            if (data->map->map_tab[y][x] == '1')
				draw_square(data->mlx, x * 32, y * 32, data->map->ceilling_rgb); //wall
			else if (data->map->map_tab[y][x] == '#')
				draw_square(data->mlx, x * 32, y * 32, 9539470);
			else if (x == data->map->player->start_x && y == data->map->player->start_y) // spawn point
				draw_square(data->mlx, x * 32, y * 32, 2883328);
			else
				draw_square(data->mlx, x * 32, y * 32, data->map->floor_rgb); //floor
            x++;
        }
        y++;
    }
}
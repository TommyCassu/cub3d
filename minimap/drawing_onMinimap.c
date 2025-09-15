/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_onMinimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:23:55 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/15 17:29:50 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    pixels_to_image_minimap_player(t_data *data, int x, int y, int pixcolor)
{
	int    pi;

	
	pi = y * (data->mlx->img->line_s / 4) + x;
	
	if (x < 0 || y < 0 || x >= 256 || y >= 256)
		return;
	((int *)data->mlx->img->addr)[pi] = pixcolor;
}

void    draw_player_minmap(t_data *data)
{
	int px;
	int py;
	int player_size;
	int i;
	int j;
	
	player_size = 8;
	px = RES_MMAP_X / 2;
	py = RES_MMAP_X / 2;
	i = 0;
	while (i < player_size/2)
	{
		j = 0;
		while (j < player_size/2)
		{
			pixels_to_image_minimap_player(data, py + i , px + j, 0xcc0000);
			j++;
		}
		i++;
	}
}

void    draw_miniMap(t_data *data)
{
	int px = (int)data->map->player->x;
	int py = (int)data->map->player->y;
	int tiles_size = 8;
	int x;
	int y;
	int mapx;
	int mapy;
	int color ;
	
	y = 0;
	while (y < RES_MMAP_Y)
	{
		x = 0;
		while (x < RES_MMAP_X)
		{
			mapx = (int)(px - (RES_MMAP_X /tiles_size ) / 2 ) + (x / tiles_size);
			mapy = (int)(py - RES_MMAP_Y / 2 / tiles_size) + (y / tiles_size);
			if (is_minimap_status(data, x, y) == 1)
			{
				if (mapx >= 0 && mapx < data->map->width_map && mapy >= 0 && mapy < data->map->height_map)
				{
					if (mapx < 0 || mapy < 0 || mapx >= data->map->width_map || mapy >= data->map->height_map)
						color = 0x000000;
					if (data->map->map_tab[mapx][mapy] == '1')
						color = data->map->ceilling_rgb;
					else
						color = data->map->floor_rgb;
					pixels_to_image(data->mlx->img, y , x, color);
				}
			}
			x++;
		}
		y++;
	}
	draw_player_minmap(data);
}




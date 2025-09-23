/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_onMinimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:23:55 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/19 14:47:51 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	pixels_to_image_minimap_player(t_data *data, int x, int y, int pixcolor)
{
	int	pi;

	pi = y * (data->mlx->img->line_s / 4) + x;
	if (x < 0 || y < 0 || x >= 256 || y >= 256)
		return ;
	((int *)data->mlx->img->addr)[pi] = pixcolor;
}

void	draw_player_minmap(t_data *data)
{
	int	px;
	int	py;
	int	player_size;
	int	i;
	int	j;

	player_size = 8;
	px = RES_MMAP_X / 2;
	py = RES_MMAP_X / 2;
	i = 0;
	while (i < player_size / 2)
	{
		j = 0;
		while (j < player_size / 2)
		{
			pixels_to_image_minimap_player(data, py + i, px + j, 0xcc0000);
			j++;
		}
		i++;
	}
}

void	draw_cube_wall(t_data *data, int x, int y)
{
	int	i;
	int	j;
	int	center_x;
	int	center_y;

	center_x = (x - data->map->player->x) * 10 + RES_MMAP_X / 2;
	center_y = (y - data->map->player->y) * 10 + RES_MMAP_Y / 2;
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (center_x + i > 0 && j + center_y > 0 && j + center_y <= RES_MMAP_X &&
				center_x + i <= RES_MMAP_Y && is_minimap_status(data, center_x + i, j + center_y) == 1)
			{
				if (j == 0 || i == 0 || j == 10 || i == 10)
					pixels_to_image(data, center_x + i,j + center_y, 0x9b8568);
				else
					pixels_to_image(data, center_x + i, j + center_y , 0x968e7c);
			}
			j++;
		}
		i++;
	}
}

void	draw_cube_floor(t_data *data, int x, int y)
{
	int	i;
	int	j;
	int	center_x;
	int	center_y;

	center_x =  (x - data->map->player->x) * 10 + RES_MMAP_X / 2;
	center_y = (y - data->map->player->y) * 10 + RES_MMAP_Y / 2;
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (center_x + i > 0 && j + center_y > 0 && j + center_y <= RES_MMAP_X && center_x + i <= RES_MMAP_Y && is_minimap_status(data,center_x + i, j + center_y) == 1)
			{
				pixels_to_image(data, center_x + i, j + center_y, 0xFFFFFF);
			}
			j++;
		}
		i++;
	}
}

void	draw_cube_outside(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < RES_MMAP_Y)
	{
		j = 0;
		while (j < RES_MMAP_X)
		{
			if (is_minimap_status(data, j, i) == 1)
				pixels_to_image(data, j, i, 0xd2bf8d);
			j++;
		}
		i++;
	}
}

void	draw_miniMap(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	draw_cube_outside(data);
	while (y < data->map->height_map)
	{
		x = data->map->width_map - 1;
		while (x >= 0)
		{
			if (data->map->map_tab[y][x] == '1' || data->map->map_tab[y][x] == '#')
				draw_cube_wall(data, x, y);
			else
				draw_cube_floor(data, x, y);
			x--;
		}
		y++;
	}
	draw_player_minmap(data);
}

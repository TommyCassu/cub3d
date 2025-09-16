/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:49:15 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/16 13:07:01 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_tab_contour(t_data *data)
{
	int x;
	int	y;

	y = 0;
	while (y < RES_MMAP_Y)
	{
		x = 0;
		while (x < RES_MMAP_X)
		{
			if (get_pixel(data->game->img_miniMap_contour, x, y) == 0xdd00fe )
				data->game->tab_contour[y][x] = 0;
			else if (get_pixel(data->game->img_miniMap_contour, x, y) == 0xfe00dd)
				data->game->tab_contour[y][x] = 1;
			else
				data->game->tab_contour[y][x] = 2;
			x++;
		}
		y++;
	}
}

void	init_data(t_data *data)
{
    ft_memset(data, 0, sizeof(t_data));
    data->map = malloc(sizeof(t_map));
    ft_memset(data->map, 0, sizeof(t_map));
    data->mlx = malloc(sizeof(t_mlx));
    ft_memset(data->mlx, 0, sizeof(t_mlx));
    data->mlx->img = malloc(sizeof(t_img));
    ft_memset(data->mlx->img, 0, sizeof(t_img));
	data->map->textdata = malloc(sizeof(t_textdata));
    ft_memset(data->map->textdata, 0, sizeof(t_textdata));
    data->map->textdata->img[0] = malloc(sizeof(t_img));
    data->map->textdata->img[1] = malloc(sizeof(t_img));
    data->map->textdata->img[2] = malloc(sizeof(t_img));
    data->map->textdata->img[3] = malloc(sizeof(t_img));
    data->map->player = malloc(sizeof(t_player));
    ft_memset(data->map->player, 0, sizeof(t_player));
	data->map->player->jumpoffset = 0;
	data->map->player->jumpspeed = 0;
	data->map->floor_rgb = -1;
	data->map->ceilling_rgb = -1;
    data->map->player->dirX = -1;
    data->map->player->dirY = 0;
}
void	init_mlx(t_mlx *mlx, t_data *data)
{
    
    mlx->ptr = mlx_init();
	data->mlx->ptr = mlx->ptr;
	data->mlx->win = mlx_new_window(data->mlx->ptr, RES_X,
	        RES_Y, "CUB3D NxT");
    mlx->img->ptr = mlx_new_image(mlx->ptr, RES_X, RES_Y);
    mlx->img->addr = (int *)mlx_get_data_addr(mlx->img->ptr, &mlx->img->bpp,
            &mlx->img->line_s, &mlx->img->endian);
    
}


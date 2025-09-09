/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:49:15 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/27 14:35:47 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->map = malloc(sizeof(t_map));
    data->mlx = malloc(sizeof(t_mlx));
	data->map->textdata = malloc(sizeof(t_textdata));
	data->map->textdata->north = NULL;
	data->map->textdata->south = NULL;
	data->map->textdata->east = NULL;
	data->map->textdata->west = NULL;
	data->map->floor_rgb = -1;
	data->map->ceilling_rgb = -1;
	data->map->width_map = 0;
	data->map->height_map = 0;
	data->error_status = 0;
}
void	init_mlx(t_mlx *mlx, t_data *data)
{
    
    mlx->ptr = mlx_init();
	data->mlx->ptr = mlx->ptr;
	data->mlx->win = mlx_new_window(data->mlx->ptr, 1920,
	        1080, "CUB3D NxT");
    mlx_loop(data->mlx->ptr);
}

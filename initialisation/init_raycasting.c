/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:44:41 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/13 01:16:47 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    init_raycast(t_data *data)
{
    data->game = malloc(sizeof(t_game));
    ft_memset(data->game, 0, sizeof(t_game));
    data->game->img_miniMap = malloc(sizeof(t_img));
    data->game->img_miniMap_contour = malloc(sizeof(t_img));
    data->game->cameraX = 0;
    data->game->planeX = 0;
    data->game->planeY = 0.66;
}

void    setup_text_img(t_data *data)
{
    int w;
    int h;

    /* NORTH */
    data->map->textdata->img[0]->ptr = mlx_xpm_file_to_image(data->mlx->ptr, data->map->textdata->north, &w, &h);
    data->map->textdata->img[0]->addr = (int *)mlx_get_data_addr(data->map->textdata->img[0]->ptr, &data->map->textdata->img[0]->bpp, &data->map->textdata->img[0]->line_s, &data->map->textdata->img[0]->endian);
    /* SOUTH */
    data->map->textdata->img[1]->ptr = mlx_xpm_file_to_image(data->mlx->ptr, data->map->textdata->south, &w, &h);
    data->map->textdata->img[1]->addr = (int *)mlx_get_data_addr(data->map->textdata->img[1]->ptr, &data->map->textdata->img[1]->bpp, &data->map->textdata->img[1]->line_s, &data->map->textdata->img[1]->endian);
    /* EST*/
    data->map->textdata->img[2]->ptr = mlx_xpm_file_to_image(data->mlx->ptr, data->map->textdata->east, &w, &h);
    data->map->textdata->img[2]->addr = (int *)mlx_get_data_addr(data->map->textdata->img[2]->ptr, &data->map->textdata->img[2]->bpp, &data->map->textdata->img[2]->line_s, &data->map->textdata->img[2]->endian);
    /* WEST */
    data->map->textdata->img[3]->ptr = mlx_xpm_file_to_image(data->mlx->ptr, data->map->textdata->west, &w, &h);
    data->map->textdata->img[3]->addr = (int *)mlx_get_data_addr(data->map->textdata->img[3]->ptr, &data->map->textdata->img[3]->bpp, &data->map->textdata->img[3]->line_s, &data->map->textdata->img[3]->endian);

}



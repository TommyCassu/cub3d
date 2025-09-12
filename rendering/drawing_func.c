/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:39:21 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/11 16:39:44 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    draw_ceiling(t_data *data, t_game *game, int x, int color)
{
    int i;

    i = 0;
    
    while (i < game->drawStart)
    {
        pixels_to_image(data->mlx->img, x, i, color);
        i++;
    }
    
}
void    draw_floor(t_data *data, t_game *game, int x, int color)
{
    int i;

    i = game->drawEnd;
    
    while (i < RES_Y)
    {
        pixels_to_image(data->mlx->img, x, i, color);
        i++;
    }
    
}

void    draw_verline(t_data *data, t_game *game, int x, int color)
{
    int i;

    i = game->drawStart;
    
    while (i < game->drawEnd)
    {
        pixels_to_image(data->mlx->img, x, i, color);
        i++;
    }
    
}
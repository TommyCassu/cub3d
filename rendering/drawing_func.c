/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:39:21 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/15 17:29:10 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    pixels_to_image(t_img *image, int x, int y, int pixcolor)
{
	int    pi;
	
	pi = y * (image->line_s / 4) + x;
	((int *)image->addr)[pi] = pixcolor;
}

void    draw_ceiling(t_data *data, t_game *game, int x, int color)
{
	int i;

	i = 0;
	
	while (i < game->drawStart)
	{
		if ((i < 256 && x < 256 && is_minimap_status(data, x, i) == 0 ) || (i >= 256 || x >= 256))
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
		if ((i < 256 && x < 256 && is_minimap_status(data, x, i) == 0 ) || (i >= 256 || x >= 256))
			pixels_to_image(data->mlx->img, x, i, color);
		i++;
	}
	
}

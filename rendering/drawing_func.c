/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:39:21 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/16 16:50:53 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    pixels_to_image(t_data *data, int x, int y, int pixcolor)
{
	int    pi;
	if (x < 0 || x >= RES_X || y < 0 || y >= RES_Y)
		return;
	pi = y * (data->mlx->img->line_s / 4) + x;
	((int *)data->mlx->img->addr)[pi] = pixcolor;
}

void    draw_ceiling(t_data *data, t_game *game, int x, int color)
{
	int i;

	i = 0;
	
	while (i < game->drawStart)
	{
		if ((i < 256 && x < 256 && is_minimap_status(data, x, i) == 0 ) || (i >= 256 || x >= 256))
			pixels_to_image(data, x, i, color);
			
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
			pixels_to_image(data, x, i, color);
		i++;
	}
	
}

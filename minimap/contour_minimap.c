/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contour_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 00:29:19 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/16 13:18:04 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_minimap_status(t_data *data, int x, int y)
{
	return (data->game->tab_contour[y][x]);
}
void	write_contour_minimap(t_data *data)
{
	int x;
	int	y;
	unsigned int color;
	
	y = 0;
	while (y < 256)
	{
		x = 0;
		while (x < 256)
		{
			if (is_minimap_status(data, x, y) != 0)
			{
				color = get_pixel(data->game->img_miniMap_contour, x, y);
				pixels_to_image(data, x , y, color);
			}
			x++;
		}
		y++;
	}
}

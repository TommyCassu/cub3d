/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contour_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 00:29:19 by tcassu            #+#    #+#             */
/*   Updated: 2025/10/01 22:31:02 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_minimap_status(t_data *data, int x, int y)
{
	return (data->game->tab_contour[y][x]);
}

void	pixels_to_image_minimap_player(t_data *data, int x, int y, int pixcolor)
{
	int	pi;

	pi = y * (data->mlx->img->line_s / 4) + x;
	if (x < 0 || y < 0 || x >= RES_MMAP_X || y >= RES_MMAP_Y)
		return ;
	((int *)data->mlx->img->addr)[pi] = pixcolor;
}

void	write_contour_minimap(t_data *data)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < RES_MMAP_Y)
	{
		x = 0;
		while (x < RES_MMAP_X)
		{
			if (is_minimap_status(data, x, y) != 0)
			{
				color = get_pixel(data->game->img_minimap_contour, x, y);
				pixels_to_image(data, x, y, color);
			}
			x++;
		}
		y++;
	}
}

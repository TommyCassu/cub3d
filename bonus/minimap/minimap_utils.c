/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 00:29:19 by tcassu            #+#    #+#             */
/*   Updated: 2025/10/08 22:25:41 by tcassu           ###   ########.fr       */
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

void	setup_minimap(t_data *data, t_img *img_contour_map, t_img *img_minimap)
{
	char	*mini;
	int		h;
	int		w;

	mini = "./bonus/textures/minimap.xpm";
	img_contour_map->ptr = mlx_xpm_file_to_image(data->mlx->ptr,
			mini, &w, &h);
	img_contour_map->addr = (int *)mlx_get_data_addr(img_contour_map->ptr,
			&img_contour_map->bpp, &img_contour_map->line_s,
			&img_contour_map->endian);
	img_minimap->ptr = mlx_new_image(data->mlx->ptr, RES_MMAP_X, RES_MMAP_Y);
	img_minimap->addr = (int *)mlx_get_data_addr(img_minimap->ptr,
			&img_minimap->bpp, &img_minimap->line_s, &img_minimap->endian);
}

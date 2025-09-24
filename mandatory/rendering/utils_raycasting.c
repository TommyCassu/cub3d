/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:38:59 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/24 16:17:09 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_pixel(t_img *image, int x, int y)
{
	int	pi;

	pi = y * (image->line_s / 4) + x;
	return (((int *)image->addr)[pi]);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	show_fps(t_data *data)
{
	char	fpsbuffer[32];

	data->game->oldtime = data->game->time;
	data->game->time = get_time();
	data->game->frametime = (data->game->time - data->game->oldtime) / 1000.0;
	sprintf(fpsbuffer, "FPS %F", 1.0 / data->game->frametime);
	mlx_string_put(data->mlx->ptr, data->mlx->win,
		500, 20, 0x000000, fpsbuffer);
}

// void	transpose_test(t_mlx *mlx, t_img *img, int w, int h)
//{
//	int		bpp, sl, endian;
//	char	*src_data = mlx_get_data_addr(img->ptr, &bpp, &sl, &endian);
//	void	*img_dst = mlx_new_image(mlx->ptr, w, h);
//	char	*dst_data = mlx_get_data_addr(img_dst, &bpp, &sl, &endian);
//	int		x;
//	int		y;
//	int		i;
//	int		src_offset;
//	int		dst_offset;
//	int		bytes_per_pixel = bpp / 8;
//
//	img_dst = malloc(sizeof(t_img));
//	x = 0;
//
//	while (x < w)
//	{
//		y = 0;
//		while (y < h)
//		{
//			src_offset = y * sl + x * bytes_per_pixel;
//			dst_offset = x * sl + y * bytes_per_pixel;
//			i = 0;
//			while (i < bytes_per_pixel)
//			{
//				dst_data[dst_offset + i] = src_data[src_offset + i];
//				i++;
//			}
//			y++;
//		}
//		x++;
//	}
//	img = img_dst;
// }

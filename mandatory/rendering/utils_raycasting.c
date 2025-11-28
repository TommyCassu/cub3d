/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:38:59 by tcassu            #+#    #+#             */
/*   Updated: 2025/11/28 22:09:51 by npederen         ###   ########.fr       */
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

/*
	//char	fpsbuffer[32];
	//sprintf(fpsbuffer, "FPS %F", 1.0 / data->game->frametime);
	//mlx_string_put(data->mlx->ptr, data->mlx->win,
	//	500, 20, 0x000000, fpsbuffer);
*/
void	show_fps(t_data *data)
{
	data->game->oldtime = data->game->time;
	data->game->time = get_time();
	data->game->frametime = (data->game->time - data->game->oldtime) / 1000.0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render_raycast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:56:06 by npederen          #+#    #+#             */
/*   Updated: 2025/10/08 21:53:46 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray(t_data *data, int x)
{
	data->game->camera_x = 2 * x / (double)RES_X - 1;
	data->game->raydir_x = data->map->player->dir_x + data->game->plane_x
		* data->game->camera_x;
	data->game->raydir_y = data->map->player->dir_y + data->game->plane_y
		* data->game->camera_x;
	data->game->map_x = (int)data->map->player->x;
	data->game->map_y = (int)data->map->player->y;
	data->game->hit = 0;
	if (data->game->raydir_x == 0)
		data->game->delta_dist_x = 1e30;
	else
		data->game->delta_dist_x = fabs(1 / data->game->raydir_x);
	if (data->game->raydir_y == 0)
		data->game->delta_dist_y = 1e30;
	else
		data->game->delta_dist_y = fabs(1 / data->game->raydir_y);
}

void	setup_angle_rayon(t_data *data)
{
	if (data->game->raydir_x < 0)
	{
		data->game->step_x = -1;
		data->game->side_dist_x = (data->map->player->x - data->game->map_x)
			* data->game->delta_dist_x;
	}
	else
	{
		data->game->step_x = 1;
		data->game->side_dist_x = (data->game->map_x + 1.0
				- data->map->player->x) * data->game->delta_dist_x;
	}
	if (data->game->raydir_y < 0)
	{
		data->game->step_y = -1;
		data->game->side_dist_y = (data->map->player->y - data->game->map_y)
			* data->game->delta_dist_y;
	}
	else
	{
		data->game->step_y = 1;
		data->game->side_dist_y = (data->game->map_y
				+ 1.0 - data->map->player->y) * data->game->delta_dist_y;
	}
}

void	dda_loop(t_data *data)
{
	while (data->game->hit == 0)
	{
		if (data->game->side_dist_x < data->game->side_dist_y)
		{
			data->game->side_dist_x += data->game->delta_dist_x;
			data->game->map_x += data->game->step_x;
			data->game->side = 0;
		}
		else
		{
			data->game->side_dist_y += data->game->delta_dist_y;
			data->game->map_y += data->game->step_y;
			data->game->side = 1;
		}
		if (data->map->map_tab[data->game->map_x][data->game->map_y] == '1')
			data->game->hit = 1;
	}
}

void	manage_draw_limits(t_data *data)
{
	if (data->game->side == 0)
		data->game->perp_wall_dist = data->game->side_dist_x
			- data->game->delta_dist_x;
	else
		data->game->perp_wall_dist = data->game->side_dist_y
			- data->game->delta_dist_y;
	data->game->line_height = (RES_Y / data->game->perp_wall_dist);
	data->game->draw_start = -data->game->line_height / 2 + RES_Y / 2
		+ data->game->head_view;
	data->game->draw_end = data->game->line_height / 2 + RES_Y / 2
		+ data->game->head_view;
	if (data->game->draw_start < 0)
		data->game->draw_start = 0;
}

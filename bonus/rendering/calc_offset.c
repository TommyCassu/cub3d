/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_offset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:36:42 by tcassu            #+#    #+#             */
/*   Updated: 2025/10/09 16:02:39 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	closed_door(t_data *data)
{
	int	index_door;

	if (calc_offset(data))
		return ;
	index_door = get_door(data, data->game->map_y, data->game->map_x);
	if ((data->game->wall_x - floor(data->game->wall_x))
		>= data->game->door[index_door].opening_state)
		data->game->hit = 2;
	else
		data->game->hit = 0;
}

int	calc_offset_other_side(t_game *game, t_map *map)
{
	if (game->raydir_x < 0)
	{
		game->walloffset = 0.5 * game->step_x;
		game->perp_wall_dist = (game->map_x - map->player->x + game->walloffset
				+ (1 - game->step_x) / 2) / game->raydir_x;
		game->wall_x = map->player->y + game->perp_wall_dist * game->raydir_y;
		if ((game->side_dist_x) - (game->delta_dist_x * 0.5)
			< game->side_dist_y)
			return (0);
		game->map_y += game->step_y;
	}
	else
	{
		game->walloffset = 0.5 * game->step_x;
		game->perp_wall_dist = (game->map_x - map->player->x + game->walloffset
				+ (1 - game->step_x) / 2) / game->raydir_x;
		game->wall_x = map->player->y + game->perp_wall_dist * game->raydir_y;
		if (game->side_dist_x - (game->delta_dist_x * 0.5) < game->side_dist_y)
			return (0);
		game->map_y += game->step_y;
	}
	return (1);
}

int	calc_offset(t_data *data)
{
	if (data->game->side == 1)
	{
		data->game->walloffset = 0.5 * data->game->step_y;
		data->game->perp_wall_dist = (data->game->map_y - data->map->player->y
				+ data->game->walloffset + (1 - data->game->step_y) / 2)
			/ data->game->raydir_y;
		data->game->wall_x = data->map->player->x + data->game->perp_wall_dist
			* data->game->raydir_x;
		if (data->game->side_dist_y - (data->game->delta_dist_y * 0.5)
			< data->game->side_dist_x)
			return (0);
		data->game->map_x += data->game->step_x;
	}
	else
	{
		if (!calc_offset_other_side(data->game, data->map))
			return (0);
	}
	data->game->side = data->game->side ^ 1;
	data->game->walloffset = 0;
	data->game->hit = 3;
	return (1);
}

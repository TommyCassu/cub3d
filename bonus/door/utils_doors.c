/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_doors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:27:43 by tcassu            #+#    #+#             */
/*   Updated: 2025/10/09 13:38:25 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	door_crossable(t_data *data, int x, int y)
{
	int	door_id;

	door_id = 0;
	
	if (data->map->map_tab[x][y] == 'D' ||data->map->map_tab[x][y] == 'D')
	{
		while (door_id < data->game->nbdoors)
		{
			if (data->game->door[door_id].y == x
				&& data->game->door[door_id].x == y)
			{
				if (data->game->door[door_id].opening_state == 0.0)
					return (1);
				else if (data->game->door[door_id].opening_state == 1.0)
				
					return (2);
			}
			door_id++;
		}
		
	}
	return (0);
}

void	interaction_door(t_data *data)
{
	int	door_id;
	int	x;
	int	y;

	x = (int)(data->map->player->x + data->map->player->dir_x * 0.8);
	y = (int)(data->map->player->y + data->map->player->dir_y * 0.8);
	door_id = 0;
	if (data->map->map_tab[x][y] == 'D')
	{
		while (door_id < data->game->nbdoors)
		{
			if (data->game->door[door_id].y == x
				&& data->game->door[door_id].x == y)
			{
				if (data->game->door[door_id].opening_state == 0.0)
					data->game->door[door_id].status = -1;
				else if (data->game->door[door_id].opening_state == 1.0)
					data->game->door[door_id].status = +1;
			}
			door_id++;
		}
	}
}

void	mooving_door(t_data *data)
{
	int	door_id;

	door_id = 0;
	while (door_id < data->game->nbdoors)
	{
		if (data->game->door[door_id].status == +1)
		{
			data->game->door[door_id].opening_state -= 0.04;
			if (data->game->door[door_id].opening_state <= 0.0)
			{
				data->game->door[door_id].opening_state = 0;
				data->game->door[door_id].status = 0;
			}
		}
		else if (data->game->door[door_id].status == -1)
		{
			data->game->door[door_id].opening_state += 0.04;
			if (data->game->door[door_id].opening_state >= 1.0)
			{
				data->game->door[door_id].opening_state = 1;
				data->game->door[door_id].status = 0;
			}
		}
		door_id++;
	}
}

int	get_door(t_data *data, int y, int x)
{
	int	door_id;

	door_id = 0;
	while (door_id < data->game->nbdoors)
	{
		if (data->game->door[door_id].y == x
			&& data->game->door[door_id].x == y)
			return (door_id);
		door_id++;
	}
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:27:40 by tcassu            #+#    #+#             */
/*   Updated: 2025/10/06 21:28:48 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	setup_one_door(t_data *data, int y, int x, int nbdoors)
{
	data->game->door[nbdoors].opening_state = 0;
	data->game->door[nbdoors].status = 0;
	data->game->door[nbdoors].y = y;
	data->game->door[nbdoors].x = x;
}

void	setup_doors(t_data *data)
{
	int	i;
	int	j;
	int	nbdoors;

	nbdoors = 0;
	i = 0;
	data->game->door = malloc(sizeof(t_door) * data->game->nbdoors);
	while (i < data->map->height_map)
	{
		j = 0;
		while (j < data->map->width_map)
		{
			if (data->map->map_tab[i][j] == 'D')
			{
				setup_one_door(data, i, j, nbdoors);
				nbdoors++;
			}
			j++;
		}
		i++;
	}
}

void	count_door(t_data *data)
{
	int	i;
	int	j;
	int	nbdoors;

	nbdoors = 0;
	i = 0;
	while (i < data->map->height_map)
	{
		j = 0;
		while (j < data->map->width_map)
		{
			if (data->map->map_tab[i][j] == 'D')
				nbdoors++;
			j++;
		}
		i++;
	}
	data->game->nbdoors = nbdoors;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:42:08 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/27 14:57:23 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height_map)
	{
		free(map->map_tab[i]);
		i++;
	}
	free(map->map_tab);
	free(map);
}

void	ft_free_cub3d(t_data *data)
{
	if (!data)
		return ;
	if (data->map)
	{
		if (data->map->textdata)
		{
			if (data->map->textdata->north)
				free(data->map->textdata->north);
			if (data->map->textdata->south)
				free(data->map->textdata->south);
			if (data->map->textdata->east)
				free(data->map->textdata->east);
			if (data->map->textdata->west)
				free(data->map->textdata->west);
			free(data->map->textdata);
		}
		free_map(data->map);
	}
	free(data);	
}

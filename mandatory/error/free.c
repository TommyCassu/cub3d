/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:42:08 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/23 22:37:18 by npederen         ###   ########.fr       */
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
			if (data->map->textdata->n)
				free(data->map->textdata->n);
			if (data->map->textdata->s)
				free(data->map->textdata->s);
			if (data->map->textdata->e)
				free(data->map->textdata->e);
			if (data->map->textdata->w)
				free(data->map->textdata->w);
			free(data->map->textdata);
		}
		free_map(data->map);
	}
	free(data);
}

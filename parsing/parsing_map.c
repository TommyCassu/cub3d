/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:47:27 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/28 00:36:59 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_valid(char c)
{
	return (c == '0' || c == '1' || is_player(c));
}

int	check_spawn(char **map, int height, int width)
{
	int	i;
	int	j;
	int	spawn_count;

	spawn_count = 0;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (is_player(map[i][j]))
				spawn_count++;
			j++;
		}
		i++;
	}
	if (spawn_count == 0)
	{
		printf("Erreur: Aucun point de spawn trouvé.\n");
		return (1);
	}
	else if (spawn_count > 1)
	{
		printf("Erreur: Plusieurs points de spawn trouvés (%d).\n", spawn_count);
		return (1);
	}
	return (0);
}

int	is_map_closed(char **map, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || is_player(map[i][j]))
			{
				if (i <= 0 || j <= 0 || i >= height - 1 || j >= width - 1)
					return (1);
				if (!is_valid(map[i + 1][j]) || !is_valid(map[i - 1][j]) ||
					!is_valid(map[i][j + 1]) || !is_valid(map[i][j - 1]))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	parsing_map(t_map	*map)
{
	if (check_spawn(map->map_tab, map->height_map, map->width_map))
		return (0);
	if (is_map_closed(map->map_tab, map->height_map, map->width_map))
	{
		printf("error map\n");
		return (0);
	}
	return (1);
}

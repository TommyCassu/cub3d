/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:47:27 by tcassu            #+#    #+#             */
/*   Updated: 2025/11/25 19:59:05 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	spawn_count_is_1(int spawn_count)
{
	if (spawn_count == 0)
	{
		printf("Error: No spawn point found.\n");
		return (1);
	}
	else if (spawn_count > 1)
	{
		printf("Error: Multiple spawn points found (%d).\n", spawn_count);
		return (1);
	}
	return (0);
}

void	set_dir_player(t_map *map, char spawn_point)
{
	if (spawn_point == 'N')
	{
		map->player->dir_x = -1;
		map->player->dir_y = 0;
	}
	else if (spawn_point == 'E')
	{
		map->player->dir_x = 0;
		map->player->dir_y = 1;
	}
	else if (spawn_point == 'S')
	{
		map->player->dir_x = 1;
		map->player->dir_y = 0;
	}
	else
	{
		map->player->dir_x = 0;
		map->player->dir_y = -1;
	}
}

int	check_spawn(t_map *map, int height, int width)
{
	int	i;
	int	j;
	int	spawn_count;

	spawn_count = 0;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (is_player(map->map_tab[i][j]))
			{
				set_dir_player(map, map->map_tab[i][j]);
				map->player->start_x = j;
				map->player->start_y = i;
				map->player->x = i + 0.5;
				map->player->y = j + 0.5;
				spawn_count++;
			}
		}
	}
	if (spawn_count_is_1(spawn_count))
		return (1);
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
			else if (map[i][j] != '#' && map[i][j] != '\0'
				&& map[i][j] != '1')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parsing_map(t_map	*map)
{
	if (check_spawn(map, map->height_map, map->width_map))
		return (0);
	if (is_map_closed(map->map_tab, map->height_map, map->width_map))
	{
		printf("Error: Invalid map enter.\n");
		return (0);
	}
	return (1);
}

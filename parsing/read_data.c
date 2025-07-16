/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:19:29 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/27 14:36:37 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	config_memory(t_map *map, char *line, char *direction)
{
	char	*new_line;

	new_line = ft_strtrim(line + 2, " \t\n");
	if (direction[0] == 'N' && direction[1] == 'O')
		map->textdata->north = ft_strdup(new_line);
	else if (direction[0] == 'S' && direction[1] == 'O')
		map->textdata->south = ft_strdup(new_line);
	else if (direction[0] == 'W' && direction[1] == 'E')
		map->textdata->west = ft_strdup(new_line);
	else if (direction[0] == 'E' && direction[1] == 'A')
		map->textdata->east = ft_strdup(new_line);
	else if (direction[0] == 'F')
		parsing_rgb(map, line, direction);
	else if (direction[0] == 'C')
		parsing_rgb(map, line, direction);
	free(direction);
	free(new_line);
	return ;
}

int	add_data(t_data *data, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0 || ft_strncmp(line, "WE", 2) == 0
		|| ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
	{
		config_memory(data->map, line, ft_substr(line, 0, 2));
		return (1);
	}
	return (0);
}

void	malloc_map(t_map *map)
{
	int	i;

	i = 0;
	map->map_tab = malloc(sizeof(char *) * map->height_map);
	if (!map->map_tab)
		return ;
	while (i < map->height_map)
	{
		map->map_tab[i] = malloc(sizeof(char) * (map->width_map + 1));
		if (!map->map_tab[i])
			return ;
		ft_memset(map->map_tab[i], '#', map->width_map);
		map->map_tab[i][map->width_map] = '\0';
		i++;
	}
}

void	read_data(t_data *data, char *filename)
{
	int		fd;
	char	*line;
	int		map_line;

	map_line = 0;
	// Rajouter la verif de l'extension du filename
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
			map_line = 1;
		if (map_line)
			read_map(data->map, line);
		else
			add_data(data, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	malloc_map(data->map);
	free(line);
	return ;
}

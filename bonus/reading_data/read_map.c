/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:49:15 by tcassu            #+#    #+#             */
/*   Updated: 2025/10/03 18:45:03 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_map_line(char *line)
{
	int	status_map;

	status_map = 0;
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0 || ft_strncmp(line, "WE", 2) == 0
		|| ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
		return (0);
	while (*line)
	{
		if (*line == '0' || *line == '1' || *line == 'N' || *line == 'S'
			|| *line == 'E' || *line == 'W' || *line == ' ' || *line == 'D')
			status_map = 1;
		line++;
	}
	return (status_map);
}

void	read_map(t_map *map, char *line)
{
	int	size;

	size = 0;
	if (is_map_line(line))
	{
		map->height_map++;
		size = ft_strlen(line) - 1;
		if (map->width_map < size)
			map->width_map = size;
	}
}

void	write_line(t_map *map, char	*line, int *i)
{
	int	j;

	j = 0;
	while (line[j] && line[j] != '\n' && j < map->width_map)
	{
		if (line[j] == ' ')
			map->map_tab[*i][j] = '#';
		else
			map->map_tab[*i][j] = line[j];
		j++;
	}
	(*i)++;
}

void	write_map(t_map *map, char	*filename)
{
	int		fd;
	char	*line;
	int		map_line;
	int		i;

	i = 0;
	map_line = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		map_line = 0;
		if (is_map_line(line))
			map_line = 1;
		if (map_line)
			write_line(map, line, &i);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	return ;
}

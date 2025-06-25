/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:19:29 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/25 23:47:12 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	config_memory(t_map *map, char *line, char *direction)
{
	char	*new_line;
	char	*tmp_line;

	tmp_line = ft_substr(line, 3, (ft_strlen(line) - 4));
	new_line = ft_strtrim(tmp_line, " ");
	if (direction[0] == 'N' && direction[1] == 'O')
		map->textdata->north = ft_strdup(new_line);
	else if (direction[0] == 'S' && direction[1] == 'O')
		map->textdata->south = ft_strdup(new_line);
	else if (direction[0] == 'W' && direction[1] == 'E')
		map->textdata->west = ft_strdup(new_line);
	else if (direction[0] == 'E' && direction[1] == 'A')
		map->textdata->east = ft_strdup(new_line);
	else if (direction[0] == 'F')
		map->floor = ft_strdup(new_line);
	else if (direction[0] == 'C')
		map->ceilling = ft_strdup(new_line);
	free(direction);
	free(tmp_line);
	free(new_line);
	return ;
}

int	add_data(t_data *data, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0 || ft_strncmp(line, "WE", 2) == 0
		|| ft_strncmp(line, "F", 1) != 0 || ft_strncmp(line, "C", 1) != 0)
	{
		config_memory(data->map, line, ft_substr(line, 0, 2));
		return (1);
	}
	return (0);
}

void	read_data(t_data *data,  char *filename)
{
	int	fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		//break if its line map
		add_data(data, line);
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		//map
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return ;
}

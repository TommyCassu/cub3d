/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:19:29 by tcassu            #+#    #+#             */
/*   Updated: 2025/11/25 15:53:08 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	config_memory(t_data *data, char *line, char *direction)
{
	char	*new_line;

	new_line = ft_strtrim(line + 2, " \t\n");
	if (direction[0] == 'N' && direction[1] == 'O')
		data->map->textdata->n = ft_strdup(new_line);
	else if (direction[0] == 'S' && direction[1] == 'O')
		data->map->textdata->s = ft_strdup(new_line);
	else if (direction[0] == 'W' && direction[1] == 'E')
		data->map->textdata->w = ft_strdup(new_line);
	else if (direction[0] == 'E' && direction[1] == 'A')
		data->map->textdata->e = ft_strdup(new_line);
	else if (direction[0] == 'F')
		parsing_rgb(data, line, direction);
	else if (direction[0] == 'C')
		parsing_rgb(data, line, direction);
	free(direction);
	free(new_line);
	return ;
}

int	add_data(t_data *data, char *line)
{
	if ((ft_strncmp(line, "NO", 2) == 0 && !data->map->textdata->n)
		|| (ft_strncmp(line, "SO", 2) == 0 && data->map->textdata->s == NULL)
		|| (ft_strncmp(line, "EA", 2) == 0 && data->map->textdata->e == NULL)
		|| (ft_strncmp(line, "WE", 2) == 0 && data->map->textdata->w == NULL)
		|| (ft_strncmp(line, "F", 1) == 0 && data->map->floor_rgb == -1)
		|| (ft_strncmp(line, "C", 1) == 0 && data->map->ceilling_rgb == -1))
	{
		config_memory(data, line, ft_substr(line, 0, 2));
		return (1);
	}
	else if (line[0] != '\n')
	{
		printf("Error map ! %s\n", line);
		data->error_status = 1;
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

int	check_valid_map(char *line)
{
	int	len;
	int	fd;	

	if (!line)
	{
		printf("Error please provide a map !\n");
		return (1);
	}
	len = ft_strlen(line);
	if (len < 4 || ft_strcmp(line + (len - 4), ".cub") != 0)
	{
		printf("Error : Bad extension file : %s\n", line);
		return (1);
	}
	fd = open(line, O_RDONLY);
	if (fd < 0)
	{
		printf("Error : Cannot open map file : %s.\n", line);
		return (1);
	}
	return (0);
}

void	read_data(t_data *data, char *filename)
{
	int		fd;
	int		map_line;

	map_line = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	read_line_gnl(data, fd, map_line);
	close(fd);
	malloc_map(data->map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:30 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/25 18:09:09 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_valid_texture(char *line)
{
	int	len;
	int	fd;
	
	line += 3;
	len = ft_strlen(line);
	if (ft_strncmp(line + (len - 5), ".xpm", 4) != 0)
	{
		if (!(len > 4))
		return (perror("bad extantion"), 1);
	}
	fd = open(line, O_RDONLY);
	if (fd < 0)
		return (perror("Bad file"), 1);
	return (0);
}

int	parse_textures(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		check_valid_texture(line);
	else if (ft_strncmp(line, "SO", 2) == 0)
		check_valid_texture(line);
	else if (ft_strncmp(line, "EA", 2) == 0)
		check_valid_texture(line);
	else if (ft_strncmp(line, "WE", 2) == 0)
		check_valid_texture(line);
	return (1);
}

int	parsing(t_data *data, char *filename)
{
	int	fd;
	char	*line;
	
	(void)data;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strcmp(line, "\n") == 0)
		{
			parse_textures(line);
			//	map
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (1);
}

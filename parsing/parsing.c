/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:30 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/25 22:26:32 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_valid_file(char *line)
{
	int	len;
	int	fd;
	char	*new_line;
	
	
	new_line = ft_substr(line, 3, (ft_strlen(line) - 4));
	len = ft_strlen(new_line);
	if (len < 4 || ft_strcmp(new_line + (len - 4), ".xpm") != 0)
	{
		free(new_line);
		return (perror("bad extension"), 1);
	}
	fd = open(new_line, O_RDONLY);
	if (fd < 0)
	{
		free(new_line);
		return (perror("Bad file"), 1);
	}
		
	return (0);
}

int	parse_textures(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0 || ft_strncmp(line, "WE", 2) == 0)
			check_valid_file(line);
	//else if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
		// verif valid color;
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

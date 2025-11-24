/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:03:25 by tcassu            #+#    #+#             */
/*   Updated: 2025/11/24 15:50:56 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	read_line_gnl(t_data *data, int fd, int map_line)
{
	char	*line;
	char	*tmp_line;
	
	line = get_next_line(fd);
	if (line == NULL)
	{
		printf("Error map ! File is empty\n");
		data->error_status = 1;
		return ;
	}
	while (line)
	{
		if (is_map_line(line))
			map_line = 1;
		if (map_line)
			read_map(data->map, line);
		else
		{
			tmp_line = ft_strtrim(line, " \t");
			add_data(data, tmp_line);
			free(tmp_line);
		}	
		free(line);
		line = get_next_line(fd);
	}
}

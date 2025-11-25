/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:30 by tcassu            #+#    #+#             */
/*   Updated: 2025/11/25 16:43:49 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_valid_file(char *line)
{
	int	len;
	int	fd;	

	if (!line)
	{
		printf("Error map ! Directionnal image missing\n");
		return (1);
	}
	len = ft_strlen(line);
	if (len < 4 || ft_strcmp(line + (len - 4), ".xpm") != 0)
	{
		printf("Error : Bad extension file : %s.\n", line);
		return (1);
	}
	fd = open(line, O_RDONLY);
	if (fd < 0)
	{
		printf("Error : Cannot open texture file : %s.\n", line);
		return (1);
	}
	return (0);
}

int	parsing_texture(t_textdata *textures)
{
	if (check_valid_file(textures->n) || check_valid_file(textures->s)
		|| check_valid_file(textures->e) || check_valid_file(textures->w))
	{
		free(textures->n);
		free(textures->s);
		free(textures->w);
		free(textures->e);
		textures->n = NULL;
		textures->s = NULL;
		textures->e = NULL;
		textures->w = NULL;
		return (0);
	}
	return (1);
}

void	attribute_rgb(t_data *data, char **tab_value, char *direction)
{
	int	r;
	int	g;
	int	b;

	if (ft_verif_digit(tab_value[0]) && ft_verif_digit(tab_value[1])
		&& ft_verif_digit(tab_value[2]))
	{
		r = ft_atoi(tab_value[0]);
		g = ft_atoi(tab_value[1]);
		b = ft_atoi(tab_value[2]);
		if (check_rgb_limit(r, g, b, tab_value) == 1)
		{
			data->error_status = 1;
			return ;
		}
		else
		{
			if (direction[0] == 'F')
				data->map->floor_rgb = (r << 16) | (g << 8) | b;
			else if (direction[0] == 'C')
				data->map->ceilling_rgb = (r << 16) | (g << 8) | b;
		}
	}
	ft_free(tab_value);
	free(tab_value);
}

void	parsing_rgb(t_data *data, char *line, char *direction)
{
	char	*new_value;
	char	**tab_value;
	char	*tmp;
	int		i;

	i = -1;
	new_value = NULL;
	if (direction[0] == 'F')
		new_value = ft_strtrim(line, " F\n");
	else if (direction[0] == 'C')
		new_value = ft_strtrim(line, " C\n");
	tab_value = ft_split(new_value, ',');
	if (check_rgb_value(new_value, tab_value) == 1)
		return ;
	while (++i < 3)
	{
		if (tab_value[i])
		{
			tmp = ft_strtrim(tab_value[i], " \t");
			free(tab_value[i]);
			tab_value[i] = tmp;
		}
	}
	attribute_rgb(data, tab_value, direction);
}

int	parsing(t_data *data)
{
	if (!parsing_texture(data->map->textdata))
	{
		data->error_status = 1;
		return (0);
	}
	if (data->map->ceilling_rgb == -1 || data->map->floor_rgb == -1)
	{
		if (data->error_status != 1)
			printf("Error map ! RGB wrong value\n");
		data->error_status = 1;
		return (0);
	}
	if (!parsing_map(data->map))
	{
		data->error_status = 1;
		return (0);
	}
	set_plane_dir(data->game, data->map->player);
	return (1);
}

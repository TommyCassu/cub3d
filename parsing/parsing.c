/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:30 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/28 00:37:38 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_valid_file(char *line)
{
	int	len;
	int	fd;	

	if (!line)
		return (1);
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
	if (check_valid_file(textures->north))
	{
		free(textures->north);
		textures->north = NULL;
		return (0);
	}
	else if (check_valid_file(textures->south))
	{
		free(textures->south);
		textures->south = NULL;
		return (0);
	}
	else if (check_valid_file(textures->east))
	{
		free(textures->east);
		textures->east = NULL;
		return (0);
	}
	else if (check_valid_file(textures->west))
	{
		free(textures->west);
		textures->west = NULL;
		return (0);
	}
	return (1);
}

int	ft_verif_digit(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
void	attribute_rgb(t_map *map, char **tab_value, char *direction)
{
	int		r;
	int		g;
	int		b;
	r = ft_atoi(tab_value[0]);
	g = ft_atoi(tab_value[1]);
	b = ft_atoi(tab_value[2]);
	if (!(r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255))
		return ;
	if (direction[0] == 'F')
		map->floor_rgb = (r << 16) | (g << 8) | b;
	else if (direction[0] == 'C')
		map->ceilling_rgb = (r << 16) | (g << 8) | b;
}
void	parsing_rgb(t_map *map, char *line, char *direction)
{
	char	*new_value;
	char	**tab_value;

	new_value = NULL;
	if (direction[0] == 'F')
		new_value = ft_strtrim(line, " F\n");
	else if (direction[0] == 'C')
		new_value = ft_strtrim(line, " C\n");
	tab_value = ft_split(new_value, ',');;
	if (!tab_value[0] || !tab_value[1] || !tab_value[2])
		return ;
	if (new_value)
		free(new_value);
	if (ft_verif_digit(tab_value[0]) && ft_verif_digit(tab_value[1]) && ft_verif_digit(tab_value[2]))
		attribute_rgb(map, tab_value, direction);
	ft_free(tab_value);
	free(tab_value);
}

int	parsing(t_data *data)
{
	if (!parsing_texture(data->map->textdata))
		return (0);
	if (data->map->ceilling_rgb == -1 || data->map->floor_rgb == -1)
		return (0); // error free
	if (!parsing_map(data->map))
		return (0);
	return (1);
}

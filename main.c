/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:55:14 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/28 00:37:13 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
int	error_msg(char	*msg)
{
	printf("%s\n", msg);
	//free data
	return (1);
}
*/

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height_map)
	{
		printf("%s\n", map->map_tab[i]);
		i++;
	}
	if (map->textdata->north)
		printf("%s\n", map->textdata->north);
	if (map->textdata->south)
		printf("%s\n", map->textdata->south);
	printf("%s\n", map->textdata->east);
	printf("%s\n", map->textdata->west);
	printf("%d\n", map->ceilling_rgb);
	printf("%d\n", map->floor_rgb);
}

void	init_data(t_data *data)
{
	data->map = malloc(sizeof(t_map));
	data->map->textdata = malloc(sizeof(t_textdata));
	data->map->textdata->north = NULL;
	data->map->textdata->south = NULL;
	data->map->textdata->east = NULL;
	data->map->textdata->west = NULL;
	data->map->floor_rgb = -1;
	data->map->ceilling_rgb = -1;
	data->map->width_map = 0;
	data->map->height_map = 0;
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		data = malloc(sizeof(t_data));
		init_data(data);
		read_data(data, av[1]);
		write_map(data->map, av[1]);
		if (parsing(data))
			print_map(data->map);
		ft_free_cub3d(data);
	}
	return (0);
}

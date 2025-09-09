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



int	main(int ac, char **av)
{
	t_data	*data;
	if (ac == 2)
	{
		
		data = malloc(sizeof(t_data));
		ft_memset(data, 0, sizeof(t_data));
		
		init_data(data);
		init_mlx(data->mlx, data);
		read_data(data, av[1]);
		if (data->error_status == 1)
		{
			ft_free_cub3d(data);
			return (0);
		}
		write_map(data->map, av[1]);
		if (parsing(data))
		{
			print_map(data->map);
		}

		ft_free_cub3d(data);
	}
	
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:55:14 by tcassu            #+#    #+#             */
/*   Updated: 2025/10/21 16:10:21 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height_map)
	{
		printf("%s\n", map->map_tab[i]);
		i++;
	}
	if (map->textdata->n)
		printf("%s\n", map->textdata->n);
	if (map->textdata->s)
		printf("%s\n", map->textdata->s);
}

void	setups_bonus_functions(t_data *data)
{
	setup_text_img(data, data->map->textdata);
	setup_text_sprites(data, data->game->sprite);
	count_door(data);
	setup_doors(data);
	setup_minimap(data, data->game->img_minimap_contour,
		data->game->img_minimap);
	init_tab_contour(data);
	write_contour_minimap(data);
}

void	main_hook(t_data *data)
{
	mlx_hook(data->mlx->win, MotionNotify, PointerMotionMask,
		mouse_handler, data);
	mlx_hook(data->mlx->win, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->mlx->win, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->mlx->win, DestroyNotify, NoEventMask, ft_exit, data);
	mlx_loop_hook(data->mlx->ptr, handler_render, data);
	mlx_loop(data->mlx->ptr);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2 && check_valid_map(av[1]) == 0)
	{
		data = malloc(sizeof(t_data));
		init_data(data);
		init_mlx(data->mlx, data);
		init_raycast(data);
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
			setups_bonus_functions(data);
			main_hook(data);
		}
		ft_free_cub3d(data);
	}
	else
		printf("program needs two arguments <./cub3d file.cub>\n");
	return (0);
}

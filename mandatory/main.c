/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:55:14 by tcassu            #+#    #+#             */
/*   Updated: 2025/11/25 15:52:01 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
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

int	handler_render(t_data *data)
{
	key_handler(data, data->game, data->map->player);
	render_raycast(data, data->game);
	return (0);
}

void	main_hook(t_data *data)
{
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
			setup_text_img(data, data->map->textdata);
			main_hook(data);
		}
		ft_free_cub3d(data);
	}
	else
		printf("program needs two arguments <./cub3d file.cub>\n");
	return (0);
}

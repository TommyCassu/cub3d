/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:55:14 by tcassu            #+#    #+#             */
/*   Updated: 2025/10/01 13:18:54 by npederen         ###   ########.fr       */
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

int	test_rend(t_data *data)
{
	key_handler(data, data->game, data->map->player);
	render_raycast(data, data->game);
	draw_mini_map(data);
	return (0);
}
void setup_minimap(t_data *data)
{
	char	*mini;
	int		h;
	int		w;

	mini = "./bonus/textures/minimap.xpm";
	data->game->img_minimap_contour->ptr = mlx_xpm_file_to_image(data->mlx->ptr, mini, &w, &h);
	// data->game->img_minimap->ptr = mlx_new_image(data->mlx->ptr, RES_MMAP_X, RES_MMAP_Y);
	data->game->img_minimap_contour->addr = (int *)mlx_get_data_addr(data->game->img_minimap_contour->ptr, &data->game->img_minimap_contour->bpp,
																	 &data->game->img_minimap_contour->line_s, &data->game->img_minimap_contour->endian);
	/* map */
	data->game->img_minimap->ptr = mlx_new_image(data->mlx->ptr, RES_MMAP_X, RES_MMAP_Y);
	data->game->img_minimap->addr = (int *)mlx_get_data_addr(data->game->img_minimap->ptr, &data->game->img_minimap->bpp,
															 &data->game->img_minimap->line_s, &data->game->img_minimap->endian);
}
int	main(int ac, char **av)
{
	t_data *data;

	if (ac == 2)
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
			setup_text_img(data, data->map->textdata);
			setup_minimap(data);
			init_tab_contour(data);
			write_contour_minimap(data);
			mlx_hook(data->mlx->win, KeyPress, KeyPressMask, key_press, data);
			mlx_hook(data->mlx->win, KeyRelease, KeyReleaseMask, key_release, data);
			mlx_hook(data->mlx->win, DestroyNotify, NoEventMask, ft_exit, data);
			mlx_loop_hook(data->mlx->ptr, test_rend, data);
			mlx_loop(data->mlx->ptr);
		}
		ft_free_cub3d(data);
	}

	return (0);
}

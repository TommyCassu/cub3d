/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:55:14 by tcassu            #+#    #+#             */
/*   Updated: 2025/10/03 21:01:40 by npederen         ###   ########.fr       */
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

int	test_rend(t_data *data)
{
	render_raycast(data, data->game);
	key_handler(data, data->game, data->map->player);
	draw_mini_map(data);
	door_counter(data);
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
int	mouse_handler(int new_xpos, int new_ypos, void *param)
{
	t_data *data;
	data = (t_data *)param;
	static int old_xpos = RES_X / 2;
	static int old_ypos = RES_Y / 2;
	mlx_mouse_get_pos(data->mlx->ptr, data->mlx->win, &new_xpos, &new_ypos);
	if (new_xpos < old_xpos)
	{
		turn_left(data->game, data->map->player);
		old_xpos = new_xpos;
		old_ypos = new_ypos;
	}
	if (new_xpos > old_xpos)
	{
		turn_right(data->game, data->map->player);
		old_xpos = new_xpos;
		old_ypos = new_ypos;
	}
	//if (new_ypos < (RES_Y / 2 + 100))
	//{
	//	if (data->game->head_view < 200)
	//		data->game->head_view += 4;
	//	old_ypos = new_ypos;
	//}
	//if (new_ypos > (RES_Y / 2 - 100))
	//{
	//	if (data->game->head_view > -200)
	//		data->game->head_view -= 4;
	//	old_ypos = new_ypos;
	//}
	if(old_xpos > 1900 || old_xpos < 15 || old_ypos < 15 || old_ypos > 1000)
		mlx_mouse_move(data->mlx->ptr, data->mlx->win, RES_X / 2, RES_Y / 2);
	return (0);
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
			setup_text_sprites(data, data->game->sprite);
			setup_minimap(data);
			init_tab_contour(data);
			write_contour_minimap(data);
			mlx_hook(data->mlx->win, MotionNotify, PointerMotionMask, mouse_handler, data);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:02:41 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/09 18:30:33 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void    draw_player(t_mlx *mlx, int px, int py, int color)
{
	int i, j;

	i = 0;
	while (i < 8) // carré de 8x8
	{
		j = 0;
		while (j < 8)
		{
			pixels_to_image(mlx->img, px + j, py + i, color);
			j++;
		}
		i++;
	}
}

int	handler_player(int key, void *param)
{
	int		x;
	int		y;
	t_data	*data;

	data = (t_data *)param;
	x = data->map->player->x;
	y = data->map->player->y;
	//if (key == XK_Escape)
	//	handler_exit_data(data);
	if ((key == XK_w || key == XK_Up))
		move_player(data, 'W');
	else if ((key == XK_a || key == XK_Left))
		move_player(data, 'A');
	else if ((key == XK_s || key == XK_Down))
		move_player(data, 'S');
	else if ((key == XK_d || key == XK_Right))
		move_player(data, 'D');
	return (0);
}

void	move_player(t_data *data, char key)
{
	int step = 4;
	 if (key == 'W')
		data->map->player->y -= step;
	else if (key == 'S')
		data->map->player->y += step;
	else if (key == 'A')
		data->map->player->x -= step;
	else if (key == 'D')
		data->map->player->x += step;
	mlx_clear_window(data->mlx->ptr, data->mlx->win);
	draw_map(data);
	draw_player(data->mlx, data->map->player->x, data->map->player->y, 0xFF0000);

	mlx_put_image_to_window(data->mlx->ptr, data->mlx->win, data->mlx->img->ptr, 0, 0);
}
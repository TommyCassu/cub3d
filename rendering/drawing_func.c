/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:39:21 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/24 16:29:15 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	pixels_to_image(t_data *data, int x, int y, int pixcolor)
{
	int	pi;

	if (x < 0 || x >= RES_X || y < 0 || y >= RES_Y)
		return ;
	pi = y * (data->mlx->img->line_s / 4) + x;
	((int *)data->mlx->img->addr)[pi] = pixcolor;
}

void	draw_ceiling(t_data *data, t_game *game, int x, int color)
{
	int	i;

	i = 0;
	while (i < game->draw_start)
	{
		if ((i < 256 && x < 256 && is_minimap_status(data, x, i) == 0)
			|| (i >= 256 || x >= 256))
			pixels_to_image(data, x, i, color);
		i++;
	}
}

void	init_floor_params(t_data *data, t_game *game, int y)
{
	game->jumpoffsetresy = (int)(data->map->player->jumpoffset * RES_Y);
	game->ray_dir_x0 = data->map->player->dir_x - game->plane_x;
	game->ray_dir_y0 = data->map->player->dir_y - game->plane_y;
	game->ray_dir_x1 = data->map->player->dir_x + game->plane_x;
	game->ray_dir_y1 = data->map->player->dir_y + game->plane_y;
	game->p = y - RES_Y / 2 - game->jumpoffsetresy - game->head_view;
	game->pos_z = 0.5 * RES_Y;
	game->row_distance = game->pos_z / game->p;
	game->floor_step_x = game->row_distance * (game->ray_dir_x1
			- game->ray_dir_x0) / RES_X;
	game->floor_step_y = game->row_distance * (game->ray_dir_y1
			- game->ray_dir_y0) / RES_X;
	game->floor_x = data->map->player->x + game->row_distance
		* game->ray_dir_x0;
	game->floor_y = data->map->player->y + game->row_distance
		* game->ray_dir_y0;
}

void	draw_floor(t_data *data, t_game *game, t_map *map)
{
	int	y;
	int	x;

	y = (RES_Y / 2) + game->jumpoffsetresy + game->head_view;
	while (y < RES_Y)
	{
		init_floor_params(data, game, y);
		x = 0;
		while (++x < RES_X)
		{
			game->cell_x = (int)(game->floor_x);
			game->cell_y = (int)(game->floor_y);
			game->tx = (int)(TEXT_SIZE * (game->floor_x - game->cell_x))
				& (TEXT_SIZE - 1);
			game->ty = (int)(TEXT_SIZE * (game->floor_y - game->cell_y))
				& (TEXT_SIZE - 1);
			game->floor_x += game->floor_step_x;
			game->floor_y += game->floor_step_y;
			game->color = get_pixel(map->textdata->img[4], game->tx, game->ty);
			if ((y < 256 && x < 256 && is_minimap_status(data, x, y) == 0)
				|| (y >= 256 || x >= 256))
				pixels_to_image(data, x, y, game->color);
		}
		y++;
	}
}

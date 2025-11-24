/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 03:23:27 by tcassu            #+#    #+#             */
/*   Updated: 2025/11/24 03:24:15 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_floor_params(t_data *data, t_game *game, int y)
{
	game->jumpoffsetresy = (int)(data->map->player->jumpoffset * RES_Y);
	game->ray_dir_x0 = data->map->player->dir_x - game->plane_x;
	game->ray_dir_y0 = data->map->player->dir_y - game->plane_y;
	game->ray_dir_x1 = data->map->player->dir_x + game->plane_x;
	game->ray_dir_y1 = data->map->player->dir_y + game->plane_y;
	game->p = (y - (RES_Y / 2)) + game->jumpoffsetresy + game->head_view;
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

void	select_side_floor(t_data *data, t_game *game)
{
	if (game->side == 0 && data->game->raydir_x > 0)
	{
		game->floor_x_wall = data->game->map_x;
		game->floor_y_wall = data->game->map_y + data->game->wall_x;
	}
	else if (game->side == 0 && data->game->raydir_x < 0)
	{
		game->floor_x_wall = data->game->map_x + 1.0;
		game->floor_y_wall = data->game->map_y + data->game->wall_x;
	}
	else if (game->side == 1 && data->game->raydir_y > 0)
	{
		game->floor_x_wall = data->game->map_x + data->game->wall_x;
		game->floor_y_wall = data->game->map_y;
	}
	else
	{
		game->floor_x_wall = data->game->map_x + data->game->wall_x;
		game->floor_y_wall = data->game->map_y + 1.0;
	}
}

double	calc_weight(t_data *data, t_game *game, int y)
{
	double	dist_wall;
	double	dist_player;
	double	current_dist;

	dist_wall = game->perp_wall_dist;
	dist_player = 0.0;
	current_dist = (RES_Y + (2 * game->jumpoffsetresy
				* game->perp_wall_dist))
		/ (2 * (y - data->game->head_view) - RES_Y);
	return ((current_dist - dist_player) / (dist_wall - dist_player));
}

void	get_pixel_floor_color(t_game *game, t_map *map)
{
	if (map->map_tab[(int)game->current_floor_x]
		[(int)game->current_floor_y]
		&& (map->map_tab[(int)game->current_floor_x]
			[(int)game->current_floor_y] == '2'
			|| map->map_tab[(int)game->current_floor_x]
			[(int)game->current_floor_y] == 'D'))
		game->color = get_pixel(map->textdata->img[6],
				game->floor_text_x, game->floor_text_y);
	else
		game->color = get_pixel(map->textdata->img[4],
				game->floor_text_x, game->floor_text_y);
}

void	draw_floor(t_data *data, t_game *game, t_map *map, int x)
{
	double	weight;
	int		y;

	select_side_floor(data, game);
	if (game->draw_end < 0)
		game->draw_end = RES_Y;
	y = game->draw_end + 1;
	while (y < RES_Y)
	{
		weight = calc_weight(data, game, y);
		game->current_floor_x = weight * game->floor_x_wall
			+ (1.0 - weight) * data->map->player->x;
		game->current_floor_y = weight * game->floor_y_wall
			+ (1.0 - weight) * data->map->player->y;
		game->floor_text_x = (int)(game->current_floor_x
				* TEXT_SIZE) & (TEXT_SIZE - 1);
		game->floor_text_y = (int)(game->current_floor_y
				* TEXT_SIZE) & (TEXT_SIZE - 1);
		get_pixel_floor_color(game, map);
		if ((y < 256 && x < 256 && is_minimap_status(data, x, y) == 0)
			|| (y >= 256 || x >= 256))
			pixels_to_image(data, x, y, game->color);
		y++;
	}
}

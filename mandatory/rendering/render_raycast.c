/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:48:32 by tcassu            #+#    #+#             */
/*   Updated: 2025/10/08 21:54:33 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	select_texture_side(t_game *game)
{
	if (game->side == 0)
	{
		if (game->raydir_x > 0)
			game->text_num = 0;
		else
			game->text_num = 1;
	}
	else
	{
		if (game->raydir_y > 0)
			game->text_num = 2;
		else
			game->text_num = 3;
	}
}

void	get_texture_pos(t_data *data)
{
	double	wall_x;
	int	size_img_text;

	size_img_text = data->map->textdata->img[data->game->text_num]->h;
	if (data->game->side == 0)
		wall_x = data->map->player->y + data->game->perp_wall_dist
			* data->game->raydir_y;
	else
		wall_x = data->map->player->x + data->game->perp_wall_dist
			* data->game->raydir_x;
	wall_x -= floor(wall_x);
	data->game->tex_x = (int)(wall_x * (double)(size_img_text));
	if (data->game->side == 0 && data->game->raydir_x > 0)
		data->game->tex_x = size_img_text - data->game->tex_x - 1;
	if (data->game->side == 1 && data->game->raydir_y < 0)
		data->game->tex_x = size_img_text - data->game->tex_x - 1;
	data->game->step = 1.0 * size_img_text / data->game->line_height;
	data->game->tex_pos = ((data->game->draw_start - RES_Y / 2
				+ data->game->line_height / 2) * data->game->step);
}

void	draw_wall_col(t_data *data, int x)
{
	int	i;
	int	color;

	color = 0xeeeeee;
	i = data->game->draw_start;
	if (data->game->draw_end >= RES_Y)
		data->game->draw_end = RES_Y - 1;
	while (i < data->game->draw_end)
	{
		data->game->tex_y = (int)data->game->tex_pos
				& (data->map->textdata->img[data->game->text_num]->h - 1);
		data->game->tex_pos += data->game->step;
		color = get_pixel(data->map->textdata->img[data->game->text_num],
				data->game->tex_x, data->game->tex_y);
		if (data->game->side == 1)
			color = (color >> 1) & 8355711;
		pixels_to_image(data, x, i, color);
		i++;
	}
}

void	render_raycast(t_data *data, t_game *game)
{
	int	x;

	while (1)
	{
		x = -1;
		while (++x < RES_X)
		{
			init_ray(data, x);
			setup_angle_rayon(data);
			dda_loop(data);
			manage_draw_limits(data);
			select_texture_side(game);
			get_texture_pos(data);
			draw_wall_col(data, x);
			draw_ceiling(data, game, x, data->map->ceilling_rgb);
			draw_floor(data, game, x, data->map->floor_rgb);
		}
		mlx_put_image_to_window(data->mlx->ptr, data->mlx->win,
			data->mlx->img->ptr, 0, 0);
		show_fps(data);
		game->movespeed = game->frametime * 8.0;
		game->rotspeed = game->frametime * 3.0;
		break ;
	}
}

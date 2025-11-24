/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:48:32 by tcassu            #+#    #+#             */
/*   Updated: 2025/11/24 14:39:24 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	select_texture_side(t_data *data, t_game *game)
{
	if (data->map->map_tab[data->game->map_x][data->game->map_y] == 'D')
	{
		game->text_num = 5;
		return ;
	}
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
	int	index_door;

	index_door = get_door(data, data->game->map_y, data->game->map_x);
	if (data->map->map_tab[data->game->map_x][data->game->map_y] == 'D')
		data->game->tex_x = (int)(((data->game->wall_x
						+ (1.0 - data->game->door[index_door].opening_state))
					- floor(data->game->wall_x
						+ (1.0 - data->game->door[index_door].opening_state)))
				* TEXT_SIZE);
	else
		data->game->tex_x = (int)(data->game->wall_x * (double)(TEXT_SIZE));
	if (data->game->side == 0 && data->game->raydir_x > 0)
		data->game->tex_x = TEXT_SIZE - data->game->tex_x - 1;
	if (data->game->side == 1 && data->game->raydir_y < 0)
		data->game->tex_x = TEXT_SIZE - data->game->tex_x - 1;
	data->game->step = 1.0 * TEXT_SIZE / data->game->line_height;
	data->game->tex_pos = (data->game->draw_start - RES_Y / 2
			+ data->game->line_height / 2 - data->game->head_view
			- data->game->jumpoffsetresy) * data->game->step;
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
		data->game->tex_y = (int)data->game->tex_pos & (TEXT_SIZE - 1);
		data->game->tex_pos += data->game->step;
		color = get_pixel(data->map->textdata->img[data->game->text_num],
				data->game->tex_x, data->game->tex_y);
		if (data->game->side == 1)
			color = (color >> 1) & 8355711;
		if ((i < 256 && x < 256 && is_minimap_status(data, x, i) == 0)
			|| (i >= 256 || x >= 256))
			pixels_to_image(data, x, i, color);
		i++;
	}
}

void	render_raycast(t_data *data, t_game *game)
{
	int		x;
	double	zbuffer[RES_X];

	while (1)
	{
		x = -1;
		calcul_jump_offset(data);
		while (++x < RES_X)
		{
			init_ray(data, x);
			setup_angle_rayon(data);
			dda_loop(data);
			manage_draw_limits(data);
			select_texture_side(data, game);
			get_texture_pos(data);
			draw_wall_col(data, x);
			zbuffer[x] = game->perp_wall_dist;
			draw_floor(data, game, data->map, x);
			draw_ceiling(data, game, x, data->map->ceilling_rgb);
		}
		render_sprite(data, game, game->sprite, zbuffer);
		mlx_put_image_to_window(data->mlx->ptr, data->mlx->win,
			data->mlx->img->ptr, 0, 0);
		show_fps(data);
		game->movespeed = game->frametime * 8.0;
		game->rotspeed = game->frametime * 2.0;
		break ;
	}
}

void	calcul_jump_offset(t_data *data)
{
	if (data->map->player->isjumping)
	{
		data->map->player->jumpoffset += data->map->player->jumpspeed;
		data->map->player->jumpspeed -= 0.02;
		if (data->map->player->jumpoffset <= 0)
		{
			data->map->player->jumpoffset = 0;
			data->map->player->isjumping = 0;
		}
	}
}

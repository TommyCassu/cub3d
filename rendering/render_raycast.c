/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:48:32 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/24 14:58:08 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	select_texture_side(t_game *game)
{
	/* Select the good texture (NORTH/SOUTH/EAST/WEST)*/
	if (game->side == 0)
	{
		if (game->rayDir_x > 0)
			game->textNum = 0;
		else
			game->textNum = 1;
	}
	else
	{
		if (game->rayDir_y > 0)
			game->textNum = 2;
		else
			game->textNum = 3;
	}
}

void	get_texture_pos(t_data *data)
{
	double	wall_x;

	data->game->jumpoffsetresy = (int)(data->map->player->jumpoffset * RES_Y);
	if (data->game->side == 0)
		wall_x = data->map->player->y + data->game->perpWallDist
			* data->game->rayDir_y;
	else
		wall_x = data->map->player->x + data->game->perpWallDist
			* data->game->rayDir_x;
	wall_x -= floor(wall_x);
	data->game->texX = (int)(wall_x * (double)(TEXT_SIZE));
	if (data->game->side == 0 && data->game->rayDir_x > 0)
		data->game->texX = TEXT_SIZE - data->game->texX - 1;
	if (data->game->side == 1 && data->game->rayDir_y < 0)
		data->game->texX = TEXT_SIZE - data->game->texX - 1;
	data->game->step = 1.0 * TEXT_SIZE / data->game->lineHeight;
	data->game->texPos = ((data->game->drawStart - RES_Y / 2
				+ data->game->lineHeight / 2 - data->game->jumpoffsetresy
				- data->game->headView)) * data->game->step;
}

void	draw_wall_col(t_data *data, int x)
{
	int	i;
	int	color;

	color = 0xeeeeee;
	i = data->game->drawStart;
	if (data->game->drawEnd >= RES_Y)
		data->game->drawEnd = RES_Y - 1;
	while (i < data->game->drawEnd)
	{
		data->game->texY = (int)data->game->texPos & (TEXT_SIZE - 1);
		data->game->texPos += data->game->step;
		color = get_pixel(data->map->textdata->img[data->game->textNum],
				data->game->texX, data->game->texY);
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
	int	x;

	while (1)
	{
		x = -1;
		draw_floor(data, game, data->map);
		calcul_jump_offset(data);
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
		}
		mlx_put_image_to_window(data->mlx->ptr, data->mlx->win,
			data->mlx->img->ptr, 0, 0);
		show_fps(data);
		game->moveSpeed = game->frameTime * 8.0;
		game->rotSpeed = game->frameTime * 3.0;
		break ;
	}
}

void	calcul_jump_offset(t_data *data)
{
	if (data->map->player->isjumping)
	{
		data->map->player->jumpoffset += data->map->player->jumpspeed;
		data->map->player->jumpspeed -= 0.001;
		if (data->map->player->jumpoffset <= 0)
		{
			data->map->player->jumpoffset = 0;
			data->map->player->isjumping = 0;
		}
	}
}

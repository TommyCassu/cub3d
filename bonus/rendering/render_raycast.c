/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:48:32 by tcassu            #+#    #+#             */
/*   Updated: 2025/10/09 14:51:33 by npederen         ###   ########.fr       */
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
			+ data->game->line_height / 2 - data->game->head_view - data->game->jumpoffsetresy) * data->game->step;
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
		//draw_floor(data, game, data->map);
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
		
		double sprite_x = game->sprite[0].x - data->map->player->x;
		double sprite_y = game->sprite[0].y - data->map->player->y;
		double inv_det = 1.0 / (game->plane_x * data->map->player->dir_y - data->map->player->dir_x * game->plane_y); //required for correct matrix multiplication
		double transform_x = inv_det * (data->map->player->dir_y * sprite_x - data->map->player->dir_x * sprite_y);
		double transform_y = inv_det * (-game->plane_y * sprite_x + game->plane_x * sprite_y); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spritescreen_x = (int)((RES_X / 2) * (1 + transform_x / transform_y));
		#define uDiv 2
		#define vDiv 2
		#define vMove 200.0
		int vmove_screen = (int)(vMove / transform_y);

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(RES_Y / (transform_y))) / vDiv; //using "transform_y" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawstart_y = -spriteHeight / 2 + RES_Y / 2 + vmove_screen + data->game->head_view + data->game->jumpoffsetresy;
		if(drawstart_y < 0)
			drawstart_y = 0;
		int drawend_y = spriteHeight / 2 + RES_Y / 2 + vmove_screen + data->game->head_view + data->game->jumpoffsetresy;
		if(drawend_y >= RES_Y)
			drawend_y = RES_Y - 1;
		//calculate width of the sprite
		int spriteWidth = abs((int) (RES_Y / (transform_y))) / uDiv; 
		int drawstart_x = -spriteWidth / 2 + spritescreen_x;
		if(drawstart_x < 0)
			drawstart_x = 0;
		int drawend_x = spriteWidth / 2 + spritescreen_x;
		if(drawend_x > RES_X)
			drawend_x = RES_X;
		/* calcul angle sprite player*/
		double dx = data->game->sprite->x - data->map->player->y;
		double dy = data->game->sprite->y - data->map->player->x;
		double angleToSprite = atan2(dx, dy);
		double pa = atan2(data->map->player->dir_y, data->map->player->dir_x);
		double relativeAngle = angleToSprite - pa;
		
		while (relativeAngle < 0)
			relativeAngle += 2*M_PI;
		while (relativeAngle >= 2*M_PI)
			relativeAngle -= 2*M_PI;
		int dirIndex = (int)((relativeAngle + M_PI) / (2*M_PI) * 8) % 8;
		int stripe = drawstart_x;
		
		while (stripe < drawend_x)
		{
			
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spritescreen_x)) * 128 / spriteWidth) / 256;
			texX += floor(data->game->compteur) * 128;
			if(transform_y > 0 && transform_y < zbuffer[stripe])
			{
				int y = drawstart_y;
				while(y < drawend_y) //for every pixel of the current stripe
				{
					int d = (y - data->game->head_view - data->game->jumpoffsetresy - vmove_screen) * 256 - RES_Y * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = (((d  * 128) / spriteHeight) / 256) + (dirIndex * 128);
					unsigned int color = get_pixel(data->game->sprite->img_sprite[0], texX , texY );
					if((color & 0x00FFFFFF) != 0)
						if ((y < 256 && stripe < 256 && is_minimap_status(data, stripe, y) == 0)
							|| (y >= 256 || stripe >= 256))
							pixels_to_image(data, stripe, y, color); //paint pixel if it isn't black, black is the invisible color
					y++;
				}
			}
			stripe++;
		}
		data->game->compteur += 0.2;
		if (data->game->compteur >= 21)
			data->game->compteur = 0;
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

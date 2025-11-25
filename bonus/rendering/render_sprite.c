/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:33:45 by npederen          #+#    #+#             */
/*   Updated: 2025/11/25 03:14:27 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	setup_sprite(t_data *data, t_game *game, t_sprite *sprite)
{
	sprite->sprite_x = sprite[0].x - data->map->player->x;
	sprite->sprite_y = sprite[0].y - data->map->player->y;
	sprite->inv_det = 1.0 / (game->plane_x * data->map->player->dir_y
			- data->map->player->dir_x * game->plane_y); //required for correct matrix multiplication
	sprite->transform_x = sprite->inv_det
		* (data->map->player->dir_y * sprite->sprite_x
			- data->map->player->dir_x * sprite->sprite_y);
	sprite->transform_y = sprite->inv_det * (-game->plane_y
			* sprite->sprite_x + game->plane_x * sprite->sprite_y); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])
	sprite->spritescreen_x = (int)((RES_X / 2)
			* (1 + sprite->transform_x / sprite->transform_y));
	sprite->vmove_screen = (int)(VMOVE / sprite->transform_y);
}

void	calc_sprite(t_game *game, t_sprite *sprite)
{
	//calculate height of the sprite on screen
	sprite->sprite_height = abs((int)(RES_Y / (sprite->transform_y))) / VDIV; //using "transform_y" instead of the real distance prevents fisheye
	//calculate lowest and highest pixel to fill in current stripe
	sprite->drawstart_y = -sprite->sprite_height / 2 + RES_Y / 2
		+ sprite->vmove_screen + game->head_view + game->jumpoffsetresy;
	if (sprite->drawstart_y < 0)
		sprite->drawstart_y = 0;
	sprite->drawend_y = sprite->sprite_height / 2 + RES_Y / 2
		+ sprite->vmove_screen + game->head_view + game->jumpoffsetresy;
	if (sprite->drawend_y >= RES_Y)
		sprite->drawend_y = RES_Y - 1;
	//calculate width of the sprite
	sprite->sprite_width = abs((int)(RES_Y / (sprite->transform_y))) / UDIV;
	sprite->drawstart_x = -sprite->sprite_width / 2 + sprite->spritescreen_x;
	if (sprite->drawstart_x < 0)
		sprite->drawstart_x = 0;
	sprite->drawend_x = sprite->sprite_width / 2 + sprite->spritescreen_x;
	if (sprite->drawend_x > RES_X)
		sprite->drawend_x = RES_X;
}

/* calcul angle sprite player*/
void	calcul_angle_sprite(t_data *data, t_game *game)
{
	game->sprite->pa = atan2(-data->map->player->dir_y, data->map->player->dir_x);
	
	while (game->sprite->pa < 0)
		game->sprite->pa += 2 * M_PI;
	while (game->sprite->pa >= 2 * M_PI)
		game->sprite->pa -= 2 * M_PI;
	game->sprite->dir_index = (int)((game->sprite->pa)
			/ (2 * M_PI) * 8);
	if (game->sprite->dir_index < 0)
		game->sprite->dir_index = 0;
	if (game->sprite->dir_index > 7)
		game->sprite->dir_index = 7;
	printf("%f\n", game->sprite->pa);
	game->sprite->stripe = game->sprite->drawstart_x;
}

void	print_sprite(t_data *data, t_game *game, t_sprite *sprite)
{
	int				y;
	unsigned int	color;

	y = sprite->drawstart_y;
	while (y < sprite->drawend_y) //for every pixel of the current stripe
	{
		sprite->d = (y - game->head_view - game->jumpoffsetresy
				- sprite->vmove_screen) * 256 - RES_Y * 128
			+ sprite->sprite_height * 128; //256 and 128 factors to avoid floats
		sprite->tex_ysprite = (((sprite->d * 128) / sprite->sprite_height)
				/ 256) + (sprite->dir_index * 128);
		color = get_pixel(sprite->img_sprite[0], sprite->tex_xsprite,
				sprite->tex_ysprite);
		if ((color & 0x00FFFFFF) != 0)
			if ((y < 256 && sprite->stripe < 256
					&& is_minimap_status(data, sprite->stripe, y) == 0)
				|| (y >= 256 || sprite->stripe >= 256))
				pixels_to_image(data, sprite->stripe, y, color); //paint pixel if it isn't black, black is the invisible color
		y++;
	}
}

void	render_sprite(t_data *data, t_game *game, t_sprite *sprite, double *buf)
{
	setup_sprite(data, game, sprite);
	calc_sprite(game, sprite);
	calcul_angle_sprite(data, game);
	while (sprite->stripe < sprite->drawend_x)
	{
		sprite->tex_xsprite = (int)(256 * (sprite->stripe
					- (-sprite->sprite_width / 2 + sprite->spritescreen_x))
				* 128 / sprite->sprite_width) / 256;
		sprite->tex_xsprite += floor(game->compteur) * 128;
		if (sprite->transform_y > 0 && sprite->transform_y
			< buf[sprite->stripe])
		{
			print_sprite(data, game, sprite);
		}
		game->sprite->stripe++;
	}
	data->game->compteur += 0.2;
	if (data->game->compteur >= 21)
		data->game->compteur = 0;
}

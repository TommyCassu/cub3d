/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:44:41 by tcassu            #+#    #+#             */
/*   Updated: 2025/11/25 18:35:26 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_raycast_two(t_data *data)
{
	data->game->camera_x = 0.0;
	data->game->plane_x = 0.0;
	data->game->wall_x = 0.0;
	data->game->plane_y = 0.66;
	data->game->head_view = 0;
	data->game->ray_dir_x0 = 0.0;
	data->game->ray_dir_y0 = 0.0;
	data->game->ray_dir_x1 = 0.0;
	data->game->ray_dir_y1 = 0.0;
	data->game->pos_z = 0.0;
	data->game->row_distance = 0.0;
	data->game->floor_x = 0.0;
	data->game->floor_y = 0.0;
	data->game->floor_step_y = 0.0;
	data->game->floor_step_x = 0.0;
	data->game->jumpoffsetresy = (int)(data->map->player->jumpoffset * RES_Y);
	data->game->compteur = 0;
}

void	init_raycast(t_data *data)
{
	data->game = malloc(sizeof(t_game));
	ft_memset(data->game, 0, sizeof(t_game));
	data->game->sprite = malloc(sizeof(t_sprite));
	ft_memset(data->game->sprite, 0, sizeof(t_sprite));
	data->game->sprite[0].x = SPRITE_X;
	data->game->sprite[0].y = SPRITE_Y;
	data->game->sprite->img_sprite[0] = malloc(sizeof(t_img));
	data->game->img_minimap = malloc(sizeof(t_img));
	data->game->img_minimap_contour = malloc(sizeof(t_img));
	init_raycast_two(data);
}

void	setup_text_sprites(t_data *data, t_sprite *sprite)
{
	int	w;
	int	h;

	sprite->img_sprite[0]->ptr = mlx_xpm_file_to_image(data->mlx->ptr,
			"./bonus/textures/sprites/1.xpm", &w, &h);
	sprite->img_sprite[0]->addr = (int *)mlx_get_data_addr(sprite
			->img_sprite[0]->ptr, &sprite->img_sprite[0]->bpp,
			&sprite->img_sprite[0]->line_s, &sprite->img_sprite[0]->endian);
}

void	setup_text_img_presset(t_data *data, t_textdata *t)
{
	t->img[4]->ptr = mlx_xpm_file_to_image(data->mlx->ptr,
			"./bonus/textures/floor.xpm", &t->img[4]->w, &t->img[4]->h);
	t->img[4]->addr = (int *)mlx_get_data_addr(t->img[4]->ptr, &t->img[4]->bpp,
			&t->img[4]->line_s, &t->img[4]->endian);
	t->img[5]->ptr = mlx_xpm_file_to_image(data->mlx->ptr,
			"./bonus/textures/door.xpm", &t->img[5]->w, &t->img[5]->h);
	t->img[5]->addr = (int *)mlx_get_data_addr(t->img[5]->ptr, &t->img[5]->bpp,
			&t->img[5]->line_s, &t->img[5]->endian);
	t->img[6]->ptr = mlx_xpm_file_to_image(data->mlx->ptr,
			"./bonus/textures/floor2.xpm", &t->img[6]->w, &t->img[6]->h);
	t->img[6]->addr = (int *)mlx_get_data_addr(t->img[6]->ptr, &t->img[6]->bpp,
			&t->img[6]->line_s, &t->img[6]->endian);
}

void	setup_text_img(t_data *data, t_textdata *t)
{
	t->img[0]->ptr = mlx_xpm_file_to_image(data->mlx->ptr, t->n, &t->img[0]->w, &t->img[0]->h);
	t->img[0]->addr = (int *)mlx_get_data_addr(t->img[0]->ptr, &t->img[0]->bpp,
			&t->img[0]->line_s, &t->img[0]->endian);
	t->img[1]->ptr = mlx_xpm_file_to_image(data->mlx->ptr, t->s, &t->img[1]->w, &t->img[1]->h);
	t->img[1]->addr = (int *)mlx_get_data_addr(t->img[1]->ptr, &t->img[1]->bpp,
			&t->img[1]->line_s, &t->img[1]->endian);
	t->img[2]->ptr = mlx_xpm_file_to_image(data->mlx->ptr, t->e, &t->img[2]->w, &t->img[2]->h);
	t->img[2]->addr = (int *)mlx_get_data_addr(t->img[2]->ptr, &t->img[2]->bpp,
			&t->img[2]->line_s, &t->img[2]->endian);
	t->img[3]->ptr = mlx_xpm_file_to_image(data->mlx->ptr, t->w, &t->img[3]->w, &t->img[3]->h);
	t->img[3]->addr = (int *)mlx_get_data_addr(t->img[3]->ptr, &t->img[3]->bpp,
			&t->img[3]->line_s, &t->img[3]->endian);
	setup_text_img_presset(data, t);
}

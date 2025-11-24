/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:44:41 by tcassu            #+#    #+#             */
/*   Updated: 2025/11/24 15:34:50 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_raycast(t_data *data)
{
	data->game = malloc(sizeof(t_game));
	ft_memset(data->game, 0, sizeof(t_game));
	data->game->camera_x = 0.0;
	data->game->plane_x = 0.0;
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
	data->game->jumpoffsetresy = ((int)(data->map->player->jumpoffset * RES_Y)
			/ data->game->perp_wall_dist);
}

void	setup_text_img(t_data *data, t_textdata *t)
{
	int	w;
	int	h;

	t->img[0]->ptr = mlx_xpm_file_to_image(data->mlx->ptr, t->n, &w, &h);
	t->img[0]->addr = (int *)mlx_get_data_addr(t->img[0]->ptr, &t->img[0]->bpp,
			&t->img[0]->line_s, &t->img[0]->endian);
	t->img[1]->ptr = mlx_xpm_file_to_image(data->mlx->ptr, t->s, &w, &h);
	t->img[1]->addr = (int *)mlx_get_data_addr(t->img[1]->ptr, &t->img[1]->bpp,
			&t->img[1]->line_s, &t->img[1]->endian);
	t->img[2]->ptr = mlx_xpm_file_to_image(data->mlx->ptr, t->e, &w, &h);
	t->img[2]->addr = (int *)mlx_get_data_addr(t->img[2]->ptr, &t->img[2]->bpp,
			&t->img[2]->line_s, &t->img[2]->endian);
	t->img[3]->ptr = mlx_xpm_file_to_image(data->mlx->ptr, t->w, &w, &h);
	t->img[3]->addr = (int *)mlx_get_data_addr(t->img[3]->ptr, &t->img[3]->bpp,
			&t->img[3]->line_s, &t->img[3]->endian);
}

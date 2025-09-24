/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render_raycast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:56:06 by npederen          #+#    #+#             */
/*   Updated: 2025/09/24 14:58:02 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray(t_data *data, int x)
{
	/* Setup ray */
	data->game->cameraX = 2 * x / (double)RES_X - 1;
	data->game->rayDir_x = data->map->player->dirX + data->game->planeX
		* data->game->cameraX;
	data->game->rayDir_y = data->map->player->dirY + data->game->planeY
		* data->game->cameraX;
	data->game->mapX = (int)data->map->player->x;
	data->game->mapY = (int)data->map->player->y;
	data->game->hit = 0;
	/* calcul length of ray */
	if (data->game->rayDir_x == 0)
		data->game->deltaDistX = 1e30;
	else
		data->game->deltaDistX = fabs(1 / data->game->rayDir_x);
	if (data->game->rayDir_y == 0)
		data->game->deltaDistY = 1e30;
	else
		data->game->deltaDistY = fabs(1 / data->game->rayDir_y);
}

void	setup_angle_rayon(t_data *data)
{
	/* Algo DDA ( Setup angle rayon ) */
	if (data->game->rayDir_x < 0)
	{
		data->game->stepX = -1;
		data->game->sideDistX = (data->map->player->x - data->game->mapX)
			* data->game->deltaDistX;
	}
	else
	{
		data->game->stepX = 1;
		data->game->sideDistX = (data->game->mapX + 1.0 - data->map->player->x)
			* data->game->deltaDistX;
	}
	if (data->game->rayDir_y < 0)
	{
		data->game->stepY = -1;
		data->game->sideDistY = (data->map->player->y - data->game->mapY)
			* data->game->deltaDistY;
	}
	else
	{
		data->game->stepY = 1;
		data->game->sideDistY = (data->game->mapY + 1.0 - data->map->player->y)
			* data->game->deltaDistY;
	}
}

void	dda_loop(t_data *data)
{
	/* ALgo DDA Loop */
	while (data->game->hit == 0)
	{
		if (data->game->sideDistX < data->game->sideDistY)
		{
			data->game->sideDistX += data->game->deltaDistX;
			data->game->mapX += data->game->stepX;
			data->game->side = 0;
		}
		else
		{
			data->game->sideDistY += data->game->deltaDistY;
			data->game->mapY += data->game->stepY;
			data->game->side = 1;
		}
		if (data->map->map_tab[data->game->mapX][data->game->mapY] == '1')
			data->game->hit = 1;
	}
}
void	manage_draw_limits(t_data *data)
{
	/* Calculate the distance of the rayon from the cam position in the cam direction*/
	if (data->game->side == 0)
		data->game->perpWallDist = data->game->sideDistX
			- data->game->deltaDistX;
	else
		data->game->perpWallDist = data->game->sideDistY
			- data->game->deltaDistY;
	/* Calcul height of line to draw colone wall */
	data->game->lineHeight = (RES_Y / data->game->perpWallDist);
	data->game->drawStart = -data->game->lineHeight / 2
		+ RES_Y / 2 + data->game->headView;
	data->game->drawEnd = data->game->lineHeight / 2
		+ RES_Y / 2 + data->game->headView;
	/*apply jump offset*/
	data->game->drawStart += (int)(data->map->player->jumpoffset * RES_Y);
	data->game->drawEnd += (int)(data->map->player->jumpoffset * RES_Y);
	if (data->game->drawStart < 0)
		data->game->drawStart = 0;
}

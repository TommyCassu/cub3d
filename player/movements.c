/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:29:51 by npederen          #+#    #+#             */
/*   Updated: 2025/09/24 14:46:37 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	go_forward(t_data *data, t_player *player)
{
	double	msdirx;
	double	msdiry;

	msdirx = data->map->player->dirX * data->game->moveSpeed;
	msdiry = data->map->player->dirY * data->game->moveSpeed;
	if ((int)(player->x + msdirx) < 0 || (int)(player->x + msdirx)
		>= data->map->height_map || (int)(player->y + msdiry) < 0
		|| (int)(player->y + msdiry) >= data->map->width_map)
		return (1);
	if (data->map->map_tab[(int)(player->x + msdirx)][(int)player->y] != '1')
		player->x += msdirx;
	if (data->map->map_tab[(int)player->x][(int)(player->y + msdiry)] != '1')
		player->y += msdiry;
	return (0);
}

int	go_backward(t_data *data, t_player *player)
{
	double	msdirx;
	double	msdiry;

	msdirx = data->map->player->dirX * data->game->moveSpeed;
	msdiry = data->map->player->dirY * data->game->moveSpeed;
	if ((int)(player->x - msdirx) < 0 || (int)(player->x - msdirx)
		>= data->map->height_map || (int)(player->y - msdiry) < 0
		|| (int)(player->y - msdiry) >= data->map->width_map)
		return (1);
	if (data->map->map_tab[(int)(player->x - msdirx)][(int)player->y] != '1')
		player->x -= msdirx;
	if (data->map->map_tab[(int)player->x][(int)(player->y - msdiry)] != '1')
		player->y -= msdiry;
	return (0);
}

int	go_right(t_data *data, t_player *player)
{
	double	msplany;
	double	msplanx;

	msplany = data->game->planeY * data->game->moveSpeed;
	msplanx = data->game->planeX * data->game->moveSpeed;
	if ((int)(player->x + msplanx) < 0 || (int)(player->x + msplanx)
		>= data->map->height_map || (int)(player->y + msplany) < 0
		|| (int)(player->y + msplany) >= data->map->width_map)
		return (1);
	if (data->map->map_tab[(int)(player->x + msplanx)][(int)player->y] != '1')
		player->x += msplanx;
	if (data->map->map_tab[(int)player->x][(int)(player->y + msplany)] != '1')
		player->y += msplany;
	return (0);
}

int	go_left(t_data *data, t_player *player)
{
	double	msplany;
	double	msplanx;

	msplany = data->game->planeY * data->game->moveSpeed;
	msplanx = data->game->planeX * data->game->moveSpeed;
	if ((int)(player->x - msplanx) < 0 || (int)(player->x - msplanx)
		>= data->map->height_map || (int)(player->y - msplany) < 0
		|| (int)(player->y - msplany) >= data->map->width_map)
		return (1);
	if (data->map->map_tab[(int)(player->x - msplanx)][(int)player->y] != '1')
		player->x -= msplanx;
	if (data->map->map_tab[(int)player->x][(int)(player->y - msplany)] != '1')
		player->y -= msplany;
	return (0);
}

void	move_head(t_game *game, t_player *player)
{
	if (game->keyTab[key_Jump] == 1 && player->isjumping == 0)
	{
		player->isjumping = 1;
		player->jumpspeed = 0.02;
	}
	if (game->keyTab[key_Up] == 1)
		if (game->headView < 100)
			game->headView += 4;
	if (game->keyTab[key_Down] == 1)
		if (game->headView > -100)
			game->headView -= 4;
}

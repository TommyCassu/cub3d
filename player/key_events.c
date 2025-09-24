/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:40:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/24 14:46:03 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int key, t_data *data)
{
	if (key == XK_a || key == XK_q)
		data->game->keyTab[key_A] = 1;
	if (key == XK_d)
		data->game->keyTab[key_D] = 1;
	if (key == XK_w || key == XK_z)
		data->game->keyTab[key_W] = 1;
	if (key == XK_s)
		data->game->keyTab[key_S] = 1;
	if (key == XK_Up)
		data->game->keyTab[key_Up] = 1;
	if (key == XK_Down)
		data->game->keyTab[key_Down] = 1;
	if (key == XK_Right)
		data->game->keyTab[key_Right] = 1;
	if (key == XK_Left)
		data->game->keyTab[key_Left] = 1;
	if (key == XK_space)
		data->game->keyTab[key_Jump] = 1;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == XK_a || key == XK_q)
		data->game->keyTab[key_A] = 0;
	if (key == XK_d)
		data->game->keyTab[key_D] = 0;
	if (key == XK_w || key == XK_z)
		data->game->keyTab[key_W] = 0;
	if (key == XK_s)
		data->game->keyTab[key_S] = 0;
	if (key == XK_Up)
		data->game->keyTab[key_Up] = 0;
	if (key == XK_Down)
		data->game->keyTab[key_Down] = 0;
	if (key == XK_Right)
		data->game->keyTab[key_Right] = 0;
	if (key == XK_Left)
		data->game->keyTab[key_Left] = 0;
	if (key == XK_space)
		data->game->keyTab[key_Jump] = 0;
	return (0);
}

void	turn_right(t_game *game, t_player *player)
{
	game->old_dir_x = player->dirX;
	player->dirX = player->dirX * cos(-game->rotSpeed)
		- player->dirY * sin(-game->rotSpeed);
	player->dirY = game->old_dir_x * sin(-game->rotSpeed)
		+ player->dirY * cos(-game->rotSpeed);
	game->old_plane_x = game->planeX;
	game->planeX = game->planeX * cos(-game->rotSpeed)
		- game->planeY * sin(-game->rotSpeed);
	game->planeY = game->old_plane_x * sin(-game->rotSpeed)
		+ game->planeY * cos(-game->rotSpeed);
}

void	turn_left(t_game *game, t_player *player)
{
	game->old_dir_x = player->dirX;
	player->dirX = player->dirX * cos(game->rotSpeed)
		- player->dirY * sin(game->rotSpeed);
	player->dirY = game->old_dir_x * sin(game->rotSpeed)
		+ player->dirY * cos(game->rotSpeed);
	game->old_plane_x = game->planeX;
	game->planeX = game->planeX * cos(game->rotSpeed)
		- game->planeY * sin(game->rotSpeed);
	game->planeY = game->old_plane_x * sin(game->rotSpeed)
		+ game->planeY * cos(game->rotSpeed);
}

int	key_handler(t_data *data, t_game *game, t_player *player)
{
	if ((int)player->y < 0 || (int)player->y >= data->map->width_map
		|| (int)player->x >= data->map->height_map || (int)player->x < 0)
		return (1);
	if (game->keyTab[key_W] == 1)
		if (go_forward(data, player))
			return (1);
	if (game->keyTab[key_S] == 1)
		if (go_backward(data, player))
			return (1);
	if (game->keyTab[key_D] == 1)
		if (go_right(data, player))
			return (1);
	if (game->keyTab[key_A] == 1)
		if (go_left(data, player))
			return (1);
	if (game->keyTab[key_Right] == 1)
		turn_right(game, player);
	if (game->keyTab[key_Left] == 1)
		turn_left(game, player);
	move_head(game, player);
	return (0);
}

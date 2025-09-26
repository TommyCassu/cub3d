/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:40:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/27 01:06:32 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int key, t_data *data)
{
	if (key == XK_a || key == XK_q)
		data->game->key_tab[KEY_A] = 1;
	if (key == XK_d)
		data->game->key_tab[KEY_D] = 1;
	if (key == XK_w || key == XK_z)
		data->game->key_tab[KEY_W] = 1;
	if (key == XK_s)
		data->game->key_tab[KEY_S] = 1;
	if (key == XK_Right)
		data->game->key_tab[KEY_RIGHT] = 1;
	if (key == XK_Left)
		data->game->key_tab[KEY_LEFT] = 1;
	if (key == XK_space)
		data->game->key_tab[KEY_JUMP] = 1;
	if (key == XK_Escape)
		ft_exit(data);
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == XK_a || key == XK_q)
		data->game->key_tab[KEY_A] = 0;
	if (key == XK_d)
		data->game->key_tab[KEY_D] = 0;
	if (key == XK_w || key == XK_z)
		data->game->key_tab[KEY_W] = 0;
	if (key == XK_s)
		data->game->key_tab[KEY_S] = 0;
	if (key == XK_Right)
		data->game->key_tab[KEY_RIGHT] = 0;
	if (key == XK_Left)
		data->game->key_tab[KEY_LEFT] = 0;
	if (key == XK_space)
		data->game->key_tab[KEY_JUMP] = 0;
	return (0);
}

void	turn_right(t_game *game, t_player *player)
{
	game->old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(-game->rotspeed) - player->dir_y
		* sin(-game->rotspeed);
	player->dir_y = game->old_dir_x * sin(-game->rotspeed) + player->dir_y
		* cos(-game->rotspeed);
	game->old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(-game->rotspeed) - game->plane_y
		* sin(-game->rotspeed);
	game->plane_y = game->old_plane_x * sin(-game->rotspeed) + game->plane_y
		* cos(-game->rotspeed);
}

void	turn_left(t_game *game, t_player *player)
{
	game->old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(game->rotspeed) - player->dir_y
		* sin(game->rotspeed);
	player->dir_y = game->old_dir_x * sin(game->rotspeed) + player->dir_y
		* cos(game->rotspeed);
	game->old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(game->rotspeed) - game->plane_y
		* sin(game->rotspeed);
	game->plane_y = game->old_plane_x * sin(game->rotspeed) + game->plane_y
		* cos(game->rotspeed);
}

int	key_handler(t_data *data, t_game *game, t_player *player)
{
	if ((int)player->y < 0 || (int)player->y >= data->map->width_map
		|| (int)player->x >= data->map->height_map || (int)player->x < 0)
		return (1);
	if (game->key_tab[KEY_W] == 1)
		if (go_forward(data, player))
			return (1);
	if (game->key_tab[KEY_S] == 1)
		if (go_backward(data, player))
			return (1);
	if (game->key_tab[KEY_D] == 1)
		if (go_right(data, player))
			return (1);
	if (game->key_tab[KEY_A] == 1)
		if (go_left(data, player))
			return (1);
	if (game->key_tab[KEY_RIGHT] == 1)
		turn_right(game, player);
	if (game->key_tab[KEY_LEFT] == 1)
		turn_left(game, player);
	return (0);
}

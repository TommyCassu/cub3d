/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:40:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/23 23:06:54 by npederen         ###   ########.fr       */
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

int	key_handler(t_data *data, t_game *game, t_player *player, char **map_tab)
{
	double	old_dir_x;
	double	old_plane_x;
	double	msdirx = data->map->player->dirX * game->moveSpeed;
	double	msdiry = data->map->player->dirY * game->moveSpeed;
	double	msplany = game->planeY * game->moveSpeed;
	double	msplanx = game->planeX * game->moveSpeed;
	
	if ((int)player->y < 0 || (int)player->y >= data->map->width_map || (int)player->x >= data->map->height_map || (int)player->x < 0)
		return (1);
	if (game->keyTab[key_W] == 1)
	{
		if ((int)(player->x + msdirx) < 0 || (int)(player->x + msdirx) >= data->map->height_map || (int)(player->y + msdiry) < 0 || (int)(player->y + msdiry) >= data->map->width_map)
			return (1);
		if (map_tab[(int)(player->x + msdirx)][(int)player->y] != '1')
			player->x += msdirx;
		if (map_tab[(int)player->x][(int)(player->y + msdiry)] != '1')
			player->y += msdiry;
	}
	if (game->keyTab[key_S] == 1)
	{
		if ((int)(player->x - msdirx) < 0 || (int)(player->x - msdirx) >= data->map->height_map || (int)(player->y - msdiry) < 0 || (int)(player->y - msdiry) >= data->map->width_map)
			return (1);
		if (map_tab[(int)(player->x - msdirx)][(int)player->y] != '1')
			player->x -= msdirx;
		if (map_tab[(int)player->x][(int)(player->y - msdiry)] != '1')
			player->y -= msdiry;
	}
	if (game->keyTab[key_D] == 1)
	{
		if ((int)(player->x + msplanx) < 0 || (int)(player->x + msplanx) >= data->map->height_map || (int)(player->y + msplany) < 0 || (int)(player->y + msplany) >= data->map->width_map)
			return (1);
		if (map_tab[(int)(player->x + msplanx)][(int)player->y] != '1')
			player->x += msplanx;
		if (map_tab[(int)player->x][(int)(player->y + msplany)] != '1')
			player->y += msplany;
	}
	if (game->keyTab[key_A] == 1)
	{
		if ((int)(player->x - msplanx) < 0 || (int)(player->x - msplanx) >= data->map->height_map || (int)(player->y - msplany) < 0 || (int)(player->y - msplany) >= data->map->width_map)
			return (1);
		if (map_tab[(int)(player->x - msplanx)][(int)player->y] != '1')
			player->x -= msplanx;
		if (map_tab[(int)player->x][(int)(player->y - msplany)] != '1')
			player->y -= msplany;
	}
	if (game->keyTab[key_Right] == 1)
	{
		old_dir_x = player->dirX;
		player->dirX = player->dirX * cos(-game->rotSpeed) - player->dirY * sin(-game->rotSpeed);
		player->dirY = old_dir_x * sin(-game->rotSpeed) + player->dirY * cos(-game->rotSpeed);
		old_plane_x = game->planeX;
		game->planeX = game->planeX * cos(-game->rotSpeed) - game->planeY * sin(-game->rotSpeed);
		game->planeY = old_plane_x * sin(-game->rotSpeed) + game->planeY * cos(-game->rotSpeed);
	}
	if (game->keyTab[key_Left] == 1)
	{
		old_dir_x = player->dirX;
		player->dirX = player->dirX * cos(game->rotSpeed) - player->dirY * sin(game->rotSpeed);
		player->dirY = old_dir_x * sin(game->rotSpeed) + player->dirY * cos(game->rotSpeed);
		old_plane_x = game->planeX;
		game->planeX = game->planeX * cos(game->rotSpeed) - game->planeY * sin(game->rotSpeed);
		game->planeY = old_plane_x * sin(game->rotSpeed) + game->planeY * cos(game->rotSpeed);
	}
	if (game->keyTab[key_Jump] == 1 && player->isjumping == 0)
	{
		player->isjumping = 1;
		player->jumpspeed = 0.02;
	}
	if (game->keyTab[key_Up] == 1)
	{
		if (game->headView < 100)
			game->headView += 4;
	}
	if (game->keyTab[key_Down] == 1)
	{
		if (game->headView > -100)
			game->headView -= 4;
	}
	return (0);
}

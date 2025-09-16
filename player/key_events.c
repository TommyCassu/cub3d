/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:40:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/16 16:48:12 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


int     key_press(int key, t_data *data)
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

int     key_release(int key, t_data *data)
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

int    key_handler(t_data *data)
{
	double oldDirX;
	double oldPlaneX;

	if ((int)data->map->player->y < 0 || (int)data->map->player->y >= data->map->height_map || (int)data->map->player->x >= data->map->width_map || (int)data->map->player->x < 0)
			return (1);
	if (data->game->keyTab[key_W] == 1)
	{
		if ((int)(data->map->player->x + data->map->player->dirX * data->game->moveSpeed) < 0 || (int)(data->map->player->x + data->map->player->dirX * data->game->moveSpeed) >= data->map->width_map || (int)(data->map->player->y + data->map->player->dirY * data->game->moveSpeed) < 0 || (int)(data->map->player->y + data->map->player->dirY * data->game->moveSpeed) >= data->map->height_map)
			return (1);
		if (data->map->map_tab[(int)(data->map->player->x + data->map->player->dirX * data->game->moveSpeed)][(int)data->map->player->y] != '1')
			data->map->player->x += data->map->player->dirX * data->game->moveSpeed;
		if (data->map->map_tab[(int)data->map->player->x][(int)(data->map->player->y + data->map->player->dirY * data->game->moveSpeed)] != '1')
			data->map->player->y += data->map->player->dirY * data->game->moveSpeed;
	}
	if (data->game->keyTab[key_S] == 1)
	{
		if ((int)(data->map->player->x - data->map->player->dirX * data->game->moveSpeed) < 0 || (int)(data->map->player->x - data->map->player->dirX * data->game->moveSpeed) >= data->map->width_map || (int)(data->map->player->y - data->map->player->dirY * data->game->moveSpeed) < 0 || (int)(data->map->player->y - data->map->player->dirY * data->game->moveSpeed) >= data->map->height_map)
			return (1);
		if (data->map->map_tab[(int)(data->map->player->x - data->map->player->dirX * data->game->moveSpeed)][(int)data->map->player->y] != '1')
			data->map->player->x -= data->map->player->dirX * data->game->moveSpeed;
		if (data->map->map_tab[(int)data->map->player->x][(int)(data->map->player->y - data->map->player->dirY * data->game->moveSpeed)] != '1')
			data->map->player->y -= data->map->player->dirY * data->game->moveSpeed;
	}
	if (data->game->keyTab[key_D] == 1)
	{
		if ((int)(data->map->player->x + data->game->planeX * data->game->moveSpeed) < 0 || (int)(data->map->player->x + data->game->planeX * data->game->moveSpeed) >= data->map->width_map || (int)(data->map->player->y + data->game->planeY * data->game->moveSpeed) < 0 || (int)(data->map->player->y + data->game->planeY * data->game->moveSpeed) >= data->map->height_map)
			return (1);
		if (data->map->map_tab[(int)(data->map->player->x + data->game->planeX * data->game->moveSpeed)][(int)data->map->player->y] != '1')
			data->map->player->x += data->game->planeX * data->game->moveSpeed;
		if (data->map->map_tab[(int)data->map->player->x][(int)(data->map->player->y + data->game->planeY * data->game->moveSpeed)] != '1')
			data->map->player->y += data->game->planeY * data->game->moveSpeed;
	}
	if (data->game->keyTab[key_A] == 1)
	{
		if ((int)(data->map->player->x - data->game->planeX * data->game->moveSpeed) < 0 || (int)(data->map->player->x - data->game->planeX * data->game->moveSpeed) >= data->map->width_map || (int)(data->map->player->y - data->game->planeY * data->game->moveSpeed) < 0 || (int)(data->map->player->y - data->game->planeY * data->game->moveSpeed) >= data->map->height_map)
			return (1);
		if (data->map->map_tab[(int)(data->map->player->x - data->game->planeX * data->game->moveSpeed)][(int)data->map->player->y] != '1')
			data->map->player->x -= data->game->planeX * data->game->moveSpeed;
		if (data->map->map_tab[(int)data->map->player->x][(int)(data->map->player->y - data->game->planeY * data->game->moveSpeed)] != '1')
			data->map->player->y -= data->game->planeY * data->game->moveSpeed;
	}
	if (data->game->keyTab[key_Right] == 1)
	{
		oldDirX = data->map->player->dirX;
		data->map->player->dirX = data->map->player->dirX * cos(-data->game->rotSpeed) - data->map->player->dirY * sin(-data->game->rotSpeed);
		data->map->player->dirY = oldDirX * sin(-data->game->rotSpeed) + data->map->player->dirY * cos(-data->game->rotSpeed);
		oldPlaneX = data->game->planeX;
		data->game->planeX = data->game->planeX * cos(-data->game->rotSpeed) - data->game->planeY * sin(-data->game->rotSpeed);
		data->game->planeY = oldPlaneX * sin(-data->game->rotSpeed) + data->game->planeY * cos(-data->game->rotSpeed);
	}
	if (data->game->keyTab[key_Left] == 1)
	{
		oldDirX = data->map->player->dirX;
		data->map->player->dirX = data->map->player->dirX * cos(data->game->rotSpeed) - data->map->player->dirY * sin(data->game->rotSpeed);
		data->map->player->dirY = oldDirX * sin(data->game->rotSpeed) + data->map->player->dirY * cos(data->game->rotSpeed);
		oldPlaneX = data->game->planeX;
		data->game->planeX = data->game->planeX * cos(data->game->rotSpeed) - data->game->planeY * sin(data->game->rotSpeed);
		data->game->planeY = oldPlaneX * sin(data->game->rotSpeed) + data->game->planeY * cos(data->game->rotSpeed);
	}
	if (data->game->keyTab[key_Jump] == 1 && data->map->player->isjumping == 0)
	{
		data->map->player->isjumping = 1;
		data->map->player->jumpspeed = 0.02;
	}
  if (data->game->keyTab[key_Up] == 1)
  {
    if (data->game->headView < 100)
      data->game->headView +=4;
  }
  if (data->game->keyTab[key_Down] == 1)
  {
      if (data->game->headView > -100)
        data->game->headView -=4;
  }
  return (0);
}
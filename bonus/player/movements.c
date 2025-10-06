/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:29:51 by npederen          #+#    #+#             */
/*   Updated: 2025/10/06 04:22:32 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	go_forward(t_data *data, t_player *player)
{
	double	msdirx;
	double	msdiry;

	msdirx = data->map->player->dir_x * data->game->movespeed;
	msdiry = data->map->player->dir_y * data->game->movespeed;
	if ((int)(player->x + msdirx) < 0 || (int)(player->x + msdirx)
		>= data->map->height_map || (int)(player->y + msdiry) < 0
			|| (int)(player->y + msdiry) >= data->map->width_map)
		return (1);
	if ((data->map->map_tab[(int)(player->x + msdirx)][(int)player->y] == 'D' && data->game->door <= 0))
		return (1);
	if ((data->map->map_tab[(int)player->x][(int)(player->y + msdiry)] == 'D' && data->game->door <= 0))
		return (1);	
	if (data->map->map_tab[(int)(player->x + msdirx)][(int)player->y] != '1' )
		player->x += msdirx;
	if (data->map->map_tab[(int)player->x][(int)(player->y + msdiry)] != '1')
		player->y += msdiry;
	return (0);
}

int	go_backward(t_data *data, t_player *player)
{
	double	msdirx;
	double	msdiry;

	msdirx = data->map->player->dir_x * data->game->movespeed;
	msdiry = data->map->player->dir_y * data->game->movespeed;
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

	msplany = data->game->plane_y * data->game->movespeed;
	msplanx = data->game->plane_x * data->game->movespeed;
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

	msplany = data->game->plane_y * data->game->movespeed;
	msplanx = data->game->plane_x * data->game->movespeed;
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
	if (game->key_tab[KEY_JUMP] == 1 && player->isjumping == 0)
	{
		player->isjumping = 1;
		player->jumpspeed = 0.02;
	}
	if (game->key_tab[KEY_UP] == 1)
		if (game->head_view < 100)
			game->head_view += 4;
	if (game->key_tab[KEY_DOWN] == 1)
		if (game->head_view > -100)
			game->head_view -= 4;
}

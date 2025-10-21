/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:03:27 by tcassu            #+#    #+#             */
/*   Updated: 2025/10/08 22:32:11 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handler_render(t_data *data)
{
	mooving_door(data);
	render_raycast(data, data->game);
	key_handler(data, data->game, data->map->player);
	draw_mini_map(data);
	return (0);
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
	move_head(game, player);
	return (0);
}

int	mouse_handler(int new_xpos, int new_ypos, void *param)
{
	t_data		*data;
	static int	old_xpos = RES_X / 2;
	static int	old_ypos = RES_Y / 2;

	data = (t_data *)param;
	mlx_mouse_get_pos(data->mlx->ptr, data->mlx->win, &new_xpos, &new_ypos);
	if (new_xpos < old_xpos)
	{
		turn_left(data->game, data->map->player);
		old_xpos = new_xpos;
		old_ypos = new_ypos;
	}
	if (new_xpos > old_xpos)
	{
		turn_right(data->game, data->map->player);
		old_xpos = new_xpos;
		old_ypos = new_ypos;
	}
	if (old_xpos > 1900 || old_xpos < 15 || old_ypos < 15 || old_ypos > 1000)
		mlx_mouse_move(data->mlx->ptr, data->mlx->win, RES_X / 2, RES_Y / 2);
	return (0);
}

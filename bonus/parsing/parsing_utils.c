/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:50:06 by npederen          #+#    #+#             */
/*   Updated: 2025/11/25 19:46:52 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_valid(char c)
{
	return (c == '0' || c == '1' || c == '2'
		|| c == '3' || c == 'D' || is_player(c));
}

void	set_plane_dir(t_game *game, t_player *player)
{
	if (player->dir_x == -1 && player->dir_y == 0)
	{
		game->plane_x = 0.0;
		game->plane_y = 0.66;
	}
	else if (player->dir_x == 0 && player->dir_y == 1)
	{
		game->plane_x = 0.66;
		game->plane_y = 0.0;
	}
	else if (player->dir_x == 1 && player->dir_y == 0)
	{
		game->plane_x = 0.0;
		game->plane_y = -0.66;
	}
	else
	{
		game->plane_x = -0.66;
		game->plane_y = 0.0;
	}
}

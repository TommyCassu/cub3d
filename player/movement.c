/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:02:41 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/09 16:03:50 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	update_player_img(t_app *game, int nx, int ny, char key)
{
	int	x;
	int	y;

	x = game->coor_x * 32;
	y = game->coor_y * 32;
	if (game->map[game->coor_y][game->coor_x] == 'C' \
	|| game->map[game->coor_y][game->coor_x] == 'I')
		mlx_put_image_to_window(game->mlx, game->win, game->img_island, x, y);
	else
		mlx_put_image_to_window(game->mlx, game->win, \
		game->img_background, x, y);
	update_boat_img(game, nx, ny, key);
	game->moves_counter++;
	ft_putstr_fd("moves_counter: ", 1);
	ft_putnbr_fd(game->moves_counter, 1);
	write(1, "\n", 1);
}

void	move_player(t_app *game, char key, int x, int y)
{
	if (key == 'W')
	{
		update_player_img(game, x, (y - 1), 'W');
		update_player_xy(game, x, (y - 1));
	}
	if (key == 'A')
	{
		update_player_img(game, (x - 1), y, 'A');
		update_player_xy(game, (x - 1), y);
	}
	if (key == 'S')
	{
		update_player_img(game, x, (y + 1), 'S');
		update_player_xy(game, x, (y + 1));
	}
	if (key == 'D')
	{
		update_player_img(game, (x + 1), y, 'D');
		update_player_xy(game, (x + 1), y);
	}
	if (game->map[y][x] == 'C' || game->map[y][x] == 'I')
		game->map[y][x] = 'I';
	else
		game->map[y][x] = '0';
}
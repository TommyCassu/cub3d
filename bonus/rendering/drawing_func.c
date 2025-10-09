/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:39:21 by tcassu            #+#    #+#             */
/*   Updated: 2025/10/09 03:03:36 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	pixels_to_image(t_data *data, int x, int y, int pixcolor)
{
	int	pi;

	if (x < 0 || x >= RES_X || y < 0 || y >= RES_Y)
		return ;
	pi = y * (data->mlx->img->line_s / 4) + x;
	((int *)data->mlx->img->addr)[pi] = pixcolor;
}

void	draw_ceiling(t_data *data, t_game *game, int x, int color)
{
	int	i;

	i = 0;
	while (i < game->draw_start)
	{
		if ((i < 256 && x < 256 && is_minimap_status(data, x, i) == 0)
			|| (i >= 256 || x >= 256))
			pixels_to_image(data, x, i, color);
		i++;
	}
}

void	init_floor_params(t_data *data, t_game *game, int y)
{
	game->jumpoffsetresy = (int)(data->map->player->jumpoffset * RES_Y);
	game->ray_dir_x0 = data->map->player->dir_x - game->plane_x;
	game->ray_dir_y0 = data->map->player->dir_y - game->plane_y;
	game->ray_dir_x1 = data->map->player->dir_x + game->plane_x;
	game->ray_dir_y1 = data->map->player->dir_y + game->plane_y;
	game->p = (y - (RES_Y / 2)) + game->jumpoffsetresy + game->head_view;
	game->pos_z = 0.5 * RES_Y;
	game->row_distance = game->pos_z / game->p;
	game->floor_step_x = game->row_distance * (game->ray_dir_x1
			- game->ray_dir_x0) / RES_X;
	game->floor_step_y = game->row_distance * (game->ray_dir_y1
			- game->ray_dir_y0) / RES_X;
	game->floor_x = data->map->player->x + game->row_distance
		* game->ray_dir_x0;
	game->floor_y = data->map->player->y + game->row_distance
		* game->ray_dir_y0;
}

void	draw_floor(t_data *data, t_game *game, t_map *map, int x)
{
	double	floorXWall;
	double	floorYWall;
	double distWall, distPlayer, currentDist;
	
	if(game->side == 0 && data->game->raydir_x > 0)
      {
        floorXWall = data->game->map_x;
        floorYWall = data->game->map_y + data->game->wall_x;
      }
      else if(game->side == 0 && data->game->raydir_x < 0)
      {
        floorXWall = data->game->map_x + 1.0;
        floorYWall = data->game->map_y + data->game->wall_x;
      }
      else if(game->side == 1 && data->game->raydir_y > 0)
      {
        floorXWall = data->game->map_x + data->game->wall_x;
        floorYWall = data->game->map_y;
      }
      else
      {
        floorXWall = data->game->map_x + data->game->wall_x;
        floorYWall = data->game->map_y + 1.0;
      }

	  distWall = game->perp_wall_dist;
      distPlayer = 0.0;
	
	  if(game->draw_end < 0)
	  	game->draw_end = RES_Y;

      for(int y = game->draw_end + 1; y < RES_Y; y++)
      {
        currentDist = RES_Y / (2.0 * y - RES_Y);

        double weight = (currentDist - distPlayer) / (distWall  - distPlayer);

        double currentFloorX = weight * floorXWall + (1.0 - weight) * data->map->player->x;
        double currentFloorY = weight * floorYWall + (1.0 - weight) * data->map->player->y;

        int floorTexX, floorTexY;
        floorTexX = (int)(currentFloorX * TEXT_SIZE) & (TEXT_SIZE - 1);
        floorTexY = (int)(currentFloorY * TEXT_SIZE) & (TEXT_SIZE - 1);
		if (map->map_tab[(int)currentFloorX][(int)currentFloorY] && (map->map_tab[(int)currentFloorX][(int)currentFloorY] == '2' || map->map_tab[(int)currentFloorX][(int)currentFloorY] == 'D'))
			game->color = get_pixel(map->textdata->img[6],floorTexX, floorTexY);
		else
			game->color = get_pixel(map->textdata->img[4],floorTexX, floorTexY);	
		if ((y < 256 && x < 256 && is_minimap_status(data, x, y) == 0)
				|| (y >= 256 || x >= 256))
				pixels_to_image(data, x, y, game->color);
	}
}

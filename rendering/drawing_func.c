/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:39:21 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/23 16:35:54 by tcassu           ###   ########.fr       */
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
	while (i < game->drawStart)
	{
		if ((i < 256 && x < 256 && is_minimap_status(data, x, i) == 0) || (i >= 256 || x >= 256))
			pixels_to_image(data, x, i, color);
		i++;
	}
	
}
void    draw_floor(t_data *data, t_game *game)
{
	double rayDirX0;
	double rayDirY0;
	double rayDirX1;
	double rayDirY1;
	double posZ;
	int p;
	int y;
	int color;
	float rowDistance;
		
	y = (RES_Y / 2) + (int)(data->map->player->jumpoffset * RES_Y) + game->headView;
	while (y < RES_Y)
	{
		rayDirX0 = data->map->player->dirX - game->planeX;
		rayDirY0 = data->map->player->dirY - game->planeY;
		rayDirX1 = data->map->player->dirX + game->planeX;
		rayDirY1 = data->map->player->dirY + game->planeY;

		p = y - RES_Y / 2 - (int)(data->map->player->jumpoffset * RES_Y) - game->headView ;
		
		posZ = 0.5 * RES_Y;
		rowDistance = posZ / p;

		double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / RES_X;
		double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / RES_X;

	  // real world coordinates of the leftmost column. This will be updated as we step to the right.
		double floorX = data->map->player->x + rowDistance * rayDirX0 ;
		double floorY = data->map->player->y + rowDistance * rayDirY0 ;

		for(int x = 0; x < RES_X; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx = (int)(TEXT_SIZE * (floorX - cellX)) & (TEXT_SIZE - 1);
			int ty = (int)(TEXT_SIZE * (floorY - cellY)) & (TEXT_SIZE - 1);

			floorX += floorStepX;
			floorY += floorStepY;
			
			color = get_pixel(data->map->textdata->img[4], tx, ty);
			if ((y < 256 && x < 256 && is_minimap_status(data, x, y) == 0 ) || (y >= 256 || x >= 256))
					pixels_to_image(data, x, y, color);
		}
		y++;
	}

}

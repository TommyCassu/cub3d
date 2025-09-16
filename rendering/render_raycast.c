/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:48:32 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/15 15:34:38 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    render_raycast(t_data *data, t_game *game, t_player *player)
{
    int x;
    double deltaDistX;
    double deltaDistY;
    int color;
    double  frameTime;
    double wallX;
    int texX;
    int texY;
    double step;
    double texPos;
    int i;
    int textNum;
    
    color = 0xeeeeee;
    
    while (1)
    {
        x = 0;
        while (x < RES_X)
        {
            /* Setup ray */
            game->cameraX = 2 * x / (double)RES_X - 1;
            game->rayDir_x = player->dirX + game->planeX * game->cameraX;
            game->rayDir_y = player->dirY + game->planeY * game->cameraX;
    
            game->mapX = (int)player->x;
            game->mapY = (int)player->y;
            game->hit = 0;
            
            /* calcul length of ray */
            if (game->rayDir_x == 0)
                deltaDistX = 1e30;
            else
                deltaDistX = fabs(1 / game->rayDir_x);
            
            if ( game->rayDir_y == 0)
                deltaDistY = 1e30;
            else
                deltaDistY = fabs(1 / game->rayDir_y);
            
            /* Algo DDA ( Setup angle rayon ) */
            if (game->rayDir_x < 0)
            {
                game->stepX = -1;
                game->sideDistX = (player->x - game->mapX) * deltaDistX;
            }
            else
            {
                game->stepX = 1;
                game->sideDistX = (game->mapX + 1.0 - player->x) * deltaDistX;
            }
            if (game->rayDir_y < 0)
            {
                game->stepY = -1;
                game->sideDistY = (player->y - game->mapY) * deltaDistY;
            }
            else
            {
                game->stepY = 1;
                game->sideDistY = (game->mapY + 1.0 - player->y) * deltaDistY;
            }
    
            /* ALgo DDA Loop */
            while (game->hit == 0)
            {
                if (game->sideDistX < game->sideDistY)
                {
                    game->sideDistX += deltaDistX;
                    game->mapX += game->stepX;
                    game->side = 0;
                }
                else
                {
                    game->sideDistY += deltaDistY;
                    game->mapY += game->stepY;
                    game->side = 1;
                }

                if (data->map->map_tab[game->mapX][game->mapY] == '1')
                    game->hit = 1;
            }
    
            /* Calculate the distance of the rayon from the cam position in the cam direction*/
            if (game->side == 0)
                game->perpWallDist = game->sideDistX - deltaDistX;
            else
                game->perpWallDist = game->sideDistY - deltaDistY;

            /* Calcul height of line to draw colone wall */
            game->lineHeight = RES_Y / game->perpWallDist;
            
            /* */
            game->drawStart = -game->lineHeight / 2 + RES_Y / 2 + game->headView;
            
            if (game->drawStart < 0)
                game->drawStart = 0;
            game->drawEnd = game->lineHeight / 2 + RES_Y / 2 + game->headView;

            /* Select the good texture (NORTH/SOUTH/EAST/WEST)*/
            if (game->side == 0)
            {
                if (game->rayDir_x > 0)
                    textNum = 0;
                else
                    textNum = 1;
            }
            else
            {
                if (game->rayDir_y > 0)
                    textNum = 2;
                else
                    textNum = 3;
            }
            /* TEST TEXTURING */
            if (game->side == 0)
            {
                wallX = player->y + game->perpWallDist * game->rayDir_y;
            }
            else
            {
                wallX = player->x + game->perpWallDist * game->rayDir_x;
            }
            wallX -= floor(wallX);
            texX = (int)(wallX * (double)(TEXT_SIZE));
            if (game->side == 0 && game->rayDir_x > 0)
            {
                texX = TEXT_SIZE - texX -1;
            }
            if ( game->side == 1 && game->rayDir_y < 0)
            {
                texX = TEXT_SIZE - texX -1;
            }
            
            step = 1.0 * TEXT_SIZE / game->lineHeight;
            texPos = (game->drawStart - RES_Y / 2 + game->lineHeight / 2 - game->headView) * step;
            
            i = game->drawStart;
            if (game->drawEnd >= RES_Y)
                game->drawEnd = RES_Y - 1;
            while (i < game->drawEnd)
            {
                texY = (int)texPos & (TEXT_SIZE - 1);
                texPos += step;
                color = get_pixel(data->map->textdata->img[textNum], texX, texY);
                if (game->side == 1)
                    color = (color >> 1) & 8355711;
                if ((i < 256 && x < 256 && is_minimap_status(data, x, i) == 0 ) || (i >= 256 || x >= 256))
                    pixels_to_image(data->mlx->img, x, i, color);
                i++;
            }             
            draw_ceiling(data, game, x, 0x21c6e5);
            draw_floor(data, game, x, 0x6aa84f);
            x++;
        }
        mlx_put_image_to_window(data->mlx->ptr, data->mlx->win, data->mlx->img->ptr, 0, 0);
        game->oldTime = game->time;
        game->time = get_time();
        frameTime = (game->time - game->oldTime) / 1000.0;
        /* Temporaire */
        char fpsbuffer[32];
        sprintf(fpsbuffer, "FPS %F", 1.0/frameTime);
        mlx_string_put(data->mlx->ptr, data->mlx->win, 500, 20, 0x000000, fpsbuffer);
        //printf("%s\n", fpsbuffer);
        game->moveSpeed = frameTime * 8.0;
        game->rotSpeed = frameTime * 3.0;
        break;
    }
}

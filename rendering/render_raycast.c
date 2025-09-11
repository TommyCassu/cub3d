/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:48:32 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/11 02:59:30 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    clear_img(t_img *img)
{
    int y;
    int x;

    y = 0;
    while (y < RES_Y)
    {
        x = 0;
        while (x < RES_X)
        {
            pixels_to_image(img, x, y, 0x000000);
            x++;
        }
        y++;
    }
}
void    draw_ceiling(t_data *data, t_game *game, int x, int color)
{
    int i;

    i = 0;
    
    while (i < game->drawStart)
    {
        pixels_to_image(data->mlx->img, x, i, color);
        i++;
    }
    
}
void    draw_floor(t_data *data, t_game *game, int x, int color)
{
    int i;

    i = game->drawEnd;
    
    while (i < RES_Y)
    {
        pixels_to_image(data->mlx->img, x, i, color);
        i++;
    }
    
}
void    draw_verline(t_data *data, t_game *game, int x, int color)
{
    int i;

    i = game->drawStart;
    
    while (i < game->drawEnd)
    {
        pixels_to_image(data->mlx->img, x, i, color);
        i++;
    }
    
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

int    key_handler(int key, t_data *data)
{
    double oldDirX;
    double oldPlaneX;

    if ((key == XK_w || key == XK_Up))
    {
        printf("up\n");
        if (data->map->map_tab[(int)(data->map->player->x + data->map->player->dirX * data->game->moveSpeed)][(int)data->map->player->y] == '0')
            data->map->player->x += data->map->player->dirX * data->game->moveSpeed;
        if (data->map->map_tab[(int)data->map->player->x][(int)(data->map->player->y + data->map->player->dirY * data->game->moveSpeed)] == '0')
            data->map->player->y += data->map->player->dirY * data->game->moveSpeed;
    }
    if ((key == XK_s || key == XK_Down))
    {
        if (data->map->map_tab[(int)(data->map->player->x - data->map->player->dirX * data->game->moveSpeed)][(int)data->map->player->y] == '0')
            data->map->player->x -= data->map->player->dirX * data->game->moveSpeed;
        if (data->map->map_tab[(int)data->map->player->x][(int)(data->map->player->y - data->map->player->dirY * data->game->moveSpeed)] == '0')
            data->map->player->y -= data->map->player->dirY * data->game->moveSpeed;
    }
    if ((key == XK_d || key == XK_Right))
    {
        printf("droite\n");
        oldDirX = data->map->player->dirX;
        data->map->player->dirX = data->map->player->dirX * cos(-data->game->rotSpeed) - data->map->player->dirY * sin(-data->game->rotSpeed);
        data->map->player->dirY = oldDirX * sin(-data->game->rotSpeed) + data->map->player->dirY * cos(-data->game->rotSpeed);
        oldPlaneX = data->game->planeX;
        data->game->planeX = data->game->planeX * cos(-data->game->rotSpeed) - data->game->planeY * sin(-data->game->rotSpeed);
        data->game->planeY = oldPlaneX * sin(-data->game->rotSpeed) + data->game->planeY * cos(-data->game->rotSpeed);
    }
    if ((key == XK_a || key == XK_Left))
    {
        oldDirX = data->map->player->dirX;
        data->map->player->dirX = data->map->player->dirX * cos(data->game->rotSpeed) - data->map->player->dirY * sin(data->game->rotSpeed);
        data->map->player->dirY = oldDirX * sin(data->game->rotSpeed) + data->map->player->dirY * cos(data->game->rotSpeed);
        oldPlaneX = data->game->planeX;
        data->game->planeX = data->game->planeX * cos(data->game->rotSpeed) - data->game->planeY * sin(data->game->rotSpeed);
        data->game->planeY = oldPlaneX * sin(data->game->rotSpeed) + data->game->planeY * cos(data->game->rotSpeed);
    }
    return (0);
}

void    render_raycast(t_data *data, t_game *game, t_player *player)
{
    int x;
    double deltaDistX;
    double deltaDistY;
    int color;
    double  frameTime;
    
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
                //printf("[%c]\n", data->map->map_tab[game->mapX][game->mapY]);
                if (data->map->map_tab[game->mapX][game->mapY] == '1')
                    game->hit = 1;
            }
    
            /* Calculate the distance of the rayon from the cam position in the cam direction*/
            if (game->side == 0)
                game->perpWallDist = game->sideDistX - deltaDistX;
            else
                game->perpWallDist = game->sideDistY - deltaDistY;
             //printf("%F oooo %F ---- %F\n", game->perpWallDist, game->sideDistX, deltaDistY);
            /* Calcul height of line to draw colone wall */
            game->lineHeight = RES_Y / game->perpWallDist;
            
            /* */
            
            game->drawStart = -game->lineHeight / 2 + RES_Y / 2;
            
            if (game->drawStart < 0)
                game->drawStart = 0;
            game->drawEnd = game->lineHeight / 2 + RES_Y / 2;
            //asm("int $3");
            //printf("%d ======== %d ---- %d\n", game->lineHeight, game->drawStart, game->drawEnd);
            if (game->drawEnd >= RES_Y)
                game->drawEnd = RES_Y - 1;
            
            if (game->side == 0)
            {
                if (game->rayDir_x > 0)
                    color = 0xeeeeee;
                else
                    color = 0xeeeeee;
            }
            else
            {
                if (game->rayDir_y > 0)
                    color = 0xeeeeee / 2;
                else
                    color = 0xeeeeee / 2;
            }
            
            draw_verline(data, game, x, color);
            draw_ceiling(data, game, x, 0x21c6e5);
            draw_floor(data, game, x, 0x6aa84f);
            x++;
        }
        game->oldTime = game->time;
        game->time = get_time();
        frameTime = (game->time - game->oldTime) / 1000.0;
        /* temporaire (clear l'ancienne affichage, affiche celle actuelle, clear memoire de l'img pour la suivante)*/
        mlx_put_image_to_window(data->mlx->ptr, data->mlx->win, data->mlx->img->ptr, 0, 0);
        /* */

        game->moveSpeed = frameTime * 5.0;
        game->rotSpeed = frameTime * 3.0;
        break;
    }
}

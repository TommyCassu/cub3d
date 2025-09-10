/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:55:14 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/10 19:43:17 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
# include <X11/X.h>
# include <X11/keysym.h>


void    print_map(t_map *map)
{
    int    i;

    i = 0;
    while (i < map->height_map)
    {
        printf("%s\n", map->map_tab[i]);
        i++;
    }
    if (map->textdata->north)
        printf("%s\n", map->textdata->north);
    if (map->textdata->south)
        printf("%s\n", map->textdata->south);
}

int    main(int ac, char **av)
{
    t_data    *data;
    if (ac == 2)
    {
        data = malloc(sizeof(t_data));   
        init_data(data);
        init_mlx(data->mlx, data);
        init_raycast(data);
        read_data(data, av[1]);
        if (data->error_status == 1)
        {
            ft_free_cub3d(data);
            return (0);
        }
        write_map(data->map, av[1]);
        if (parsing(data))
        {
            print_map(data->map);
            //draw_map(data);
			//draw_player(data->mlx, data->map->player->x, data->map->player->y, 0xFF0000);
            
			mlx_hook(data->mlx->win, KeyPress, KeyPressMask, key_handler, data);
	        //mlx_put_image_to_window(data->mlx->ptr, data->mlx->win, data->mlx->img->ptr, 0, 0);
            render_raycast(data, data->game, data->map->player);
			mlx_loop(data->mlx->ptr);
        }

        ft_free_cub3d(data);
    }
    
    return (0);
}

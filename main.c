/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:55:14 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/11 14:04:47 by tcassu           ###   ########.fr       */
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
int    test_rend(t_data *data)
{
    render_raycast(data, data->game, data->map->player);
    mlx_put_image_to_window(data->mlx->ptr, data->mlx->win, data->mlx->img->ptr, 0, 0);
    return (0);
}
int    main(int ac, char **av)
{
    t_data    *data;
    int w;
    int h;

    h = 32;
    w = 32;
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
            data->map->textdata->img->ptr = mlx_xpm_file_to_image(data->mlx->ptr, data->map->textdata->north, &w, &h);
            data->map->textdata->img->addr = (int *)mlx_get_data_addr(data->map->textdata->img->ptr, &data->map->textdata->img->bpp, &data->map->textdata->img->line_s, &data->map->textdata->img->endian);
            mlx_loop_hook(data->mlx->ptr, test_rend, data);
            mlx_hook(data->mlx->win, KeyPress, KeyPressMask, key_handler, data);
			mlx_loop(data->mlx->ptr);
        }
        ft_free_cub3d(data);
    }
    
    return (0);
}

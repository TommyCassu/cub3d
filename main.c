/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:55:14 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/11 16:30:31 by tcassu           ###   ########.fr       */
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
    key_handler(data);
    render_raycast(data, data->game, data->map->player);
    
    return (0);
}

void    transpose_test(t_mlx *mlx, t_img *img, int w, int h)
{
    int bpp, sl, endian;
    char *src_data = mlx_get_data_addr(img->ptr, &bpp, &sl, &endian);
    void *img_dst = mlx_new_image(mlx->ptr, w, h);
    char *dst_data = mlx_get_data_addr(img_dst, &bpp, &sl, &endian);
    int x;
    int y;
    int i;
    int src_offset;
    int dst_offset;
    int bytes_per_pixel = bpp / 8;
    
    img_dst = malloc(sizeof(t_img));
    x = 0;
    
    while (x < w)
    {
        y = 0;
        while (y < h)
        {
            src_offset = y * sl + x * bytes_per_pixel;
            dst_offset = x * sl + y * bytes_per_pixel;
            i = 0;
            while (i < bytes_per_pixel)
            {
                dst_data[dst_offset + i] = src_data[src_offset + i];
                i++;
            }
            y++;
        }
        x++;
    }
    img = img_dst;
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
            //transpose_test(data->mlx, data->map->textdata->img,w , h);
            
            mlx_hook(data->mlx->win, KeyPress, KeyPressMask, key_press, data);
            mlx_hook(data->mlx->win, KeyRelease, KeyReleaseMask, key_release, data);
            mlx_loop_hook(data->mlx->ptr, test_rend, data);
			mlx_loop(data->mlx->ptr);
        }
        ft_free_cub3d(data);
    }
    
    return (0);
}

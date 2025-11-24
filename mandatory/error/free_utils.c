/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:08:42 by tcassu            #+#    #+#             */
/*   Updated: 2025/11/24 16:31:16 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height_map)
	{
		free(map->map_tab[i]);
		i++;
	}
	free(map->map_tab);
	free(map);
}

void	ft_free_map(t_data *data)
{
	if (data->map->textdata)
	{
		if (data->map->textdata->n)
			free(data->map->textdata->n);
		if (data->map->textdata->s)
			free(data->map->textdata->s);
		if (data->map->textdata->e)
			free(data->map->textdata->e);
		if (data->map->textdata->w)
			free(data->map->textdata->w);
		if (data->error_status == 0)
			ft_free_imgs(data);
		if (data->map->textdata->img[0])
			free(data->map->textdata->img[0]);
		if (data->map->textdata->img[1])
			free(data->map->textdata->img[1]);
		if (data->map->textdata->img[2])
			free(data->map->textdata->img[2]);
		if (data->map->textdata->img[3])
			free(data->map->textdata->img[3]);
		free(data->map->textdata);
	}
	if (data->map->player)
		free(data->map->player);
	free_map(data->map);
}

void	ft_free_imgs(t_data *data)
{
	if (data->map->textdata->img[0]->ptr)
		mlx_destroy_image(data->mlx->ptr, data->map->textdata->img[0]->ptr);
	if (data->map->textdata->img[1]->ptr)
		mlx_destroy_image(data->mlx->ptr, data->map->textdata->img[1]->ptr);
	if (data->map->textdata->img[2]->ptr)
		mlx_destroy_image(data->mlx->ptr, data->map->textdata->img[2]->ptr);
	if (data->map->textdata->img[3]->ptr)
		mlx_destroy_image(data->mlx->ptr, data->map->textdata->img[3]->ptr);
}

void	ft_free_mlx(t_data *data)
{
	if (data->mlx->img)
	{
		mlx_destroy_image(data->mlx->ptr, data->mlx->img->ptr);
		free(data->mlx->img);
	}
	if (data->mlx->win)
		mlx_destroy_window(data->mlx->ptr, data->mlx->win);
	mlx_destroy_display(data->mlx->ptr);
	free(data->mlx->ptr);
	free(data->mlx);
}

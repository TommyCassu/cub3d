/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:02:41 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/16 13:20:12 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void    draw_player(t_mlx *mlx, int px, int py, int color)
{
	int i, j;

	i = 0;
	while (i < 8) // carré de 8x8
	{
		j = 0;
		while (j < 8)
		{
			//pixels_to_image(mlx->img, px + j, py + i, color);
			j++;
		}
		i++;
	}
}

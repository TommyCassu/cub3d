/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:44:41 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/10 19:31:49 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    init_raycast(t_data *data)
{
    data->game = malloc(sizeof(t_game));
    ft_memset(data->game, 0, sizeof(t_game));
    data->game->cameraX = 0;
    data->game->planeX = 0;
    data->game->planeY = 0.66;
}
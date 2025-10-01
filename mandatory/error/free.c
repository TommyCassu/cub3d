/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:42:08 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/27 01:09:51 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_exit(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_free_cub3d(data);
	exit(0);
}

void	ft_free_cub3d(t_data *data)
{
	if (!data)
		return ;
	if (data->map)
		ft_free_map(data);
	if (data->game)
		free(data->game);
	if (data->mlx)
		ft_free_mlx(data);
	free(data);
}

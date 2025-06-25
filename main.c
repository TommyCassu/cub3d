/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:55:14 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/25 23:06:39 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
int	error_msg(char	*msg)
{
	printf("%s\n", msg);
	//free data
	return (1);
}
*/

void	init_data(t_data *data)
{
	data->map = malloc(sizeof(t_map));
	data->map->textdata = malloc(sizeof(t_textdata));
	data->map->floor = NULL;
	data->map->ceilling = NULL;
	
}

int	main(int ac, char **av)
{
	t_data	*data;
	
	if (ac == 2)
	{
		data = malloc(sizeof(t_data));
		init_data(data);
		read_data(data, av[1]);
	}
	return (0);
}
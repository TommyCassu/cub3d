/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:55:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/25 23:00:26 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include "libft/libft.h"
# include <stdio.h>

typedef struct	s_textdata
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textdata;

typedef struct	s_map
{
	int	**map_tab;
	t_textdata	*textdata;
	char	*floor;
	char	*ceilling;
}	t_map;

typedef struct	s_data
{
	t_map	*map;
}	t_data;

/* Parsing */
void    read_data(t_data *data,  char *filename);

#endif
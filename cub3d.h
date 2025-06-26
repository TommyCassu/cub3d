/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:55:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/27 01:04:25 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include "libft/libft.h"
# include <stdio.h>

typedef struct s_textdata
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textdata;

typedef struct s_map
{
	char		**map_tab;
	t_textdata	*textdata;
	char		*floor;
	char		*ceilling;
	int			height_map;
	int			width_map;
}	t_map;

typedef struct s_data
{
	t_map	*map;
}	t_data;

/* Parsing */
void	read_data(t_data *data,  char *filename);
void	read_map(t_map *map, char *line);
int		is_map_line(char *line);
void	write_map(t_map *map, char	*filename);

#endif
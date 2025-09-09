/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:55:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/09 18:31:37 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <stdio.h>

typedef struct s_textdata
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textdata;

typedef struct s_img
{
	void		*ptr;
	int			*addr;
	int			line_s;
	int			bpp;
	int			endian;
}				t_img;

typedef struct s_player
{
	int x;
	int y;
	int	start_x;
	int	start_y;
}			t_player;

typedef struct s_map
{
	char		**map_tab;
	t_player	*player;
	t_textdata	*textdata;
	int			floor_rgb;
	int			ceilling_rgb;
	int			height_map;
	int			width_map;
}	t_map;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
	t_img		*img;
}				t_mlx;

typedef struct s_data
{
	t_map	*map;
	t_mlx	*mlx;
	int		error_status;
}	t_data;

/* initialisation */
void	init_data(t_data *data);
void	init_mlx(t_mlx *mlx, t_data *data);

/* Parsing */
void	read_data(t_data *data, char *filename);
void	read_map(t_map *map, char *line);
int		is_map_line(char *line);
void	write_map(t_map *map, char	*filename);
int		parsing(t_data *data);
void	ft_free(char **result);
void	parsing_rgb(t_data *data, char *line, char *direction);
int		parsing_map(t_map	*map);
void	print_map(t_map *map);

/* draw map */
void    draw_map(t_data *data);
/* Free / error*/
void	ft_free_cub3d(t_data *data);
//minimap
void    pixels_to_image(t_img *image, int x, int y, int pixcolor);


//player
void	draw_player(t_mlx *mlx, int px, int py, int color);
int		handler_player(int key, void *param);
void	move_player(t_data *data, char key);



#endif
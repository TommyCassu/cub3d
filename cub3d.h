/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:55:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/23 15:48:36 by npederen         ###   ########.fr       */
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
# include <math.h>
#	include <stdio.h>          
#	include <stdlib.h>
# include <sys/time.h>

# define RES_X 1920
# define RES_Y 1080
# define RES_MMAP_X 256
# define RES_MMAP_Y 256
# define key_Up 1
# define key_Down 2
# define key_Left 3
# define key_Right 4
# define key_W 5
# define key_S 6
# define key_A 7
# define key_D 8
# define key_Jump 9
# define TEXT_SIZE 128

typedef struct s_img
{
	void		*ptr;
	int			*addr;
	int			line_s;
	int			bpp;
	int			endian;
}				t_img;

typedef struct s_textdata
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	t_img	*img[5];
}	t_textdata;



typedef struct s_player
{
	double x;
	double y;
	double	start_x;
	double	start_y;
	double dirX;
	double dirY;
	int isjumping;
	double jumpspeed;
	double jumpoffset;
}			t_player;

typedef struct s_game
{
	double time; //time of current frame
	double oldTime; //time of previous frame
	double planeX; 
	double planeY;
	double rayDir_x;
	double rayDir_y;
	double cameraX;
	double moveSpeed;
	double rotSpeed;
	int mapY;
	int mapX;
	double sideDistY;
    double sideDistX;
    double perpWallDist;
	int stepX;
    int stepY;
	int hit;
    int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
	int	headView;
	int	keyTab[32];
	t_img	*img_miniMap;
	t_img	*img_miniMap_contour;
	int		tab_contour[256][256];
}	t_game;

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
	t_game	*game;
	int		error_status;
}	t_data;

/* initialisation */
void	init_data(t_data *data);
void	init_mlx(t_mlx *mlx, t_data *data);
void	init_raycast(t_data *data);
void    setup_text_img(t_data *data);


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
void    draw_miniMap(t_data *data);
/* Free / error*/
void	ft_free_cub3d(t_data *data);
/* Minimap */
void    draw_miniMap(t_data *data);
void    setup_minimap(t_data *data);

/* --- Player --- */
	/* Movement */
	/* Key events */
int     key_press(int key, t_data *data);
int     key_release(int key, t_data *data);
int		key_handler(t_data *data);

/* --- Rendering --- */
	/* render_raycast */
void    render_raycast(t_data *data, t_game *game, t_player *player);
	/* drawing_func */
void    draw_ceiling(t_data *data, t_game *game, int x, int color);
void    draw_floor(t_data *data, t_game *game);
void    pixels_to_image(t_data *data, int x, int y, int pixcolor);
	/* Utils_raycasting */
int		get_pixel(t_img *image, int x, int y);
long	get_time(void);

void	init_tab_contour(t_data *data);
int		is_minimap_status(t_data *data, int x, int y);
void	write_contour_minimap(t_data *data);

void    transpose_test(t_mlx *mlx, t_img *img, int w, int h);
#endif
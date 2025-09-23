/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:55:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/09/23 23:03:39 by npederen         ###   ########.fr       */
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
	char	*n;
	char	*s;
	char	*w;
	char	*e;
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
	double deltaDistY;
	double deltaDistX;
	int textNum;
	int texX;
	int texY;
	double texPos;
	double step;
	int stepX;
	int stepY;
	int hit;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
	int	headView;
	int	keyTab[32];
	double	ray_dir_x0;
	double	ray_dir_y0;
	double	ray_dir_x1;
	double	ray_dir_y1;
	double	pos_z;
	int		p;
	int		color;
	float	row_distance;
	double	floor_x;
	double	floor_y;
	double	floor_step_y;
	double	floor_step_x;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	int		jumpoffsetresy;
	t_img	*img_miniMap;
	t_img	*img_miniMap_contour;
	int		tab_contour[256][256];
	double frameTime;
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

/* --- error --- */
	/* free.c */
void	ft_free(char **result);
void	ft_free_cub3d(t_data *data);
/* --- initialisation --- */
	/* init_raycasting.c */
void	init_raycast(t_data *data);
void	setup_text_img(t_data *data, t_textdata *textdata);
	/* init.c */
void	init_tab_contour(t_data *data);
void	init_data(t_data *data);
void	init_mlx(t_mlx *mlx, t_data *data);
/* --- Parsing --- */
	/* parsing_map.c */
int		spawn_count_is_1(int spawn_count);
int		check_spawn(t_map *map, int height, int width);
int		is_map_closed(char **map, int height, int width);
int		parsing_map(t_map	*map);
	/* parsing_utils.c */
int		is_player(char c);
int		is_valid(char c);
int		ft_verif_digit(char	*str);
	/* parsing.c */
int		check_valid_file(char *line);
int		parsing_texture(t_textdata *textures);
void	attribute_rgb(t_data *data, char **tab_value, char *direction);
void	parsing_rgb(t_data *data, char *line, char *direction);
int		parsing(t_data *data);
/* --- Player --- */
	/* key_events.c */
int		key_press(int key, t_data *data);
int		key_release(int key, t_data *data);
int	key_handler(t_data *data, t_game *game, t_player *player, char **map_tab);
/* --- reading_data --- */
	/* read_data.c */
void	config_memory(t_data *data, char *line, char *direction);
int		add_data(t_data *data, char *line);
void	malloc_map(t_map *map);
void	read_data(t_data *data, char *filename);
	/* read_map.c */
int		is_map_line(char *line);
void	read_map(t_map *map, char *line);
void	write_line(t_map *map, char	*line, int *i);
void	write_map(t_map *map, char	*filename);
/* --- Rendering --- */
	/* drawing_func */
void	pixels_to_image(t_data *data, int x, int y, int pixcolor);
void	draw_ceiling(t_data *data, t_game *game, int x, int color);
void	init_floor_params(t_data *data, t_game *game, int y);
void	draw_floor(t_data *data, t_game *game, t_map* map);
	/* render_raycast */
void	init_ray(t_data *data, int x);
void	setup_angle_rayon(t_data *data);
void	dda_loop(t_data *data);
void	manage_draw_limits(t_data *data);
void	select_texture_side(t_game *game);
void	get_texture_pos(t_data *data);
void	draw_wall_col(t_data *data, int x);
void	show_fps(t_data *data);
void	render_raycast(t_data *data, t_game *game);
void	calcul_jump_offset(t_data *data);
	/* Utils_raycasting */
int		get_pixel(t_img *image, int x, int y);
long	get_time(void);
/* --- Minimap --- */
	/* contour_minimap.c */
int		is_minimap_status(t_data *data, int x, int y);
void	pixels_to_image_minimap_player(t_data *data, int x, int y, int pixcolor);
void	write_contour_minimap(t_data *data);
	/* drawing_onMinimap.c */
void	draw_player_minmap(t_data *data);
void	draw_cube_wall(t_data *data, int x, int y);
void	draw_cube_floor(t_data *data, int x, int y);
void	draw_cube_outside(t_data *data);
void	draw_mini_map(t_data *data);
/* --- Main.c --- */
void	print_map(t_map *map);
int		test_rend(t_data *data);
void	setup_minimap(t_data *data);

//void    transpose_test(t_mlx *mlx, t_img *img, int w, int h);
#endif